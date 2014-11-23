namespace ca2d
{
	class LuaReference;
}

// Allow lua values to be automatically converted to references
// by declaring a function with LuaReference as an argument
%typemap(in) ca2d::LuaReference
{
	// Copy value to top of stack
	lua_pushvalue(L, 1);

	// Register a reference for the value at the top of the stack
	$1 = LuaReference(luaL_ref(L, LUA_REGISTRYINDEX), L);
}