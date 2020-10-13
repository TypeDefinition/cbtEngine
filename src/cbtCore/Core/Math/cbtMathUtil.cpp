/*!
    \file cbtMathUtil.cpp
*/

// Include CBT
#include "cbtMathUtil.h"

// Include STL
#include <float.h>
#include <limits.h>

NS_CBT_BEGIN

// Static Constant Variable(s)
const cbtF32 cbtMathUtil::EPSILON = 0.000001f;
const cbtF32 cbtMathUtil::PI = 3.14159265359f;
const cbtF32 cbtMathUtil::RAD2DEG = 180.0f / PI;
const cbtF32 cbtMathUtil::DEG2RAD = PI / 180.0f;

const cbtF32 cbtMathUtil::F32_MAX = FLT_MAX;
const cbtF32 cbtMathUtil::F32_MIN = FLT_MIN;
const cbtF32 cbtMathUtil::F32_LOWEST = -FLT_MAX;

const cbtF64 cbtMathUtil::F64_MAX = DBL_MAX;
const cbtF64 cbtMathUtil::F64_MIN = DBL_MIN;
const cbtF64 cbtMathUtil::F64_LOWEST = -DBL_MAX;

const cbtS8 cbtMathUtil::S8_MAX = SCHAR_MAX;
const cbtS8 cbtMathUtil::S8_MIN = SCHAR_MIN;

const cbtU8 cbtMathUtil::U8_MAX = UCHAR_MAX;
const cbtU8 cbtMathUtil::U8_MIN = 0;

const cbtS16 cbtMathUtil::S16_MAX = SHRT_MAX;
const cbtS16 cbtMathUtil::S16_MIN = SHRT_MIN;

const cbtU16 cbtMathUtil::U16_MAX = USHRT_MAX;
const cbtU16 cbtMathUtil::U16_MIN = 0;

const cbtS32 cbtMathUtil::S32_MAX = INT_MAX;
const cbtS32 cbtMathUtil::S32_MIN = INT_MIN;

const cbtU32 cbtMathUtil::U32_MAX = UINT_MAX;
const cbtU32 cbtMathUtil::U32_MIN = 0;

const cbtS64 cbtMathUtil::S64_MAX = LLONG_MAX;
const cbtS64 cbtMathUtil::S64_MIN = LLONG_MIN;

const cbtU64 cbtMathUtil::U64_MAX = ULLONG_MAX;
const cbtU64 cbtMathUtil::U64_MIN = 0;

NS_CBT_END