#pragma once

/*! \file cbtMain.h
    \brief The file containing the main function of the C++ application.
*/

// Memory Leak Checking
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

// SDL (This tells SDL that we have our own entry point.)
#define SDL_MAIN_HANDLED

// Include CBT
#include "Application/cbtApplication.h"

/**
    \brief The main function of the C++ application.
*/
int main(int argc, char** argv)
{
    _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF);

    NS_CBT::cbtApplication* app = NS_CBT::cbtApplication::GetInstance();
    app->Run();
    NS_CBT::cbtApplication::Destroy();

    return 0;
}