#pragma once

#include "OpenGLWindow.h"
#include "../scripting/LuaEngine.h"

#include <stdint.h>
#include <chrono>
#include <thread>
#include <memory>
#include <vector>
#include <mutex>

#include "Entity.h"

namespace ca2d
{
    class Game
        : public OpenGLWindow
    {
    public:

        /* Create a game with the specified window parameters */
        Game(int width, int height);

        /* Clean up application resources */
        ~Game();

        /* Update the game */
        virtual void update(double dt);

        /* Render the game */
        virtual void render();

        /* The game's main loop */
        bool run();

        /* Whether the game should be running */
        bool isRunning() const;

        /* Create an entity */
        Entity* createEntity();

        /* Clear entities */
        void clearEntities();

        /* Get current time in seconds */
        double getTime() const;

    protected:

        /* Get the FPS of the game */
        int getFPS() const;

        /* Whether the game should be running */
        bool mRunning;

        /* The main lua engine */
        LuaEngine mLuaEngine;

    private:

        /* Game timer */
        std::chrono::system_clock::time_point mLastUpdate;

        /* Framerate counter */
        uint32_t mLastFpsUpdate;
        int mFrames, mFPS;

        /* The lua prompt thread */
        std::thread mLuaThread;

        /* Game state mutex */
        std::mutex mGameStateMutex;

        /* The entities */
        std::vector<std::unique_ptr<Entity>> mEntities;

    };

    /* Whether the game should be running */
    inline bool Game::isRunning() const
    {
        return mRunning;
    }

    /* Get the FPS of the game */
    inline int Game::getFPS() const
    {
        return mFPS;
    }
}