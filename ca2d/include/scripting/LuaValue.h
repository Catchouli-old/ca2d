#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <lua.hpp>

#include "LuaReference.h"

namespace ca2d
{
    /** Possible types for lua values. Tables, functions,
        userdata, and threads are stored as LuaReferences */
    enum class LuaValueType
    {
        NIL,
        NUMBER,
        STRING,
        BOOLEAN,
        TABLE,
        FUNCTION,
        USERDATA,
        THREAD,
        LIGHTUSERDATA
    };

    /** A generic lua value of type <type> */
    struct LuaValue
    {
        LuaValueType type;

        double number;
        std::string string;
        bool boolean;
        LuaReference reference;

        static LuaValue fromStack(lua_State* luaState, int idx);
    };

    inline LuaValue LuaValue::fromStack(lua_State* luaState, int idx)
    {
        LuaValue luaValue;
        luaValue.type = LuaValueType::NIL;

        // Convert result to LuaValue and add to vector
        switch (lua_type(luaState, idx))
        {

        case LUA_TNIL:
            lua_remove(luaState, idx);
            break;

        case LUA_TNUMBER:
            luaValue.type = LuaValueType::NUMBER;
            luaValue.number = lua_tonumber(luaState, idx);
            lua_remove(luaState, idx);
            break;

        case LUA_TSTRING:
            luaValue.type = LuaValueType::STRING;
            luaValue.string = std::string(lua_tostring(luaState, idx));
            lua_remove(luaState, idx);
            break;

        case LUA_TBOOLEAN:
            luaValue.type = LuaValueType::BOOLEAN;
            luaValue.boolean = lua_toboolean(luaState, idx) != 0;
            lua_remove(luaState, idx);
            break;

        case LUA_TTABLE:
            luaValue.type = LuaValueType::TABLE;
            lua_pushvalue(luaState, idx);
            luaValue.reference = LuaReference(luaL_ref(luaState, LUA_REGISTRYINDEX), luaState);
            lua_remove(luaState, idx);
            break;

        case LUA_TFUNCTION:
            luaValue.type = LuaValueType::FUNCTION;
            lua_pushvalue(luaState, idx);
            lua_remove(luaState, idx);
            luaValue.reference = LuaReference(luaL_ref(luaState, LUA_REGISTRYINDEX), luaState);
            break;

        case LUA_TUSERDATA:
            luaValue.type = LuaValueType::USERDATA;
            lua_pushvalue(luaState, idx);
            lua_remove(luaState, idx);
            luaValue.reference = LuaReference(luaL_ref(luaState, LUA_REGISTRYINDEX), luaState);
            break;

        case LUA_TTHREAD:
            luaValue.type = LuaValueType::THREAD;
            lua_pushvalue(luaState, idx);
            lua_remove(luaState, idx);
            luaValue.reference = LuaReference(luaL_ref(luaState, LUA_REGISTRYINDEX), luaState);
            break;

        case LUA_TLIGHTUSERDATA:
            luaValue.type = LuaValueType::LIGHTUSERDATA;
            lua_pushvalue(luaState, idx);
            lua_remove(luaState, idx);
            luaValue.reference = LuaReference(luaL_ref(luaState, LUA_REGISTRYINDEX), luaState);
            break;

        default:
            std::cerr << "Unknown lua type, returning nil" << std::endl;
            lua_remove(luaState, idx);
            break;

        }

        return luaValue;
    }
}