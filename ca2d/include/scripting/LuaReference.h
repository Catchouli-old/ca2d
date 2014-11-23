#pragma once

#include <lua.hpp>
#include <assert.h>
#include <functional>
#include <memory>

namespace ca2d
{

    /** A reference tracked lua reference class that can be
        used as an argument for swig-wrapped functions */
    class LuaReference
    {
    public:

        /** Default constructor - effictively useless but allows delayed initialisation */
        LuaReference();

        /** Create a lua reference attached to a given lua state */
        LuaReference(int ref, lua_State* luaState);

        /** Accessor for the reference */
        int getReference() const;

        /** Accessor for the lua state */
        lua_State* getLuaState() const;

    private:

        void deleter(int* ptr, lua_State* luaState);

        /* A shared reference-counted reference that automatically luaL_unrefs itself */
        //ca2d::SharedReference<int, LuaRefDeleter, LUA_REFNIL> mRef;
        std::shared_ptr<int> mRef;

        /** The lua state this reference was obtained from */
        lua_State* mLuaState;
    };

    /** Accessor for the reference */
    inline int LuaReference::getReference() const
    {
        return *mRef.get();
    }

    /** Accessor for the lua state */
    inline lua_State* LuaReference::getLuaState() const
    {
        return mLuaState;
    }
}