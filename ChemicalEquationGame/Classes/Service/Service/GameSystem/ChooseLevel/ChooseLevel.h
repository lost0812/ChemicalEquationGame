#pragma once
#include "GeneralKit.h"
#include "define.h"
#include "cocos2d.h"
#include "iostream"
#include "vector"

class CChooseLevel : public SingleTon<CChooseLevel>
{
public:
  std::vector<CLevelData> m_Levels;
public:
  CChooseLevel();
  ~CChooseLevel();
  bool LoadConfig();
private:
};