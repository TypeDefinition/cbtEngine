#pragma once

// Include CBT
#include "Input/CBTInput.h"
#include "Core/Event/CBTEvent.h"

NS_CBT_BEGIN

class CBTInputEvent : public CBTEvent
{
public:
    const CBTInputName m_InputName;
    virtual ~CBTInputEvent() {}

protected:
    CBTInputEvent(CBTInputName _name)
        : m_InputName(_name)
    {}
};

class CBTAxisEvent : public CBTInputEvent
{
public:
    enum Axis { W, X, Y, Z, };

    const Axis m_Axis;
    const cbtF32 m_Value;

    CBTAxisEvent(CBTInputName _name, Axis _axis, cbtF32 _value)
        : CBTInputEvent(_name), m_Axis(_axis), m_Value(_value)
    {}
    virtual ~CBTAxisEvent() {}
};

class CBTButtonEvent : public CBTInputEvent
{
public:
    enum ButtonState { PRESS, HOLD, RELEASE, };

    const ButtonState m_State;

    CBTButtonEvent(CBTInputName _name, ButtonState _state)
        : CBTInputEvent(_name), m_State(_state)
    {}
    virtual ~CBTButtonEvent() {}
};

struct CBTCursorPosition
{
private:
    cbtF32 m_X, m_Y;

public:
    CBTCursorPosition(cbtF32 _x = 0.0f, cbtF32 _y = 0.0f) { Set(_x, _y); }
    CBTCursorPosition(const CBTCursorPosition& _other) { Set(_other.m_X, _other.m_Y); }
    ~CBTCursorPosition() {}

    void Set(cbtF32 _x, cbtF32 _y) { m_X = _x; m_Y = _y; }
    cbtF32 GetX() const { return m_X; }
    cbtF32 GetY() const { return m_Y; }

    CBTCursorPosition& operator=(const CBTCursorPosition& _other) { Set(_other.m_X, _other.m_Y); return *this; }
};

class CBTClickEvent : public CBTButtonEvent
{
public:
    const CBTCursorPosition m_CursorPosition;

    CBTClickEvent(CBTInputName _name, ButtonState _state, CBTCursorPosition _cursorPosition)
        : CBTButtonEvent(_name, _state), m_CursorPosition(_cursorPosition)
    {}
    virtual ~CBTClickEvent() {}
};

NS_CBT_END