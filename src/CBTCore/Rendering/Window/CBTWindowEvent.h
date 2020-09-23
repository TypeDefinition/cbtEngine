#pragma once

// Include CBT
#include "Core/Event/CBTEvent.h"
#include "CBTWindowProperties.h"

NS_CBT_BEGIN

class CBTWindowEvent : public CBTEvent
{
protected:
    CBTWindowEvent() {}

public:
    virtual ~CBTWindowEvent() {}
};

class CBTResizeWindowEvent : public CBTWindowEvent
{
public:
    const CBTWindowProperties m_Properties;

    CBTResizeWindowEvent(const CBTWindowProperties& _properties) : m_Properties(_properties) {}
    virtual ~CBTResizeWindowEvent() {}
};

NS_CBT_END