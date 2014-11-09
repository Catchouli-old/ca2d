#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include <sstream>
#include <thread>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <swigluaruntime.h>

#include "luafuncs.h"
#include "Component.h"

#include "maths/Colour.h"
#include "maths/Maths.h"
#include "scripting/LuaPrompt.h"

int main(int argc, char** argv)
{
    bool running = true;

    DEFINE_COMPONENT("Transform", TransformComponent);
    DEFINE_COMPONENT("Colour", ColourComponent);

    addComponent("Transform");

    // Initialise lua state
    lua_State* luaState = luaL_newstate();

    // Open lua libs
    luaL_openlibs(luaState);

    // Load config file
    if (luaL_loadfile(luaState, "config.lua") || lua_pcall(luaState, 0, 0, 0))
    {
        error(luaState, "%s", lua_tostring(luaState, -1));
    }

    // Read values
    int width = getInt(luaState, "width");
    int height = getInt(luaState, "height");

    printf("width: %d, height: %d\nelements: %d\n", width, height, lua_gettop(luaState));

    ColourComponent col;
    col.r = 1;

    // Pass col to lua
    swig_type_info* typeinfo = SWIG_TypeQuery(luaState, "ColourComponent *");

    if (typeinfo == nullptr)
    {
        std::cerr << "Invalid typeinfo" << std::endl;
        system("pause");
        exit(1);
    }
    
    SWIG_NewPointerObj(luaState, &col, typeinfo, 0);
    lua_setglobal(luaState, "col");

    // Do lua prompt in separate thread
    std::thread luaThread(ca2d::luaprompt, luaState, running);

    // Main loop
    while (running)
    {
        // Wait 2 seconds
        std::chrono::milliseconds time(2000);
        std::this_thread::sleep_for(time);

        // Output colour value
        std::cout << "col.r == " << col.r << std::endl;
    }

    // Wait for threads to finish
    luaThread.join();

    // Clean up
    lua_close(luaState);

    system("pause");
}