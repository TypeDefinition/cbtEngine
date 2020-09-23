#pragma once

// Include CBT
#include "cbtEvent.h"

// Include STD
#include <functional>

NS_CBT_BEGIN

/**
    \brief Used to subscribe to an cbtEventDispatcher to receive cbtEvent(s) from that cbtEventDispatcher. It is possible to subscribe to multiple EventDispatchers.
*/
class cbtEventListener
{
private:
    /// When a cbtEvent is received, the function assigned to m_Callback is invoked. The event will be passed to the function as a parameter.
    std::function<void(cbtEvent*)> m_Callback = nullptr;

public:
    /**
        \brief Default Constructor.

        \return A cbtEventListener
    */
    cbtEventListener() {}
    /**
        \brief Destructor.
    */
    ~cbtEventListener() {}

    /**
        \brief Sets a function to be called when an cbtEvent is received.
               Use CBT_CALLBACK_0, CBT_CALLBACK_1, CBT_CALLBACK_2 etc. to set a non-static member function as a callback.
               Learn more about CBT_CALLBACK in CBTMacros.h.
        
        \param _callback The callback function to invoke when an cbtEvent is received.

        \sa CBTMacros.h
    */
    void SetCallback(const std::function<void(cbtEvent*)>& _callback) { m_Callback = _callback; }

    /**
        \brief Used by cbtEventDispatcher to invoke the callback and pass the cbtEvent.
        
        \param _event The cbtEvent that is received.
    */
    void InvokeCallback(cbtEvent* _event) { if (m_Callback != nullptr) { m_Callback(_event); } }
};

NS_CBT_END