#pragma once

#include <coment/systems/EntityProcessingSystem.h>

#include "../components/Position.h"
#include "../components/Velocity.h"

class MovementSystem
    : public coment::EntityProcessingSystem
{
public:

    MovementSystem()
    {

    }

    void registerComponents()
    {
        registerComponent<Position>();
        registerComponent<Velocity>();
    }

    /** Move entities by their velocity */
    void process(const coment::Entity& e) override
    {
        Position* p = _world->getComponent<Position>(e);
        const Velocity* v = _world->getComponent<Velocity>(e);

        p->x += v->x * _world->getDelta();
        p->y += v->y * _world->getDelta();
    }

};