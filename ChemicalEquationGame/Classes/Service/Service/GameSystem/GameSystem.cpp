#include "GameSystem.h"
#include "iostream"

CGameSystem::CGameSystem()
{

}

void CGameSystem::InitCtrClass()
{
  ChooseLevel = new CChooseLevel;
}

bool CGameSystem::LoadConfig()
{
  if (!ChooseLevel->LoadConfig())
  {
    return false;
  }
  return true;
}

CGameSystem::~CGameSystem()
{

}
