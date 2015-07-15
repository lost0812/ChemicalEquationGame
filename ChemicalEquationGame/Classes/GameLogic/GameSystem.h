#pragma once

class CGameSystem /*: public SingleTon<CGameSystem>*/
{
private:
  int m_GameState;                //сно╥в╢л╛
private:
  static CGameSystem* m_Instace;  //
  CGameSystem();
public:
  CGameSystem* GetInstance();
  virtual ~CGameSystem();
};