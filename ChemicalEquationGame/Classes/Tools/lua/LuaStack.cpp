#include "LuaStack.h"

extern "C"{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
//#pragma comment(lib, "lua5.1.lib")

void CLuaStack::InitLuaStack()
{
  m_Lua=lua_open();
  luaopen_base(m_Lua);
  luaopen_table(m_Lua);
  luaopen_string(m_Lua);
  luaopen_math(m_Lua);
}

int CLuaStack::LoadFile( const char* file )
{
  return luaL_dofile(m_Lua, file);
}

CLuaStack::CLuaStack()
{
  InitLuaStack();
}

CLuaStack::~CLuaStack()
{
  SAFE_DELETE(m_Lua);
}
