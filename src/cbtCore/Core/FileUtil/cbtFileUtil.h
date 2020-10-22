#pragma once

// Include CBT
#include "cbtMacros.h"

NS_CBT_BEGIN

/**
    \brief A file utility class.
*/
    class cbtFileUtil
    {
    private:
        /**
            \brief Private Constructor. All functions should be static. No objects of this class should be created.
        */
        cbtFileUtil()
        {
        }

        /**
            \brief Private Destructor. All functions should be static. No objects of this class should be created.
        */
        ~cbtFileUtil()
        {
        }

    public:
        /**
            \brief Opens a file and reads it into a cbtStr.

            \param _filePath The file path of the file to open and read.

            \return A cbtStr containing the contents of the file specified by _filePath.

            \sa StringToFile(const cbtStr& _filePath, const cbtStr& _string)
        */
        static cbtStr FileToString(const cbtStr& _filePath);

        /**
            \brief Opens a file and write the contents of _string to it. If the file does not exist, it is created.

            \param _filePath The file path of the file to open and write.
            \param _string The contents to write to the file specified by _filePath.

            \sa FileToString(const cbtStr& _filePath)
        */
        static void StringToFile(const cbtStr& _filePath, const cbtStr& _string);
    };

NS_CBT_END