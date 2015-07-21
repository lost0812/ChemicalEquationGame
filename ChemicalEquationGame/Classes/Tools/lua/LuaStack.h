#pragma once
#include "GeneralKit.h"

struct lua_State;
class CLuaStack : public SingleTon<CLuaStack>
{
public:
  lua_State* m_Lua;
public:
  void InitLuaStack();
  int LoadFile(const char* file);
public:
  CLuaStack();
  ~CLuaStack();
};