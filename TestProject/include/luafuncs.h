#pragma once

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdlib.h>
#include <assert.h>

void test();

inline void error(lua_State *L, const char *fmt, ...)
{
    va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    fprintf(stderr, "\n");
    va_end(argp);
    lua_close(L);
    exit(1);
}

inline int getInt(lua_State* luaState, const char* name)
{
    lua_getglobal(luaState, name);

    if (!lua_isnumber(luaState, -1))
        error(luaState, "not a number");

    int value = (int)lua_tonumber(luaState, -1);

    lua_remove(luaState, -1);

    return value;
}

template <typename T>
void pushVal(lua_State* luaState, T val);

template <>
inline void pushVal(lua_State* luaState, int val)
{
    // Push value
    lua_pushnumber(luaState, (lua_Number)val);
}

inline void pushVals(lua_State* luaState, int& argCount) {}

template <typename T, typename... Others>
inline void pushVals(lua_State* luaState, int& argCount, T val, Others... rest)
{
    // Push value onto lua stack
    pushVal(luaState, val);

    // Increment arg counter
    argCount++;

    // Push the rest of the values
    pushVals(luaState, argCount, rest...);
}

template <typename T>
T getResult(lua_State* luaState);

template <>
inline int getResult(lua_State* luaState)
{
    if (!lua_isnumber(luaState, -1))
    {
        error(luaState, "wrong result type");
    }

    int result = (int)lua_tonumber(luaState, -1);

    lua_pop(luaState, 1);

    return result;
}

template <typename Ret, typename... Args>
inline Ret luaCall(lua_State* luaState, const char* func, Args... args)
{
    int argCount = 0;

    // Store stack depth
    int stackDepth = lua_gettop(luaState);

    // Get function
    lua_getglobal(luaState, func);

    // Push arguments onto stack
    pushVals(luaState, argCount, args...);

    // Do call
    std::cout << "Calling function with " << argCount << " arguments\n";

    if (lua_pcall(luaState, 2, 1, 0) != 0)
    {
        error(luaState, "lua error: %s", lua_tostring(luaState, -1));
    }

    // Retrieve result
    Ret result = getResult<Ret>(luaState);

    // Check stack depth is the same as at the start
    assert(stackDepth == lua_gettop(luaState));

    return result;
}