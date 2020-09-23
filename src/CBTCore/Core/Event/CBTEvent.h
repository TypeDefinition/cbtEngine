#pragma once

// Include CBT
#include "CBTMacros.h"

NS_CBT_BEGIN

/**
    \brief 
        Event(s) contain data that is dispatched by an EventDispatcher,
        and is received by an EventListener that is subscribed to the EventDispatcher.
        Create new Event types by inheriting from Event.
 
        Example Event(s): InputEvent, AxisEvent, ButtonEvent, ClickEvent
*/
class CBTEvent
{
private:
    /// A flag to state if the event has already been handled.
    cbtBool m_Handled = false;

public:
    /** 
        \brief Default Constructor.

        \return A new CBTEvent.
    */
    CBTEvent() {}
    /**
        \brief Virtual Destructor.
    */
    virtual ~CBTEvent() {}

    /**
        \brief Returns true if the event has been handled, false if it has not.

        \return Returns true if the event has been handled, false if it has not.
    */
    cbtBool IsHandled() const { return m_Handled; }
    /**
        \brief Sets the handled flag of the event to true.
    */
    void SetHandled() { m_Handled = true; }
};

NS_CBT_END