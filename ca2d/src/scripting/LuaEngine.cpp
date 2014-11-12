#include "scripting/LuaEngine.h"

#include <lua.hpp>
#include <swigluaruntime.h>

#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>

namespace ca2d
{

    /* Initialises lua library and state */
    LuaEngine::LuaEngine()
    {
        // Create lua state
        mLuaState = luaL_newstate();
    }

    /* Cleans up lua state */
    LuaEngine::~LuaEngine()
    {
        // Destroy lua state
        lua_close(mLuaState);
    }

    /* Loads the standard lua libs */
    void LuaEngine::loadStandardLibs()
    {
        // Load standard lua libs
        luaL_openlibs(mLuaState);
    }

    /* Runs lua prompt in stdin/stdout */
    void LuaEngine::prompt(std::mutex* safeUpdateMutex)
    {
        std::unique_lock<std::mutex> lock(*safeUpdateMutex, std::defer_lock);

        std::string buffer;

        // Interactive prompt
        std::cout << "> ";
        while (std::getline(std::cin, buffer))
        {
            // Lock mutex before running commands
            lock.lock();

            // Run command
            int error = luaL_loadbuffer(mLuaState, buffer.c_str(), buffer.length(), "line") ||
                lua_pcall(mLuaState, 0, 0, 0);

            // Unlock mutex
            lock.unlock();

            // Report errors
            if (error)
            {
                fprintf(stderr, "%s\n", lua_tostring(mLuaState, -1));
                lua_pop(mLuaState, 1);  /* pop error message from the stack */
            }

            std::cout << "> ";
        }
    }

    /* Require lua file */
    bool LuaEngine::require(const char* filename)
    {
        // Build command
        std::stringstream ss;
        ss << "require(\"";
        ss << filename;
        ss << "\")";

        // Run command
        return runCommand(ss.str().c_str());
    }

    /* Run lua file */
    bool LuaEngine::dofile(const char* filename)
    {
        // Build command
        std::stringstream ss;
        ss << "dofile(\"";
        ss << filename;
        ss << "\")";

        // Run command
        return runCommand(ss.str().c_str());
    }

    /* Run lua command */
    bool LuaEngine::runCommand(const char* command)
    {
        if (luaL_loadbuffer(mLuaState, command, strlen(command), "line") || lua_pcall(mLuaState, 0, 0, 0))
        {
            std::cerr << "Error running: " << command << std::endl <<
                lua_tostring(mLuaState, -1) << std::endl;

            lua_pop(mLuaState, 1);

            return false;
        }

        return true;
    }

    /* Set a global variable */
    void LuaEngine::setGlobal(const char* type, const char* name, void* ptr)
    {
        swig_type_info* typeinfo = SWIG_TypeQuery(mLuaState, type);

        if (typeinfo == nullptr)
        {
            std::cerr << "Invalid typeinfo" << std::endl;
        }

        SWIG_NewPointerObj(mLuaState, ptr, typeinfo, 0);
        lua_setglobal(mLuaState, name);
    }


}