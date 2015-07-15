#include "GameSystem.h"
#include "iostream"

CGameSystem* CGameSystem::m_Instace = NULL;

CGameSystem* CGameSystem::GetInstance()
{
  if (!m_Instace)
  {
    m_Instace = new CGameSystem;
  }
  return m_Instace;
}

CGameSystem::~CGameSystem()
{

}

CGameSystem::CGameSystem()
{

}
