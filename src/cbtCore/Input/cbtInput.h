#pragma once

/**
    \file cbtInput.h
    \brief
        When making games, for portability purposes, as well as our own sanity, we do not want to hardcode physical buttons to specific actions in our games.
        We should use a layer of abstraction. This is where our input system comes in.\n\n

        cbtInputName -
            An input name is the name we give to our actions. Examples can be JUMP, WALK or SHOOT. It is an unsigned integer with a value ranging from 0 to (CBT_MAX_INPUT_NAME-1).
            That means that we an have a maxiumum of CBT_MAX_INPUT_NAME input names.

        cbtInputContext -
            The controls of a game might differ depending on what is happening.
            Contexts is the name given to the scenario the game or player is currently in. Examples can be WALKING, DRIVING, COMBAT, MAIN_MENU, PAUSE_MENU.
            For example during the context COMBAT, Left-Click may mean PUNCH, but during the context DRIVING, Left-Click may mean HONK.
            This allows us to make the same physical controls do different things when different 
            We can represent these contexts using cbtInputContext. As cbtInputContext has 16bits, we can have up to 16 contexts.

        cbtControllerIndex -
            It is possible to have multiple controllers active at the same time, such as in a couch co-op game.
            CBTControllerindex allows us to specify which controller we want to trigger which actions.
            For example in a couch co-op game, we want inputs from CBT_CONTROLLER_1 to control player 1, and CBT_CONTROLLER_2 to control player 2.
            We can represent these controllers using cbtControllerIndex. As cbtControllerIndex has 16bits, we can have up to 16 controllers.

        cbtKeycode -
            This is a 32bit unsigned integer that represents the physical key being pressed. For the full list of available keycodes, check CBTKeyode.h.

        cbtControllerMask (16bit ControllerIndex + 16bit InputContext + 32bit Keycode) -
            This is a 64bit mask made by combining a cbtInputContext, a cbtControllerIndex and a cbtKeycode.
            To register a control, we will register with an InputHandler a cbtInputName and a cbtControllerMask.
            This means that whenever the conditions of the cbtControllerMask is met (correct context, controller and physical button), an event representing cbtInputName will be dispatched.
*/

// Include CBT
#include "cbtKeycode.h"

NS_CBT_BEGIN

/// \brief Input name.
    typedef cbtU32 cbtInputName;

/// \brief The maximum number of input names.
#define CBT_MAX_INPUT_NAME 128

/// \brief 64bit Input Mask.
    typedef cbtU64 cbtInputMask;

/// \brief 16bit Controller Index.
    typedef cbtU16 cbtControllerIndex;

#define CBT_CONTROLLER_NONE 0x0000
#define CBT_CONTROLLER_ALL 0xFFFF

#define CBT_CONTROLLER_1 0x0001
#define CBT_CONTROLLER_2 0x0002
#define CBT_CONTROLLER_3 0x0004
#define CBT_CONTROLLER_4 0x0008
#define CBT_CONTROLLER_5 0x0010
#define CBT_CONTROLLER_6 0x0020
#define CBT_CONTROLLER_7 0x0040
#define CBT_CONTROLLER_8 0x0080

#define CBT_CONTROLLER_9 0x0100
#define CBT_CONTROLLER_10 0x0200
#define CBT_CONTROLLER_11 0x0400
#define CBT_CONTROLLER_12 0x0800
#define CBT_CONTROLLER_13 0x1000
#define CBT_CONTROLLER_14 0x2000
#define CBT_CONTROLLER_15 0x4000
#define CBT_CONTROLLER_16 0x8000

#define CBT_CONTROLLER_DEFAULT CBT_CONTROLLER_ALL

/// \brief Input Context
    typedef cbtU16 cbtInputContext;

#define CBT_INPUT_CONTEXT_NONE 0x0000
#define CBT_INPUT_CONTEXT_ALL 0xFFFF

#define CBT_INPUT_CONTEXT_1 0x0001
#define CBT_INPUT_CONTEXT_2 0x0002
#define CBT_INPUT_CONTEXT_3 0x0004
#define CBT_INPUT_CONTEXT_4 0x0008
#define CBT_INPUT_CONTEXT_5 0x0010
#define CBT_INPUT_CONTEXT_6 0x0020
#define CBT_INPUT_CONTEXT_7 0x0040
#define CBT_INPUT_CONTEXT_8 0x0080

#define CBT_INPUT_CONTEXT_9 0x0100
#define CBT_INPUT_CONTEXT_10 0x0200
#define CBT_INPUT_CONTEXT_11 0x0400
#define CBT_INPUT_CONTEXT_12 0x0800
#define CBT_INPUT_CONTEXT_13 0x1000
#define CBT_INPUT_CONTEXT_14 0x2000
#define CBT_INPUT_CONTEXT_15 0x4000
#define CBT_INPUT_CONTEXT_16 0x8000

