#pragma once
#include "GeneralKit/GeneralKit.h"

class CGameSystem : public SingleTon<CGameSystem>
{
private:
  int m_GameState;                //��Ϸ״̬
public:
  CGameSystem();
  ~CGameSystem();
};