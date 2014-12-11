#pragma once

#include <iostream>
#include <vector>
#include <assert.h>
#include <lua.hpp>

namespace ca2d
{
    inline void passArgs(lua_State* luaState) {}

    template <typename T, typename... Args>
    void passArgs(lua_State* luaState, T arg, Args... args);

    template <typename T>
    void passArgs(lua_State* luaState, T arg);

    template <typename T>
    void passArg(lua_State* luaState, T arg);

    /* Call lua function */
    template <typename... Args>
    bool LuaEngine::callFunction(const char* name, Args... args)
    {
        int oldStackDepth = lua_gettop(mLuaState);

        // Get function
        lua_getglobal(mLuaState, name);

        // Push arguments to stack
        passArgs(mLuaState, args...);

        // Call function
        if (lua_pcall(mLuaState, sizeof...(args), 0, 0) != 0)
        {
            std::cerr << "Error running function `" << name << "':" <<
                lua_tostring(mLuaState, -1) << std::endl;

            // Pop error
            lua_pop(mLuaState, -1);

            lua_settop(mLuaState, oldStackDepth);
            return false;
        }

        lua_settop(mLuaState, oldStackDepth);
        return true;
    }

    /* Call lua function expecting return values */
    template <typename... Args>
    bool LuaEngine::callFunction(const char* name, std::vector<LuaValue>& ret, Args... args)
    {
        int oldStackDepth = lua_gettop(mLuaState);

        // Store old stack length
        int stackLength = lua_gettop(mLuaState);

        // Get function
        lua_getglobal(mLuaState, name);

        // Push arguments to stack
        passArgs(mLuaState, args...);

        // Call function
        if (lua_pcall(mLuaState, sizeof...(args), LUA_MULTRET, 0) != 0)
        {
            std::cerr << "Error running function `" << name << "':" <<
                lua_tostring(mLuaState, -1) << std::endl;
            
            // Pop error
            lua_pop(mLuaState, -1);

            lua_settop(mLuaState, oldStackDepth);
            return false;
        }

        // Get arguments
        int resCount = lua_gettop(mLuaState) - stackLength;

        for (int i = 0; i < resCount; ++i)
        {
            // Push into vector
            ret.push_back(LuaValue::fromStack(mLuaState, -1));
        }

        // Reverse vector
        std::reverse(ret.begin(), ret.end());

        lua_settop(mLuaState, oldStackDepth);
        return true;
    }

    /* Call lua function */
    template <typename... Args>
    bool LuaEngine::callFunction(LuaReference obj,
        const char* name, Args... args)
    {
        int oldStackDepth = lua_gettop(mLuaState);

        // Put obj on stack
        lua_rawgeti(mLuaState, LUA_REGISTRYINDEX, obj.getReference());

        // Get function
        lua_pushstring(mLuaState, name);

        lua_gettable(mLuaState, -2);

        // Push arguments to stack
        int t = lua_gettop(mLuaState);
        passArgs(mLuaState, args...);
        lua_settop(mLuaState, t + 1);

        // Call function
        if (lua_pcall(mLuaState, 1, 0, 0) != 0)
        {
            std::cerr << "Error running function `" << name << "':" <<
                lua_tostring(mLuaState, -1) << std::endl;

            // Pop error
            lua_pop(mLuaState, -1);

            lua_settop(mLuaState, oldStackDepth);
            return false;
        }

        lua_settop(mLuaState, oldStackDepth);
        return true;
    }

    /* Call lua function expecting return values */
    template <typename... Args>
    bool LuaEngine::callFunction(LuaReference obj,
        const char* name, std::vector<LuaValue>& ret, Args... args)
    {
        int oldStackDepth = lua_gettop(mLuaState);

        // Store old stack length
        int stackLength = lua_gettop(mLuaState);

        // Put obj on stack
        lua_rawgeti(mLuaState, LUA_REGISTRYINDEX, obj.getReference());

        // Get function
        lua_pushstring(mLuaState, name);
        lua_gettable(mLuaState, -2);
        lua_remove(mLuaState, -2);

        // Push arguments to stack
        passArgs(mLuaState, args...);

        // Call function
        if (lua_pcall(mLuaState, sizeof...(args), LUA_MULTRET, 0) != 0)
        {
            std::cerr << "Error running function obj.`" << name << "':" <<
                lua_tostring(mLuaState, -1) << std::endl;

            // Pop error
            lua_pop(mLuaState, -1);

            lua_settop(mLuaState, oldStackDepth);
            return false;
        }

        // Get arguments
        int resCount = lua_gettop(mLuaState) - stackLength;

        for (int i = 0; i < resCount; ++i)
        {
            // Push into vector
            ret.push_back(LuaValue::fromStack(mLuaState, -1));
        }

        // Reverse vector
        std::reverse(ret.begin(), ret.end());

        lua_settop(mLuaState, oldStackDepth);
        return true;
    }

    /* Pass a list of arguments to lua */
    template <typename T, typename... Args>
    void passArgs(lua_State* luaState, T arg, Args... args)
    {
        // Pass arg and then unpack the rest of args
        passArg(luaState, arg);
        passArgs(luaState, args...);
    }

    /* Pass a list of arguments to lua (last argument) */
    template <typename T>
    void passArgs(lua_State* luaState, T arg)
    {
        // Pass final arg
        passArg(luaState, arg);
    }
    
    /* Pass an argument to lua (int override) */
    template <>
    inline void passArg(lua_State* luaState, int arg)
    {
        lua_pushnumber(luaState, (lua_Number)arg);
    }

    /* Pass an argument to lua (float override) */
    template <>
    inline void passArg(lua_State* luaState, float arg)
    {
        lua_pushnumber(luaState, (lua_Number)arg);
    }

    /* Pass an argument to lua (double override) */
    template <>
    inline void passArg(lua_State* luaState, double arg)
    {
        lua_pushnumber(luaState, (lua_Number)arg);
    }

    /* Pass an argument to lua (string override) */
    template <>
    inline void passArg(lua_State* luaState, const char* arg)
    {
        lua_pushstring(luaState, arg);
    }

    /* Pass an argument to lua (nil override) */
    template <>
    inline void passArg(lua_State* luaState, nullptr_t)
    {
        lua_pushnil(luaState);
    }

    /* Pass an argument to lua (bool override) */
    template <>
    inline void passArg(lua_State* luaState, bool arg)
    {
        lua_pushboolean(luaState, (int)arg);
    }

    /* Pass an argument to lua (reference override) */
    template <>
    inline void passArg(lua_State* luaState, LuaReference arg)
    {
        lua_rawgeti(luaState, LUA_REGISTRYINDEX, arg.getReference());
    }
}