#include "app/TestApp.h"

#include <lua.hpp>

#include <sstream>

#include <SDL2/SDL.h>
#include <rendering/OpenGL.h>

#include "game/systems/MovementSystem.h"
#include "game/systems/CircleRenderSystem.h"
#include "game/systems/CircleCollisionSystem.h"
#include "game/systems/MouseFollowSystem.h"

/** Create default TestApp */
TestApp::TestApp()
    : ca2d::Game(800, 600)
{
    static MovementSystem ms;
    static CircleRenderSystem crs;
    static CircleCollisionSystem ccs;
    static MouseFollowSystem mfs;

    // Load scene
    mLuaEngine.dofile("scene.lua");
    mLuaEngine.require("test");

    // Set world pointer
    mWorld.setValue<Game*>("game", (Game*)this);
    mWorld.setValue<ca2d::OpenGLWindow*>("window", &mWindow);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 800.0, 0.0, 600.0, 0.0, 10.0);

    // Register systems
    mWorld.registerSystem(ms);
    mWorld.registerSystem(crs);
    mWorld.registerSystem(ccs);
    mWorld.registerSystem(mfs);

    // Create entities
    srand(time(0));
    auto randf = [] { return ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f; };

    //static coment::Entity e = mWorld.createEntity();
    //e.addComponent<Position>(400, 300);
    //e.addComponent<Velocity>(500.0f * randf(), 500.0f * randf());
    //e.addComponent<Radius>(30.0f);
    //e.addComponent<Color>(0.5f, 1, 1);
    //e.addComponent<CircleCollider>();
    //e.addComponent<Color>(0.5f, 1, 1);

    //mLuaEngine.setGlobal("coment::Entity *", "circle", &e);
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
        mWindow.setTitle(ss.str().c_str());
    }
}

/** Render TestApp */
void TestApp::render()
{
    static float w = 800;
    static float h = 600;

    glPushMatrix();
    //glScalef(h / w, 1.0f, 1.0f);

    Game::render();

    glPopMatrix();
}