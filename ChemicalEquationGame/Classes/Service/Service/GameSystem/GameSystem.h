#pragma once
#include "GeneralKit.h"
#include "ChooseLevel/ChooseLevel.h"

enum GameState
{
	EGS_START_ON,
	EGS_CHOOSE_MODEL,
	EGS_MAX,
};
class CGameSystem : public SingleTon<CGameSystem>
{
private:
  int m_GameState;                //ÓÎÏ·×´Ì¬
public:
  //GameSystem ¿ØÖÆÀà
  CChooseLevel* ChooseLevel;
public:
	AUTOGETSET(int, m_GameState)
public:
  CGameSystem();
  void InitCtrClass();
  bool LoadConfig();
  ~CGameSystem();
};