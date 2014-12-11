#include "app/SceneEdit.h"

#include <lua.hpp>

#include <sstream>

#include <SDL2/SDL.h>
#include <rendering/OpenGL.h>

/** Create default TestApp */
SceneEdit::SceneEdit()
    : ca2d::Game(800, 600), mGwenRenderer(mWindow.getSDLWindow()), mSkin(&mGwenRenderer),
    mWindowCanvas(-1, -1, 800, 600, &mSkin, "ca2d Scene Editor")
{

}

/** Clean up application resources */
SceneEdit::~SceneEdit()
{

}

/** Update TestApp */
void SceneEdit::update(double dt)
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
void SceneEdit::render()
{
    static float w = 800;
    static float h = 600;

    // Main render
    glPushMatrix();
    glScalef(h / w, 1.0f, 1.0f);

    Game::render();

    glPopMatrix();

    // Render gui
}