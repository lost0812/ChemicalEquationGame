#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
public:
  void menuStartGameCallback(cocos2d::Ref* pSender);
  void menuSaveDataCallback(cocos2d::Ref* pSender);
  void menuAchieveCallback(cocos2d::Ref* pSender);
  void menuSettingCallback(cocos2d::Ref* pSender);

//自定义
private:
  cocos2d::Sprite* m_SpriteBk;
  cocos2d::MenuItemImage* m_MenuStartGame;          //开始游戏
  cocos2d::MenuItemImage* m_MenuSaveData;           //数据统计
  cocos2d::MenuItemImage* m_MenuAchieve;            //功成名就
  cocos2d::MenuItemImage* m_MenuSetting;            //系统设置
public:

protected:

    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
