#pragma once

// Include CBT
#include "CBTMacros.h"

NS_CBT_BEGIN

enum CBTWindowFlags : cbtU32
{
    CBT_WINDOW_NONE = 0,
    CBT_WINDOW_FULLSCREEN = 1,
    CBT_WINDOW_BORDERLESS = 2,
};

struct CBTWindowProperties
{
public:
    cbtU32 m_Width, m_Height;
    cbtU32 m_Flags;
    cbtStr m_Title;

    CBTWindowProperties()
        : m_Width(1280)
        , m_Height(720)
        , m_Flags(CBT_WINDOW_NONE)
        , m_Title("Unnamed Window")
    {}
    ~CBTWindowProperties() {}

    inline cbtBool IsFullscreen() const { return (m_Flags & CBT_WINDOW_FULLSCREEN); }
    inline cbtBool IsBorderless() const { return (m_Flags & CBT_WINDOW_BORDERLESS); }
};

NS_CBT_END