#pragma once

// Include CBT
#include "cbtMacros.h"

NS_CBT_BEGIN

/**
    \brief 
        cbtEvent(s) contain data that is dispatched by an cbtEventDispatcher,
        and is received by an cbtEventListener that is subscribed to the cbtEventDispatcher.
        Create new cbtEvent types by inheriting from cbtEvent.
 
        Example cbtEvent(s): InputEvent, AxisEvent, ButtonEvent, ClickEvent
*/
class cbtEvent
{
private:
    /// A flag to state if the event has already been handled.
    cbtBool m_Handled = false;

public:
    /** 
        \brief Default Constructor.

        \return A new cbtEvent.
    */
    cbtEvent() {}
    /**
        \brief Virtual Destructor.
    */
    virtual ~cbtEvent() {}

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