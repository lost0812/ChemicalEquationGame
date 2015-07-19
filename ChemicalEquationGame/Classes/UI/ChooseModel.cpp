#include "UI.h"
#include "header.h"
USING_NS_CC;

Scene* CChooseModel::createScene()
{
  Scene* scene = Scene::create();
  Layer* layer = CChooseModel::create();
  scene->addChild(layer);
  return scene;
}

bool CChooseModel::init()
{
  if ( !Layer::init() )
  {
    return false;
  }
  Size visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  m_ChooseModelBk = Sprite::create("ChoosePatternpng.png");
  m_ChooseModelBk->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
  this->addChild(m_ChooseModelBk, 0);

  MenuItemImage* m_MenuCheckPoint = MenuItemImage::create(
    "CheckPoint1.png",
    "CheckPoint2.png",
    CC_CALLBACK_1(CChooseModel::menuCheckPointCallback, this));
  m_MenuCheckPoint->setPosition(Vec2(280 ,280));
  Menu* menuCheck = Menu::create(m_MenuCheckPoint, NULL);
  menuCheck->setPosition(Vec2::ZERO);
  this->addChild(menuCheck, 1);

  MenuItemImage* m_MenuLearn = MenuItemImage::create(
    "Learn1.png",
    "Learn2.png",
    CC_CALLBACK_1(CChooseModel::menuLearnCallback, this));
  m_MenuLearn->setPosition(Vec2(220 ,190));
  Menu* menuLearn = Menu::create(m_MenuLearn, NULL);
  menuLearn->setPosition(Vec2::ZERO);
  this->addChild(menuLearn, 2);

  MenuItemImage* m_MenuDekaron = MenuItemImage::create(
    "Dekaron1.png",
    "Dekaron2.png",
    CC_CALLBACK_1(CChooseModel::menuDekaronCallback, this));
  m_MenuDekaron->setPosition(Vec2(160 ,100));
  Menu* menuDekaron = Menu::create(m_MenuDekaron, NULL);
  menuDekaron->setPosition(Vec2::ZERO);
  this->addChild(menuDekaron, 3);

  MenuItemImage* m_MenuBack = MenuItemImage::create(
    "Back1.png",
    "Back2.png",
    CC_CALLBACK_1(CChooseModel::menuBackCallback, this));
  m_MenuBack->setPosition(Vec2(440 ,80));
  Menu* menuBack = Menu::create(m_MenuBack, NULL);
  menuBack->setPosition(Vec2::ZERO);
  this->addChild(menuBack, 4);

}

void CChooseModel::menuCheckPointCallback( cocos2d::Ref* pSender )
{

}

void CChooseModel::menuLearnCallback( cocos2d::Ref* pSender )
{

}

void CChooseModel::menuDekaronCallback( cocos2d::Ref* pSender )
{

}

void CChooseModel::menuBackCallback( cocos2d::Ref* pSender )
{
  CCTransitionScene * reScene = NULL;
  CCScene * s = HelloWorld::createScene();
  float t = 1.2f;
  reScene = CCTransitionProgressOutIn::create(t, s);
  CCDirector::sharedDirector()->replaceScene(reScene);
  GameMgr->Setm_GameState(EGS_START_ON);
}
