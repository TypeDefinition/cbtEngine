#pragma once

// Include CBT
#include "cbtMacros.h"
#include "Debug/cbtDebug.h"

// Include STD
#include <mutex>

NS_CBT_BEGIN

/**
    \brief A queue of function pointers (commands) to be executed.
*/
    class cbtCommandQueue
    {
    private:
        typedef std::function<void(void)> CommandFunc;

        /// The size of the buffer.
        static constexpr cbtU32 COMMAND_BUFFER_SIZE = 10485760; // 10MB
        /// The maximum number of commands that can be queued.
        static constexpr cbtU32 s_MaxCommands = COMMAND_BUFFER_SIZE / sizeof(CommandFunc);
        /// The buffer to store the commands. It is split into 2 sections, a section to queue the commands and a section to execute the commands.
        cbtByte m_Buffer[COMMAND_BUFFER_SIZE * 2];
        /// A pointer to the start of the command queue.
        cbtByte* m_QueueBuffer;
        /// A pointer to the commands to be executed.
        cbtByte* m_ExecuteBuffer;

        /// A mutex for the queuing of commands.
        std::mutex m_QueueBufferMutex;
        /// A mutex for the executing of commands.
        std::mutex m_ExecuteBufferMutex;

    public:
        /**
            \brief Constructor

            \return A cbtCommandQueue.
        */
        cbtCommandQueue()
        {
            // Create a 20MB buffer. Allocate 10MB to m_ExecuteBuffer and 10MB to m_QueueBuffer.
            // The first 4 bytes of the buffer is used to store the number of commands stored in the buffer.
            m_ExecuteBuffer = m_Buffer;
            m_QueueBuffer = m_ExecuteBuffer + COMMAND_BUFFER_SIZE;
            std::memset(m_Buffer, 0, COMMAND_BUFFER_SIZE * 2);
        }

        /**
            \brief Destructor
        */
        ~cbtCommandQueue()
        {
            std::lock_guard<std::mutex> executeLock(m_ExecuteBufferMutex);
            std::lock_guard<std::mutex> queueLock(m_QueueBufferMutex);
        }

        /**
            \brief Adds a command to the queue.

            \param _commandFunc The command to add to the queue.

            \sa ExecuteCommmands()
        */
        void QueueCommand(CommandFunc _commandFunc)
        {
            std::lock_guard<std::mutex> queueLock(m_QueueBufferMutex);

            // The first 4 bytes in the buffer is used to store commandCount.
            void* commandCountPtr = m_QueueBuffer; // Convert m_QueueBuffer to a void pointer.
            cbtU32 commandCount = *static_cast<cbtU32*>(commandCountPtr); // Get the current number of commands queued.

            // Check if the max number of commands has already been reached.
            if (commandCount == s_MaxCommands)
            {
                CBT_LOG_WARN(CBT_LOG_CATEGORY_APPLICATION, "Insufficient Buffer Size In Command Queue!");
                CBT_ASSERT(false);
            }

            // Get the position to insert the new command.
            void* bufferPointer = m_QueueBuffer;
            bufferPointer =
                    static_cast<cbtByte*>(bufferPointer) + (sizeof(cbtU32) + sizeof(CommandFunc) * commandCount);
            *static_cast<CommandFunc*>(bufferPointer) = _commandFunc;

            // Add one to the commandCount.
            ++(*static_cast<cbtU32*>(commandCountPtr));
        }

        /**
            \brief
                Execute the queued commands.
                When this function is called, the current queue buffer becomes the execute buffer and the current execute buffer becomes the queue buffer.
                Having 2 buffers allows commands to be queued safely while ExecuteCommmands() is running. This is useful especially if the commands executed by
                ExecuteCommmands() called QueueCommand(CommandFunc _commandFunc).

            \sa QueueCommand(CommandFunc _commandFunc)
        */
        void ExecuteCommmands()
        {
            std::lock_guard<std::mutex> executeLock(m_ExecuteBufferMutex);
            std::unique_lock<std::mutex> queueLock(m_QueueBufferMutex);

            // Swap the execute and queue buffers.
            cbtByte* tempBufferPtr = m_ExecuteBuffer;
            m_ExecuteBuffer = m_QueueBuffer;
            m_QueueBuffer = tempBufferPtr;
            std::memset(m_QueueBuffer, 0, COMMAND_BUFFER_SIZE);

            queueLock.unlock();

            // The first 4 bytes in the buffer is used to store commandCount.
            void* commandCountPtr = m_ExecuteBuffer; // Convert m_ExecuteBuffer to a void pointer.
            cbtU32 commandCount = *static_cast<cbtU32*>(commandCountPtr); // Get the current number of commands queued.

            // Convert m_QueueBuffer to a void pointer.
            void* bufferPointer = m_ExecuteBuffer;
            // Get the position to insert the new command.
            bufferPointer = static_cast<cbtByte*>(bufferPointer) + sizeof(cbtU32);

            for (cbtU32 i = 0; i < commandCount; ++i)
            {
                (*static_cast<CommandFunc*>(bufferPointer))();
                bufferPointer = static_cast<cbtByte*>(bufferPointer) + sizeof(CommandFunc);
            }
        }
    };

NS_CBT_END