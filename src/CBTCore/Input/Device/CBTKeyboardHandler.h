#pragma once

// Include CBT
#include "Input/CBTInput.h"
#include "Input/CBTInputEvent.h"
#include "Core/Event/CBTEventDispatcher.h"

// Include STD
#include <bitset>
#include <unordered_map>

NS_CBT_BEGIN

class CBTKeyboardHandler
{
protected:
    std::bitset<CBT_MAX_INPUT_NAME> m_PreviousInputState;
    std::bitset<CBT_MAX_INPUT_NAME> m_CurrentInputState;

    std::unordered_map<CBTInputMask, std::bitset<CBT_MAX_INPUT_NAME>> m_RegisteredInputs;

public:
    // Constructor(s) & Destructor
    CBTKeyboardHandler();
    virtual ~CBTKeyboardHandler();

    // Input Registration
    void RegisterButton(CBTInputMask _mask, CBTInputName _inputName);
    void UnregisterButton(CBTInputMask _mask, CBTInputName _inputName);

    // Events
    void OnKeyPress(CBTInputContext _context, CBTKeycode _keycode);
    void OnKeyRelease(CBTInputContext _context, CBTKeycode _keycode);
    void DispatchEvents(CBTEventDispatcher& _dispatcher);
};

NS_CBT_END