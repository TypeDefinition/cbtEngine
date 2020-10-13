#pragma once

// Include CBT
#include "cbtMacros.h"

NS_CBT_BEGIN

template <typename T>
struct cbtFlags
{
    static const cbtU32 FLAGS;
    static cbtBool HasFlags(cbtU32 _flags)
    {
        return (_flags & FLAGS) == _flags;
    }
};

// Macro(s)
#define CBT_DEFINE_FLAGS(__TYPE__, __FLAGS__) template <> const cbtU32 cbtFlags<__TYPE__>::FLAGS = __FLAGS__

NS_CBT_END