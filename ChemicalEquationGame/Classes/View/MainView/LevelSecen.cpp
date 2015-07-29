#include "UI.h"
#include "header.h"
USING_NS_CC;

Scene* CLevelSecen::createScene()
{
  Scene* scene = Scene::create();
  Layer* layer = CLevelSecen::create();
  scene->addChild(layer);
  return scene;
}

bool CLevelSecen::init()
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
  CChooseLevel* LevelData = GameMgr->ChooseLevel;
  int Size = LevelData->m_Levels.size();
  m_Sprites.clear();
  for (int i = 0; i < Size; i++)
  {
    char* fileName = "Level1.png";
    Sprite* sprite = Sprite::create(fileName);
    sprite->setPosition(Vec2(LevelData->m_Levels[i].PointX, LevelData->m_Levels[i].PointY));
    sprite->setTag(i);   //Tag作为触摸获取逻辑数据
    this->addChild(sprite);
    m_Sprites.push_back(sprite);
  }
  return true;
}
