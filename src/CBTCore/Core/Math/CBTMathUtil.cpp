/*!
    \file CBTMathUtil.cpp
*/

// Include CBT
#include "CBTMathUtil.h"

NS_CBT_BEGIN

// Static Constant Variable(s)
const cbtF32 CBTMathUtil::EPSILON = 0.000001f;
const cbtF32 CBTMathUtil::PI = 3.14159265359f;
const cbtF32 CBTMathUtil::RAD2DEG = 180.0f / PI;
const cbtF32 CBTMathUtil::DEG2RAD = PI / 180.0f;

const cbtF32 CBTMathUtil::F32_MAX = FLT_MAX;
const cbtF32 CBTMathUtil::F32_MIN = FLT_MIN;
const cbtF32 CBTMathUtil::F32_LOWEST = -FLT_MAX;

const cbtF64 CBTMathUtil::F64_MAX = DBL_MAX;
const cbtF64 CBTMathUtil::F64_MIN = DBL_MIN;
const cbtF64 CBTMathUtil::F64_LOWEST = -DBL_MAX;

const cbtS8 CBTMathUtil::S8_MAX = SCHAR_MAX;
const cbtS8 CBTMathUtil::S8_MIN = SCHAR_MIN;

const cbtU8 CBTMathUtil::U8_MAX = UCHAR_MAX;
const cbtU8 CBTMathUtil::U8_MIN = 0;

const cbtS16 CBTMathUtil::S16_MAX = SHRT_MAX;
const cbtS16 CBTMathUtil::S16_MIN = SHRT_MIN;

const cbtU16 CBTMathUtil::U16_MAX = USHRT_MAX;
const cbtU16 CBTMathUtil::U16_MIN = 0;

const cbtS32 CBTMathUtil::S32_MAX = INT_MAX;
const cbtS32 CBTMathUtil::S32_MIN = INT_MIN;

const cbtU32 CBTMathUtil::U32_MAX = UINT_MAX;
const cbtU32 CBTMathUtil::U32_MIN = 0;

const cbtS64 CBTMathUtil::S64_MAX = LLONG_MAX;
const cbtS64 CBTMathUtil::S64_MIN = LLONG_MIN;

const cbtU64 CBTMathUtil::U64_MAX = ULLONG_MAX;
const cbtU64 CBTMathUtil::U64_MIN = 0;

NS_CBT_END