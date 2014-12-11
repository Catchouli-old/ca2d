#pragma once

#include "OpenGLWindow.h"
#include "../scripting/LuaEngine.h"

#include <coment/World.h>

#include <stdint.h>
#include <chrono>
#include <thread>
#include <memory>
#include <vector>
#include <mutex>
#include <sstream>

namespace ca2d
{
    class Game
    {
    public:

        /** Create a game with the specified window parameters */
        Game(int width, int height);

        /** Clean up application resources */
        ~Game();

        /** Update the game */
        virtual void update(double dt);

        /** Render the game */
        virtual void render();

        /** Handle an event */
        virtual bool handleEvent(SDL_Event event);

        /** The game's main loop */
        bool run();

        /** Whether the game should be running */
        bool isRunning() const;

        /** Get current time in seconds */
        double getTime() const;

    protected:

        /** Get the FPS of the game */
        int getFPS() const;

        /** Whether the game should be running */
        bool mRunning;

        /** The game's main window */
        OpenGLWindow mWindow;

        /** The entity world */
        coment::World mWorld;

        /** The main lua engine */
        LuaEngine mLuaEngine;

    private:

        /** Game timer */
        std::thread mLuaPromptThread;
        std::mutex mSafeUpdateMutex;
        std::chrono::system_clock::time_point mLastUpdate;

        /** Framerate counter */
        uint32_t mLastFpsUpdate;
        int mFrames, mFPS;

    };

    /** Whether the game should be running */
    inline bool Game::isRunning() const
    {
        return mRunning;
    }

    /** Get the FPS of the game */
    inline int Game::getFPS() const
    {
        return mFPS;
    }
}