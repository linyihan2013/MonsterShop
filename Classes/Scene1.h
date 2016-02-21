#include "cocos2d.h"

class Scene1 : public cocos2d::Scene {
    public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Scene1);
};