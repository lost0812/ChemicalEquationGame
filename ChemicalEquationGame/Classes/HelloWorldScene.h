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

//�Զ���
private:
  cocos2d::Sprite* m_SpriteBk;
  cocos2d::MenuItemImage* m_MenuStartGame;          //��ʼ��Ϸ
  cocos2d::MenuItemImage* m_MenuSaveData;           //����ͳ��
  cocos2d::MenuItemImage* m_MenuAchieve;            //��������
  cocos2d::MenuItemImage* m_MenuSetting;            //ϵͳ����
public:

protected:

    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
