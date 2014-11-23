#pragma once

#include "Component.h"
#include "../scripting/LuaEngine.h"
#include "../scripting/LuaReference.h"

namespace ca2d
{

    /** A component class that takes a lua reference. */
    class LuaComponent
        : public Component
    {
    public:

        /** Construct a lua component from a lua table reference. */
        LuaComponent(LuaReference tableRef)
            : mTableRef(tableRef)
        {

        }

        virtual void update(float dt)
        {
            LuaEngine* eng = LuaEngine::fromLuaState(mTableRef.getLuaState());

            eng->callFunction(mTableRef, "update", mTableRef, dt);
        }

        virtual void render()
        {
            LuaEngine* eng = LuaEngine::fromLuaState(mTableRef.getLuaState());

            eng->callFunction(mTableRef, "render", mTableRef);
        }

    private:

        /** The reference to the lua table */
        LuaReference mTableRef;

    };

}