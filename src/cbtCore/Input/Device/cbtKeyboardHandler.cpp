// Include CBT
#include "cbtKeyboardHandler.h"

NS_CBT_BEGIN

// Constructor(s) & Destructor
    cbtKeyboardHandler::cbtKeyboardHandler()
    {
        m_PreviousInputState.reset();
        m_CurrentInputState.reset();
    }

    cbtKeyboardHandler::~cbtKeyboardHandler()
    {
    }

// Input Registration
    void cbtKeyboardHandler::RegisterButton(cbtInputMask _mask, cbtInputName _inputName)
    {
        std::unordered_map<cbtInputMask, std::bitset<CBT_MAX_INPUT_NAME>>::iterator iter = m_RegisteredInputs.find(
                _mask);
        if (iter == m_RegisteredInputs.end())
        {
            m_RegisteredInputs.insert(
                    std::pair<cbtInputMask, std::bitset<CBT_MAX_INPUT_NAME>>(_mask, std::bitset<CBT_MAX_INPUT_NAME>()));
            iter = m_RegisteredInputs.find(_mask);
        }

        iter->second[_inputName] = 1;
    }

    void cbtKeyboardHandler::UnregisterButton(cbtInputMask _mask, cbtInputName _inputName)
    {
        std::unordered_map<cbtInputMask, std::bitset<CBT_MAX_INPUT_NAME>>::iterator iter = m_RegisteredInputs.find(
                _mask);
        if (iter == m_RegisteredInputs.end())
        { return; }

        iter->second[_inputName] = 0;
        if (iter->second.none())
        { m_RegisteredInputs.erase(iter); }
    }

// Keyboard Events
    void cbtKeyboardHandler::OnKeyPress(cbtInputContext _context, cbtKeycode _keycode)
    {
        // Keyboard is always treated as controller 1.
        cbtInputMask mask = cbtInput::GenerateInputMask(_context, CBT_CONTROLLER_1, _keycode);

        for (std::unordered_map<cbtInputMask,
                                std::bitset<CBT_MAX_INPUT_NAME>>::const_iterator iter = m_RegisteredInputs.begin();
             iter != m_RegisteredInputs.end(); ++iter)
        {
            if (!cbtInput::CompareMask(mask, iter->first))
            { continue; }
            m_CurrentInputState |= iter->second;
        }
    }

    void cbtKeyboardHandler::OnKeyRelease(cbtInputContext _context, cbtKeycode _keycode)
    {
        // Keyboard is always treated as controller 1.
        cbtInputMask mask = cbtInput::GenerateInputMask(_context, CBT_CONTROLLER_1, _keycode);

        for (std::unordered_map<cbtInputMask,
                                std::bitset<CBT_MAX_INPUT_NAME>>::const_iterator iter = m_RegisteredInputs.begin();
             iter != m_RegisteredInputs.end(); ++iter)
        {
            if (!cbtInput::CompareMask(mask, iter->first))
            { continue; }
            m_CurrentInputState = (m_CurrentInputState & ~iter->second);
        }
    }

    void cbtKeyboardHandler::DispatchEvents(cbtEventDispatcher& _dispatcher)
    {
        for (cbtU32 i = 0; i < CBT_MAX_INPUT_NAME; ++i)
        {
            // Button Press
            if (m_CurrentInputState[i] & ~m_PreviousInputState[i])
            {
                // Send both a press and a hold event.
                _dispatcher.DispatchEvent<cbtInputEvent>(
                        new cbtButtonEvent(static_cast<cbtInputName>(i), cbtButtonEvent::PRESS));
                _dispatcher.DispatchEvent<cbtInputEvent>(
                        new cbtButtonEvent(static_cast<cbtInputName>(i), cbtButtonEvent::HOLD));
            }
                // Button Hold
            else if (m_CurrentInputState[i] & m_PreviousInputState[i])
            {
                _dispatcher.DispatchEvent<cbtInputEvent>(
                        new cbtButtonEvent(static_cast<cbtInputName>(i), cbtButtonEvent::HOLD));
            }
                // Button Release
            else if (~m_CurrentInputState[i] & m_PreviousInputState[i])
            {
                _dispatcher.DispatchEvent<cbtInputEvent>(
                        new cbtButtonEvent(static_cast<cbtInputName>(i), cbtButtonEvent::RELEASE));
            }
        }

        // Update Button States
        m_PreviousInputState = m_CurrentInputState;
    }

NS_CBT_END