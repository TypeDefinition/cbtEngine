#pragma once

// Include CBT
#include "CBTMacros.h"
#include "Core/Event/CBTEventDispatcher.h"
#include "CBTWindowProperties.h"

NS_CBT_BEGIN

class CBTWindow
{
protected:
    CBTWindowProperties m_Properties;
    CBTEventDispatcher m_EventDispatcher;

public:
    CBTWindow(const CBTWindowProperties& _properties) : m_Properties(_properties) {}
    virtual ~CBTWindow() {}

    inline const CBTWindowProperties& GetProperties() { return m_Properties; }
    const CBTEventDispatcher* GetEventDispatcher() const { return &m_EventDispatcher; }
    CBTEventDispatcher* GetEventDispatcher() { return &m_EventDispatcher; }

    virtual void Resize(cbtU32 _width, cbtU32 _height) = 0;
    virtual void SwapBuffers() = 0;

    // Cannot name this CreateWindow as it will clash with a Visual Studio Macro.
    static CBTWindow* CreateCBTWindow(const CBTWindowProperties& _properties);
};

NS_CBT_END