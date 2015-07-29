#include "cocos2d.h"
#include "iostream"
#include "vector"

USING_NS_CC;

class CLevelSecen : public Layer
{
private:
  std::vector<Sprite*> m_Sprites;
  Sprite* m_ChooseModelBk;
public:
  static Scene* createScene();
  virtual bool init(); 
protected:
  CREATE_FUNC(CLevelSecen);
};