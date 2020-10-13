#pragma once

// Include CBT
#include "cbtMacros.h"

NS_CBT_BEGIN

enum cbtWindowFlags : cbtU32
{
    CBT_WINDOW_NONE = 0,
    CBT_WINDOW_FULLSCREEN = 1,
    CBT_WINDOW_BORDERLESS = 2,
};

struct cbtWindowProperties
{
public:
    cbtU32 m_Width, m_Height;
    cbtU32 m_Flags;
    cbtStr m_Title;

    cbtWindowProperties()
        : m_Width(1280)
        , m_Height(720)
        , m_Flags(CBT_WINDOW_NONE)
        , m_Title("Unnamed Window")
    {}
    ~cbtWindowProperties() {}

    inline cbtBool IsFullscreen() const { return (m_Flags & CBT_WINDOW_FULLSCREEN); }
    inline cbtBool IsBorderless() const { return (m_Flags & CBT_WINDOW_BORDERLESS); }
};

NS_CBT_END