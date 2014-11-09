#include "scripting/LuaPrompt.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>
#include <string.h>

namespace ca2d
{

    /* Runs lua prompt in stdin/stdout until running is false */
    void luaprompt(lua_State* luaState, bool& running)
    {
        char buff[256];

        // Interactive prompt
        while (running && fgets(buff, sizeof(buff), stdin) != NULL)
        {
            int error = luaL_loadbuffer(luaState, buff, strlen(buff), "line") ||
                lua_pcall(luaState, 0, 0, 0);

            if (error)
            {
                fprintf(stderr, "%s\n", lua_tostring(luaState, -1));
                lua_pop(luaState, 1);  /* pop error message from the stack */
            }
        }
    }

}