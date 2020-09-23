#pragma once

/*!
    \file cbtMathUtil.h
*/

// Include CBT
#include "cbtMacros.h"

// Include STD
#include <cmath>
#include <limits>

NS_CBT_BEGIN

/// A maths utility class.
class cbtMathUtil
{
private:
    // Constructor(s) & Destructor
    /**
        \brief Constructor of MathUtil.
        It is private to prevent the creation and destruction of a MathUtil object.
        MathUtil is purely an interface class.

        \sa ~MathUtil.
    */
    cbtMathUtil() {}
    /**
        \brief Destructor of MathUtil.
        It is private to prevent the creation and destruction of a MathUtil object.
        MathUtil is purely an interface class.

        \sa MathUtil.
    */
    ~cbtMathUtil() {}

public:
    // Static Constant Variable(s)
    static const cbtF32 EPSILON; ///< A small float taken to be the margin of error when comparing 2 floats.
    static const cbtF32 PI; ///< π
    static const cbtF32 RAD2DEG; ///< Multiply by this to convert from radian to degrees.
    static const cbtF32 DEG2RAD; ///< Multiply by this to convert from degrees to radian.

    static const cbtF32 F32_MAX; ///< The largest value a 32bit float can represent.
    static const cbtF32 F32_MIN; ///< The smallest positive value a 32bit float can represent.
    static const cbtF32 F32_LOWEST; ///< The lowest negative value a 32bit float an represent.

    static const cbtF64 F64_MAX; ///< The largest value a 64bit float can represent.
    static const cbtF64 F64_MIN; ///< The smallest positive value a 64bit float can represent.
    static const cbtF64 F64_LOWEST; ///< The lowest negative value a 64bit float an represent.

    static const cbtS8 S8_MAX; ///< The largest positive value a 8bit signed integer an represent.
    static const cbtS8 S8_MIN; ///< The smallest negative value a 8bit signed integer an represent.

    static const cbtU8 U8_MAX; ///< The largest positive value a 8bit unsigned integer an represent.
    static const cbtU8 U8_MIN; ///< The smallest negative value a 8bit unsigned integer an represent.

    static const cbtS16 S16_MAX; ///< The largest positive value a 16bit signed integer an represent.
    static const cbtS16 S16_MIN; ///< The smallest negative value a 16bit signed integer an represent.

    static const cbtU16 U16_MAX; ///< The largest positive value a 16bit unsigned integer an represent.
    static const cbtU16 U16_MIN; ///< The smallest negative value a 16bit unsigned integer an represent.

    static const cbtS32 S32_MAX; ///< The largest positive value a 32bit signed integer an represent.
    static const cbtS32 S32_MIN; ///< The smallest negative value a 32bit signed integer an represent.

    static const cbtU32 U32_MAX; ///< The largest positive value a 32bit unsigned integer an represent.
    static const cbtU32 U32_MIN; ///< The smallest negative value a 32bit unsigned integer an represent.

    static const cbtS64 S64_MAX; ///< The largest positive value a 64bit signed integer an represent.
    static const cbtS64 S64_MIN; ///< The smallest negative value a 64bit signed integer an represent.

    static const cbtU64 U64_MAX; ///< The largest positive value a 64bit unsigned integer an represent.
    static const cbtU64 U64_MIN; ///< The smallest negative value a 64bit unsigned integer an represent.

    // Interface Function(s)
    /**
        \brief Checks if _a and _b are approximately equal.

        \param _a The first value to compare.
        \param _b The second value to compare.

        \return Returns true if the difference between _a and _b is less than or equal to EPSILON.
    */
    template <typename T>
    static cbtBool IsApproxEqual(T _a, T _b)
    {
        return static_cast<T>(EPSILON) > Abs<T>(_a - _b);
    }

    /**
        \brief Returns the absolute value of _value. If _value is a negative number, return -_value, which is a positive number.

        \param _value The value to find the absolute of.

        \return The absolute value of _value. If _value is a negative number, return -_value, which is a positive number.
    */
    template <typename T>
    static T Abs(T _value)
    {
        return (static_cast<T>(0) > _value) ? -_value : _value;
    }

    /**
        \brief Returns the lesser of 2 values.

        \param _a The first value to compare.
        \param _b The second value to compare.

        \return Returns the minimum of the 2 parameters.
    */
    template <typename T>
    static T Min(T _a, T _b)
    {
        return (_a > _b) ? _b : _a;
    }

    /**
        \brief Returns the smallest of 3 or more values.

        \param _a The first value to compare.
        \param _b The second value to compare.
        \param _args The third, forth etc. value to compare.

        \return Returns the minimum of the 3 or more parameters.
    */
    template <typename T, typename... Args>
    static T Min(T _a, T _b, Args... _args)
    {
        return Min(Min<T>(_a, _b), _args);
    }

    /**
        \brief Returns the greater of 2 values.

        \param _a The first value to compare.
        \param _b The second value to compare.

        \return Returns the maximum of the 2 parameters.
    */
    template <typename T>
    static T Max(T _a, T _b)
    {
        return (_a > _b) ? _a : _b;
    }

