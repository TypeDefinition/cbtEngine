#pragma once

// Include CBT
#include "Input/cbtInput.h"
#include "Input/cbtInputEvent.h"
#include "Core/Event/cbtEventDispatcher.h"

// Include STD
#include <bitset>
#include <unordered_map>

NS_CBT_BEGIN

    class cbtKeyboardHandler
    {
    protected:
        std::bitset<CBT_MAX_INPUT_NAME> m_PreviousInputState;
        std::bitset<CBT_MAX_INPUT_NAME> m_CurrentInputState;

        std::unordered_map<cbtInputMask, std::bitset<CBT_MAX_INPUT_NAME>> m_RegisteredInputs;

    public:
        // Constructor(s) & Destructor
        cbtKeyboardHandler();

        virtual ~cbtKeyboardHandler();

        // Input Registration
        void RegisterButton(cbtInputMask _mask, cbtInputName _inputName);

        void UnregisterButton(cbtInputMask _mask, cbtInputName _inputName);

        // Events
        void OnKeyPress(cbtInputContext _context, cbtKeycode _keycode);

        void OnKeyRelease(cbtInputContext _context, cbtKeycode _keycode);

        void DispatchEvents(cbtEventDispatcher& _dispatcher);
    };

NS_CBT_END