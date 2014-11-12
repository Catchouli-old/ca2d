#include "app/Game.h"

#include <lua.hpp>

#include <iostream>
#include <sstream>
#include <stdio.h>

#include "rendering/OpenGL.h"

#include "SDL/SDL.h"

namespace ca2d
{
    extern "C" int luaopen_engine(lua_State*);

    /** Create a game with the specified window parameters */
    Game::Game(int width, int height)
        : mRunning(true), OpenGLWindow(width, height)
    {
        // Initialise game timer
        mLastUpdate = std::chrono::high_resolution_clock::now();

        // Initialise FPS counter
        mLastFpsUpdate = SDL_GetTicks();
        mFrames = 0;
        mFPS = 0;

        // Load lua libs
        mLuaEngine.loadStandardLibs();

        // Set up lua thread
        mLuaThread = std::thread(&LuaEngine::prompt, &mLuaEngine, &mGameStateMutex);
        
        // Load engine bindings
        luaL_requiref(mLuaEngine.getLuaState(), "engine", luaopen_engine, 0);

        // Copy engine bindings to global scope
        mLuaEngine.runCommand("for k,v in pairs(engine) do _G[k]=v end");

        // Print available engine bindings
        mLuaEngine.runCommand("print(\"Available engine bindings:\")");
        mLuaEngine.runCommand("for key,value in pairs(engine) do print(key) end");
        mLuaEngine.runCommand("io.write(\"> \")");

        // Push game into lua globals
        mLuaEngine.setGlobal("ca2d::Game *", "game", this);
    }

    /** Clean up application resources */
    Game::~Game()
    {
        fclose(stdin);
        mLuaThread.detach();
    }

    /** Update the game */
    void Game::update(double dt)
    {
        for (auto& ent : mEntities)
        {
            ent->update((float)dt);
        }
    }

    /** Render the game */
    void Game::render()
    {
        // Clear screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render entities
        for (auto& ent : mEntities)
        {
            ent->render();
        }
    }

    /** The game's main loop */
    bool Game::run()
    {
        if (!mRunning)
            return false;

        // Check for messages
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    mRunning = false;
                }
                break;
            case SDL_QUIT:
                mRunning = false;
                break;
            }
        }

        // Update timer
        std::chrono::system_clock::time_point time = std::chrono::high_resolution_clock::now();
        std::chrono::system_clock::duration diff = time - mLastUpdate;
        mLastUpdate = time;

        // Update FPS counter
        mFrames++;

        if (SDL_GetTicks() - mLastFpsUpdate >= 1000)
        {
            mFPS = mFrames;
            mFrames = 0;
            mLastFpsUpdate = SDL_GetTicks();
        }

        // Update
        mGameStateMutex.lock();
        update(std::chrono::duration_cast<std::chrono::duration<float, std::chrono::seconds::period>>(diff).count());

        // Render
        render();
        mGameStateMutex.unlock();

        // Flip buffers
        swap();

        // Return whether we should keep running
        return mRunning;
    }

    /** Create an entity */
    Entity* Game::createEntity()
    {
        Entity* e = new Entity();

        mEntities.push_back(std::unique_ptr<Entity>(e));

        return e;
    }

    /** Clear entities */
    void Game::clearEntities()
    {
        mEntities.clear();
    }

    /** Get current time in seconds */
    double Game::getTime() const
    {
        return SDL_GetTicks() / 1000.0;
    }

}