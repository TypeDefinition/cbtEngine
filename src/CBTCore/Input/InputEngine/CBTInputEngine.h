#pragma once

// Include CBT
#include "Core/General/CBTSingleton.h"
#include "Core/Event/CBTEventDispatcher.h"
#include "Input/CBTInputEvent.h"
#include "Input/Device/CBTKeyboardHandler.h"

// Include STD
#include <queue>
#include <functional>

NS_CBT_BEGIN

class CBTInputEngine : public CBTSingleton<CBTInputEngine>
{
    friend class CBTSingleton<CBTInputEngine>;

protected:
    CBTInputContext m_InputContext; ///< Current Input Context
    CBTEventDispatcher m_EventDispatcher;

    // Constructor(s) & Destructor
    CBTInputEngine() : m_InputContext(CBT_INPUT_CONTEXT_DEFAULT) {}
    virtual ~CBTInputEngine() {}

    static CBTInputEngine* CreateInstance();

public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Exit() = 0;

    virtual CBTKeyboardHandler* GetKeyboardHandler() = 0;
    virtual const CBTKeyboardHandler* GetKeyboardHandler() const = 0;

    CBTInputContext GetContext() { return m_InputContext; }
    void SetContext(CBTInputContext _context) { m_InputContext = _context; }

    const CBTEventDispatcher* GetEventDispatcher() const { return &m_EventDispatcher; }
    CBTEventDispatcher* GetEventDispatcher() { return &m_EventDispatcher; }
};

NS_CBT_END