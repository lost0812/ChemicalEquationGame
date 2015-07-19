#pragma once

#include "cocos2d.h"

class CChooseModel : public cocos2d::Layer
{
private:
  cocos2d::Sprite* m_ChooseModelBk;
  cocos2d::MenuItemImage* m_MenuCheckPoint;         //关卡模式
  cocos2d::MenuItemImage* m_MenuLearn;              //学习模式
  cocos2d::MenuItemImage* m_MenuDekaron;            //挑战模式
  cocos2d::MenuItemImage* m_MenuBack;               //返回
public:
  void menuCheckPointCallback(cocos2d::Ref* pSender);
  void menuLearnCallback(cocos2d::Ref* pSender);
  void menuDekaronCallback(cocos2d::Ref* pSender);
  void menuBackCallback(cocos2d::Ref* pSender);
public:
  static cocos2d::Scene* createScene();
  virtual bool init(); 
protected:
  CREATE_FUNC(CChooseModel);
};