    /**
        \brief Returns the largest of 3 or more values.

        \param _a The first value to compare.
        \param _b The second value to compare.
        \param _args The third, forth etc. value to compare.

        \return Returns the maximum of the 3 or more parameters.
    */
    template <typename T, typename... Args>
    static T Max(T _a, T _b, Args... _args)
    {
        return Max(Max<T>(_a, _b), _args);
    }

    /**
        \brief Constrain a value to lie between 2 further values.

        \param _value Specify the value to constrain.
        \param _min Specify the lower end of the range into which to constrain _value.
        \param _max Specify the upper end of the range into which to constrain _value.

        \return Returns the maximum of the 2 parameters. Returns _a if _a is more than _b, otherwise it returns _b.
    */
    template <typename T>
    static T Clamp(T _value, T _min, T _max)
    {
        if (_min > _value) { return _min; }
        if (_value > _max) { return _max; }

        return _value;
    }

    /**
        \brief Get the base-2 logarithm of _value.

        \return Returns the base-2 logarithm of _value.
    */
    static cbtF32 Log2(cbtF32 _value)
    {
        return log2f(_value);
    }

    /**
        \brief Get a random integer.

        \return Returns a random integer.
    */
    static cbtS32 RandomInt()
    {
        return std::rand();
    }

    /**
        \brief Get a random integer within a specified range.

        \param _min Specify the lower range of the randomly generated integer. (Inclusive)
        \param _max Specify the upper range of the randomly generated integer. (Exclusive)

        \return Returns a random integer between _min and _max-1.
    */
    static cbtS32 RandomInt(cbtS32 _min, cbtS32 _max)
    {
        return RandomInt() % (_max - _min) + _min;
    }

    /**
        \brief Get the smallest multiple of _a greater than _b.

        \param _a The number to get the multiple of.
        \param _b The number the multiple must be greater than.

        \return Returns a random integer between _min and _max-1.
    */
    static cbtU32 SmallestMultipleGreaterThan(cbtU32 _a, cbtU32 _b)
    {
        cbtU32 remainder = (_a + _b) % _a;
        return remainder == 0 ? _b : _a + _b - remainder;
    }

    /**
        \brief Get the nth term of the Fibonacci Sequence.

        \param _n The nth term of the Fibonacci Sequence.

        \return Returns the nth term of the Fibonacci Sequence.

        \warning Beware of unsigned integer overflow.
    */
    static cbtU32 Fibonacci(cbtU32 _n)
    {
        // If _n is 0, return 0.
        if (_n == 0) { return 0; }
        cbtU32 l = 0; // L, because L is 2 alphabets before n.
        cbtU32 m = 1; // M, because m is 1 alphabet before n.
        cbtU32 fib = l + m;
        // We have to start from term 1 instead of term 0. Because it is impossible to have both l and m be 0 and progress from there. No matter how you add 0 together it is still 0.
        for (cbtU32 i = 1; i < _n; ++i)
        {
            fib = l + m;
            l = m;
            m = fib;
        }
        return fib;
    }

    /**
        \brief Generate the Fibonacci Sequence from n = _start to n = _end and place it into a buffer.

        \param _start The nth term of the Fibonacci Sequence to start. (Inclusive)
        \param _end The nth term of the Fibonacci Sequence to end. (Exclusive)

        \return Returns the Fibonacci Sequence.

        \warning Beware of unsigned integer overflow. The size of buffer must be at least (_end - _start) elements.
    */
    static void Fibonacci(cbtU32 _start, cbtU32 _end, cbtU32* _buffer)
    {
        for (cbtU32 i = _start; i < _end; ++i)
        {
            if (i < _start + 2)
            {
                _buffer[i - _start] = Fibonacci(i);
            }
            else
            {
                _buffer[i - _start] = _buffer[i - _start - 1] + _buffer[i - _start - 2];
            }
        }
    }

    /**
        \brief Generate n terms of Fibonacci Sequence and place it into a buffer.

        \param _n The number of terms of the Fibonacci Sequence to generate.

        \return Returns n terms of the Fibonacci Sequence.

        \warning Beware of unsigned integer overflow. The size of buffer must be at least n elements.
    */
    static void Fibonacci(cbtU32 _n, cbtU32* _buffer)
    {
        for (cbtU32 i = 0; i < _n; ++i)
        {
            if (i < 2)
            {
                _buffer[i] = i;
                continue;
            }
            _buffer[i] = _buffer[i - 1] + _buffer[i - 2];
        }
    }

    /**
        \brief Calculate the factorial of a number.

        \param _n The number to calculate the factorial of.

        \return The factorial of a number.

        \warning Beware of unsigned integer overflow.
    */
    static cbtU32 Factorial(cbtU32 _n)
    {
        if (_n < 2) { return 1; }

        cbtU32 factorial = 1;
        for (cbtU32 i = 2; i <= _n; ++i)
        {
            factorial *= i;
        }

        return factorial;
    }
};

NS_CBT_END