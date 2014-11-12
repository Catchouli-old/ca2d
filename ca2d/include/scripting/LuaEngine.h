#pragma once

#include <mutex>

struct lua_State;

namespace ca2d
{

    class LuaEngine
    {
    public:

        /** Initialises lua library and state */
        LuaEngine();

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

        /** Set a global variable */
        void setGlobal(const char* type, const char* name, void* ptr);

    private:

        /** The lua state */
        lua_State* mLuaState;

    };

    /** Returns a pointer to the lua state */
    inline lua_State* LuaEngine::getLuaState() const
    {
        return mLuaState;
    }

}