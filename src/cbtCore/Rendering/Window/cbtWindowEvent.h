#pragma once

// Include CBT
#include "Core/Event/cbtEvent.h"
#include "cbtWindowProperties.h"

NS_CBT_BEGIN

    class cbtWindowEvent : public cbtEvent
    {
    protected:
        cbtWindowEvent()
        {
        }

    public:
        virtual ~cbtWindowEvent()
        {
        }
    };

    class cbtResizeWindowEvent : public cbtWindowEvent
    {
    public:
        const cbtWindowProperties m_Properties;

        cbtResizeWindowEvent(const cbtWindowProperties& _properties)
                :m_Properties(_properties)
        {
        }

        virtual ~cbtResizeWindowEvent()
        {
        }
    };

NS_CBT_END