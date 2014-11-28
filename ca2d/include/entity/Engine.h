#pragma once

#include <vector>

#include "Entity.h"
#include "Component.h"

namespace ca2d
{
    /** An entity engine, responsible for managing entities */
    class Engine
    {
    public:

        /** Create an empty entity engine */
        Engine();

        /** Create an entity */
        Entity* createEntity();

        /** Clear entities */
        void clearEntities();

        /** Process entities */
        void processEntities();

    private:

        /** The entities */
        std::vector<std::unique_ptr<Entity>> mEntities;

    };
}