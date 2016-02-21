#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

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

    return true;
}

void HelloWorld::onFrameEvent(Frame* frame) {
    EventFrame* evnt = dynamic_cast<EventFrame*>(frame);
    if (!evnt)
        return;
    log("hehehe");
    std::string str = evnt->getEvent();
    if (str == "xxoo")
    {
        log("come on baby");
    }
}
