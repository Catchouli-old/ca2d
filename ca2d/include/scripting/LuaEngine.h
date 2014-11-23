#pragma once

#include <mutex>
#include <array>
#include <vector>

#include "LuaValue.h"

struct lua_State;

namespace ca2d
{

    /** An engine that creates a lua reference and allows easy access to it */
    class LuaEngine
    {
    public:

        /** Initialises lua library and state */
        LuaEngine();

        LuaEngine(const LuaEngine&) = delete;
        LuaEngine& operator=(const LuaEngine&) = delete;

        /** Cleans up lua state */
        ~LuaEngine();

        /** Returns a pointer to the lua state */
        lua_State* getLuaState() const;

        /** Loads the standard lua libs */
        void loadStandardLibs();

        /** Runs lua prompt in stdin/stdout */
        void prompt(std::mutex* safeUpdateMutex);

        /** Require lua file */
        bool require(const char* filename);

        /** Run lua file */
        bool dofile(const char* filename);

        /** Run lua command */
        bool runCommand(const char* command);

        /** Get a global variable from the lua state */
        LuaValue getGlobal(const char* name) const;

        /** Set a global variable */
        void setGlobal(const char* type, const char* name, void* ptr);

        /** Call lua function */
        template <typename... Args>
        bool callFunction(const char* name, Args... args);

        /** Call lua function expecting return values */
        template <typename... Args>
        bool callFunction(const char* name,
            std::vector<LuaValue>& ret, Args... args);

        /** Call lua function on object */
        template <typename... Args>
        bool callFunction(LuaReference obj, const char* name,
            Args... args);

        /** Call lua function expecting return values */
        template <typename... Args>
        bool callFunction(LuaReference obj, const char* name,
            std::vector<LuaValue>& ret, Args... args);

        /** Get a lua engine back from the lua state.
            This function only works on lua states constructed by LuaEngine. */
        static LuaEngine* fromLuaState(lua_State* luaState);

    private:

        /** Whether the lua state should be cleaned up (does this instance own the lua state?) */
        bool mCleanup;

        /** The lua state */
        lua_State* mLuaState;

    };

    /** Returns a pointer to the lua state */
    inline lua_State* LuaEngine::getLuaState() const
    {
        return mLuaState;
    }

    /** Get a global variable from the lua state */
    inline LuaValue LuaEngine::getGlobal(const char* name) const
    {
        lua_getglobal(mLuaState, name);

        return LuaValue::fromStack(mLuaState, -1);
    }

}

// Inline definitions
#include "LuaEngine.inl"