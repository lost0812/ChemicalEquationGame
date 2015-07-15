#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemImage* closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    Menu* menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    LabelTTF* label = LabelTTF::create("欢迎来到化学方程俱乐部", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    m_SpriteBk = Sprite::create("Sta_Bk.png");
    m_SpriteBk->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(m_SpriteBk, 0);
    
    MenuItemImage* m_MenuStartGame = MenuItemImage::create(
      "Sta_StartGame1.png",
      "Sta_StartGame2.png",
      CC_CALLBACK_1(HelloWorld::menuStartGameCallback, this));
    m_MenuStartGame->setPosition(Vec2(120 ,240));
    Menu* menuStart = Menu::create(m_MenuStartGame, NULL);
    menuStart->setPosition(Vec2::ZERO);
    this->addChild(menuStart, 1);

    MenuItemImage* m_MenuSaveData = MenuItemImage::create(
      "Sta_SaveData1.png",
      "Sta_SaveData2.png",
      CC_CALLBACK_1(HelloWorld::menuSaveDataCallback, this));
    m_MenuSaveData->setPosition(Vec2(300 ,250));
    Menu* menuData = Menu::create(m_MenuSaveData, NULL);
    menuData->setPosition(Vec2::ZERO);
    this->addChild(menuData, 1);

    MenuItemImage* m_MenuAchieve = MenuItemImage::create(
      "Sta_Achieve1.png",
      "Sta_Achieve2.png",
      CC_CALLBACK_1(HelloWorld::menuAchieveCallback, this));
    m_MenuAchieve->setPosition(Vec2(470 ,220));
    Menu* menuAchieve = Menu::create(m_MenuAchieve, NULL);
    menuAchieve->setPosition(Vec2::ZERO);
    this->addChild(menuAchieve, 1);

    MenuItemImage* m_MenuSetting = MenuItemImage::create(
      "Sta_Setting1.png",
      "Sta_Setting2.png",
      CC_CALLBACK_1(HelloWorld::menuSettingCallback, this));
    m_MenuSetting->setPosition(Vec2(40 ,40));
    Menu* menuSetting = Menu::create(m_MenuSetting, NULL);
    menuSetting->setPosition(Vec2::ZERO);
    this->addChild(menuSetting, 1);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuStartGameCallback( cocos2d::Ref* pSender )
{

}

void HelloWorld::menuSaveDataCallback( cocos2d::Ref* pSender )
{

}

void HelloWorld::menuAchieveCallback( cocos2d::Ref* pSender )
{

}

void HelloWorld::menuSettingCallback( cocos2d::Ref* pSender )
{

}
