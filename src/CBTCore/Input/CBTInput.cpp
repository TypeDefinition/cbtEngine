// Include CBT
#include "CBTInput.h"

NS_CBT_BEGIN

CBTInputMask CBTInput::GenerateInputMask(CBTInputContext _context, CBTControllerIndex _controllerIndex, CBTKeycode _keyCode)
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

CBTInputContext CBTInput::GetContext(CBTInputMask _inputMask)
{
    _inputMask >>= 48;
    _inputMask &= 0x000000000000FFFF;

    return static_cast<cbtU16>(_inputMask);
}

CBTControllerIndex CBTInput::GetControllerIndex(CBTInputMask _inputMask)
{
    _inputMask >>= 32;
    _inputMask &= 0x000000000000FFFF;

    return static_cast<cbtU16>(_inputMask);
}

CBTKeycode CBTInput::GetKeycode(CBTInputMask _inputMask)
{
    _inputMask &= 0x00000000FFFFFFFF;

    return static_cast<CBTKeycode>(_inputMask);
}

cbtBool CBTInput::CompareContext(CBTInputContext _contextA, CBTInputContext _contextB)
{
    return (_contextA & _contextB) != 0;
}

cbtBool CBTInput::CompareControllerIndex(CBTControllerIndex _controllerIndexA, CBTControllerIndex _controllerIndexB)
{
    return (_controllerIndexA & _controllerIndexB) != 0;
}

cbtBool CBTInput::CompareKeyCode(CBTKeycode _keyCodeA, CBTKeycode _keyCodeB)
{
    return _keyCodeA == _keyCodeB;
}

cbtBool CBTInput::CompareMask(CBTInputMask _maskA, CBTInputMask _maskB)
{
    cbtU16 contextA = GetContext(_maskA);
    cbtU16 contextB = GetContext(_maskB);

    cbtU16 controllerIndexA = GetControllerIndex(_maskA);
    cbtU16 controllerIndexB = GetControllerIndex(_maskB);

    CBTKeycode keyCodeA = GetKeycode(_maskA);
    CBTKeycode keyCodeB = GetKeycode(_maskB);

    return CompareContext(contextA, contextB) && CompareControllerIndex(controllerIndexA, controllerIndexB) && CompareKeyCode(keyCodeA, keyCodeB);
}

NS_CBT_END