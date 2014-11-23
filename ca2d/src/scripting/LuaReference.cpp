#include "scripting/LuaReference.h"

namespace ca2d
{

    /** Default constructor - effictively useless but allows delayed initialisation */
    LuaReference::LuaReference()
    {

    }

    /** Create a lua reference attached to a given lua state */
    LuaReference::LuaReference(int ref, lua_State* luaState)
        : mLuaState(luaState)
    {
        // Bind deleter function
        std::function<void(int*)> deleter = std::bind(&LuaReference::deleter, this, std::placeholders::_1, mLuaState);

        // Initialise shared ptr
        mRef = std::shared_ptr<int>(new int(ref), deleter);
    }

    void LuaReference::deleter(int* ptr, lua_State* luaState)
    {
        luaL_unref(luaState, LUA_REGISTRYINDEX, *ptr);
        delete ptr;
    }
}