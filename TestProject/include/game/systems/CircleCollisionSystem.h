#pragma once

#include <app/Game.h>

#include <coment/systems/EntityProcessingSystem.h>

#include "../components/Position.h"
#include "../components/Velocity.h"
#include "../components/Radius.h"
#include "../components/CircleCollider.h"

class CircleCollisionSystem
    : public coment::EntityProcessingSystem
{
public:

    CircleCollisionSystem()
    {

    }

    void registerComponents()
    {
        registerComponent<Position>();
        registerComponent<Velocity>();
        registerComponent<Radius>();
        registerComponent<CircleCollider>();
    }

    /** Render a circle at position */
    void process(const coment::Entity& e) override
    {
        const Radius* r = _world->getComponent<Radius>(e);
        Position* p = _world->getComponent<Position>(e);
        Velocity* v = _world->getComponent<Velocity>(e);

        // Get window dimensions
        int w, h;

        ca2d::OpenGLWindow* window = _world->getValue<ca2d::OpenGLWindow*>("window");
        SDL_GetWindowSize(window->getSDLWindow(), &w, &h);

        if (p->x + r->v > w)
        {
            v->x *= -1.0f;
            p->x = w - r->v;
        }
        if (p->x - r->v < 0)
        {
            v->x *= -1.0f;
            p->x = r->v;
        }
        if (p->y + r->v > h)
        {
            v->y *= -1.0f;
            p->y = h - r->v;
        }
        if (p->y - r->v < 0)
        {
            v->y *= -1.0f;
            p->y = r->v;
        }
    }

};