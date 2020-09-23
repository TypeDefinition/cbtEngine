// Include CBT
#include "CBTKeyboardHandler.h"

NS_CBT_BEGIN

// Constructor(s) & Destructor
CBTKeyboardHandler::CBTKeyboardHandler()
{
    m_PreviousInputState.reset();
    m_CurrentInputState.reset();
}

CBTKeyboardHandler::~CBTKeyboardHandler() {}

// Input Registration
void CBTKeyboardHandler::RegisterButton(CBTInputMask _mask, CBTInputName _inputName)
{
    std::unordered_map<CBTInputMask, std::bitset<CBT_MAX_INPUT_NAME>>::iterator iter = m_RegisteredInputs.find(_mask);
    if (iter == m_RegisteredInputs.end())
    {
        m_RegisteredInputs.insert(std::pair<CBTInputMask, std::bitset<CBT_MAX_INPUT_NAME>>(_mask, std::bitset<CBT_MAX_INPUT_NAME>()));
        iter = m_RegisteredInputs.find(_mask);
    }

    iter->second[_inputName] = 1;
}

void CBTKeyboardHandler::UnregisterButton(CBTInputMask _mask, CBTInputName _inputName)
{
    std::unordered_map<CBTInputMask, std::bitset<CBT_MAX_INPUT_NAME>>::iterator iter = m_RegisteredInputs.find(_mask);
    if (iter == m_RegisteredInputs.end()) { return; }

    iter->second[_inputName] = 0;
    if (iter->second.none()) { m_RegisteredInputs.erase(iter); }
}

// Keyboard Events
void CBTKeyboardHandler::OnKeyPress(CBTInputContext _context, CBTKeycode _keycode)
{
    // Keyboard is always treated as controller 1.
    CBTInputMask mask = CBTInput::GenerateInputMask(_context, CBT_CONTROLLER_1, _keycode);

    for (std::unordered_map<CBTInputMask, std::bitset<CBT_MAX_INPUT_NAME>>::const_iterator iter = m_RegisteredInputs.begin(); iter != m_RegisteredInputs.end(); ++iter)
    {
        if (!CBTInput::CompareMask(mask, iter->first)) { continue; }
        m_CurrentInputState |= iter->second;
    }
}

void CBTKeyboardHandler::OnKeyRelease(CBTInputContext _context, CBTKeycode _keycode)
{
    // Keyboard is always treated as controller 1.
    CBTInputMask mask = CBTInput::GenerateInputMask(_context, CBT_CONTROLLER_1, _keycode);

    for (std::unordered_map<CBTInputMask, std::bitset<CBT_MAX_INPUT_NAME>>::const_iterator iter = m_RegisteredInputs.begin(); iter != m_RegisteredInputs.end(); ++iter)
    {
        if (!CBTInput::CompareMask(mask, iter->first)) { continue; }
        m_CurrentInputState = (m_CurrentInputState & ~iter->second);
    }
}

void CBTKeyboardHandler::DispatchEvents(CBTEventDispatcher& _dispatcher)
{
    for (cbtU32 i = 0; i < CBT_MAX_INPUT_NAME; ++i)
    {
        // Button Press
        if (m_CurrentInputState[i] & ~m_PreviousInputState[i])
        {
            // Send both a press and a hold event.
            _dispatcher.DispatchEvent<CBTInputEvent>(new CBTButtonEvent(static_cast<CBTInputName>(i), CBTButtonEvent::PRESS));
            _dispatcher.DispatchEvent<CBTInputEvent>(new CBTButtonEvent(static_cast<CBTInputName>(i), CBTButtonEvent::HOLD));
        }
        // Button Hold
        else if (m_CurrentInputState[i] & m_PreviousInputState[i])
        {
            _dispatcher.DispatchEvent<CBTInputEvent>(new CBTButtonEvent(static_cast<CBTInputName>(i), CBTButtonEvent::HOLD));
        }
        // Button Release
        else if (~m_CurrentInputState[i] & m_PreviousInputState[i])
        {
            _dispatcher.DispatchEvent<CBTInputEvent>(new CBTButtonEvent(static_cast<CBTInputName>(i), CBTButtonEvent::RELEASE));
        }
    }

    // Update Button States
    m_PreviousInputState = m_CurrentInputState;
}

NS_CBT_END