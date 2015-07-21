#include "ChooseLevel.h"
#include "Header.h"

extern "C"{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

CChooseLevel::CChooseLevel()
{
  LoadConfig();
}

CChooseLevel::~CChooseLevel()
{

}

bool CChooseLevel::LoadConfig()
{
  if (LuaStack->LoadFile("stage.lua"))
    return false;
  lua_getglobal(LuaStack->m_Lua, "Level");
  int Idx = lua_gettop(LuaStack->m_Lua);
  lua_pushnil(LuaStack->m_Lua);
  while (lua_next(LuaStack->m_Lua, Idx))
  {
    CLevelData LevelData;
    lua_pushstring(LuaStack->m_Lua, "Level");
    lua_gettable(LuaStack->m_Lua, -2);
    LevelData.Level = lua_tonumber(LuaStack->m_Lua, -1);
    lua_pop(LuaStack->m_Lua, 1);

    lua_pushstring(LuaStack->m_Lua, "Type");
    lua_gettable(LuaStack->m_Lua, -2);
    LevelData.Type = lua_tonumber(LuaStack->m_Lua, -1);
    lua_pop(LuaStack->m_Lua, 1);

    lua_pushstring(LuaStack->m_Lua, "PointX");
    lua_gettable(LuaStack->m_Lua, -2);
    LevelData.PointX = lua_tonumber(LuaStack->m_Lua, -1);
    lua_pop(LuaStack->m_Lua, 1);

    lua_pushstring(LuaStack->m_Lua, "PointY");
    lua_gettable(LuaStack->m_Lua, -2);
    LevelData.PointY = lua_tonumber(LuaStack->m_Lua, -1);
    lua_pop(LuaStack->m_Lua, 1);

    lua_pop(LuaStack->m_Lua, 1);
    m_Levels.push_back(LevelData);
  }
  return true;
}
