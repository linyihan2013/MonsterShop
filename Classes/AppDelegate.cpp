#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MyClassReader.h"
#include "ui/UIImageView.h"
#include "ui/UIHelper.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

#define userDefault UserDefault::getInstance()
using namespace cocostudio::timeline;
using namespace cocos2d::ui;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    
    GLView::setGLContextAttrs(glContextAttrs);
} 

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("MonsterShop");
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(1920, 1080, ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    CSLoader* instance = CSLoader::getInstance();
    instance->registReaderObject("MyClassReader", (ObjectFactory::Instance)MyClassReader::getInstance);
    // run
    setUpgradeCondition();
    if (userDefault->getBoolForKey("first_time", true)){
        userDefault->setBoolForKey("first_time", false);
        /* auto rootNode = CSLoader::createNode("Scene1_1.csb");
        scene1->addChild(rootNode);
        auto skip = rootNode->getChildByName("Button_1");*/
    }
    
    Scene *scene = HelloWorld::createScene();
    auto rootNode = CSLoader::createNode("Scene3.csb");
    ActionTimeline* action = CSLoader::createTimeline("Scene3.csb");
    scene->addChild(rootNode);
    
    rootNode->runAction(action);
    action->gotoFrameAndPlay(0, 995, true);
    director->runWithScene(scene);
    rootNode->schedule(SEL_SCHEDULE(&AppDelegate::BG_float), 0.02, CC_REPEAT_FOREVER, 0);

    return true;
}



