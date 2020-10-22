#pragma once

// Include CBT
#include "Input/cbtInput.h"
#include "Core/Event/cbtEvent.h"

NS_CBT_BEGIN

    class cbtInputEvent : public cbtEvent
    {
    public:
        const cbtInputName m_InputName;

        virtual ~cbtInputEvent()
        {
        }

    protected:
        cbtInputEvent(cbtInputName _name)
                :m_InputName(_name)
        {
        }
    };

    class cbtAxisEvent : public cbtInputEvent
    {
    public:
        enum Axis
        {
            W, X, Y, Z,
        };

        const Axis m_Axis;
        const cbtF32 m_Value;

        cbtAxisEvent(cbtInputName _name, Axis _axis, cbtF32 _value)
                :cbtInputEvent(_name), m_Axis(_axis), m_Value(_value)
        {
        }

        virtual ~cbtAxisEvent()
        {
        }
    };

    class cbtButtonEvent : public cbtInputEvent
    {
    public:
        enum ButtonState
        {
            PRESS, HOLD, RELEASE,
        };

        const ButtonState m_State;

        cbtButtonEvent(cbtInputName _name, ButtonState _state)
                :cbtInputEvent(_name), m_State(_state)
        {
        }

        virtual ~cbtButtonEvent()
        {
        }
    };

    struct cbtCursorPosition
    {
    private:
        cbtF32 m_X, m_Y;

    public:
        cbtCursorPosition(cbtF32 _x = 0.0f, cbtF32 _y = 0.0f)
        {
            Set(_x, _y);
        }

        cbtCursorPosition(const cbtCursorPosition& _other)
        {
            Set(_other.m_X, _other.m_Y);
        }

        ~cbtCursorPosition()
        {
        }

        void Set(cbtF32 _x, cbtF32 _y)
        {
            m_X = _x;
            m_Y = _y;
        }

        cbtF32 GetX() const
        {
            return m_X;
        }

        cbtF32 GetY() const
        {
            return m_Y;
        }

        cbtCursorPosition& operator=(const cbtCursorPosition& _other)
        {
            Set(_other.m_X, _other.m_Y);
            return *this;
        }
    };

    class cbtClickEvent : public cbtButtonEvent
    {
    public:
        const cbtCursorPosition m_CursorPosition;

        cbtClickEvent(cbtInputName _name, ButtonState _state, cbtCursorPosition _cursorPosition)
                :cbtButtonEvent(_name, _state), m_CursorPosition(_cursorPosition)
        {
        }

        virtual ~cbtClickEvent()
        {
        }
    };

NS_CBT_END