#pragma once

// Include CBT
#include "Core/General/cbtSingleton.h"
#include "Core/Event/cbtEventDispatcher.h"
#include "Input/cbtInputEvent.h"
#include "Input/Device/cbtKeyboardHandler.h"

// Include STD
#include <queue>
#include <functional>

NS_CBT_BEGIN

class cbtInputEngine : public cbtSingleton<cbtInputEngine>
{
    friend class cbtSingleton<cbtInputEngine>;

protected:
    cbtInputContext m_InputContext; ///< Current Input Context
    cbtEventDispatcher m_EventDispatcher;

    // Constructor(s) & Destructor
    cbtInputEngine() : m_InputContext(CBT_INPUT_CONTEXT_DEFAULT) {}
    virtual ~cbtInputEngine() {}

    static cbtInputEngine* CreateInstance();

public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Exit() = 0;

    virtual cbtKeyboardHandler* GetKeyboardHandler() = 0;
    virtual const cbtKeyboardHandler* GetKeyboardHandler() const = 0;

    cbtInputContext GetContext() { return m_InputContext; }
    void SetContext(cbtInputContext _context) { m_InputContext = _context; }

    const cbtEventDispatcher* GetEventDispatcher() const { return &m_EventDispatcher; }
    cbtEventDispatcher* GetEventDispatcher() { return &m_EventDispatcher; }
};

NS_CBT_END