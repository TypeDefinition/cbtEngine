// Include CBT
#include "cbtInput.h"

NS_CBT_BEGIN

    cbtInputMask
    cbtInput::GenerateInputMask(cbtInputContext _context, cbtControllerIndex _controllerIndex, cbtKeycode _keyCode)
    {
        cbtU64 inputMask = 0;

        // Context
        cbtU64 contextMask = (cbtU64)_context;
        contextMask <<= 48;
        contextMask &= 0xFFFF000000000000;
        inputMask |= contextMask;

        // Controller Index
        cbtU64 controllerIndexMask = (cbtU64)_controllerIndex;
        controllerIndexMask <<= 32;
        controllerIndexMask &= 0x0000FFFF00000000;
        inputMask |= controllerIndexMask;

        // KeyCode
        cbtU64 keyCodeMask = (cbtU64)_keyCode;
        keyCodeMask &= 0x00000000FFFFFFFF;
        inputMask |= keyCodeMask;

        return inputMask;
    }

    cbtInputContext cbtInput::GetContext(cbtInputMask _inputMask)
    {
        _inputMask >>= 48;
        _inputMask &= 0x000000000000FFFF;

        return static_cast<cbtU16>(_inputMask);
    }

    cbtControllerIndex cbtInput::GetControllerIndex(cbtInputMask _inputMask)
    {
        _inputMask >>= 32;
        _inputMask &= 0x000000000000FFFF;

        return static_cast<cbtU16>(_inputMask);
    }

    cbtKeycode cbtInput::GetKeycode(cbtInputMask _inputMask)
    {
        _inputMask &= 0x00000000FFFFFFFF;

        return static_cast<cbtKeycode>(_inputMask);
    }

    cbtBool cbtInput::CompareContext(cbtInputContext _contextA, cbtInputContext _contextB)
    {
        return (_contextA & _contextB) != 0;
    }

    cbtBool
    cbtInput::CompareControllerIndex(cbtControllerIndex _controllerIndexA, cbtControllerIndex _controllerIndexB)
    {
        return (_controllerIndexA & _controllerIndexB) != 0;
    }

    cbtBool cbtInput::CompareKeyCode(cbtKeycode _keyCodeA, cbtKeycode _keyCodeB)
    {
        return _keyCodeA == _keyCodeB;
    }

    cbtBool cbtInput::CompareMask(cbtInputMask _maskA, cbtInputMask _maskB)
    {
        cbtU16 contextA = GetContext(_maskA);
        cbtU16 contextB = GetContext(_maskB);

        cbtU16 controllerIndexA = GetControllerIndex(_maskA);
        cbtU16 controllerIndexB = GetControllerIndex(_maskB);

        cbtKeycode keyCodeA = GetKeycode(_maskA);
        cbtKeycode keyCodeB = GetKeycode(_maskB);

        return CompareContext(contextA, contextB) && CompareControllerIndex(controllerIndexA, controllerIndexB) &&
                CompareKeyCode(keyCodeA, keyCodeB);
    }

NS_CBT_END