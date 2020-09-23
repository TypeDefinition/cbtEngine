#pragma once

// Include CBT
#include "CBTEvent.h"

// Include STD
#include <functional>

NS_CBT_BEGIN

/**
    \brief Used to subscribe to an EventDispatcher to receive Event(s) from that EventDispatcher. It is possible to subscribe to multiple EventDispatchers.
*/
class CBTEventListener
{
private:
    /// When a Event is received, the function assigned to m_Callback is invoked. The event will be passed to the function as a parameter.
    std::function<void(CBTEvent*)> m_Callback = nullptr;

public:
    /**
        \brief Default Constructor.

        \return A CBTEventListener
    */
    CBTEventListener() {}
    /**
        \brief Destructor.
    */
    ~CBTEventListener() {}

    /**
        \brief Sets a function to be called when an Event is received.
               Use CBT_CALLBACK_0, CBT_CALLBACK_1, CBT_CALLBACK_2 etc. to set a non-static member function as a callback.
               Learn more about CBT_CALLBACK in CBTMacros.h.
        
        \param _callback The callback function to invoke when an Event is received.

        \sa CBTMacros.h
    */
    void SetCallback(const std::function<void(CBTEvent*)>& _callback) { m_Callback = _callback; }

    /**
        \brief Used by EventDispatcher to invoke the callback and pass the Event.
        
        \param _event The Event that is received.
    */
    void InvokeCallback(CBTEvent* _event) { if (m_Callback != nullptr) { m_Callback(_event); } }
};

NS_CBT_END