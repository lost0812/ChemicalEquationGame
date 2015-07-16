#pragma once
#include "GeneralKit/GeneralKit.h"

class CGameSystem : public SingleTon<CGameSystem>
{
private:
  int m_GameState;                //сно╥в╢л╛
public:
  CGameSystem();
  ~CGameSystem();
};