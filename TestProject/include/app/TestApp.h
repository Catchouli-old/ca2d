#pragma once

#include <app/Game.h>

#include <thread>

class TestApp
    : public ca2d::Game
{
public:

    /** Create default TestApp */
    TestApp();

    /** Clean up application resources */
    ~TestApp();

    /** Update TestApp */
    void update(double dt) override;

    /** Render TestApp */
    void render() override;

protected:

}; 