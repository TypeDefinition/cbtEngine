#pragma once

// Include CBT
#include "cbtMacros.h"

// Engine(s)
#include "Core/General/cbtSingleton.h"
#include "Game/GameEngine/cbtGameEngine.h"
#include "Rendering/RenderEngine/cbtRenderEngine.h"
#include "Input/InputEngine/cbtInputEngine.h"

NS_CBT_BEGIN

/*!
    \brief
        The interface of the application base class to be inherited by the game application.

        On startup, an application is created. The order in which the functions are called is as follows:
        1. Run - This function simply calls the rest of the function(s) below. It is the starting point which will start the whole game loop.

        2. Init - This is where the core systems needed for the game to run (Rendering, Audio, Input, Physics etc.) are initialised.
        3. PostInit - This is a virtual interface function for the derived class. Any game specific systems should be initialised here. RegisterScene and PushScene to CBTSceneManager to get the game started.

        4. PreUpdate - This is a virtual interface function for the derived class. It is called before every frame Update.
        5. Update - This function updates the core systems. It is called every frame.
        6. PostUpdate - This is a virtual interface function for the derived class. It is called every frame after Update.

        7. PreExit - This is a virtual interface function for the derived class. Any game specific systems should be destroyed here.
        8. Exit - This is where the core systems needed for the game to run (Rendering, Audio, Input, Physics etc.) are destroyed.
*/
class cbtApplication : public cbtSingleton<cbtApplication>
{
    friend class cbtSingleton<cbtApplication>;

protected:
    /// The name of the application.
    cbtStr m_Name;
    /// A flag to exit the game loop. Set to true to quit the application.
    cbtBool m_Quit = false;

    /// The duration taken for the current frame.
    cbtF32 m_DeltaTime = 0.0f;
    /// The duration that has passed since the application started.
    cbtF32 m_TimePassed = 0.0f;

protected:
    /**
        \brief Constructs a new cbtApplication with given name.

        \param _name The name of the application.

        \return A cbtApplication of name _name.
    */
    cbtApplication(const cbtStr& _name) : m_Name(_name) {}
    /**
        \brief Destructor
    */
    virtual ~cbtApplication() {}

    /**
        \brief An undefined static function to create an cbtApplication object. Define it in your game to make it return the derived class application for your game.

        Example:\n
        \code{.cpp}
        // In Header File
        class MyGame : public NS_CBT::cbtApplication
        {
            // Implement Variable & Function(s)
        };

        // In CPP File
        NS_CBT::cbtApplication* NS_CBT::cbtApplication::CreateInstance() { return new MyGame("My Game"); }
        \endcode

        \return Returns a CBTAppliation pointer to a derived class of cbtApplication as implemented by the user.
    */
    static cbtApplication* CreateInstance();

public:
    /**
        \brief Returns the duration taken for the current frame.

        \return Returns the duration taken for the current frame.
    */
    inline cbtF32 GetDeltaTime() const { return m_DeltaTime; }
    /**
        \brief Returns the duration that has passed since the application started.

        \return Returns the duration that has passed since the application started.
    */
    inline cbtF32 GetTimePassed() const { return m_TimePassed; }

    /**
        \brief Returns the name of the application as given by the user as a cbtStr.

        \return Returns the name of the application as given by the user as a cbtStr.
    */
    inline const cbtStr& GetName() const { return m_Name; }
    /**
        \brief Sets the m_Quit flag to true which will cause the game loop to break and quit the application.
    */
    void Quit() { m_Quit = true; }
    /**
        \brief Run the application. It is the starting point which will start the whole game loop.
    */
    void Run();

    /**
        \brief This is where the core systems needed for the game to run(Rendering, Audio, Input, Physics etc.) are initialised.
    */
    void Init();
    /**
        \brief This is a virtual interface function for the derived class. Any game specific systems should be initialised here. RegisterScene and PushScene to CBTSceneManager to get the game started.
    */
    virtual void PostInit() = 0;

    /**
        \brief This is a virtual interface function for the derived class. It is called before every frame Update.
     */
    virtual void PreUpdate() = 0;
    /**
        \brief This function updates the core systems. It is called every frame.
    */
    void Update();
    /**
        \brief This is a virtual interface function for the derived class. It is called every frame after Update.
    */
    virtual void PostUpdate() = 0;

    /**
        \brief This is a virtual interface function for the derived class. Any game specific systems should be destroyed here.
    */
    virtual void PreExit() = 0;
    /**
        \brief This is where the core systems needed for the game to run(Rendering, Audio, Input, Physics etc.) are destroyed.
    */
    void Exit();
};

NS_CBT_END