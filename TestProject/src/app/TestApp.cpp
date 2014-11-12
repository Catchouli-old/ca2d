#include "app/TestApp.h"

#include <lua.hpp>

#include <swigluaruntime.h>

#include <sstream>

#include <SDL/SDL.h>
#include <rendering/OpenGL.h>

#include "app/Components.h"

/** Create default TestApp */
TestApp::TestApp()
    : ca2d::Game(800, 600)
{
    // Load scene
    mLuaEngine.dofile("scene.lua");
}

/** Clean up application resources */
TestApp::~TestApp()
{

}

/** Update TestApp */
void TestApp::update(double dt)
{
    Game::update(dt);

    // Update title with FPS
    static int fps = -1;
    
    if (getFPS() != fps)
    {
        fps = getFPS();

        std::stringstream ss;
        ss << "FPS: " << fps;
        SDL_WM_SetCaption(ss.str().c_str(), nullptr);
    }
}

/** Render TestApp */
void TestApp::render()
{
    static float w = (float)SDL_GetVideoSurface()->w;
    static float h = (float)SDL_GetVideoSurface()->h;

    glPushMatrix();
    glScalef(h / w, 1.0f, 1.0f);

    Game::render();

    glPopMatrix();
}