#pragma once

// Include CBT
#include "CBTMacros.h"
#include "Core/General/CBTSingleton.h"
#include "Core/Math/CBTVector3.h"

NS_CBT_BEGIN

class CBTAudioEngine : public CBTSingleton<CBTAudioEngine>
{
    friend class CBTSingleton<CBTAudioEngine>;

protected:
    CBTAudioEngine() {}
    virtual ~CBTAudioEngine() {}

    static CBTAudioEngine* CreateInstance() { return nullptr; }

public:
    virtual void Init() = 0;
    virtual void Exit() = 0;
};

NS_CBT_END