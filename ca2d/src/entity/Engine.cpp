#include "entity/Engine.h"

#include <SDL2/SDL.h>

namespace ca2d
{

    /** Create an empty entity engine */
    Engine::Engine()
    {

    }

    /** Create an entity */
    Entity* Engine::createEntity()
    {
        Entity* e = new Entity();

        mEntities.push_back(std::unique_ptr<Entity>(e));

        return e;
    }

    /** Clear entities */
    void Engine::clearEntities()
    {
        mEntities.clear();
    }

    /** Process entities */
    void Engine::processEntities()
    {
        static double time = SDL_GetTicks() / 1000.0;

        double newTime = SDL_GetTicks() / 1000.0;
        double dt = newTime - time;
        time = newTime;

        for (auto& e : mEntities)
        {
            e->update(dt);
            e->render();
        }
    }

}