#pragma once
#include "GeneralKit.h"
//#include "Level.h"

enum GameState
{
	EGS_START_ON,
	EGS_CHOOSE_MODEL,
	EGS_MAX,
};
class CGameSystem : public SingleTon<CGameSystem>
{
private:
  int m_GameState;                //сно╥в╢л╛
public:
	AUTOGETSET(int, m_GameState)
public:
  CGameSystem();
  ~CGameSystem();
};