#define CBT_INPUT_CONTEXT_DEFAULT CBT_INPUT_CONTEXT_ALL

/**
    \brief Input Utility Class
*/
    class cbtInput
    {
    private:
        /**
            \brief Private Constructor. All functions should be static. No objects of this class should be created.
        */
        cbtInput() = default;

        /**
            \brief Private Destructor. All functions should be static. No objects of this class should be created.
        */
        ~cbtInput() = default;

    public:
        /**
            \brief Generate an cbtInputMask given a cbtInputContext, cbtControllerIndex and cbtKeycode.

            \param _context The input context.
            \param _controllerIndex The controller index.
            \param _keycode The keycode.

            \return An cbtInputMask representing the given cbtInputContext, cbtControllerIndex and cbtKeycode.

            \sa GetContext, GetControllerIndex, GetKeycode, CompareContext, CompareControllerIndex, CompareKeyCode, CompareMask
        */
        static cbtInputMask
        GenerateInputMask(cbtInputContext _context, cbtControllerIndex _controllerIndex, cbtKeycode _keyCode);

        /**
            \brief Extract the cbtInputContext from a cbtInputMask.

            \param _inputMask The cbtInputMask to extract from.

            \return The cbtInputContext of the cbtInputMask.

            \sa GenerateInputMask, GetControllerIndex, GetKeycode, CompareContext, CompareControllerIndex, CompareKeyCode, CompareMask
        */
        static cbtInputContext GetContext(cbtInputMask _inputMask);

        /**
            \brief Extract the cbtControllerIndex from a cbtInputMask.

            \param _inputMask The cbtInputMask to extract from.

            \return The cbtControllerIndex of the cbtInputMask.

            \sa GenerateInputMask, GetContext, GetKeycode, CompareContext, CompareControllerIndex, CompareKeyCode, CompareMask
        */
        static cbtControllerIndex GetControllerIndex(cbtInputMask _inputMask);

        /**
            \brief Extract the cbtKeycode from a cbtInputMask.

            \param _inputMask The cbtInputMask to extract from.

            \return The cbtKeycode of the cbtInputMask.

            \sa GenerateInputMask, GetContext, GetControllerIndex, CompareContext, CompareControllerIndex, CompareKeyCode, CompareMask
        */
        static cbtKeycode GetKeycode(cbtInputMask _inputMask);

        /**
            \brief Compare 2 CBTInputContexts.

            \param _contextA The first cbtInputContext to compare.
            \param _contextB The second cbtInputContext to compare.

            \return Returns (_contextA & _contextB) != 0.

            \sa GenerateInputMask, GetContext, GetControllerIndex, GetKeycode, CompareControllerIndex, CompareKeyCode, CompareMask
        */
        static cbtBool CompareContext(cbtInputContext _contextA, cbtInputContext _contextB);

        /**
            \brief Compare 2 cbtControllerIndex.

            \param _controllerIndexA The first cbtControllerIndex to compare.
            \param _controllerIndexB The second cbtControllerIndex to compare.

            \return Returns (_controllerIndexA & _controllerIndexB) != 0.

            \sa GenerateInputMask, GetContext, GetControllerIndex, GetKeycode, CompareContext, CompareKeyCode, CompareMask
        */
        static cbtBool
        CompareControllerIndex(cbtControllerIndex _controllerIndexA, cbtControllerIndex _controllerIndexB);

        /**
            \brief Compare 2 cbtKeycode.

            \param _keyCodeA The first cbtKeycode to compare.
            \param _keyCodeB The second cbtKeycode to compare.

            \return Returns _keyCodeA == _keyCodeB.

            \sa GenerateInputMask, GetContext, GetControllerIndex, GetKeycode, CompareContext, CompareControllerIndex, CompareMask
        */
        static cbtBool CompareKeyCode(cbtKeycode _keyCodeA, cbtKeycode _keyCodeB);

        /**
            \brief Compare 2 cbtInputMask.

            \param _maskA The first cbtInputMask to compare.
            \param _maskB The second cbtInputMask to compare.

            \return Returns true result of comparing the masks' controller index, keycode and input context.

            \sa GenerateInputMask, GetContext, GetControllerIndex, GetKeycode, CompareContext, CompareControllerIndex, CompareKeyCode
        */
        static cbtBool CompareMask(cbtInputMask _maskA, cbtInputMask _maskB);
    };

NS_CBT_END