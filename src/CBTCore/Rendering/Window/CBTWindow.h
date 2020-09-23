#pragma once

// Include CBT
#include "cbtMacros.h"
#include "Core/Event/cbtEventDispatcher.h"
#include "cbtWindowProperties.h"

NS_CBT_BEGIN

class cbtWindow
{
protected:
    cbtWindowProperties m_Properties;
    cbtEventDispatcher m_EventDispatcher;

public:
    cbtWindow(const cbtWindowProperties& _properties) : m_Properties(_properties) {}
    virtual ~cbtWindow() {}

    inline const cbtWindowProperties& GetProperties() { return m_Properties; }
    const cbtEventDispatcher* GetEventDispatcher() const { return &m_EventDispatcher; }
    cbtEventDispatcher* GetEventDispatcher() { return &m_EventDispatcher; }

    virtual void Resize(cbtU32 _width, cbtU32 _height) = 0;
    virtual void SwapBuffers() = 0;

    // Cannot name this CreateWindow as it will clash with a Visual Studio Macro.
    static cbtWindow* CreateCBTWindow(const cbtWindowProperties& _properties);
};

NS_CBT_END