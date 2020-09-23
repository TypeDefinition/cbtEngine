#pragma once

// Include CBT
#include "CBT.h" // Include CBT.h in order to include the Main.h, which includes our application's entry point.

USING_NS_CBT;

class Sandbox : public NS_CBT::cbtApplication
{
protected:
    virtual ~Sandbox();

public:
    Sandbox(const cbtStr& _name);

    virtual void PostInit();
    virtual void PreUpdate();
    virtual void PostUpdate();
    virtual void PreExit();
};