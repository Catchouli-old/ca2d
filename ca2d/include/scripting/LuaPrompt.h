#pragma once

struct lua_State;

namespace ca2d
{

    /* Runs lua prompt in stdin/stdout until running is false */
    void luaprompt(lua_State* luaState, bool& running);

}