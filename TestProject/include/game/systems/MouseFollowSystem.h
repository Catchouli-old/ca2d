#pragma once

#include <app/Game.h>

#include <coment/systems/EntityProcessingSystem.h>

#include "../components/Position.h"
#include "../components/MouseFollow.h"

class MouseFollowSystem
    : public coment::EntityProcessingSystem
{
public:

    MouseFollowSystem()
    {

    }

    void registerComponents()
    {
        registerComponent<Position>();
        registerComponent<MouseFollow>();
    }

    /** Render a circle at position */
    void process(const coment::Entity& e) override
    {
        Position* p = _world->getComponent<Position>(e);

        // Get window dimensions
        int x, y;

        ca2d::OpenGLWindow* window = _world->getValue<ca2d::OpenGLWindow*>("window");
        SDL_GetMouseState(&x, &y);

        p->x = (float)x;
        p->y = (float)y;
    }

};