void AppDelegate::BG_float(float d) {
    ImageView* image = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*)this, "Image_1"));
    ImageView* image1 = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*)this, "Image_1_0"));
    image->setPositionX(image->getPositionX() + 12.5);
    image1->setPositionX(image1->getPositionX() + 12.5);

    if (image1->getPositionX() <= 0 && image1->getPositionX() > -12.5) {
        image->setPositionX(image1->getPositionX() - 4995);
    }
    if (image->getPositionX() <= 0 && image->getPositionX() > -12.5) {
        image1->setPositionX(image->getPositionX() - 4995);
    }
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::setUpgradeCondition() {
    userDefault->setIntegerForKey("needExp_1", 10);
    userDefault->setIntegerForKey("needExp_2", 20);
    userDefault->setIntegerForKey("needExp_3", 30);
    userDefault->setIntegerForKey("needExp_4", 40);

    userDefault->setIntegerForKey("needExp_5", 50);
    userDefault->setIntegerForKey("needExp_6", 60);
    userDefault->setIntegerForKey("needExp_7", 70);
    userDefault->setIntegerForKey("needExp_8", 80);

    userDefault->setIntegerForKey("needExp_9", 90);
    userDefault->setIntegerForKey("needExp_10", 1000);
    userDefault->setIntegerForKey("needExp_11", 1100);
    userDefault->setIntegerForKey("needExp_12", 1200);

    userDefault->setIntegerForKey("needExp_13", 1300);
    userDefault->setIntegerForKey("needExp_14", 1400);
    userDefault->setIntegerForKey("needExp_15", 1500);
    userDefault->setIntegerForKey("needExp_16", 1600);

    userDefault->setIntegerForKey("needExp_17", 1700);
    userDefault->setIntegerForKey("needExp_18", 1800);
    userDefault->setIntegerForKey("needExp_19", 1900);
    userDefault->setIntegerForKey("needExp_20", 2000);

    userDefault->setStringForKey("customeName_1_1", "baize");
    userDefault->setStringForKey("customeName_1_2", "bianfu");
    userDefault->setStringForKey("customeName_1_3", "caomao");
    userDefault->setStringForKey("customeName_1_4", "fenghuang");
    userDefault->setStringForKey("customeName_1_5", "guiche");
    userDefault->setStringForKey("customeName_1_6", "guihuo");

    userDefault->setStringForKey("customeName_2_1", "haishe");
    userDefault->setStringForKey("customeName_2_2", "jiangshi");
    userDefault->setStringForKey("customeName_2_3", "jiujiu");
    userDefault->setStringForKey("customeName_2_4", "mao");
    userDefault->setStringForKey("customeName_2_5", "mianju");
    userDefault->setStringForKey("customeName_2_6", "zongzi");

    userDefault->setStringForKey("customeName_3_1", "mubei");
    userDefault->setStringForKey("customeName_3_2", "shui");
    userDefault->setStringForKey("customeName_3_3", "suanyu");
    userDefault->setStringForKey("customeName_3_4", "xuanwu");
    userDefault->setStringForKey("customeName_3_5", "yingzhao");
    userDefault->setStringForKey("customeName_3_6", "youling");

    userDefault->setStringForKey("customeName_1_1_1", "baizezuo");
    userDefault->setStringForKey("customeName_1_2_1", "bianfuz");
    userDefault->setStringForKey("customeName_1_3_1", "caomaoz");
    userDefault->setStringForKey("customeName_1_4_1", "fenghuangzuo");
    userDefault->setStringForKey("customeName_1_5_1", "guichez");
    userDefault->setStringForKey("customeName_1_6_1", "guihuozuo");

    userDefault->setStringForKey("customeName_2_1_1", "haishez");
    userDefault->setStringForKey("customeName_2_2_1", "jiangshizuo");
    userDefault->setStringForKey("customeName_2_3_1", "jiujiuz");
    userDefault->setStringForKey("customeName_2_4_1", "maozuo");
    userDefault->setStringForKey("customeName_2_5_1", "mianjuz");
    userDefault->setStringForKey("customeName_2_6_1", "zongzizuo");

    userDefault->setStringForKey("customeName_3_1_1", "mubeiz");
    userDefault->setStringForKey("customeName_3_2_1", "shuiz");
    userDefault->setStringForKey("customeName_3_3_1", "suanyuzuo");
    userDefault->setStringForKey("customeName_3_4_1", "xuanwuzuo");
    userDefault->setStringForKey("customeName_3_5_1", "yingzhaoz");
    userDefault->setStringForKey("customeName_3_6_1", "youlingz");

    userDefault->setIntegerForKey("customeFrames_1_1", 15);
    userDefault->setIntegerForKey("customeFrames_1_2", 12);
    userDefault->setIntegerForKey("customeFrames_1_3", 16);
    userDefault->setIntegerForKey("customeFrames_1_4", 8);
    userDefault->setIntegerForKey("customeFrames_1_5", 12);
    userDefault->setIntegerForKey("customeFrames_1_6", 11);

    userDefault->setIntegerForKey("customeFrames_2_1", 11);
    userDefault->setIntegerForKey("customeFrames_2_2", 16);
    userDefault->setIntegerForKey("customeFrames_2_3", 14);
    userDefault->setIntegerForKey("customeFrames_2_4", 13);
    userDefault->setIntegerForKey("customeFrames_2_5", 16);
    userDefault->setIntegerForKey("customeFrames_2_6", 14);

    userDefault->setIntegerForKey("customeFrames_3_1", 14);
    userDefault->setIntegerForKey("customeFrames_3_2", 13);
    userDefault->setIntegerForKey("customeFrames_3_3", 10);
    userDefault->setIntegerForKey("customeFrames_3_4", 12);
    userDefault->setIntegerForKey("customeFrames_3_5", 19);
    userDefault->setIntegerForKey("customeFrames_3_6", 19);

    userDefault->setDoubleForKey("customeScale_1_1", 2);
    userDefault->setDoubleForKey("customeScale_1_2", 2.5);
    userDefault->setDoubleForKey("customeScale_1_3", 1.5);
    userDefault->setDoubleForKey("customeScale_1_4", 1.5);
    userDefault->setDoubleForKey("customeScale_1_5", 1);
    userDefault->setDoubleForKey("customeScale_1_6", 1.25);

    userDefault->setDoubleForKey("customeScale_2_1", 1.8);
    userDefault->setDoubleForKey("customeScale_2_2", 2);
    userDefault->setDoubleForKey("customeScale_2_3", 1);
    userDefault->setDoubleForKey("customeScale_2_4", 2);
    userDefault->setDoubleForKey("customeScale_2_5", 1.3);
    userDefault->setDoubleForKey("customeScale_2_6", 1.4);

    userDefault->setDoubleForKey("customeScale_3_1", 1.75);
    userDefault->setDoubleForKey("customeScale_3_2", 1);
    userDefault->setDoubleForKey("customeScale_3_3", 2);
    userDefault->setDoubleForKey("customeScale_3_4", 1.8);
    userDefault->setDoubleForKey("customeScale_3_5", 1.3);
    userDefault->setDoubleForKey("customeScale_3_6", 0.8);

    userDefault->setIntegerForKey("customeNeeds_1", 312);
    userDefault->setIntegerForKey("customeNeeds_2", 423);
    userDefault->setIntegerForKey("customeNeeds_3", 134);
    userDefault->setIntegerForKey("customeNeeds_4", 241);
    userDefault->setIntegerForKey("customeNeeds_5", 413);
    userDefault->setIntegerForKey("customeNeeds_6", 124);

    userDefault->setIntegerForKey("goodPrice_1_1", 100);
    userDefault->setIntegerForKey("goodPrice_1_2", 200);
    userDefault->setIntegerForKey("goodPrice_1_3", 300);
    userDefault->setIntegerForKey("goodPrice_1_4", 400);

    userDefault->setIntegerForKey("goodPrice_2_1", 500);
    userDefault->setIntegerForKey("goodPrice_2_2", 600);
    userDefault->setIntegerForKey("goodPrice_2_3", 800);
    userDefault->setIntegerForKey("goodPrice_2_4", 1000);

    userDefault->setIntegerForKey("goodPrice_3_1", 1100);
    userDefault->setIntegerForKey("goodPrice_3_2", 1200);
    userDefault->setIntegerForKey("goodPrice_3_3", 1400);
    userDefault->setIntegerForKey("goodPrice_3_4", 1600);

    userDefault->setIntegerForKey("goodProfit_1_1", 5);
    userDefault->setIntegerForKey("goodProfit_1_2", 10);
    userDefault->setIntegerForKey("goodProfit_1_3", 15);
    userDefault->setIntegerForKey("goodProfit_1_4", 20);

    userDefault->setIntegerForKey("goodProfit_2_1", 25);
    userDefault->setIntegerForKey("goodProfit_2_2", 30);
    userDefault->setIntegerForKey("goodProfit_2_3", 35);
    userDefault->setIntegerForKey("goodProfit_2_4", 40);

    userDefault->setIntegerForKey("goodProfit_3_1", 45);
    userDefault->setIntegerForKey("goodProfit_3_2", 50);
    userDefault->setIntegerForKey("goodProfit_3_3", 55);
    userDefault->setIntegerForKey("goodProfit_3_4", 60);

    userDefault->setIntegerForKey("goodTime_1_1", 5);
    userDefault->setIntegerForKey("goodTime_1_2", 5);
    userDefault->setIntegerForKey("goodTime_1_3", 5);
    userDefault->setIntegerForKey("goodTime_1_4", 5);

    userDefault->setIntegerForKey("goodTime_2_1", 7);
    userDefault->setIntegerForKey("goodTime_2_2", 7);
    userDefault->setIntegerForKey("goodTime_2_3", 7);
    userDefault->setIntegerForKey("goodTime_2_4", 7);

    userDefault->setIntegerForKey("goodTime_3_1", 10);
    userDefault->setIntegerForKey("goodTime_3_2", 10);
    userDefault->setIntegerForKey("goodTime_3_3", 10);
    userDefault->setIntegerForKey("goodTime_3_4", 10);

    userDefault->setIntegerForKey("goodUnlocked_1_3", 1000);
    userDefault->setIntegerForKey("goodUnlocked_1_4", 1500);
    userDefault->setIntegerForKey("goodUnlocked_2_3", 2000);
    userDefault->setIntegerForKey("goodUnlocked_2_4", 2500);
    userDefault->setIntegerForKey("goodUnlocked_3_3", 3000);
    userDefault->setIntegerForKey("goodUnlocked_3_4", 3500);

    userDefault->flush();
}
