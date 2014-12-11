#pragma once

#include <app/Game.h>

#include <Gwen/Gwen.h>
#include <Gwen/Skins/Simple.h>
#include <Gwen/Skins/TexturedBase.h>
#include <gwen/Controls/WindowCanvas.h>

#include <gwen/SDL2Renderer.h>
#include <gwen/SDL2Input.h>

class SceneEdit
    : public ca2d::Game
{
public:

    /** Create default TestApp */
    SceneEdit();

    /** Clean up application resources */
    ~SceneEdit();

    /** Update TestApp */
    void update(double dt) override;

    /** Render TestApp */
    void render() override;

protected:

    Gwen::Renderer::SDL2Renderer mGwenRenderer;
    Gwen::Skin::TexturedBase mSkin;
    Gwen::Controls::WindowCanvas mWindowCanvas;

};