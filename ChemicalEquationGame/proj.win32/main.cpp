#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"
#include "Header.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    GameMgr->InitCtrClass();
    GameMgr->LoadConfig();  //��ʼ�����õ�
    AppDelegate app;
    return Application::getInstance()->run();
}
