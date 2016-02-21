#include "MyClass.h"
#include "ui/UIText.h"
#include "ui/UIHelper.h"
#include "ui/UITextBMFont.h"
#include "ui/UIPageView.h"
#include "ui/UITextAtlas.h"
#include "ui/CocosGUI.h"
#include "MyIconv.h"
#include <ctime>
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

#define userDefault UserDefault::getInstance()

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

static int call = 0;
static Node* root = NULL;
static Node* panel1 = NULL;
static Node* panel2 = NULL;
static Node* panel3 = NULL;
static int money1 = 0;
static int money2 = 0;
static int money3 = 0;
static bool satis1 = false;
static bool satis2 = false;
static bool satis3 = false;
static int curHun = 0;
static int maxHun = 20;
static int po = 1;
static bool buyEnable = true;
static bool groupEnable = true;
static int book_index = 1;
Layer* layer2;

Ref* sender1;
Ref* sender2;

MyClass::MyClass() {}

Widget::ccWidgetTouchCallback MyClass::onLocateTouchCallback(const string &callBackName) {
    if (callBackName == "onTouch") {
        return CC_CALLBACK_2(MyClass::onTouch, this);
    } else if (callBackName == "ToBuild1") {
        return CC_CALLBACK_2(MyClass::ToBuild1, this);
    } else if (callBackName == "ToBuild2") {
        return CC_CALLBACK_2(MyClass::ToBuild2, this);
    } else if (callBackName == "ToBuild3") {
        return CC_CALLBACK_2(MyClass::ToBuild3, this);
    } else if (callBackName == "Check") {
        return CC_CALLBACK_2(MyClass::Check, this);
    }
    return nullptr;
}

Widget::ccWidgetClickCallback MyClass::onLocateClickCallback(const string &callBackName) {
    if (callBackName == "ReturnToGame") {
        return CC_CALLBACK_1(MyClass::ReturnToGame, this);
    } else if (callBackName == "AboutUs") {
        return CC_CALLBACK_1(MyClass::AboutUs, this);
    } else if (callBackName == "EnterGame") {
        return CC_CALLBACK_1(MyClass::EnterGame, this);
    } else if (callBackName == "Quit") {
        return CC_CALLBACK_1(MyClass::Quit, this);
    } else if (callBackName == "StartGame") {
        return CC_CALLBACK_1(MyClass::StartGame, this);
    } else if (callBackName == "StartGame1") {
        return CC_CALLBACK_1(MyClass::StartGame1, this);
    } else if (callBackName == "EnterGame1") {
        return CC_CALLBACK_1(MyClass::EnterGame1, this);
    } else if (callBackName == "BGM") {
        return CC_CALLBACK_1(MyClass::BGM, this);
    } else if (callBackName == "SE") {
        return CC_CALLBACK_1(MyClass::SE, this);
    } else if (callBackName == "ToRelations") {
        return CC_CALLBACK_1(MyClass::ToRelations, this);
    } else if (callBackName == "ToDic") {
        return CC_CALLBACK_1(MyClass::ToDic, this);
    } else if (callBackName == "ToBook") {
        return CC_CALLBACK_1(MyClass::ToBook, this);
    } else if (callBackName == "GroupBuy") {
        return CC_CALLBACK_1(MyClass::GroupBuy, this);
    }
    return nullptr;
}

void MyClass::BGM(cocos2d::Ref* sender) {
    if (userDefault->getBoolForKey("bgm1", true)) {
        userDefault->setBoolForKey("bgm1", false);
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    } else {
        userDefault->setBoolForKey("bgm1", true);
        SimpleAudioEngine::getInstance()->playBackgroundMusic("mp3/BGM.mp3", true);
    }
}

void MyClass::SE(cocos2d::Ref* sender) {
    if (userDefault->getBoolForKey("bgm2", true)) {
        userDefault->setBoolForKey("bgm2", false);
    } else {
        userDefault->setBoolForKey("bgm2", true);
        SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
    }
}

Widget::ccWidgetEventCallback MyClass::onLocateEventCallback(const string &callBackName) {
    if (callBackName == "onEvent") {
        return CC_CALLBACK_2(MyClass::onEvent, this);
    }
    return nullptr;
}

bool IConvConvert(const char *from_charset, const char *to_charset, const char *inbuf, int inlen, char *outbuf, int outlen) {
    iconv_t cd = iconv_open(to_charset, from_charset);
    if (cd == 0) return false;
    const char **pin = &inbuf;
    char **pout = &outbuf;
    memset(outbuf, 0, outlen);
    size_t ret = iconv(cd, pin, (size_t *) &inlen, pout, (size_t *) &outlen);
    iconv_close(cd);
    return ret == (size_t) (-1) ? false : true;
}

std::string IConvConvert_GBKToUTF8(const std::string& str) {
    const char* textIn = str.c_str();
    char textOut[256];
    bool ret = IConvConvert("gb2312", "utf-8", textIn, strlen(textIn), textOut, 256);
    return ret ? string(textOut) : string();
}

void MyClass::onTouch(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type) {
}

void MyClass::lbar1(float t) {
    int index = dynamic_cast<PageView*>(getChildByName("PageView_1"))->getCurPageIndex() + 1;
    ImageView* image1 = dynamic_cast<ImageView*>(getChildByName("Image_7"));
    ImageView* image2 = dynamic_cast<ImageView*>(getChildByName("Image_8"));
    ImageView* image3 = dynamic_cast<ImageView*>(getChildByName("Image_9"));

    if (index == 1) {
        image1->setVisible(true);
        image2->setVisible(false);
        image3->setVisible(false);
    } else if (index == 2) {
        image1->setVisible(false);
        image2->setVisible(true);
        image3->setVisible(false);
    } else if (index == 3) {
        image1->setVisible(false);
        image2->setVisible(false);
        image3->setVisible(true);
    }
}

void MyClass::ToRelations(cocos2d::Ref* sender) {
    if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
    if ( userDefault->getBoolForKey("relationUnlocked", true)) {
        Lock();
        auto layer = CSLoader::createNode("Layer2.csb");
        layer2 = dynamic_cast<Layer*>(layer);
       
        auto bkg = LayerColor::create(Color4B(0, 0, 0, 128));
        Size winSize = Director::getInstance()->getWinSize();
        layer->setPosition(winSize.width * 0.1, winSize.height *0.1);
        bkg->addChild(layer);
        addChild(bkg, 5);
        auto btnClose = dynamic_cast<Button*>(layer->getChildByName("Button_1"));
        btnClose->addClickEventListener(([this, bkg, layer](Ref*) {
            if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
            layer->unscheduleAllCallbacks();
            this->removeChild(bkg);
            Unlock();
            SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
            TextureCache::getInstance()->removeUnusedTextures();
        }));
        layer->schedule(CC_SCHEDULE_SELECTOR(MyClass::lbar1), 0.25f, CC_REPEAT_FOREVER, 0);
        int i, j;
        for (i = 1; i <= 3; i++) {
            for (j = 1; j <= 6; j++) {
                string state = "customeUnlocked_";
                state += String::createWithFormat("%d", i)->getCString();
                state += "_";
                state += String::createWithFormat("%d", j)->getCString();
                string tmp2 = "Image_";
                tmp2 += String::createWithFormat("%d", j)->getCString();
                string tmp = "Panel_";
                tmp += String::createWithFormat("%d", i)->getCString();
                auto image = dynamic_cast<ImageView*>(layer->getChildByName("PageView_1")->getChildByName(tmp.c_str())->getChildByName(tmp2.c_str()));

                if (userDefault->getBoolForKey(state.c_str(), false) == false) {
                    Vec2 position = image->getPosition();
                    image->setOpacity(0);
                    char szName[100] = {0};
                    sprintf(szName, "monsters/Unlocked.png");
                    Sprite *sprite = Sprite::create(szName);
                    sprite->setAnchorPoint(Point(0.5, 0.5));
                    sprite->setPosition(position);
                    sprite->setScale(0.8);
                    layer->getChildByName("PageView_1")->getChildByName(tmp.c_str())->addChild(sprite);
                } else {
                    tmp2 = "Text_";
                    tmp2 += String::createWithFormat("%d", j)->getCString();
                    auto text = dynamic_cast<Text*>(layer->getChildByName("PageView_1")->getChildByName(tmp.c_str())->getChildByName(tmp2.c_str()));
                    tmp2 = "LoadingBar_";
                    tmp2 += String::createWithFormat("%d", j)->getCString();
                    auto loading = dynamic_cast<LoadingBar*>(layer->getChildByName("PageView_1")->getChildByName(tmp.c_str())->getChildByName(tmp2.c_str()));
                    tmp2 = "customeLove_";
                    tmp2 += String::createWithFormat("%d", i)->getCString();
                    tmp2 += "_";
                    tmp2 += String::createWithFormat("%d", j)->getCString();
                    int love = userDefault->getIntegerForKey(tmp2.c_str(), 0);
                    string love_str = String::createWithFormat("%d", love)->getCString();
                    love_str += "/5";
                    text->setString(love_str);
                    loading->setPercent(love*20.0);

                    image->addClickEventListener(([this, i, j, layer, tmp, text, love](Ref*) {
                        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                        auto image1 = dynamic_cast<ImageView*>(layer->getChildByName("Image_38"));
                        auto image2 = dynamic_cast<ImageView*>(layer->getChildByName("Image_39"));
                        auto image3 = dynamic_cast<ImageView*>(layer->getChildByName("Image_40"));
                        auto image4 = dynamic_cast<ImageView*>(layer->getChildByName("Image_41"));
                        auto image5 = dynamic_cast<ImageView*>(layer->getChildByName("Image_42"));
                        auto loading2 = dynamic_cast<LoadingBar*>(layer->getChildByName("LoadingBar_9"));
                        loading2->setVisible(true);
                        loading2->setPercent(love*20.0);

                        auto text1 = dynamic_cast<Text*>(layer->getChildByName("Text_22"));
                        auto text2 = dynamic_cast<Text*>(layer->getChildByName("Text_23"));
                        auto text3 = dynamic_cast<Text*>(layer->getChildByName("Text_24"));

                        Vec2 position = image1->getPosition();
                        image1->setVisible(true);
                        image1->setOpacity(0);

                        char szName[100] = {0};
                        sprintf(szName, "monsters/\%d/\%d.png", i, j);
                        Sprite *sprite = Sprite::create(szName);
                        sprite->setAnchorPoint(Point(0.5, 0.5));
                        sprite->setPosition(position);
                        sprite->setScale(1.5);
                        sprite->setTag(1);
                        layer->removeChildByTag(1);
                        layer->addChild(sprite);

                        image2->setVisible(true);
                        string tmp5 = "customeNeeds_";
                        tmp5 += String::createWithFormat("%d", j)->getCString();
                        int num1 = userDefault->getIntegerForKey(tmp5.c_str(), 312);
                        int num2 = num1 % 10;
                        num1 /= 10;
                        int num3 = num1 % 10;
                        int num4 = num1 / 10;

                        Vec2 position2 = image3->getPosition();
                        image3->setVisible(true);
                        image3->setOpacity(0);
                        char szName2[100] = {0};
                        sprintf(szName2, "goods/\%d/\%d.png", i, num2);
                        Sprite *sprite2 = Sprite::create(szName2);
                        sprite2->setAnchorPoint(Point(0.5, 0.5));
                        sprite2->setPosition(position2);
                        sprite2->setScale(0.3);
                        sprite2->setTag(2);
                        layer->removeChildByTag(2);
                        layer->addChild(sprite2);

                        Vec2 position3 = image4->getPosition();
                        image4->setVisible(true);
                        image4->setOpacity(0);
                        char szName3[100] = {0};
                        sprintf(szName3, "goods/\%d/\%d.png", i, num3);
                        Sprite *sprite3 = Sprite::create(szName3);
                        sprite3->setAnchorPoint(Point(0.5, 0.5));
                        sprite3->setPosition(position3);
                        sprite3->setScale(0.3);
                        sprite3->setTag(3);
                        layer->removeChildByTag(3);
                        layer->addChild(sprite3);

                        if (love >= 5) {
                            Vec2 position4 = image5->getPosition();
                            image5->setVisible(true);
                            image5->setOpacity(0);
                            char szName4[100] = {0};
                            sprintf(szName4, "goods/\%d/\%d.png", i, num4);
                            Sprite *sprite4 = Sprite::create(szName4);
                            sprite4->setAnchorPoint(Point(0.5, 0.5));
                            sprite4->setPosition(position4);
                            sprite4->setScale(0.3);
                            sprite4->setTag(4);
                            layer->removeChildByTag(4);
                            layer->addChild(sprite4);
                        } else {
                            layer->removeChildByTag(4);
                        }

                        string tmp3 = "ChineseName_";
                        tmp3 += String::createWithFormat("%d", i)->getCString();
                        tmp3 += "_";
                        tmp3 += String::createWithFormat("%d", j)->getCString();
                        string tmp4 = userDefault->getStringForKey(tmp3.c_str());
                        text1->setString(tmp4);
                        text1->setVisible(true);
                        text2->setString(text->getString());
                        text2->setVisible(true);
                        text3->setVisible(true);
                    }));
                }
            }
        }
    }
}

void MyClass::ToDic(cocos2d::Ref* sender) {
    if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
    if (userDefault->getBoolForKey("dicUnlocked", true)) {
        Lock();
        auto layer = CSLoader::createNode("Layer5.csb");
        auto bkg = LayerColor::create(Color4B(0, 0, 0, 128));
        Size winSize = Director::getInstance()->getWinSize();
        layer->setPosition(winSize.width * 0.1, winSize.height *0.1);
        bkg->addChild(layer);
        addChild(bkg, 5);
        auto btnClose = dynamic_cast<Button*>(layer->getChildByName("Button_17"));
        btnClose->addClickEventListener(([this, bkg](Ref*) {
            if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
            this->removeChild(bkg);
            Unlock();
            SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
            TextureCache::getInstance()->removeUnusedTextures();
        }));

        int i, j;
        for (i = 1; i <= 3; i++) {
            for (j = 1; j <= 6; j++) {
                string state = "customeUnlocked_";
                state += String::createWithFormat("%d", i)->getCString();
                state += "_";
                state += String::createWithFormat("%d", j)->getCString();
                string tmp = "Panel_";
                tmp += String::createWithFormat("%d", i)->getCString();
                string tmp2 = "Image_";
                tmp2 += String::createWithFormat("%d", j)->getCString();
                string tmp3 = "Text_";
                tmp3 += String::createWithFormat("%d", i)->getCString();
                tmp3 += String::createWithFormat("%d", j)->getCString();
                auto image = dynamic_cast<ImageView*>(layer->getChildByName("ListView_1")->getChildByName(tmp.c_str())->getChildByName(tmp2.c_str()));

                if (userDefault->getBoolForKey(state.c_str(), false) == false) {
                    auto text = dynamic_cast<Text*>(layer->getChildByName("ListView_1")->getChildByName(tmp.c_str())->getChildByName(tmp3.c_str()));
                    text->setVisible(false);
                    Vec2 position = image->getPosition();
                    image->setOpacity(0);
                    char szName[100] = {0};
                    sprintf(szName, "monsters/Unlocked.png");
                   
                    /*Sprite *sprite = Sprite::create(szName);
                    sprite->setAnchorPoint(Point(0.5, 0.5));
                    sprite->setPosition(position);
                    layer->getChildByName("ListView_1")->getChildByName(tmp.c_str())->addChild(sprite);*/

                    ImageView* image1 = ImageView::create(szName);
                    image1->setAnchorPoint(Point(0.5, 0.5));
                    image1->setPosition(position);
                    image1->setTouchEnabled(true);
                    layer->getChildByName("ListView_1")->getChildByName(tmp.c_str())->addChild(image1);

                    image1->addClickEventListener(([this](Ref*) {
                        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                        auto layer = CSLoader::createNode("Layer30.csb");
                        auto bkg = LayerColor::create(Color4B(0, 0, 0, 128));
                        Size winSize = Director::getInstance()->getWinSize();
                        layer->setPosition(winSize.width * 0.3, winSize.height *0.3);
                        bkg->addChild(layer);
                        addChild(bkg, 6);
                        auto btnClose = dynamic_cast<Button*>(layer->getChildByName("Button_1"));
                        btnClose->addClickEventListener(([this, bkg](Ref*) {
                            this->removeChild(bkg);
                        }));
                    }));
                } else {
                    image->addClickEventListener(([this, i, j, layer, tmp](Ref*) {
                        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                        int i1, j1;
                        for (i1 = 1; i1 <= 3; i1++) {
                            for (j1 = 1; j1 <= 6; j1++) {
                                string tmp3 = "Panel_";
                                tmp3 += String::createWithFormat("%d", i1)->getCString();
                                string tmp4 = "Image_";
                                tmp4 += String::createWithFormat("%d", j1)->getCString();
                                auto image1 = dynamic_cast<ImageView*>(layer->getChildByName("ListView_1")->getChildByName(tmp3.c_str())->getChildByName(tmp4.c_str()));
                                image1->setTouchEnabled(false);
                            }
                        }

                        auto layer2 = CSLoader::createNode("Layer21.csb");
                        auto bkg2 = LayerColor::create(Color4B(0, 0, 0, 128));
                        Size winSize2 = Director::getInstance()->getWinSize();
                        layer2->setPosition(winSize2.width * 0.1, winSize2.height *0.1);
                        bkg2->addChild(layer2);
                        addChild(bkg2, 6);
                        auto btnClose2 = dynamic_cast<Button*>(layer2->getChildByName("Button_1"));
                        btnClose2->addClickEventListener(([this, bkg2, layer](Ref*) {
                            if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                            int i2, j2;
                            for (i2 = 1; i2 <= 3; i2++) {
                                for (j2 = 1; j2 <= 6; j2++) {
                                    string tmp31 = "Panel_";
                                    tmp31 += String::createWithFormat("%d", i2)->getCString();
                                    string tmp41 = "Image_";
                                    tmp41 += String::createWithFormat("%d", j2)->getCString();
                                    auto image11 = dynamic_cast<ImageView*>(layer->getChildByName("ListView_1")->getChildByName(tmp31.c_str())->getChildByName(tmp41.c_str()));
                                    image11->setTouchEnabled(true);
                                }
                            }

                            this->removeChild(bkg2);
                            //AnimationCache::destroyInstance();
                            SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
                            TextureCache::getInstance()->removeUnusedTextures();
                        }));

                        auto image1 = dynamic_cast<ImageView*>(layer2->getChildByName("Image_169"));
                        auto image2 = dynamic_cast<ImageView*>(layer2->getChildByName("Image_40"));
                        auto image3 = dynamic_cast<ImageView*>(layer2->getChildByName("Image_41"));
                        auto image4 = dynamic_cast<ImageView*>(layer2->getChildByName("Image_42"));

                        auto text1 = dynamic_cast<Text*>(layer2->getChildByName("Text_22"));
                        auto text2 = dynamic_cast<Text*>(layer2->getChildByName("Text_24"));

                        string str1 = "customeName_";
                        str1 += String::createWithFormat("%d", i)->getCString();
                        str1 += "_";
                        str1 += String::createWithFormat("%d", j)->getCString();
                        string name = userDefault->getStringForKey(str1.c_str());
                        str1 = "customeFrames_";
                        str1 += String::createWithFormat("%d", i)->getCString();
                        str1 += "_";
                        str1 += String::createWithFormat("%d", j)->getCString();
                        int frames = userDefault->getIntegerForKey(str1.c_str())*2;

                        Sprite *sprite = Sprite::create();
                        auto animation = Animation::create();
                        for (int i = 1; i < frames; i++) {
                            char szName[100] = {0};
                            sprintf(szName, "monsters/%sb/%sb%02d.png", name.c_str(), name.c_str(), i);
                            animation->addSpriteFrameWithFile(szName);
                        }
                        animation->setDelayPerUnit(1.0f / frames);
                        animation->setRestoreOriginalFrame(true);
                        sprite->runAction(RepeatForever::create(Animate::create(animation)));

                        Vec2 position = image1->getPosition();
                        image1->setVisible(true);
                        image1->setOpacity(0);
                        sprite->setAnchorPoint(Point(0.5, 0.5));
                        sprite->setPosition(position);
                        sprite->setScale(1);
                        layer2->addChild(sprite);

                        image2->setVisible(true);
                        Vec2 position2 = image2->getPosition();
                        image2->setOpacity(0);
                        string tmp5 = "customeNeeds_";
                        tmp5 += String::createWithFormat("%d", j)->getCString();
                        int num1 = userDefault->getIntegerForKey(tmp5.c_str(), 312);
                        int num2 = num1 % 10;
                        num1 /= 10;
                        int num3 = num1 % 10;
                        int num4 = num1 / 10;

                        Vec2 position3 = image3->getPosition();
                        image3->setVisible(true);
                        image3->setOpacity(0);

                        char szName2[100] = {0};
                        sprintf(szName2, "goods/\%d/\%d.png", i, num2);
                        Sprite *sprite2 = Sprite::create(szName2);
                        sprite2->setAnchorPoint(Point(0.5, 0.5));
                        sprite2->setPosition(position2);
                        sprite2->setScale(0.5);
                        layer2->addChild(sprite2);

                        Vec2 position4 = image4->getPosition();
                        image4->setVisible(true);
                        image4->setOpacity(0);
                        char szName3[100] = {0};
                        sprintf(szName3, "goods/\%d/\%d.png", i, num3);
                        Sprite *sprite3 = Sprite::create(szName3);
                        sprite3->setAnchorPoint(Point(0.5, 0.5));
                        sprite3->setPosition(position3);
                        sprite3->setScale(0.5);
                        layer2->addChild(sprite3);

                        char szName4[100] = {0};
                        sprintf(szName4, "goods/\%d/\%d.png", i, num4);
                        Sprite *sprite4 = Sprite::create(szName4);
                        sprite4->setAnchorPoint(Point(0.5, 0.5));
                        sprite4->setPosition(position4);
                        sprite4->setScale(0.5);
                        layer2->addChild(sprite4);

                        string tmp3 = "ChineseName_";
                        tmp3 += String::createWithFormat("%d", i)->getCString();
                        tmp3 += "_";
                        tmp3 += String::createWithFormat("%d", j)->getCString();
                        string tmp4 = userDefault->getStringForKey(tmp3.c_str());
                        text1->setString(tmp4);
                        text1->setVisible(true);

                        tmp3 = "ChineseStory_";
                        tmp3 += String::createWithFormat("%d", i)->getCString();
                        tmp3 += "_";
                        tmp3 += String::createWithFormat("%d", j)->getCString();
                        tmp4 = userDefault->getStringForKey(tmp3.c_str());
                        text2->setString(tmp4);
                        text2->setVisible(true);
                    }));
                }
            }
        }
    }
}

void MyClass::ToBook(cocos2d::Ref* sender) {
    if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
    if (userDefault->getBoolForKey("bookUnlocked", true)) {
        int index = dynamic_cast<PageView*>(this->getChildByName("PageView_1"))->getCurPageIndex() + 1;
        Lock();
        string tmp, tmp1, tmp2;
        tmp += "ableToBook_";
        tmp += String::createWithFormat("%d", index)->getCString();
        tmp2 += "buildState_";
        tmp2 += String::createWithFormat("%d", index)->getCString();

        if (userDefault->getBoolForKey(tmp.c_str(), true) && userDefault->getBoolForKey(tmp2.c_str(), false)) {
            int *numTmp = new int[10];
            for (int i = 0; i < 10; i++) {
                numTmp[i] = i;
            }
            auto layer = CSLoader::createNode("Layer6.csb");
            auto bkg = LayerColor::create(Color4B(0, 0, 0, 128));
            Size winSize = Director::getInstance()->getWinSize();
            layer->setPosition(winSize.width * 0.1, winSize.height *0.1);
            bkg->addChild(layer);
            addChild(bkg, 5);

            for (int i = 1; i < 5; i++) {
                string tmp = "Text_";
                tmp += String::createWithFormat("%d", i + 1)->getCString();
                string tmp2 = "Panel_";
                tmp2 += String::createWithFormat("%d", i + 1)->getCString();
                string tmp3 = "goodPrice_";
                tmp3 += String::createWithFormat("%d", index)->getCString();
                tmp3 += "_";
                tmp3 += String::createWithFormat("%d", i)->getCString();
                auto text1 = dynamic_cast<Text*>(layer->getChildByName("Panel_1")->getChildByName(tmp2.c_str())->getChildByName(tmp.c_str()));
                string str = IConvConvert_GBKToUTF8("金币");
                text1->setString(String::createWithFormat("%d", userDefault->getIntegerForKey(tmp3.c_str()))->getCString() + str);

                tmp = "Name_";
                tmp += String::createWithFormat("%d", i+1)->getCString();
                tmp3 = "ChineseName1_";
                tmp3 += String::createWithFormat("%d", index)->getCString();
                tmp3 += "_";
                tmp3 += String::createWithFormat("%d", i)->getCString();
                auto text11 = dynamic_cast<Text*>(layer->getChildByName("Panel_1")->getChildByName(tmp2.c_str())->getChildByName(tmp.c_str()));
                text11->setString(userDefault->getStringForKey(tmp3.c_str()));

                tmp = "Text_";
                tmp += String::createWithFormat("%d", i + 1)->getCString();
                tmp += "_Copy";
                tmp3 = "goodTime_";
                tmp3 += String::createWithFormat("%d", index)->getCString();
                tmp3 += "_";
                tmp3 += String::createWithFormat("%d", i)->getCString();
                auto text2 = dynamic_cast<Text*>(layer->getChildByName("Panel_1")->getChildByName(tmp2.c_str())->getChildByName(tmp.c_str()));
                str = IConvConvert_GBKToUTF8("秒");
                text2->setString(String::createWithFormat("%d", userDefault->getIntegerForKey(tmp3.c_str()))->getCString() + str);

                string key = "goodsBoxs_";
                key += String::createWithFormat("%d", index)->getCString();
                key += "_";
                key += String::createWithFormat("%d", i)->getCString();
                tmp = "LoadingBar_";
                tmp += String::createWithFormat("%d", i)->getCString();
                auto loading = dynamic_cast<LoadingBar*>(layer->getChildByName("Panel_1")->getChildByName(tmp2.c_str())->getChildByName(tmp.c_str()));
                loading->setPercent(userDefault->getIntegerForKey(key.c_str())*20);

                string key1 = "goodsNum_";
                key1 += String::createWithFormat("%d", index)->getCString();
                key1 += "_";
                key1 += String::createWithFormat("%d", i)->getCString();
                string tmp4 = "Text_5_";
                tmp4 += String::createWithFormat("%d", i + 1)->getCString();
                auto text4 = dynamic_cast<Text*>(layer->getChildByName("Panel_1")->getChildByName(tmp2.c_str())->getChildByName(tmp4.c_str()));
                text4->setString(String::createWithFormat("%d", userDefault->getIntegerForKey(key1.c_str()))->getCString());

                tmp4 = "goodsUnlocked_";
                tmp4 += String::createWithFormat("%d", index)->getCString();
                tmp4 += "_";
                tmp4 += String::createWithFormat("%d", i)->getCString();
                key = "Image_";
                key += String::createWithFormat("%d", i+1)->getCString();
                auto image = dynamic_cast<ImageView*>(layer->getChildByName("Panel_1")->getChildByName(tmp2.c_str())->getChildByName(key.c_str()));
                Vec2 position = image->getPosition();
                image->setVisible(true);
                image->setOpacity(0);
                image->setTouchEnabled(false);
                char szName[100] = {0};
                sprintf(szName, "goods/\%d/\%d.png", index, i);

                Sprite *sprite = Sprite::create(szName);
                sprite->setAnchorPoint(Point(0, 1));
                sprite->setPosition(position);
                layer->getChildByName("Panel_1")->getChildByName(tmp2.c_str())->addChild(sprite);
                string tmp7 = "Button_3";
                auto button1 = dynamic_cast<Button*>(layer->getChildByName("Panel_1")->getChildByName(tmp2.c_str())->getChildByName(tmp7.c_str()));
                tmp7 = "Button_4";
                auto button2 = dynamic_cast<Button*>(layer->getChildByName("Panel_1")->getChildByName(tmp2.c_str())->getChildByName(tmp7.c_str()));
                string tmp6 = "TextField_";
                tmp6 += String::createWithFormat("%d", i + 1)->getCString();
                auto textField = dynamic_cast<TextField*>(layer->getChildByName("Panel_1")->getChildByName(tmp2.c_str())->getChildByName(tmp6.c_str()));

                if (userDefault->getBoolForKey(tmp4.c_str(), false) != true) {
                    graySprite(sprite);
                    image->setTouchEnabled(true);
                    textField->setString("0");
                    textField->setTouchEnabled(false);

                    button1->setTouchEnabled(false);
                    button2->setTouchEnabled(false);
                }

                button1->addClickEventListener(([this, textField](Ref*) {
                    if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                    String str2 = textField->getStringValue();
                    int num = str2.intValue();
                    num++;
                    textField->setString(String::createWithFormat("%d", num)->getCString());
                }));

                button2->addClickEventListener(([this, textField](Ref*) {
                    if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                    String str2 = textField->getStringValue();
                    int num = str2.intValue();
                    if (num) num--;
                    textField->setString(String::createWithFormat("%d", num)->getCString());
                }));

                image->addClickEventListener(([this, image, sprite, index, layer, tmp2, i, tmp4, button1, button2](Ref*) {
                    if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                    auto layer1 = CSLoader::createNode("Layer8.csb");
                    auto bkg1 = LayerColor::create(Color4B(0, 0, 0, 128));
                    Size winSize = Director::getInstance()->getWinSize();
                    layer1->setPosition(winSize.width * 0.2, winSize.height *0.2);
                    bkg1->addChild(layer1);
                    addChild(bkg1, 6);

                    auto text1_1 = dynamic_cast<Text*>(layer1->getChildByName("Text_18"));
                    text1_1->setVisible(false);
                    auto text1_2 = dynamic_cast<Text*>(layer1->getChildByName("Text_17"));

                    string name = image->getName();
                    string name1 = "goodUnlocked_";
                    name1 += String::createWithFormat("%d", index)->getCString();
                    name1 += "_";
                    name1 += (name[6] - 1);

                    int money = userDefault->getIntegerForKey(name1.c_str());
                    string str = IConvConvert_GBKToUTF8("解锁将花费");
                    str += String::createWithFormat("%d", money)->getCString();
                    str += IConvConvert_GBKToUTF8("金币。");

                    text1_2->setString(str);
                    auto btnClose1 = dynamic_cast<Button*>(layer1->getChildByName("Button_3_Copy"));
                    btnClose1->addClickEventListener(([this, bkg1](Ref*) {
                        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                        this->removeChild(bkg1);
                    }));

                    auto btnClose2 = dynamic_cast<Button*>(layer1->getChildByName("Button_3"));
                    btnClose2->addClickEventListener(([this, sprite, money, layer, tmp2, i, image, tmp4, bkg1, button1, button2](Ref*) {
                        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                        int cur_money = userDefault->getIntegerForKey("money", 1000);
                        auto layer2 = CSLoader::createNode("Layer1.csb");
                        auto bkg2 = LayerColor::create(Color4B(0, 0, 0, 128));
                        Size winSize = Director::getInstance()->getWinSize();
                        layer2->setPosition(winSize.width * 0.3, winSize.height *0.3);
                        bkg2->addChild(layer2);
                        addChild(bkg2, 7);

                        auto text1_3 = dynamic_cast<Text*>(layer2->getChildByName("Text_1"));
                        if (cur_money >= money && (userDefault->getBoolForKey(tmp4.c_str(), false) == false)) {
                            cur_money -= money;
                            string str1 = IConvConvert_GBKToUTF8("解锁成功！");
                            text1_3->setString(str1);

                            sprite->setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
                            string tmp6 = "TextField_";
                            tmp6 += String::createWithFormat("%d", i + 1)->getCString();
                            image->setTouchEnabled(false);

                            auto textField = dynamic_cast<TextField*>(layer->getChildByName("Panel_1")->getChildByName(tmp2.c_str())->getChildByName(tmp6.c_str()));
                            textField->setString("0");
                            textField->setTouchEnabled(true);

                            button1->setTouchEnabled(true);
                            button2->setTouchEnabled(true);

                            userDefault->setBoolForKey(tmp4.c_str(), true);
                            grow(5, (0 - money));
                        } else {
                            string str1 = IConvConvert_GBKToUTF8("金币不足！");
                            text1_3->setString(str1);
                        }
                        removeChild(bkg1);

                        auto btnClose3 = dynamic_cast<Button*>(layer2->getChildByName("Button_1"));
                        btnClose3->addClickEventListener(([this, bkg2](Ref*) {
                            if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                            this->removeChild(bkg2);
                        }));
                    }));
                }));
            }

            auto btnClose = dynamic_cast<Button*>(layer->getChildByName("Button_1"));
            btnClose->addClickEventListener(([this, bkg](Ref*) {
                if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                this->removeChild(bkg);
                Unlock();
                SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
                TextureCache::getInstance()->removeUnusedTextures();
            }));

            Node *rootNode = root;
            auto btnOrder = dynamic_cast<Button*>(layer->getChildByName("Button_2"));
            btnOrder->addClickEventListener(([this, bkg, layer, index, rootNode, numTmp](Ref*) {
                if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                Unlock();
                auto layer1 = CSLoader::createNode("Layer8.csb");
                auto bkg1 = LayerColor::create(Color4B(0, 0, 0, 128));
                Size winSize = Director::getInstance()->getWinSize();
                layer1->setPosition(winSize.width * 0.2, winSize.height *0.2);
                bkg1->addChild(layer1);
                addChild(bkg1, 8);

                auto btnClose1 = dynamic_cast<Button*>(layer1->getChildByName("Button_3_Copy"));
                btnClose1->addClickEventListener(([this, bkg1](Ref*) {
                    if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                    this->removeChild(bkg1);
                }));

                int money = 0, time = 0, num;
                for (int i = 1; i < 5; i++) {
                    string tmp = "TextField_";
                    tmp += String::createWithFormat("%d", i + 1)->getCString();
                    string tmp2 = "Panel_";
                    tmp2 += String::createWithFormat("%d", i + 1)->getCString();
                    string tmp3 = "goodPrice_";
                    tmp3 += String::createWithFormat("%d", index)->getCString();
                    tmp3 += "_";
                    tmp3 += String::createWithFormat("%d", i)->getCString();
                    auto textField = dynamic_cast<TextField*>(layer->getChildByName("Panel_1")->getChildByName(tmp2.c_str())->getChildByName(tmp.c_str()));
                    string text = textField->getStringValue();

                    tmp = "Text_";
                    tmp += String::createWithFormat("%d", i + 1)->getCString();
                    auto text1 = dynamic_cast<Text*>(layer->getChildByName("Panel_1")->getChildByName(tmp2.c_str())->getChildByName(tmp.c_str()));
                    string text1_1 = text1->getStringValue();
                    tmp = "Text_";
                    tmp += String::createWithFormat("%d", i + 1)->getCString();
                    tmp += "_Copy";
                    auto text2 = dynamic_cast<Text*>(layer->getChildByName("Panel_1")->getChildByName(tmp2.c_str())->getChildByName(tmp.c_str()));
                    string text2_1 = text2->getStringValue();

                    num = atoi(text.c_str());
                    int money_tmp = 0, time_tmp = 0;
                    for (unsigned int i1 = 0; i1 < text1_1.length(); i1++) {
                        if ('0' <= text1_1[i1] && text1_1[i1] <= '9') {
                            money_tmp *= 10;
                            money_tmp += (text1_1[i1] - '0');
                        }
                    }
                    money += num*money_tmp;
                    for (unsigned int i1 = 0; i1 < text2_1.length(); i1++) {
                        if ('0' <= text2_1[i1] && text2_1[i1] <= '9') {
                            time_tmp *= 10;
                            time_tmp += (text2_1[i1] - '0');
                        }
                    }
                    time += num*time_tmp;
                    numTmp[i] = num;
                }
                auto text3 = dynamic_cast<Text*>(layer1->getChildByName("Text_17"));
                string str2 = IConvConvert_GBKToUTF8("将花费");
                str2 += String::createWithFormat("%d", money)->getCString();
                str2 += IConvConvert_GBKToUTF8("金币和");
                str2 += String::createWithFormat("%d", time)->getCString();
                str2 += IConvConvert_GBKToUTF8("秒。");
                text3->setString(str2);

                auto btnOrder1 = dynamic_cast<Button*>(layer1->getChildByName("Button_3"));
                btnOrder1->addClickEventListener(([this, bkg1, money, index, numTmp, layer, rootNode, bkg, time](Ref*) {
                    if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                    int curMoney = userDefault->getIntegerForKey("money");
                    if (curMoney >= money) {
                        curMoney -= money;
                        userDefault->setIntegerForKey("money", curMoney);
                        for (int j = 1; j < 5; j++) {
                            string key = "goodsBoxs_";
                            key += String::createWithFormat("%d", index)->getCString();
                            key += "_";
                            key += String::createWithFormat("%d", j)->getCString();

                            int goodNum = userDefault->getIntegerForKey(key.c_str(), 0);
                            goodNum += numTmp[j];
                            if (goodNum <= 5) userDefault->setIntegerForKey(key.c_str(), goodNum);
                            else userDefault->setIntegerForKey(key.c_str(), 5);

                            string tmp = "Text_4_";
                            tmp += String::createWithFormat("%d", j + 1)->getCString();
                            string tmp2 = "Panel_";
                            tmp2 += String::createWithFormat("%d", j + 1)->getCString();
                            auto text3 = dynamic_cast<Text*>(layer->getChildByName("Panel_1")->getChildByName(tmp2.c_str())->getChildByName(tmp.c_str()));
                            text3->setString(String::createWithFormat("%d", goodNum)->_string);

                            string key1 = "goodsNum_";
                            key1 += String::createWithFormat("%d", index)->getCString();
                            key1 += "_";
                            key1 += String::createWithFormat("%d", j)->getCString();
                            
                            int goodNum1 = userDefault->getIntegerForKey(key1.c_str(), 0);
                            goodNum1 += numTmp[j] * 50;
                            if (goodNum1 <= 250) userDefault->setIntegerForKey(key1.c_str(), goodNum1);
                            else userDefault->setIntegerForKey(key1.c_str(), 250);
                        }
                        auto textBMLabel3 = dynamic_cast<Text*>(rootNode->getChildByName("Text_36"));
                        textBMLabel3->setString(String::createWithFormat("%d", curMoney)->getCString());
                        this->removeChild(bkg1);
                        this->removeChild(bkg);

                        Text* text25;
                        Text* text26;
                        ImageView* image;
                        book_index = index;
                        if (index == 1) {
                            text25 = dynamic_cast<Text*>(rootNode->getChildByName("PageView_1")->getChildByName("Panel_1")->getChildByName("Text_25"));
                            text26 = dynamic_cast<Text*>(rootNode->getChildByName("PageView_1")->getChildByName("Panel_1")->getChildByName("Text_2"));
                            image = dynamic_cast<ImageView*>(rootNode->getChildByName("PageView_1")->getChildByName("Panel_1")->getChildByName("Image_3"));
                        } else if (index == 2) {
                            text25 = dynamic_cast<Text*>(rootNode->getChildByName("PageView_1")->getChildByName("Panel_1_Copy")->getChildByName("Text_25_Copy"));
                            text26 = dynamic_cast<Text*>(rootNode->getChildByName("PageView_1")->getChildByName("Panel_1_Copy")->getChildByName("Text_2_Copy"));
                            image = dynamic_cast<ImageView*>(rootNode->getChildByName("PageView_1")->getChildByName("Panel_1_Copy")->getChildByName("Image_3_Copy"));
                        } else if (index == 3) {
                            text25 = dynamic_cast<Text*>(rootNode->getChildByName("PageView_1")->getChildByName("Panel_1_Copy_0")->getChildByName("Text_25_Copy_0"));
                            text26 = dynamic_cast<Text*>(rootNode->getChildByName("PageView_1")->getChildByName("Panel_1_Copy_0")->getChildByName("Text_2_Copy_0"));
                            image = dynamic_cast<ImageView*>(rootNode->getChildByName("PageView_1")->getChildByName("Panel_1_Copy_0")->getChildByName("Image_3_Copy_0"));
                        }
                        text25->setVisible(true);
                        text26->setVisible(true);
                        image->setVisible(true);
                        string time_str;
                        int minutes = time / 60;
                        int seconds = time % 60;
                        int hours = minutes / 60;
                        minutes %= 60;
                        if (0 <= hours && hours < 10) time_str += "0";
                        time_str += String::createWithFormat("%d", hours)->getCString();
                        time_str += ":";
                        if (0 <= minutes && minutes < 10) time_str += "0";
                        time_str += String::createWithFormat("%d", minutes)->getCString();
                        time_str += ":";
                        if (0 <= seconds && seconds < 10) time_str += "0";
                        time_str += String::createWithFormat("%d", seconds)->getCString();

                        string tmp;
                        tmp += "ableToBook_";
                        tmp += String::createWithFormat("%d", index)->getCString();
                        userDefault->setBoolForKey(tmp.c_str(), false);
                        text26->setText(time_str.c_str());

                        if (index == 1) {
                            for (int i = 2; i < 86; i = i + 2) {
                                char szName[100] = {0};
                                sprintf(szName, "UI/huodao/huodaol/huodaol%02d.png", i);
                                TextureCache::sharedTextureCache()->addImageAsync(szName, CC_CALLBACK_1(MyClass::Callback3, this));
                            }
                        } else if (index == 2) {
                            for (int i = 2; i < 86; i = i + 2) {
                                char szName[100] = {0};
                                sprintf(szName, "UI/huodao/huodaom/huodaom%02d.png", i);
                                TextureCache::sharedTextureCache()->addImageAsync(szName, CC_CALLBACK_1(MyClass::Callback3, this));
                            }
                        } else if (index == 3) {
                            for (int i = 2; i < 86; i = i + 2) {
                                char szName[100] = {0};
                                sprintf(szName, "UI/huodao/huodaor/huodaor%02d.png", i);
                                TextureCache::sharedTextureCache()->addImageAsync(szName, CC_CALLBACK_1(MyClass::Callback3, this));
                            }
                        }
                       
                        text26->schedule(SEL_SCHEDULE(&MyClass::Update), 1);
                    } else {
                        this->removeChild(bkg1);
                        this->removeChild(bkg);

                        auto layer2 = CSLoader::createNode("Layer1.csb");
                        auto bkg2 = LayerColor::create(Color4B(0, 0, 0, 128));
                        Size winSize = Director::getInstance()->getWinSize();
                        layer2->setPosition(winSize.width * 0.3, winSize.height *0.3);
                        bkg2->addChild(layer2);
                        addChild(bkg2);

                        auto btnClose2 = dynamic_cast<Button*>(layer2->getChildByName("Button_1"));
                        btnClose2->addClickEventListener(([this, bkg2](Ref*) {
                            if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                            this->removeChild(bkg2);
                        }));
                    }
                }));
                SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
                TextureCache::getInstance()->removeUnusedTextures();
            }));
        }
    }
}

void MyClass::AboutUs(cocos2d::Ref* sender) {
    Scene* scene1 = Scene::create();
    auto rootNode = CSLoader::createNode("Scene2.csb");
    scene1->addChild(rootNode);
    Director::getInstance()->replaceScene(scene1);
}

void MyClass::ReturnToGame(cocos2d::Ref* sender) {
    if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
    Scene* scene1 = Scene::create();
    auto rootNode = CSLoader::createNode("Scene3.csb");
    scene1->addChild(rootNode);
    Director::getInstance()->replaceScene(scene1);
}

void MyClass::StartGame(cocos2d::Ref* sender) {
    userDefault->setBoolForKey("first_time", true);
    userDefault->setIntegerForKey("money", 1000);
    userDefault->setBoolForKey("buildState_1", false);
    userDefault->setBoolForKey("buildState_2", false);
    userDefault->setBoolForKey("buildState_3", false);

    userDefault->setBoolForKey("goodsUnlocked_1_1", false);
    userDefault->setBoolForKey("goodsUnlocked_1_2", false);
    userDefault->setBoolForKey("goodsUnlocked_1_3", false);
    userDefault->setBoolForKey("goodsUnlocked_1_4", false);

    userDefault->setBoolForKey("goodsUnlocked_2_1", false);
    userDefault->setBoolForKey("goodsUnlocked_2_2", false);
    userDefault->setBoolForKey("goodsUnlocked_2_3", false);
    userDefault->setBoolForKey("goodsUnlocked_2_4", false);

    userDefault->setBoolForKey("goodsUnlocked_3_1", false);
    userDefault->setBoolForKey("goodsUnlocked_3_2", false);
    userDefault->setBoolForKey("goodsUnlocked_3_3", false);
    userDefault->setBoolForKey("goodsUnlocked_3_4", false);

    userDefault->setIntegerForKey("goodsBoxs_1_1", 0);
    userDefault->setIntegerForKey("goodsBoxs_1_2", 0);
    userDefault->setIntegerForKey("goodsBoxs_1_3", 0);
    userDefault->setIntegerForKey("goodsBoxs_1_4", 0);

    userDefault->setIntegerForKey("goodsBoxs_2_1", 0);
    userDefault->setIntegerForKey("goodsBoxs_2_2", 0);
    userDefault->setIntegerForKey("goodsBoxs_2_3", 0);
    userDefault->setIntegerForKey("goodsBoxs_2_4", 0);

    userDefault->setIntegerForKey("goodsBoxs_3_1", 0);
    userDefault->setIntegerForKey("goodsBoxs_3_2", 0);
    userDefault->setIntegerForKey("goodsBoxs_3_3", 0);
    userDefault->setIntegerForKey("goodsBoxs_3_4", 0);

    userDefault->setIntegerForKey("goodsNum_1_1", 0);
    userDefault->setIntegerForKey("goodsNum_1_2", 0);
    userDefault->setIntegerForKey("goodsNum_1_3", 0);
    userDefault->setIntegerForKey("goodsNum_1_4", 0);

    userDefault->setIntegerForKey("goodsNum_2_1", 0);
    userDefault->setIntegerForKey("goodsNum_2_2", 0);
    userDefault->setIntegerForKey("goodsNum_2_3", 0);
    userDefault->setIntegerForKey("goodsNum_2_4", 0);

    userDefault->setIntegerForKey("goodsNum_3_1", 0);
    userDefault->setIntegerForKey("goodsNum_3_2", 0);
    userDefault->setIntegerForKey("goodsNum_3_3", 0);
    userDefault->setIntegerForKey("goodsNum_3_4", 0);

    userDefault->setIntegerForKey("customeLove_1_1", 0);
    userDefault->setIntegerForKey("customeLove_1_2", 0);
    userDefault->setIntegerForKey("customeLove_1_3", 0);
    userDefault->setIntegerForKey("customeLove_1_4", 0);
    userDefault->setIntegerForKey("customeLove_1_5", 0);
    userDefault->setIntegerForKey("customeLove_1_6", 0);

    userDefault->setIntegerForKey("customeLove_2_1", 0);
    userDefault->setIntegerForKey("customeLove_2_2", 0);
    userDefault->setIntegerForKey("customeLove_2_3", 0);
    userDefault->setIntegerForKey("customeLove_2_4", 0);
    userDefault->setIntegerForKey("customeLove_2_5", 0);
    userDefault->setIntegerForKey("customeLove_2_6", 0);

    userDefault->setIntegerForKey("customeLove_3_1", 0);
    userDefault->setIntegerForKey("customeLove_3_2", 0);
    userDefault->setIntegerForKey("customeLove_3_3", 0);
    userDefault->setIntegerForKey("customeLove_3_4", 0);
    userDefault->setIntegerForKey("customeLove_3_5", 0);
    userDefault->setIntegerForKey("customeLove_3_6", 0);

    userDefault->setBoolForKey("customeUnlocked_1_1", false);
    userDefault->setBoolForKey("customeUnlocked_1_2", false);
    userDefault->setBoolForKey("customeUnlocked_1_3", false);
    userDefault->setBoolForKey("customeUnlocked_1_4", false);
    userDefault->setBoolForKey("customeUnlocked_1_5", false);
    userDefault->setBoolForKey("customeUnlocked_1_6", false);

    userDefault->setBoolForKey("customeUnlocked_2_1", false);
    userDefault->setBoolForKey("customeUnlocked_2_2", false);
    userDefault->setBoolForKey("customeUnlocked_2_3", false);
    userDefault->setBoolForKey("customeUnlocked_2_4", false);
    userDefault->setBoolForKey("customeUnlocked_2_5", false);
    userDefault->setBoolForKey("customeUnlocked_2_6", false);

    userDefault->setBoolForKey("customeUnlocked_3_1", false);
    userDefault->setBoolForKey("customeUnlocked_3_2", false);
    userDefault->setBoolForKey("customeUnlocked_3_3", false);
    userDefault->setBoolForKey("customeUnlocked_3_4", false);
    userDefault->setBoolForKey("customeUnlocked_3_5", false);
    userDefault->setBoolForKey("customeUnlocked_3_6", false);

    userDefault->setIntegerForKey("money", 1000);
    userDefault->setIntegerForKey("currentExp", 0);
    userDefault->setIntegerForKey("level", 1);

    EnterGame(sender);
}

void MyClass::EnterGame(cocos2d::Ref* sender) {
    SimpleAudioEngine::getInstance()->playBackgroundMusic("mp3/BGM.mp3", true);
    po = 1;
    savename();
    Unlock();
    userDefault->setBoolForKey("groupBuyEnabled", false);
    Scene* scene1 = Scene::create();
    auto rootNode = CSLoader::createNode("SceneX.csb");
    root = rootNode;
    scene1->addChild(rootNode);
    Director::getInstance()->replaceScene(scene1);

    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    TextureCache::getInstance()->removeUnusedTextures();

    for (int i = 1; i < 4; i++) {
        string tmp = "ableToBook_";
        tmp += String::createWithFormat("%d", i)->getCString();
        userDefault->setBoolForKey(tmp.c_str(), true);
    }
    int level = userDefault->getIntegerForKey("level", 1);
    maxHun = 18 + level * 2;
    curHun = maxHun;

    string level_str = String::createWithFormat("%d", level)->getCString();
    int currentExp = userDefault->getIntegerForKey("currentExp", 0);
    string currentExp_str = String::createWithFormat("%d", currentExp)->getCString();
    string needExp_str1 = "needExp_" + level_str;
    int needExp = userDefault->getIntegerForKey(needExp_str1.c_str());
    string needExp_str = String::createWithFormat("%d", needExp)->getCString();
    int money = userDefault->getIntegerForKey("money", 1000);
    if (money == 1000) userDefault->setIntegerForKey("money", 1000);
    string money_str = String::createWithFormat("%d", money)->getCString();

    auto textBMLabel = dynamic_cast<Text*>(rootNode->getChildByName("Text_34"));
    textBMLabel->setString(level_str);
    auto textBMLabel2 = dynamic_cast<Text*>(rootNode->getChildByName("Text_35"));
    textBMLabel2->setString(currentExp_str + "/" + needExp_str);
    auto textBMLabel3 = dynamic_cast<Text*>(rootNode->getChildByName("Text_36"));
    textBMLabel3->setString(money_str);
    auto loading1 = dynamic_cast<LoadingBar*>(rootNode->getChildByName("LoadingBar_2"));
    loading1->setPercent(currentExp*100.0/needExp);
    auto loading2 = dynamic_cast<LoadingBar*>(rootNode->getChildByName("LoadingBar_3"));
    loading2->setPercent(curHun*100.0 / maxHun);
    auto textBMLabel4 = dynamic_cast<Text*>(rootNode->getChildByName("Text_1"));
    string curHun_str = String::createWithFormat("%d", curHun)->getCString();
    string maxHun_str = String::createWithFormat("%d", maxHun)->getCString();
    textBMLabel4->setString(curHun_str + "/" + maxHun_str);

    if (userDefault->getBoolForKey("buildState_1", false)) {
        root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update1), 5.0f, CC_REPEAT_FOREVER, 2);
        root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update11), 5.0f, CC_REPEAT_FOREVER, 1);
        auto image = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*)rootNode, "Image_18"));
        image->setVisible(false);
        image->setTouchEnabled(false);
        auto image2 = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*)rootNode, "Image_27"));
        image2->setVisible(true);
        auto image3 = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*) rootNode, "Image_1"));
        image3->setTouchEnabled(true);
    } else {
        Sprite *sprite = Sprite::create();
        auto animation = Animation::create();

        for (int i = 1; i < 23; i++) {
            char szName[100] = {0};
            sprintf(szName, "UI/dan1/dan100%02d.png", i);
            animation->addSpriteFrameWithFile(szName);
        }
        animation->setDelayPerUnit(1.5f / 22);
        animation->setRestoreOriginalFrame(true);
        sprite->runAction(RepeatForever::create(Animate::create(animation)));
        rootNode->getChildByName("PageView_1")->getChildByName("Panel_1")->addChild(sprite);
        sprite->setPosition(Vec2(1100, 600));
        sprite->setTag(31);
    }
    if (userDefault->getBoolForKey("buildState_2", false)) {
        root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update2), 5.0f, CC_REPEAT_FOREVER, 1);
        root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update21), 5.0f, CC_REPEAT_FOREVER, 0.5);
        auto image = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*)rootNode, "Image_18_Copy"));
        image->setVisible(false);
        image->setTouchEnabled(false);
        auto image2 = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*)rootNode, "Image_27_Copy"));
        image2->setVisible(true);
        auto image3 = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*) rootNode, "Image_1_Copy"));
        image3->setTouchEnabled(true);
    } else {
        Sprite *sprite = Sprite::create();
        auto animation = Animation::create();

        for (int i = 1; i < 24; i++) {
            char szName[100] = {0};
            sprintf(szName, "UI/dan2/dan200%02d.png", i);
            animation->addSpriteFrameWithFile(szName);
        }
        animation->setDelayPerUnit(1.5f / 23);
        animation->setRestoreOriginalFrame(true);
        sprite->runAction(RepeatForever::create(Animate::create(animation)));
        rootNode->getChildByName("PageView_1")->getChildByName("Panel_1_Copy")->addChild(sprite);
        sprite->setPosition(Vec2(1260, 540));
        sprite->setTag(32);
    }
    if (userDefault->getBoolForKey("buildState_3", false)) {
        root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update3), 5.0f, CC_REPEAT_FOREVER, 1);
        root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update31), 5.0f, CC_REPEAT_FOREVER, 2);
        auto image = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*)rootNode, "Image_18_Copy_0"));
        image->setVisible(false);
        image->setTouchEnabled(false);
        auto image2 = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*)rootNode, "Image_27_Copy_0"));
        image2->setVisible(true);
        auto image3 = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*) rootNode, "Image_1_Copy_0"));
        image3->setTouchEnabled(true);
    } else {
        Sprite *sprite = Sprite::create();
        auto animation = Animation::create();

        for (int i = 1; i < 23; i++) {
            char szName[100] = {0};
            sprintf(szName, "UI/dan3/dan300%02d.png", i);
            animation->addSpriteFrameWithFile(szName);
        }
        animation->setDelayPerUnit(1.5f / 22);
        animation->setRestoreOriginalFrame(true);
        sprite->runAction(RepeatForever::create(Animate::create(animation)));
        rootNode->getChildByName("PageView_1")->getChildByName("Panel_1_Copy_0")->addChild(sprite);
        sprite->setPosition(Vec2(1410, 600));
        sprite->setTag(33);
    }
    string tmp3 = "groupBuyEnabled";
    userDefault->setBoolForKey(tmp3.c_str(), false);
    auto view = dynamic_cast<PageView*>(root->getChildByName("PageView_1"));
    panel1 = view->getChildByName("Panel_1");
    panel2 = view->getChildByName("Panel_1_Copy");
    panel3 = view->getChildByName("Panel_1_Copy_0");

    scene1->schedule(CC_SCHEDULE_SELECTOR(MyClass::HunUpdate), 5.0f, CC_REPEAT_FOREVER, 5);
    scene1->schedule(CC_SCHEDULE_SELECTOR(MyClass::lbar), 0.25f, CC_REPEAT_FOREVER, 0);
    scene1->schedule(CC_SCHEDULE_SELECTOR(MyClass::ToGroupBuy), 60.0f, CC_REPEAT_FOREVER, 20.0f);
}

void MyClass::lbar(float t) {
    int index = dynamic_cast<PageView*>(root->getChildByName("PageView_1"))->getCurPageIndex() + 1;
    int num = index - po;
    if (num != 0) {
        auto sprite = dynamic_cast<Sprite*>(root->getChildByName("Sprite_1"));
        sprite->runAction(Sequence::create(MoveBy::create(0.1, Vec2(264 * num, 0)), NULL));
        po = index;
    }

    string tmp1 = "ableToBook_";
    tmp1 += String::createWithFormat("%d", index)->getCString();
    string tmp2 = "buildState_";
    tmp2 += String::createWithFormat("%d", index)->getCString();
    string tmp3 = "groupBuyEnabled";
    bool b1 = (userDefault->getBoolForKey(tmp1.c_str(), true) && userDefault->getBoolForKey(tmp2.c_str(), false));
    bool b2 = (userDefault->getBoolForKey(tmp3.c_str(), true) && userDefault->getBoolForKey(tmp2.c_str(), false));
    if (b1 != buyEnable) {
        auto image1 = dynamic_cast<Button*>(root->getChildByName("Image_14"));
        if (b1) {
            Vec2 position = image1->getPosition();
            image1->setOpacity(0);
            char szName[100] = {0};
            sprintf(szName, "UI/\MainScene/\Buy.png");
            Sprite *sprite = Sprite::create(szName);
            sprite->setPosition(position);
            sprite->setTag(1);
            root->removeChildByTag(1);
            root->addChild(sprite);
        } else {
            Vec2 position = image1->getPosition();
            image1->setOpacity(0);
            char szName[100] = {0};
            sprintf(szName, "UI/\MainScene/\Buy_not.png");
            Sprite *sprite = Sprite::create(szName);
            sprite->setPosition(position);
            sprite->setTag(1);
            root->removeChildByTag(1);
            root->addChild(sprite);
        }
        buyEnable = b1;
    }
    if (b2 != groupEnable) {
        auto image2 = dynamic_cast<Button*>(root->getChildByName("Image_13"));
        if (b2) {
            Vec2 position = image2->getPosition();
            image2->setOpacity(0);
            image2->setTouchEnabled(true);
            char szName[100] = {0};
            sprintf(szName, "UI/\MainScene/\GroupBuy.png");
            Sprite *sprite = Sprite::create(szName);
            sprite->setPosition(position);
            sprite->setTag(2);
            root->removeChildByTag(2);
            root->addChild(sprite);
        } else {
            Vec2 position = image2->getPosition();
            image2->setOpacity(0);
            image2->setTouchEnabled(false);
            char szName[100] = {0};
            sprintf(szName, "UI/\MainScene/\GroupBuy_not.png");
            Sprite *sprite = Sprite::create(szName);
            sprite->setPosition(position);
            sprite->setTag(2);
            root->removeChildByTag(2);
            root->addChild(sprite);
        }
        groupEnable = b2;
    }
}

void MyClass::GroupBuy(cocos2d::Ref* sender) {
    if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
    if ( userDefault->getBoolForKey("groupUnlocked", true)) {
        int index = dynamic_cast<PageView*>(root->getChildByName("PageView_1"))->getCurPageIndex() + 1;
        Scene* scene1 = Director::getInstance()->getRunningScene();
        if (index == 1) {
            root->unschedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update1));
            root->unschedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update11));
            root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update101), 2.5f, 3, 0.5);
            root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update111), 2.5f, 3, 1);
        } else if (index == 2) {
            root->unschedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update2));
            root->unschedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update21));
            root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update102), 2.5f, 3, 1);
            root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update121), 2.5f, 3, 0.5);
        } else if (index == 3) {
            root->unschedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update3));
            root->unschedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update31));
            root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update103), 2.5f, 3, 0.5);
            root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update131), 2.5f, 3, 1);
        }
        string tmp = "groupBuyEnabled";
        userDefault->setBoolForKey(tmp.c_str(), false);
        scene1->schedule(CC_SCHEDULE_SELECTOR(MyClass::NormalBuy), 0, 0, 9);
    }
}

void MyClass::HunUpdate(float t) {
    if (curHun < maxHun) curHun++;
    auto textBMLabel4 = dynamic_cast<Text*>(root->getChildByName("Text_1"));
    string curHun_str = String::createWithFormat("%d", curHun)->getCString();
    string maxHun_str = String::createWithFormat("%d", maxHun)->getCString();
    textBMLabel4->setString(curHun_str + "/" + maxHun_str);

    auto loading2 = dynamic_cast<LoadingBar*>(root->getChildByName("LoadingBar_3"));
    loading2->setPercent(curHun*100.0 / maxHun);
}

void MyClass::Quit(cocos2d::Ref* sender) {
    if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
    Director::getInstance()->end();
}

bool MyClass::judgeRoom_1() {
    return (userDefault->getBoolForKey("customeUnlocked_1_1", false) && userDefault->getBoolForKey("customeUnlocked_1_2", false)
        && userDefault->getBoolForKey("customeUnlocked_1_3", false) && userDefault->getBoolForKey("customeUnlocked_1_4", false)
        && userDefault->getBoolForKey("customeUnlocked_1_5", false) && userDefault->getBoolForKey("customeUnlocked_1_6", false));
}

bool MyClass::judgeRoom_2() {
    return (userDefault->getBoolForKey("customeUnlocked_2_1", false) && userDefault->getBoolForKey("customeUnlocked_2_2", false)
        && userDefault->getBoolForKey("customeUnlocked_2_3", false) && userDefault->getBoolForKey("customeUnlocked_2_4", false)
        && userDefault->getBoolForKey("customeUnlocked_2_5", false) && userDefault->getBoolForKey("customeUnlocked_2_6", false));
}

void MyClass::ToBuild1(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        if (userDefault->getBoolForKey("lockState_1", false) != true
            && userDefault->getBoolForKey("buildState_1", false) != true) {
            auto parent = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*)this, "Image_18"));
            parent->setTouchEnabled(false);
            auto layer1 = CSLoader::createNode("Layer80.csb");
            auto bkg1 = LayerColor::create(Color4B(0, 0, 0, 128));
            Size winSize = Director::getInstance()->getWinSize();
            layer1->setPosition(winSize.width * 0.2, winSize.height *0.2);
            bkg1->addChild(layer1);
            addChild(bkg1, 1);

            string str = IConvConvert_GBKToUTF8("将花费");
            str += String::createWithFormat("%d", 0)->getCString();
            str += IConvConvert_GBKToUTF8("金币。");
            auto text1_2 = dynamic_cast<Text*>(layer1->getChildByName("Text_17"));
            text1_2->setString(str);
            auto text1_1 = dynamic_cast<Text*>(layer1->getChildByName("Text_18"));
            string str1 = IConvConvert_GBKToUTF8("要不要建造呢?");
            text1_1->setString(str1);

            auto btnClose1 = dynamic_cast<Button*>(layer1->getChildByName("Button_3_Copy"));
            btnClose1->addClickEventListener(([this, bkg1, parent](Ref*) {
                if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                this->removeChild(bkg1);
                parent->setTouchEnabled(true);
            }));

            auto btnClose2 = dynamic_cast<Button*>(layer1->getChildByName("Button_3"));
            Node* root1 = root;
            btnClose2->addClickEventListener(([this, bkg1, root1](Ref*) {
                if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                root1->getChildByName("PageView_1")->getChildByName("Panel_1")->removeChildByTag(31);
                SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
                TextureCache::getInstance()->removeUnusedTextures();

                auto image = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*)this, "Image_18"));
                image->setVisible(false);
                image->setTouchEnabled(false);
                auto image2 = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*)this, "Image_26"));
                image2->setVisible(true);
                image2->setTouchEnabled(true);
                auto text = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*)this, "Text_2"));
                text->setVisible(true);
                auto image3 = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*)this, "Image_3"));
                image3->setVisible(true);
                userDefault->setBoolForKey("buildState_1", true);
                userDefault->flush();
                text->setText("00:00:03");

                for (int i = 1; i < 25; i++) {
                    char szName[100] = {0};
                    sprintf(szName, "UI/jianzhu1/jianzhu100%02d.png", i);
                    TextureCache::sharedTextureCache()->addImageAsync(szName, CC_CALLBACK_1(MyClass::Callback3, this));
                }
                text->schedule(SEL_SCHEDULE(&MyClass::Update1), 1);
                this->removeChild(bkg1);
            }));
        }
    }
}

void MyClass::ToBuild2(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        auto parent = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*)this, "Image_18_Copy"));
        parent->setTouchEnabled(false);
        if (userDefault->getBoolForKey("buildState_2", false) != true && userDefault->getIntegerForKey("level", 1) >= 4
            && userDefault->getIntegerForKey("money", 1405) >= 500) {
            auto layer1 = CSLoader::createNode("Layer80.csb");
            auto bkg1 = LayerColor::create(Color4B(0, 0, 0, 128));
            Size winSize = Director::getInstance()->getWinSize();
            layer1->setPosition(winSize.width * 0.2, winSize.height *0.2);
            bkg1->addChild(layer1);
            addChild(bkg1, 1);

            string str = IConvConvert_GBKToUTF8("解锁将花费");
            str += String::createWithFormat("%d", 500)->getCString();
            str += IConvConvert_GBKToUTF8("金币。");
            auto text1_2 = dynamic_cast<Text*>(layer1->getChildByName("Text_17"));
            text1_2->setString(str);

            auto btnClose1 = dynamic_cast<Button*>(layer1->getChildByName("Button_3_Copy"));
            btnClose1->addClickEventListener(([this, bkg1, parent](Ref*) {
                if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                this->removeChild(bkg1);
                parent->setTouchEnabled(true);
            }));

            auto btnClose2 = dynamic_cast<Button*>(layer1->getChildByName("Button_3"));
            Node* root1 = root;
            btnClose2->addClickEventListener(([this, bkg1, root1](Ref*) {
                if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                root1->getChildByName("PageView_1")->getChildByName("Panel_1_Copy")->removeChildByTag(32);
                SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
                TextureCache::getInstance()->removeUnusedTextures();

                int money = userDefault->getIntegerForKey("money", 1000);
                money -= 500;
                userDefault->setIntegerForKey("money", money);
                userDefault->setBoolForKey("buildState_2", true);
                userDefault->flush();

                auto image = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*)this, "Image_18_Copy"));
                image->setVisible(false);
                image->setTouchEnabled(false);
                auto image2 = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*)this, "Image_26_Copy"));
                image2->setVisible(true);
                image2->setTouchEnabled(true);
                auto text = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*)this, "Text_2_Copy"));
                text->setVisible(true);
                auto image3 = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*)this, "Image_3_Copy"));
                image3->setVisible(true);
                text->setText("00:00:05");
               
                for (int i = 1; i < 50; i++) {
                    char szName[100] = {0};
                    sprintf(szName, "UI/jianzhu2/jianzhu200%02d.png", i);
                    TextureCache::sharedTextureCache()->addImageAsync(szName, CC_CALLBACK_1(MyClass::Callback3, this));
                }
                text->schedule(SEL_SCHEDULE(&MyClass::Update2), 1);
                this->removeChild(bkg1);
            }));
        } else {
            auto layer = CSLoader::createNode("Layer4.csb");
            auto bkg = LayerColor::create(Color4B(0, 0, 0, 128));
            Size winSize = Director::getInstance()->getWinSize();
            layer->setPosition(winSize.width * 0.3, winSize.height *0.3);
            bkg->addChild(layer);
            addChild(bkg, 1);
            auto btnClose = dynamic_cast<Button*>(layer->getChildByName("Button_3"));
            btnClose->addClickEventListener(([this, bkg, parent](Ref*) {
                if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                this->removeChild(bkg);
                parent->setTouchEnabled(true);
            }));
        }
    }
}

void MyClass::Callback3(cocos2d::Object*) {

}

void MyClass::ToBuild3(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        auto parent = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*)this, "Image_18_Copy_0"));
        parent->setTouchEnabled(false);
        if (userDefault->getBoolForKey("lockState_3", false) != true
            && userDefault->getBoolForKey("buildState_3", false) != true && userDefault->getIntegerForKey("level", 1) >= 8
            && userDefault->getIntegerForKey("money", 1000) >= 1000) {
            auto layer1 = CSLoader::createNode("Layer80.csb");
            auto bkg1 = LayerColor::create(Color4B(0, 0, 0, 128));
            Size winSize = Director::getInstance()->getWinSize();
            layer1->setPosition(winSize.width * 0.2, winSize.height *0.2);
            bkg1->addChild(layer1);
            addChild(bkg1, 1);

            string str = IConvConvert_GBKToUTF8("解锁将花费");
            str += String::createWithFormat("%d", 1000)->getCString();
            str += IConvConvert_GBKToUTF8("金币。");
            auto text1_2 = dynamic_cast<Text*>(layer1->getChildByName("Text_17"));
            text1_2->setString(str);

            auto btnClose1 = dynamic_cast<Button*>(layer1->getChildByName("Button_3_Copy"));
            btnClose1->addClickEventListener(([this, bkg1, parent](Ref*) {
                if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                this->removeChild(bkg1);
                parent->setTouchEnabled(true);
            }));

            auto btnClose2 = dynamic_cast<Button*>(layer1->getChildByName("Button_3"));
            Node* root1 = root;
            btnClose2->addClickEventListener(([this, bkg1, root1](Ref*) {
                if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                root1->getChildByName("PageView_1")->getChildByName("Panel_1_Copy_0")->removeChildByTag(33);
                SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
                TextureCache::getInstance()->removeUnusedTextures();

                int money = userDefault->getIntegerForKey("money", 1000);
                money -= 1000;
                userDefault->setIntegerForKey("money", money);
                userDefault->setBoolForKey("buildState_3", true);
                userDefault->flush();

                auto image = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*)this, "Image_18_Copy_0"));
                image->setVisible(false);
                image->setTouchEnabled(false);
                auto image2 = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*)this, "Image_26_Copy_0"));
                image2->setVisible(true);
                image2->setTouchEnabled(true);
                auto text = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*)this, "Text_2_Copy_0"));
                text->setVisible(true);
                auto image3 = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*)this, "Image_3_Copy_0"));
                image3->setVisible(true);
                text->setText("00:00:07");

                for (int i = 1; i < 26; i++) {
                    char szName[100] = {0};
                    sprintf(szName, "UI/jianzhu3/jianzhu300%02d.png", i);
                    TextureCache::sharedTextureCache()->addImageAsync(szName, CC_CALLBACK_1(MyClass::Callback3, this));
                }
                text->schedule(SEL_SCHEDULE(&MyClass::Update3), 1);
                this->removeChild(bkg1);
            }));
        } else {
            auto layer = CSLoader::createNode("Layer3.csb");
            auto bkg = LayerColor::create(Color4B(0, 0, 0, 128));
            Size winSize = Director::getInstance()->getWinSize();
            layer->setPosition(winSize.width * 0.3, winSize.height *0.3);
            bkg->addChild(layer);
            addChild(bkg, 1);
            auto btnClose = dynamic_cast<Button*>(layer->getChildByName("Button_1"));
            btnClose->addClickEventListener(([this, bkg, parent](Ref*) {
                if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                this->removeChild(bkg);
                parent->setTouchEnabled(true);
            }));
        }
    }
}

void MyClass::Update(float t) {
    Text* dt;
    if (book_index == 1) dt = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*)this, "Text_2"));
    else if (book_index == 2) dt = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*)this, "Text_2_Copy"));
    else if (book_index == 3) dt = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*)this, "Text_2_Copy_0"));
    string text = dynamic_cast<Text*>(dt)->getString();
    int second = 0;
    second = (text[6] - '0') * 10 + (text[7] - '0');
    int minute = 0;
    minute = (text[3] - '0') * 10 + (text[4] - '0');
    int hour = 0;
    hour = (text[0] - '0') * 10 + (text[1] - '0');
    if (second > 0) {
        second--;
    } else if (minute > 0) {
        minute--;
        second = 59;
    } else if (hour > 0) {
            hour--;
            minute = 59;
            second = 59;
    }
    text = "";
    if (hour < 10) text += "0";
    text += String::createWithFormat("%d", hour)->getCString();
    text += ":";
    if (minute < 10) text += "0";
    text += String::createWithFormat("%d", minute)->getCString();
    text += ":";
    if (second < 10) text += "0";
    text += String::createWithFormat("%d", second)->getCString();
    dynamic_cast<Text*>(dt)->setText(text);

    if (second == 0 && minute == 0 && hour == 0) {
        dt->unscheduleAllCallbacks();
        Text* text2;
        ImageView* image;
        if (book_index == 1) {
            text2 = dynamic_cast<Text*>(this->getParent()->getChildByName("Text_25"));
            image = dynamic_cast<ImageView*>(this->getParent()->getChildByName("Image_3"));

            Sprite *sprite = Sprite::create();
            Animation* animation = Animation::create();
            sprite->setScale(1.5);
            for (int i = 2; i < 86; i=i+2) {
                char szName[100] = {0};
                sprintf(szName, "UI/huodao/huodaol/huodaol%02d.png", i);
                animation->addSpriteFrameWithFile(szName);
            }
            animation->setDelayPerUnit(4.0f / 42);
            animation->setRestoreOriginalFrame(false);

            sprite->runAction(RepeatForever::create(Animate::create(animation)));
            sprite->setPosition(Vec2(960, 540));
            sprite->setTag(61);
            this->getParent()->addChild(sprite);

            dt->scheduleOnce(SEL_SCHEDULE(&MyClass::Remove), 4);
        } else if (book_index == 2) {
            text2 = dynamic_cast<Text*>(this->getParent()->getChildByName("Text_25_Copy"));
            image = dynamic_cast<ImageView*>(this->getParent()->getChildByName("Image_3_Copy"));

            Sprite *sprite = Sprite::create();
            Animation* animation = Animation::create();
            sprite->setScale(1.5);
            for (int i = 2; i < 86; i=i+2) {
                char szName[100] = {0};
                sprintf(szName, "UI/huodao/huodaom/huodaom%02d.png", i);
                animation->addSpriteFrameWithFile(szName);
            }
            animation->setDelayPerUnit(4.0f / 42);
            animation->setRestoreOriginalFrame(false);

            sprite->runAction(RepeatForever::create(Animate::create(animation)));
            sprite->setPosition(Vec2(960, 540));
            sprite->setTag(62);
            this->getParent()->addChild(sprite);

            dt->scheduleOnce(SEL_SCHEDULE(&MyClass::Remove), 4);
        } else if (book_index == 3) {
            text2 = dynamic_cast<Text*>(this->getParent()->getChildByName("Text_25_Copy_0"));
            image = dynamic_cast<ImageView*>(this->getParent()->getChildByName("Image_3_Copy_0"));

            Sprite *sprite = Sprite::create();
            Animation* animation = Animation::create();
            sprite->setScale(1.5);
            for (int i = 2; i < 86; i=i+2) {
                char szName[100] = {0};
                sprintf(szName, "UI/huodao/huodaor/huodaor%02d.png", i);
                animation->addSpriteFrameWithFile(szName);
            }
            animation->setDelayPerUnit(4.0f / 42);
            animation->setRestoreOriginalFrame(false);

            sprite->runAction(RepeatForever::create(Animate::create(animation)));
            sprite->setPosition(Vec2(960, 540));
            sprite->setTag(63);
            this->getParent()->addChild(sprite);

            dt->scheduleOnce(SEL_SCHEDULE(&MyClass::Remove), 4);
        }

        text2->setVisible(false);
        image->setVisible(false);

        string tmp;
        tmp += "ableToBook_";
        int index = dynamic_cast<PageView*>(root->getChildByName("PageView_1"))->getCurPageIndex() + 1;
        tmp += String::createWithFormat("%d", index)->getCString();
        userDefault->setBoolForKey(tmp.c_str(), true);
        dt->setVisible(false);
    }
}

void MyClass::Remove(float t) {
    if (book_index == 1) {
        this->getParent()->removeChildByTag(61);
    } else if (book_index == 2) {
        this->getParent()->removeChildByTag(62);
    } else if (book_index == 3) {
        this->getParent()->removeChildByTag(63);
    }
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    TextureCache::getInstance()->removeUnusedTextures();
}

void MyClass::Update1(float t) {
    auto dt = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*)this, "Text_2"));
    string text = dynamic_cast<Text*>(dt)->getString();
    int second = 0;
    second = (text[6] - '0')*10 + (text[7] - '0');
    second--;
    text = "00:00:";
    if (second < 10) text += "0";
    text += String::createWithFormat("%d", second)->getCString();
    dynamic_cast<Text*>(dt)->setText(text);
    if (second == 0) {
        Sprite *sprite = Sprite::create();
         auto animation = Animation::create();
         sprite->setScale(1.5);

         for (int i = 1; i < 25; i++) {
         char szName[100] = {0};
         sprintf(szName, "UI/jianzhu1/jianzhu100%02d.png", i);
         animation->addSpriteFrameWithFile(szName);
         }
         animation->setDelayPerUnit(2.0f / 24);
         animation->setRestoreOriginalFrame(false);
         sprite->runAction(RepeatForever::create(Animate::create(animation)));
         sprite->setPosition(Vec2(960, 540));
         root->getChildByName("PageView_1")->getChildByName("Panel_1")->addChild(sprite);
         sprite->setTag(41);

        auto text = dynamic_cast<Text*>(this->getParent()->getChildByName("Text_2"));
        text->setVisible(false);
        auto image4 = dynamic_cast<ImageView*>(this->getParent()->getChildByName("Image_3"));
        image4->setVisible(false);

        dt->unscheduleAllCallbacks();
        dt->scheduleOnce(SEL_SCHEDULE(&MyClass::Update11), 1.8);
    }
}

void MyClass::Update11(float t) {
    auto image2 = dynamic_cast<ImageView*>(this->getParent()->getChildByName("Image_26"));
    image2->setVisible(false);
    image2->setTouchEnabled(false);
    auto image3 = dynamic_cast<ImageView*>(this->getParent()->getChildByName("Image_27"));
    image3->setVisible(true);
    auto image = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*) root, "Image_18"));
    image->setVisible(false);
    image->setTouchEnabled(false);
    auto image5 = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*) root, "Image_1"));
    image5->setTouchEnabled(true);

    root->getChildByName("PageView_1")->getChildByName("Panel_1")->removeChildByTag(41);
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    TextureCache::getInstance()->removeUnusedTextures();

    int money = userDefault->getIntegerForKey("money", 1405);
    money += 500;
    string money_str = String::createWithFormat("%d", money)->getCString();

    auto textBMLabel3 = dynamic_cast<Text*>(root->getChildByName("Text_36"));
    textBMLabel3->setString(money_str);

    for (int i = 0; i < 2; i++) {
        for (int j = 1; j < 5; j++) {
            char str[30] = "goodsUnlocked_1_";
            int len = strlen(str);
            str[len] = j + '0';
            str[len + 1] = '\0';
            bool tmp = userDefault->getBoolForKey(str, false);
            if (tmp == false) {
                tmp = true;
                userDefault->setBoolForKey(str, tmp);
                break;
            }
        }
    }

    for (int i = 1; i < 5; i++) {
        char str[30] = "goodsUnlocked_1_";
        int len = strlen(str);
        str[len] = i + '0';
        str[len + 1] = '\0';
        bool tmp = userDefault->getBoolForKey(str, false);
        if (tmp == true) {
            char str1[30] = "goodsBoxs_1_";
            int len1 = strlen(str1);
            str1[len1] = i + '0';
            str1[len1 + 1] = '\0';
            int boxs = userDefault->getIntegerForKey(str1, 0);
            boxs += 2;
            userDefault->setIntegerForKey(str1, boxs);
        }
    }

    userDefault->setIntegerForKey("goodsNum_1_1", 100);
    userDefault->setIntegerForKey("goodsNum_1_2", 100);
    userDefault->setIntegerForKey("goodsNum_1_3", 0);
    userDefault->setIntegerForKey("goodsNum_1_4", 0);
    userDefault->setBoolForKey("customeUnlocked_1_1", true);
    userDefault->setBoolForKey("customeUnlocked_1_2", true);
    userDefault->setBoolForKey("customeUnlocked_1_3", true);

    userDefault->flush();

    auto layer1 = CSLoader::createNode("Layer4.csb");
    auto bkg1 = LayerColor::create(Color4B(0, 0, 0, 128));
    Size winSize = Director::getInstance()->getWinSize();
    layer1->setPosition(winSize.width * 0.3, winSize.height *0.3);
    auto text1 = dynamic_cast<Text*>(layer1->getChildByName("Text_1"));
    string str = IConvConvert_GBKToUTF8("哇，店铺已经建造完成啦！！\n这个时候你可以选择进货！\n还能看看有什么新顾客！");
    text1->setString(str);

    bkg1->addChild(layer1);
    root->addChild(bkg1);
    auto btnClose1 = dynamic_cast<Button*>(layer1->getChildByName("Button_3"));
    btnClose1->addClickEventListener(([this, bkg1](Ref*) {
        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
        root->removeChild(bkg1);

        auto layer = CSLoader::createNode("Layer7.csb");
        auto bkg = LayerColor::create(Color4B(0, 0, 0, 128));
        Size winSize = Director::getInstance()->getWinSize();
        layer->setPosition(winSize.width * 0.1, winSize.height *0.1);
        bkg->addChild(layer);
        root->addChild(bkg, 2);
        auto btnClose = dynamic_cast<Button*>(layer->getChildByName("Button_5"));
        btnClose->addClickEventListener(([this, bkg](Ref*) {
            if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
            root->removeChild(bkg);
            grow(30, 0);

            Sprite *sprite = Sprite::create();
            sprite->setName("jiaocheng");
            root->addChild(sprite, 4);
            Size winSize = Director::getInstance()->getWinSize();
            sprite->setPosition(winSize.width * 0.5, winSize.height *0.5);
            sprite->setScale(2.25);
            Animation* animation = Animation::create();
            for (int i = 1; i < 14; i++) {
                 char szName[100] = {0};
                 sprintf(szName, "jiaocheng/jiaocheng%02d.jpg", i);
                 animation->addSpriteFrameWithFile(szName);
            }
            animation->setDelayPerUnit(39.0f / 13);
            animation->setRestoreOriginalFrame(false);

            sprite->runAction(Animate::create(animation));
            root->scheduleOnce(SEL_SCHEDULE(&MyClass::Update111), 38);

            root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update1), 5.0f, CC_REPEAT_FOREVER, 40);
            root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update11), 5.0f, CC_REPEAT_FOREVER, 41);
        }));
        auto dt = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*) layer, "Text_21"));
        dt->setString(userDefault->getStringForKey("ChineseName_1_1"));
        auto dt2 = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*) layer, "Text_25"));
        dt2->setString(userDefault->getStringForKey("ChineseName_1_2"));
        auto dt3 = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*) layer, "Text_26"));
        dt3->setString(userDefault->getStringForKey("ChineseName_1_3"));

        for (int i = 1; i <= 3; i++) {
            string t = "Image_";
            int tmp = 22 + i;
            int tmp2 = 9 + i;
            t += String::createWithFormat("%d", tmp)->getCString();
            string t2 = "Panel_";
            t2 += String::createWithFormat("%d", tmp2)->getCString();
            auto p = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*) layer, t.c_str()));
            Vec2 position = p->getPosition();

            char szName[100] = {0};
            sprintf(szName, "monsters/\%d/\%d.png", 1, i);
            Sprite *sprite = Sprite::create(szName);
            sprite->setAnchorPoint(Point(0.5, 0.5));
            sprite->setPosition(position);
            layer->getChildByName("Panel_9")->getChildByName(t2.c_str())->addChild(sprite);
        }
    }));
}

void MyClass::Update111(float t) {
    root->removeChildByName("jiaocheng");
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    TextureCache::getInstance()->removeUnusedTextures();
}

void MyClass::Update2(float t) {
    auto dt = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*)this, "Text_2_Copy"));
    string text = dynamic_cast<Text*>(dt)->getString();
    int second = 0;
    second = (text[6] - '0') * 10 + (text[7] - '0');
    second--;
    text = "00:00:";
    if (second < 10) text += "0";
    text += String::createWithFormat("%d", second)->getCString();
    dynamic_cast<Text*>(dt)->setText(text);

    if (second == 0) {
        Sprite *sprite = Sprite::create();
        sprite->setScale(1.5);

        auto animation = Animation::create();
        for (int i = 1; i < 50; i++) {
            char szName[100] = {0};
            sprintf(szName, "UI/jianzhu2/jianzhu200%02d.png", i);
            animation->addSpriteFrameWithFile(szName);
        }
        animation->setDelayPerUnit(3.3f / 49);
        animation->setRestoreOriginalFrame(false);

        sprite->runAction(RepeatForever::create(Animate::create(animation)));
        root->getChildByName("PageView_1")->getChildByName("Panel_1_Copy")->addChild(sprite);
        sprite->setPosition(Vec2(960, 540));
        sprite->setTag(42);

        auto text = dynamic_cast<Text*>(this->getParent()->getChildByName("Text_2_Copy"));
        text->setVisible(false);
        auto image4 = dynamic_cast<ImageView*>(this->getParent()->getChildByName("Image_3_Copy"));
        image4->setVisible(false);

        dt->unscheduleAllCallbacks();
        dt->scheduleOnce(SEL_SCHEDULE(&MyClass::Update12), 3.1);
    }
}

void MyClass::Update12(float t) {
    auto image2 = dynamic_cast<ImageView*>(this->getParent()->getChildByName("Image_26_Copy"));
    image2->setVisible(false);
    image2->setTouchEnabled(false);


    auto image3 = dynamic_cast<ImageView*>(this->getParent()->getChildByName("Image_27_Copy"));
    image3->setVisible(true);

    auto image = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*) root, "Image_18_Copy"));
    image->setVisible(false);
    image->setTouchEnabled(false);
    auto image5 = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*) root, "Image_1_Copy"));
    image5->setTouchEnabled(true);

    root->getChildByName("PageView_1")->getChildByName("Panel_1_Copy")->removeChildByTag(42);

    AnimationCache::getInstance()->removeAnimation("ani2");
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    TextureCache::getInstance()->removeUnusedTextures();

    for (int i = 0; i < 2; i++) {
        for (int j = 1; j < 5; j++) {
            char str[30] = "goodsUnlocked_2_";
            int len = strlen(str);
            str[len] = j + '0';
            str[len + 1] = '\0';
            bool tmp = userDefault->getBoolForKey(str, false);
            if (tmp == false) {
                tmp = true;
                userDefault->setBoolForKey(str, tmp);
                break;
            }
        }
    }

    for (int i = 1; i < 5; i++) {
        char str[30] = "goodsUnlocked_2_";
        int len = strlen(str);
        str[len] = i + '0';
        str[len + 1] = '\0';
        bool tmp = userDefault->getBoolForKey(str, false);
        if (tmp == true) {
            char str1[30] = "goodsBoxs_2_";
            int len1 = strlen(str1);
            str1[len1] = i + '0';
            str1[len1 + 1] = '\0';
            int boxs = userDefault->getIntegerForKey(str1, 0);
            boxs += 2;
            userDefault->setIntegerForKey(str1, boxs);
        }
    }

    userDefault->setIntegerForKey("goodsNum_2_1", 100);
    userDefault->setIntegerForKey("goodsNum_2_2", 100);
    userDefault->setIntegerForKey("goodsNum_2_3", 0);
    userDefault->setIntegerForKey("goodsNum_2_4", 0);
    userDefault->setBoolForKey("customeUnlocked_2_1", true);
    userDefault->setBoolForKey("customeUnlocked_2_2", true);
    userDefault->setBoolForKey("customeUnlocked_2_3", true);

    userDefault->flush();

    auto layer = CSLoader::createNode("Layer7.csb");
    auto bkg = LayerColor::create(Color4B(0, 0, 0, 128));
    Size winSize = Director::getInstance()->getWinSize();
    layer->setPosition(winSize.width * 0.1, winSize.height *0.1);
    bkg->addChild(layer);
    root->addChild(bkg, 2);
    auto btnClose = dynamic_cast<Button*>(layer->getChildByName("Button_5"));
    btnClose->addClickEventListener(([this, bkg](Ref*) {
        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
        root->removeChild(bkg);
        grow(30, 0);
    }));
    auto dt = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*) layer, "Text_21"));
    dt->setString(userDefault->getStringForKey("ChineseName_2_1"));
    auto dt2 = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*) layer, "Text_25"));
    dt2->setString(userDefault->getStringForKey("ChineseName_2_2"));
    auto dt3 = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*) layer, "Text_26"));
    dt3->setString(userDefault->getStringForKey("ChineseName_2_3"));

    for (int i = 1; i <= 3; i++) {
        string t = "Image_";
        int tmp = 22 + i;
        int tmp2 = 9 + i;
        t += String::createWithFormat("%d", tmp)->getCString();
        string t2 = "Panel_";
        t2 += String::createWithFormat("%d", tmp2)->getCString();
        auto p = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*) layer, t.c_str()));
        Vec2 position = p->getPosition();

        char szName[100] = {0};
        sprintf(szName, "monsters/\%d/\%d.png", 2, i);
        Sprite *sprite = Sprite::create(szName);
        sprite->setAnchorPoint(Point(0.5, 0.5));
        sprite->setPosition(position);
        layer->getChildByName("Panel_9")->getChildByName(t2.c_str())->addChild(sprite);
    }

    root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update2), 5.0f, CC_REPEAT_FOREVER, 1);
    root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update21), 5.0f, CC_REPEAT_FOREVER, 0.5);
}

void MyClass::Update3(float t) {
    auto dt = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*)this, "Text_2_Copy_0"));
    string text = dynamic_cast<Text*>(dt)->getString();
    int second = 0;
    second = (text[6] - '0') * 10 + (text[7] - '0');
    second--;
    text = "00:00:";
    if (second < 10) text += "0";
    text += String::createWithFormat("%d", second)->getCString();
    dynamic_cast<Text*>(dt)->setText(text);
    if (second == 0) {
        Sprite *sprite = Sprite::create();
        auto animation = Animation::create();
        sprite->setScale(1.5);

        for (int i = 1; i < 26; i++) {
            char szName[100] = {0};
            sprintf(szName, "UI/jianzhu3/jianzhu300%02d.png", i);
            animation->addSpriteFrameWithFile(szName);
        }
        animation->setDelayPerUnit(2.0f / 25);
        animation->setRestoreOriginalFrame(false);
        sprite->runAction(RepeatForever::create(Animate::create(animation)));
        root->getChildByName("PageView_1")->getChildByName("Panel_1_Copy_0")->addChild(sprite);
        sprite->setPosition(Vec2(960, 540));
        sprite->setTag(43);

        auto text = dynamic_cast<Text*>(this->getParent()->getChildByName("Text_2_Copy_0"));
        text->setVisible(false);
        auto image4 = dynamic_cast<ImageView*>(this->getParent()->getChildByName("Image_3_Copy_0"));
        image4->setVisible(false);

        dt->unscheduleAllCallbacks();
        dt->scheduleOnce(SEL_SCHEDULE(&MyClass::Update13), 1.8);
    }
}

void MyClass::Update13(float t) {
    auto image2 = dynamic_cast<ImageView*>(this->getParent()->getChildByName("Image_26_Copy_0"));
    image2->setVisible(false);
    image2->setTouchEnabled(false);
    auto image3 = dynamic_cast<ImageView*>(this->getParent()->getChildByName("Image_27_Copy_0"));
    image3->setVisible(true);

    auto image = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*) root, "Image_18_Copy_0"));
    image->setVisible(false);
    image->setTouchEnabled(false);
    auto image5 = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*) root, "Image_1_Copy_0"));
    image5->setTouchEnabled(true);

    root->getChildByName("PageView_1")->getChildByName("Panel_1_Copy_0")->removeChildByTag(43);
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    TextureCache::getInstance()->removeUnusedTextures();

    for (int i = 0; i < 2; i++) {
        for (int j = 1; j < 5; j++) {
            char str[30] = "goodsUnlocked_3_";
            int len = strlen(str);
            str[len] = j + '0';
            str[len + 1] = '\0';
            bool tmp = userDefault->getBoolForKey(str, false);
            if (tmp == false) {
                tmp = true;
                userDefault->setBoolForKey(str, tmp);
                break;
            }
        }
    }

    for (int i = 1; i < 5; i++) {
        char str[30] = "goodsUnlocked_3_";
        int len = strlen(str);
        str[len] = i + '0';
        str[len + 1] = '\0';
        bool tmp = userDefault->getBoolForKey(str, false);
        if (tmp == true) {
            char str1[30] = "goodsBoxs_3_";
            int len1 = strlen(str1);
            str1[len1] = i + '0';
            str1[len1 + 1] = '\0';
            int boxs = userDefault->getIntegerForKey(str1, 0);
            boxs += 2;
            userDefault->setIntegerForKey(str1, boxs);
        }
    }

    userDefault->setIntegerForKey("goodsNum_3_1", 100);
    userDefault->setIntegerForKey("goodsNum_3_2", 100);
    userDefault->setIntegerForKey("goodsNum_3_3", 0);
    userDefault->setIntegerForKey("goodsNum_3_4", 0);
    userDefault->setBoolForKey("customeUnlocked_3_1", true);
    userDefault->setBoolForKey("customeUnlocked_3_2", true);
    userDefault->setBoolForKey("customeUnlocked_3_3", true);

    userDefault->flush();

    auto layer = CSLoader::createNode("Layer7.csb");
    auto bkg = LayerColor::create(Color4B(0, 0, 0, 128));
    Size winSize = Director::getInstance()->getWinSize();
    layer->setPosition(winSize.width * 0.1, winSize.height *0.1);
    bkg->addChild(layer);
    root->addChild(bkg, 2);
    auto btnClose = dynamic_cast<Button*>(layer->getChildByName("Button_5"));
    btnClose->addClickEventListener(([this, bkg](Ref*) {
        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
        root->removeChild(bkg);
        grow(30, 0);
    }));
    auto dt = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*) layer, "Text_21"));
    dt->setString(userDefault->getStringForKey("ChineseName_3_1"));
    auto dt2 = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*) layer, "Text_25"));
    dt2->setString(userDefault->getStringForKey("ChineseName_3_2"));
    auto dt3 = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*) layer, "Text_26"));
    dt3->setString(userDefault->getStringForKey("ChineseName_3_3"));

    for (int i = 1; i <= 3; i++) {
        string t = "Image_";
        int tmp = 22 + i;
        int tmp2 = 9 + i;
        t += String::createWithFormat("%d", tmp)->getCString();
        string t2 = "Panel_";
        t2 += String::createWithFormat("%d", tmp2)->getCString();
        auto p = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*) layer, t.c_str()));
        Vec2 position = p->getPosition();

        char szName[100] = {0};
        sprintf(szName, "monsters/\%d/\%d.png", 3, i);
        Sprite *sprite = Sprite::create(szName);
        sprite->setAnchorPoint(Point(0.5, 0.5));
        sprite->setPosition(position);
        layer->getChildByName("Panel_9")->getChildByName(t2.c_str())->addChild(sprite);
    }

    root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update3), 5.0f, CC_REPEAT_FOREVER, 1);
    root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update31), 5.0f, CC_REPEAT_FOREVER, 2);
}

void MyClass::Custom_Update1(float t) {
    auto view = dynamic_cast<PageView*>(root->getChildByName("PageView_1"));

    srand((unsigned) time(NULL));
    int j = (rand() % 6 + 1);
    float tim = (rand() % 5)*1.0 / 10.0 + 2.0;
    string str = "customeUnlocked_1_";
    str += String::createWithFormat("%d", j)->getCString();
    while (userDefault->getBoolForKey(str.c_str(), false) == false) {
        j = (rand() % 6 + 1);
        str = "customeUnlocked_1_";
        str += String::createWithFormat("%d", j)->getCString();
    }

    string str1 = "customeName_";
    str1 += String::createWithFormat("%d", 1)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    string name = userDefault->getStringForKey(str1.c_str());
    str1 = "customeFrames_";
    str1 += String::createWithFormat("%d", 1)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    int frames = userDefault->getIntegerForKey(str1.c_str());

    string tmp = "customeLove_1_";
    tmp += String::createWithFormat("%d", j)->getCString();
    int love = userDefault->getIntegerForKey(tmp.c_str(), 0);

    string tmp5 = "customeNeeds_";
    tmp5 += String::createWithFormat("%d", j)->getCString();
    int num1 = userDefault->getIntegerForKey(tmp5.c_str(), 312);
    int num2 = num1 % 10;
    num1 /= 10;
    int num3 = num1 % 10;
    int num4 = num1 / 10;

    satis1 = false;
    money1 = 0;

    tmp = "goodsNum_1_";
    tmp += String::createWithFormat("%d", num2)->getCString();
    int good1 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box1;
    money1 = 0;
    if (good1 > 0) {
        good1--;
        satis1 = true;
        box1 = good1 / 50;
        if (good1 % 50) box1++;
        userDefault->setIntegerForKey(tmp.c_str(), good1);
        tmp = "goodsBoxs_1_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box1);
        tmp = "goodProfit_1_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        money1 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    tmp = "goodsNum_1_";
    tmp += String::createWithFormat("%d", num3)->getCString();
    int good2 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box2;
    if (good2 > 0) {
        good2--;
        satis1 = true;
        box2 = good2 / 50;
        if (good2 % 50) box2++;
        userDefault->setIntegerForKey(tmp.c_str(), good2);
        tmp = "goodsBoxs_1_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box2);
        tmp = "goodProfit_1_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        money1 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    if (love >= 5) {
        tmp = "goodsNum_1_";
        tmp += String::createWithFormat("%d", num4)->getCString();
        int good3 = userDefault->getIntegerForKey(tmp.c_str(), 0);
        int box3;
        if (good3 > 0) {
            good3--;
            satis1 = true;
            box3 = good3 / 50;
            if (good3 % 50) box3++;
            userDefault->setIntegerForKey(tmp.c_str(), good3);
            tmp = "goodsBoxs_1_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            userDefault->setIntegerForKey(tmp.c_str(), box3);
            tmp = "goodProfit_1_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            money1 += userDefault->getIntegerForKey(tmp.c_str(), 0);
        }
    }

    Sprite *sprite = Sprite::create();
    str1 = "customeScale_";
    str1 += String::createWithFormat("%d", 1)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    double scale = userDefault->getDoubleForKey(str1.c_str());
    sprite->setScale(scale);
    AnimationCache* cache = AnimationCache::getInstance();
    Animation* animation = cache->getAnimation(name);

    if (animation == NULL) {
        animation = Animation::create();
        for (int i = 1; i < frames; i++) {
            char szName[100] = {0};
            sprintf(szName, "monsters/%s/%s%02d.png", name.c_str(), name.c_str(), i);
            animation->addSpriteFrameWithFile(szName);
        }
        animation->setDelayPerUnit(1.0f / frames);
        animation->setRestoreOriginalFrame(true);
        cache->addAnimation(animation, name);
    }

    sprite->runAction(RepeatForever::create(Animate::create(animation)));

    Size size = view->getSize();
    sprite->setPosition(Vec2(size.width+100, 300));
    view->getChildByName("Panel_1")->addChild(sprite);
    sprite->setName("sprite1");
   
    char szName2[100] = {0};
    if (satis1) sprintf(szName2, "UI/\Success.png");
    else sprintf(szName2, "UI/\Fail.png");
    Sprite *sprite2 = Sprite::create(szName2);
    sprite2->runAction(FadeOut::create(0.0));
    view->getChildByName("Panel_1")->addChild(sprite2);
    
    sprite2->setName("sprite11");
    
    sprite2->setPosition(Vec2(size.width+100, 500));

    Size size1 = sprite2->getContentSize();
    ImageView* image1 = ImageView::create("UI/\Fail.png");
    image1->setOpacity(0);
    image1->setContentSize(size1);
    image1->setPosition(Vec2(size1.width/2, size1.height/2));
    image1->setTouchEnabled(true);
    sprite2->addChild(image1);
    bool satis = satis1;
    image1->addClickEventListener(([this, sprite2, satis, j](Ref*) {
        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
        sprite2->setVisible(false);
        if (satis && curHun) {
            curHun--;
            auto loading2 = dynamic_cast<LoadingBar*>(root->getChildByName("LoadingBar_3"));
            loading2->setPercent(curHun*100.0 / maxHun);
            auto textBMLabel4 = dynamic_cast<Text*>(root->getChildByName("Text_1"));
            string curHun_str = String::createWithFormat("%d", curHun)->getCString();
            string maxHun_str = String::createWithFormat("%d", maxHun)->getCString();
            textBMLabel4->setString(curHun_str + "/" + maxHun_str);

            string tmp2 = "customeLove_1_";
            tmp2 += String::createWithFormat("%d", j)->getCString();
            int love2 = userDefault->getIntegerForKey(tmp2.c_str(), 0);
            love2++;
            if (love2 <= 5) userDefault->setIntegerForKey(tmp2.c_str(), love2);
            judge1();
        }
    }));

    
    sprite2->runAction(Sequence::create(MoveBy::create(tim+0.5, Vec2(-size.width / 2-100, 0)), MoveBy::create(1.5, Vec2(0, 0)), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(-size.width / 2+100, 0)), Hide::create(), NULL));
    sprite->runAction(Sequence::create(MoveBy::create(tim+0.5, Vec2(-size.width / 2-100, 0)), FadeOut::create(0.5), MoveBy::create(1, Vec2(0, 0)), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(-size.width / 2+100, 0)), Hide::create(), NULL));
    sprite->scheduleOnce(SEL_SCHEDULE(&MyClass::Release1), 7.0f);
}

void MyClass::Custom_Update11(float t) {
    auto view = dynamic_cast<PageView*>(root->getChildByName("PageView_1"));

    srand((unsigned) time(NULL));
    int j = (rand() % 6 + 1);
    float tim = (rand() % 5)*1.0 / 10.0 + 2.0;
    string str = "customeUnlocked_1_";
    str += String::createWithFormat("%d", j)->getCString();
    while (userDefault->getBoolForKey(str.c_str(), false) == false) {
        j = (rand() % 6 + 1);
        str = "customeUnlocked_1_";
        str += String::createWithFormat("%d", j)->getCString();
    }

    string str1 = "customeName_";
    str1 += String::createWithFormat("%d", 1)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    str1 += "_1";
    string name = userDefault->getStringForKey(str1.c_str());
    str1 = "customeFrames_";
    str1 += String::createWithFormat("%d", 1)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    int frames = userDefault->getIntegerForKey(str1.c_str());

    string tmp = "customeLove_1_";
    tmp += String::createWithFormat("%d", j)->getCString();
    int love = userDefault->getIntegerForKey(tmp.c_str(), 0);

    string tmp5 = "customeNeeds_";
    tmp5 += String::createWithFormat("%d", j)->getCString();
    int num1 = userDefault->getIntegerForKey(tmp5.c_str(), 312);
    int num2 = num1 % 10;
    num1 /= 10;
    int num3 = num1 % 10;
    int num4 = num1 / 10;

    satis1 = false;
    money1 = 0;

    tmp = "goodsNum_1_";
    tmp += String::createWithFormat("%d", num2)->getCString();
    int good1 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box1;
    money1 = 0;
    if (good1 > 0) {
        good1--;
        satis1 = true;
        box1 = good1 / 50;
        if (good1 % 50) box1++;
        userDefault->setIntegerForKey(tmp.c_str(), good1);
        tmp = "goodsBoxs_1_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box1);
        tmp = "goodProfit_1_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        money1 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    tmp = "goodsNum_1_";
    tmp += String::createWithFormat("%d", num3)->getCString();
    int good2 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box2;
    if (good2 > 0) {
        good2--;
        satis1 = true;
        box2 = good2 / 50;
        if (good2 % 50) box2++;
        userDefault->setIntegerForKey(tmp.c_str(), good2);
        tmp = "goodsBoxs_1_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box2);
        tmp = "goodProfit_1_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        money1 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    if (love >= 5) {
        tmp = "goodsNum_1_";
        tmp += String::createWithFormat("%d", num4)->getCString();
        int good3 = userDefault->getIntegerForKey(tmp.c_str(), 0);
        int box3;
        if (good3 > 0) {
            good3--;
            satis1 = true;
            box3 = good3 / 50;
            if (good3 % 50) box3++;
            userDefault->setIntegerForKey(tmp.c_str(), good3);
            tmp = "goodsBoxs_1_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            userDefault->setIntegerForKey(tmp.c_str(), box3);
            tmp = "goodProfit_1_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            money1 += userDefault->getIntegerForKey(tmp.c_str(), 0);
        }
    }

    Sprite *sprite = Sprite::create();
    str1 = "customeScale_";
    str1 += String::createWithFormat("%d", 1)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    double scale = userDefault->getDoubleForKey(str1.c_str());
    sprite->setScale(scale);
    AnimationCache* cache = AnimationCache::getInstance();
    Animation* animation = cache->getAnimation(name);

    if (animation == NULL) {
        animation = Animation::create();
        for (int i = 1; i < frames; i++) {
            char szName[100] = {0};
            sprintf(szName, "monsters/%s/%s%02d.png", name.c_str(), name.c_str(), i);
            animation->addSpriteFrameWithFile(szName);
        }
        animation->setDelayPerUnit(1.0f / frames);
        animation->setRestoreOriginalFrame(true);
        cache->addAnimation(animation, name);
    }

    sprite->runAction(RepeatForever::create(Animate::create(animation)));

    Size size = view->getSize();
    sprite->setPosition(Vec2(-100, 300));
    view->getChildByName("Panel_1")->addChild(sprite);
    sprite->setName("sprite1");

    char szName2[100] = {0};
    if (satis1) sprintf(szName2, "UI/\Success.png");
    else sprintf(szName2, "UI/\Fail.png");
    Sprite *sprite2 = Sprite::create(szName2);
    sprite2->runAction(FadeOut::create(0.0));
    view->getChildByName("Panel_1")->addChild(sprite2);
    
    sprite2->setName("sprite11");
    sprite2->setPosition(Vec2(-100, 500));
   

    Size size1 = sprite2->getContentSize();
    ImageView* image1 = ImageView::create("UI/\Fail.png");
    image1->setOpacity(0);
    image1->setContentSize(size1);
    image1->setPosition(Vec2(size1.width / 2, size1.height / 2));
    image1->setTouchEnabled(true);
    sprite2->addChild(image1);
    bool satis = satis1;
    image1->addClickEventListener(([this, sprite2, satis, j](Ref*) {
        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
        sprite2->setVisible(false);
        if (satis && curHun) {
            curHun--;
            auto loading2 = dynamic_cast<LoadingBar*>(root->getChildByName("LoadingBar_3"));
            loading2->setPercent(curHun*100.0 / maxHun);
            auto textBMLabel4 = dynamic_cast<Text*>(root->getChildByName("Text_1"));
            string curHun_str = String::createWithFormat("%d", curHun)->getCString();
            string maxHun_str = String::createWithFormat("%d", maxHun)->getCString();
            textBMLabel4->setString(curHun_str + "/" + maxHun_str);

            string tmp2 = "customeLove_1_";
            tmp2 += String::createWithFormat("%d", j)->getCString();
            int love2 = userDefault->getIntegerForKey(tmp2.c_str(), 0);
            love2++;
            if (love2 <= 5) userDefault->setIntegerForKey(tmp2.c_str(), love2);

            judge1();
        }
    }));

    sprite2->runAction(Sequence::create(MoveBy::create(tim+0.5, Vec2(size.width / 2+100, 0)), MoveBy::create(1.5, Vec2(0, 0)), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(size.width / 2-100, 0)), Hide::create(), NULL));
    sprite->runAction(Sequence::create(MoveBy::create(tim+0.5, Vec2(size.width / 2+100, 0)), FadeOut::create(0.5), MoveBy::create(1, Vec2(0, 0)), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(size.width / 2-100, 0)), Hide::create(), NULL));
    sprite->scheduleOnce(SEL_SCHEDULE(&MyClass::Release1), 7.0f);
}

void MyClass::Custom_Update2(float t) {
    auto view = dynamic_cast<PageView*>(root->getChildByName("PageView_1"));

    srand((unsigned) time(NULL));
    int j = (rand() % 6 + 1);
    float tim = (rand() % 5)*1.0 / 10.0 + 2.0;
    string str = "customeUnlocked_2_";
    str += String::createWithFormat("%d", j)->getCString();
    while (userDefault->getBoolForKey(str.c_str(), false) == false) {
        j = (rand() % 6 + 1);
        str = "customeUnlocked_2_";
        str += String::createWithFormat("%d", j)->getCString();
    }

    string str1 = "customeName_";
    str1 += String::createWithFormat("%d", 2)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    string name = userDefault->getStringForKey(str1.c_str());
    str1 = "customeFrames_";
    str1 += String::createWithFormat("%d", 2)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    int frames = userDefault->getIntegerForKey(str1.c_str());

    string tmp = "customeLove_2_";
    tmp += String::createWithFormat("%d", j)->getCString();
    int love = userDefault->getIntegerForKey(tmp.c_str(), 0);

    string tmp5 = "customeNeeds_";
    tmp5 += String::createWithFormat("%d", j)->getCString();
    int num1 = userDefault->getIntegerForKey(tmp5.c_str(), 312);
    int num2 = num1 % 10;
    num1 /= 10;
    int num3 = num1 % 10;
    int num4 = num1 / 10;

    satis2 = false;
    money2 = 0;

    tmp = "goodsNum_2_";
    tmp += String::createWithFormat("%d", num2)->getCString();
    int good1 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box1;
    money2 = 0;
    if (good1 > 0) {
        good1--;
        satis2 = true;
        box1 = good1 / 50;
        if (good1 % 50) box1++;
        userDefault->setIntegerForKey(tmp.c_str(), good1);
        tmp = "goodsBoxs_2_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box1);
        tmp = "goodProfit_2_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        money2 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    tmp = "goodsNum_2_";
    tmp += String::createWithFormat("%d", num3)->getCString();
    int good2 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box2;
    if (good2 > 0) {
        good2--;
        satis2 = true;
        box2 = good2 / 50;
        if (good2 % 50) box2++;
        userDefault->setIntegerForKey(tmp.c_str(), good2);
        tmp = "goodsBoxs_2_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box2);
        tmp = "goodProfit_2_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        money2 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    if (love >= 5) {
        tmp = "goodsNum_2_";
        tmp += String::createWithFormat("%d", num4)->getCString();
        int good3 = userDefault->getIntegerForKey(tmp.c_str(), 0);
        int box3;
        if (good3 > 0) {
            good3--;
            satis2 = true;
            box3 = good3 / 50;
            if (good3 % 50) box3++;
            userDefault->setIntegerForKey(tmp.c_str(), good3);
            tmp = "goodsBoxs_2_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            userDefault->setIntegerForKey(tmp.c_str(), box3);
            tmp = "goodProfit_2_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            money2 += userDefault->getIntegerForKey(tmp.c_str(), 0);
        }
    }

    Sprite *sprite = Sprite::create();
    str1 = "customeScale_";
    str1 += String::createWithFormat("%d", 2)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    double scale = userDefault->getDoubleForKey(str1.c_str());
    sprite->setScale(scale);
    AnimationCache* cache = AnimationCache::getInstance();
    Animation* animation = cache->getAnimation(name);

    if (animation == NULL) {
        animation = Animation::create();
        for (int i = 1; i < frames; i++) {
            char szName[100] = {0};
            sprintf(szName, "monsters/%s/%s%02d.png", name.c_str(), name.c_str(), i);
            animation->addSpriteFrameWithFile(szName);
        }
        animation->setDelayPerUnit(1.0f / frames);
        animation->setRestoreOriginalFrame(true);
        cache->addAnimation(animation, name);
    }

    sprite->runAction(RepeatForever::create(Animate::create(animation)));

    Size size = view->getSize();
    sprite->setPosition(Vec2(size.width+100, 300));
    view->getChildByName("Panel_1_Copy")->addChild(sprite);
    sprite->setName("sprite2");

    char szName2[100] = {0};
    if (satis2) sprintf(szName2, "UI/\Success.png");
    else sprintf(szName2, "UI/\Fail.png");
    Sprite *sprite2 = Sprite::create(szName2);
    view->getChildByName("Panel_1_Copy")->addChild(sprite2);
    //sprite2->scheduleOnce(SEL_SCHEDULE(&MyClass::Delay2), 2.0f);
    sprite2->setName("sprite21");
    sprite2->setPosition(Vec2(size.width+100, 500));
   

    Size size1 = sprite2->getContentSize();
    ImageView* image1 = ImageView::create("UI/\Fail.png");
    image1->setOpacity(0);
    image1->setContentSize(size1);
    image1->setPosition(Vec2(size1.width / 2, size1.height / 2));
    image1->setTouchEnabled(true);
    sprite2->addChild(image1);
    bool satis = satis2;
    image1->addClickEventListener(([this, sprite2, satis, j](Ref*) {
        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");;
        sprite2->setVisible(false);
        if (satis && curHun) {
            curHun--;
            auto loading2 = dynamic_cast<LoadingBar*>(root->getChildByName("LoadingBar_3"));
            loading2->setPercent(curHun*100.0 / maxHun);
            auto textBMLabel4 = dynamic_cast<Text*>(root->getChildByName("Text_1"));
            string curHun_str = String::createWithFormat("%d", curHun)->getCString();
            string maxHun_str = String::createWithFormat("%d", maxHun)->getCString();
            textBMLabel4->setString(curHun_str + "/" + maxHun_str);

            string tmp2 = "customeLove_2_";
            tmp2 += String::createWithFormat("%d", j)->getCString();
            int love2 = userDefault->getIntegerForKey(tmp2.c_str(), 0);
            love2++;
            if (love2 <= 5) userDefault->setIntegerForKey(tmp2.c_str(), love2);

            judge2();
        }
    }));

    sprite2->runAction(Sequence::create(Hide::create(), FadeOut::create(0.0), MoveBy::create(tim+0.5, Vec2(-size.width / 2-100, 0)), MoveBy::create(1.5, Vec2(0, 0)), Show::create(), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(-size.width / 2+100, 0)), Hide::create(), NULL));
    sprite->runAction(Sequence::create(MoveBy::create(tim+0.5, Vec2(-size.width / 2-100, 0)), FadeOut::create(0.5), MoveBy::create(1, Vec2(0, 0)), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(-size.width / 2+100, 0)), Hide::create(), NULL));
    sprite->scheduleOnce(SEL_SCHEDULE(&MyClass::Release2), 7.0f);
}

void MyClass::Custom_Update21(float t) {
    auto view = dynamic_cast<PageView*>(root->getChildByName("PageView_1"));

    srand((unsigned) time(NULL));
    int j = (rand() % 6 + 1);
    float tim = (rand() % 5)*1.0 / 10.0 + 2.0;
    string str = "customeUnlocked_2_";
    str += String::createWithFormat("%d", j)->getCString();
    while (userDefault->getBoolForKey(str.c_str(), false) == false) {
        j = (rand() % 6 + 1);
        str = "customeUnlocked_2_";
        str += String::createWithFormat("%d", j)->getCString();
    }

    string str1 = "customeName_";
    str1 += String::createWithFormat("%d", 2)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    str1 += "_1";
    string name = userDefault->getStringForKey(str1.c_str());
    str1 = "customeFrames_";
    str1 += String::createWithFormat("%d", 2)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    int frames = userDefault->getIntegerForKey(str1.c_str());

    string tmp = "customeLove_2_";
    tmp += String::createWithFormat("%d", j)->getCString();
    int love = userDefault->getIntegerForKey(tmp.c_str(), 0);

    string tmp5 = "customeNeeds_";
    tmp5 += String::createWithFormat("%d", j)->getCString();
    int num1 = userDefault->getIntegerForKey(tmp5.c_str(), 312);
    int num2 = num1 % 10;
    num1 /= 10;
    int num3 = num1 % 10;
    int num4 = num1 / 10;

    satis2 = false;
    money2 = 0;

    tmp = "goodsNum_2_";
    tmp += String::createWithFormat("%d", num2)->getCString();
    int good1 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box1;
    money2 = 0;
    if (good1 > 0) {
        good1--;
        satis2 = true;
        box1 = good1 / 50;
        if (good1 % 50) box1++;
        userDefault->setIntegerForKey(tmp.c_str(), good1);
        tmp = "goodsBoxs_2_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box1);
        tmp = "goodProfit_2_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        money2 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    tmp = "goodsNum_2_";
    tmp += String::createWithFormat("%d", num3)->getCString();
    int good2 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box2;
    if (good2 > 0) {
        good2--;
        satis2 = true;
        box2 = good2 / 50;
        if (good2 % 50) box2++;
        userDefault->setIntegerForKey(tmp.c_str(), good2);
        tmp = "goodsBoxs_2_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box2);
        tmp = "goodProfit_2_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        money2 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    if (love >= 5) {
        tmp = "goodsNum_2_";
        tmp += String::createWithFormat("%d", num4)->getCString();
        int good3 = userDefault->getIntegerForKey(tmp.c_str(), 0);
        int box3;
        if (good3 > 0) {
            good3--;
            satis2 = true;
            box3 = good3 / 50;
            if (good3 % 50) box3++;
            userDefault->setIntegerForKey(tmp.c_str(), good3);
            tmp = "goodsBoxs_2_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            userDefault->setIntegerForKey(tmp.c_str(), box3);
            tmp = "goodProfit_2_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            money2 += userDefault->getIntegerForKey(tmp.c_str(), 0);
        }
    }

    Sprite *sprite = Sprite::create();
    str1 = "customeScale_";
    str1 += String::createWithFormat("%d", 2)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    double scale = userDefault->getDoubleForKey(str1.c_str());
    sprite->setScale(scale);
    AnimationCache* cache = AnimationCache::getInstance();
    Animation* animation = cache->getAnimation(name);

    if (animation == NULL) {
        animation = Animation::create();
        for (int i = 1; i < frames; i++) {
            char szName[100] = {0};
            sprintf(szName, "monsters/%s/%s%02d.png", name.c_str(), name.c_str(), i);
            animation->addSpriteFrameWithFile(szName);
        }
        animation->setDelayPerUnit(1.0f / frames);
        animation->setRestoreOriginalFrame(true);
        cache->addAnimation(animation, name);
    }

    sprite->runAction(RepeatForever::create(Animate::create(animation)));
    Size size = view->getSize();
    sprite->setPosition(Vec2(-100, 300));
    view->getChildByName("Panel_1_Copy")->addChild(sprite);
    sprite->setName("sprite2");

    char szName2[100] = {0};
    if (satis2) sprintf(szName2, "UI/\Success.png");
    else sprintf(szName2, "UI/\Fail.png");
    Sprite *sprite2 = Sprite::create(szName2);
    view->getChildByName("Panel_1_Copy")->addChild(sprite2);
    //sprite2->scheduleOnce(SEL_SCHEDULE(&MyClass::Delay2), 2.0f);
    sprite2->setName("sprite21");
    sprite2->setPosition(Vec2(-100, 500));
   

    Size size1 = sprite2->getContentSize();
    ImageView* image1 = ImageView::create("UI/\Fail.png");
    image1->setOpacity(0);
    image1->setContentSize(size1);
    image1->setPosition(Vec2(size1.width / 2, size1.height / 2));
    image1->setTouchEnabled(true);
    sprite2->addChild(image1);
    bool satis = satis2;
    image1->addClickEventListener(([this, sprite2, satis, j](Ref*) {
        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
        sprite2->setVisible(false);
        if (satis && curHun) {
            curHun--;
            auto loading2 = dynamic_cast<LoadingBar*>(root->getChildByName("LoadingBar_3"));
            loading2->setPercent(curHun*100.0 / maxHun);
            auto textBMLabel4 = dynamic_cast<Text*>(root->getChildByName("Text_1"));
            string curHun_str = String::createWithFormat("%d", curHun)->getCString();
            string maxHun_str = String::createWithFormat("%d", maxHun)->getCString();
            textBMLabel4->setString(curHun_str + "/" + maxHun_str);

            string tmp2 = "customeLove_2_";
            tmp2 += String::createWithFormat("%d", j)->getCString();
            int love2 = userDefault->getIntegerForKey(tmp2.c_str(), 0);
            love2++;
            if (love2 <= 5) userDefault->setIntegerForKey(tmp2.c_str(), love2);

            judge2();
        }
    }));

    sprite2->runAction(Sequence::create(Hide::create(), FadeOut::create(0.0), MoveBy::create(tim+0.5, Vec2(size.width / 2+100, 0)), MoveBy::create(1.5, Vec2(0, 0)), Show::create(), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(size.width / 2-100, 0)), Hide::create(), NULL));
    sprite->runAction(Sequence::create(MoveBy::create(tim+0.5, Vec2(size.width / 2+100, 0)), FadeOut::create(0.5), MoveBy::create(1, Vec2(0, 0)), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(size.width / 2-100, 0)), Hide::create(), NULL));
    sprite->scheduleOnce(SEL_SCHEDULE(&MyClass::Release2), 7.0f);
}

void MyClass::Custom_Update3(float t) {
    auto view = dynamic_cast<PageView*>(root->getChildByName("PageView_1"));

    srand((unsigned) time(NULL));
    int j = (rand() % 6 + 1);
    float tim = (rand() % 5)*1.0 / 10.0 + 2.0;
    string str = "customeUnlocked_3_";
    str += String::createWithFormat("%d", j)->getCString();
    while (userDefault->getBoolForKey(str.c_str(), false) == false) {
        j = (rand() % 6 + 1);
        str = "customeUnlocked_3_";
        str += String::createWithFormat("%d", j)->getCString();
    }

    string str1 = "customeName_";
    str1 += String::createWithFormat("%d", 3)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    string name = userDefault->getStringForKey(str1.c_str());
    str1 = "customeFrames_";
    str1 += String::createWithFormat("%d", 3)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    int frames = userDefault->getIntegerForKey(str1.c_str());

    string tmp = "customeLove_3_";
    tmp += String::createWithFormat("%d", j)->getCString();
    int love = userDefault->getIntegerForKey(tmp.c_str(), 0);

    string tmp5 = "customeNeeds_";
    tmp5 += String::createWithFormat("%d", j)->getCString();
    int num1 = userDefault->getIntegerForKey(tmp5.c_str(), 312);
    int num2 = num1 % 10;
    num1 /= 10;
    int num3 = num1 % 10;
    int num4 = num1 / 10;

    satis3 = false;
    money3 = 0;

    tmp = "goodsNum_3_";
    tmp += String::createWithFormat("%d", num2)->getCString();
    int good1 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box1;
    money3 = 0;
    if (good1 > 0) {
        good1--;
        satis3 = true;
        box1 = good1 / 50;
        if (good1 % 50) box1++;
        userDefault->setIntegerForKey(tmp.c_str(), good1);
        tmp = "goodsBoxs_3_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box1);
        tmp = "goodProfit_3_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        money3 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    tmp = "goodsNum_3_";
    tmp += String::createWithFormat("%d", num3)->getCString();
    int good2 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box2;
    if (good2 > 0) {
        good2--;
        satis3 = true;
        box2 = good2 / 50;
        if (good2 % 50) box2++;
        userDefault->setIntegerForKey(tmp.c_str(), good2);
        tmp = "goodsBoxs_3_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box2);
        tmp = "goodProfit_3_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        money3 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    if (love >= 5) {
        tmp = "goodsNum_3_";
        tmp += String::createWithFormat("%d", num4)->getCString();
        int good3 = userDefault->getIntegerForKey(tmp.c_str(), 0);
        int box3;
        if (good3 > 0) {
            good3--;
            satis3 = true;
            box3 = good3 / 50;
            if (good3 % 50) box3++;
            userDefault->setIntegerForKey(tmp.c_str(), good3);
            tmp = "goodsBoxs_3_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            userDefault->setIntegerForKey(tmp.c_str(), box3);
            tmp = "goodProfit_3_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            money3 += userDefault->getIntegerForKey(tmp.c_str(), 0);
        }
    }

    Sprite *sprite = Sprite::create();
    str1 = "customeScale_";
    str1 += String::createWithFormat("%d", 3)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    double scale = userDefault->getDoubleForKey(str1.c_str());
    sprite->setScale(scale);
    AnimationCache* cache = AnimationCache::getInstance();
    Animation* animation = cache->getAnimation(name);

    if (animation == NULL) {
        animation = Animation::create();
        for (int i = 1; i < frames; i++) {
            char szName[100] = {0};
            sprintf(szName, "monsters/%s/%s%02d.png", name.c_str(), name.c_str(), i);
            animation->addSpriteFrameWithFile(szName);
        }
        animation->setDelayPerUnit(1.0f / frames);
        animation->setRestoreOriginalFrame(true);
        cache->addAnimation(animation, name);
    }

    sprite->runAction(RepeatForever::create(Animate::create(animation)));

    Size size = view->getSize();
    sprite->setPosition(Vec2(size.width+100, 350));
    view->getChildByName("Panel_1_Copy_0")->addChild(sprite);
    sprite->setName("sprite3");

    char szName2[100] = {0};
    if (satis3) sprintf(szName2, "UI/\Success.png");
    else sprintf(szName2, "UI/\Fail.png");
    Sprite *sprite2 = Sprite::create(szName2);
    view->getChildByName("Panel_1_Copy_0")->addChild(sprite2);
    //sprite2->scheduleOnce(SEL_SCHEDULE(&MyClass::Delay3), 2.0f);
    sprite2->setName("sprite31");
    sprite2->setPosition(Vec2(size.width+100, 550));
    

    Size size1 = sprite2->getContentSize();
    ImageView* image1 = ImageView::create("UI/\Fail.png");
    image1->setOpacity(0);
    image1->setContentSize(size1);
    image1->setPosition(Vec2(size1.width / 2, size1.height / 2));
    image1->setTouchEnabled(true);
    sprite2->addChild(image1);
    bool satis = satis3;
    image1->addClickEventListener(([this, sprite2, satis, j](Ref*) {
        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
        sprite2->setVisible(false);
        if (satis && curHun) {
            curHun--;
            auto loading2 = dynamic_cast<LoadingBar*>(root->getChildByName("LoadingBar_3"));
            loading2->setPercent(curHun*100.0 / maxHun);
            auto textBMLabel4 = dynamic_cast<Text*>(root->getChildByName("Text_1"));
            string curHun_str = String::createWithFormat("%d", curHun)->getCString();
            string maxHun_str = String::createWithFormat("%d", maxHun)->getCString();
            textBMLabel4->setString(curHun_str + "/" + maxHun_str);

            string tmp2 = "customeLove_3_";
            tmp2 += String::createWithFormat("%d", j)->getCString();
            int love2 = userDefault->getIntegerForKey(tmp2.c_str(), 0);
            love2++;
            if (love2 <= 5) userDefault->setIntegerForKey(tmp2.c_str(), love2);

            judge3();
        }
    }));

    sprite2->runAction(Sequence::create(Hide::create(), FadeOut::create(0.0), MoveBy::create(tim+0.5, Vec2(-size.width / 2-100, 0)), MoveBy::create(1.5, Vec2(0, 0)), Show::create(), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(-size.width / 2+100, 0)), Hide::create(), NULL));
    sprite->runAction(Sequence::create(MoveBy::create(tim+0.5, Vec2(-size.width / 2-100, 0)), FadeOut::create(0.5), MoveBy::create(1, Vec2(0, 0)), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(-size.width / 2+100, 0)), Hide::create(), NULL));
    sprite->scheduleOnce(SEL_SCHEDULE(&MyClass::Release3), 7.0f);
}

void MyClass::Custom_Update31(float t) {
    auto view = dynamic_cast<PageView*>(root->getChildByName("PageView_1"));

    srand((unsigned) time(NULL));
    int j = (rand() % 6 + 1);
    float tim = (rand() % 5)*1.0 / 10.0 + 2.0;
    string str = "customeUnlocked_3_";
    str += String::createWithFormat("%d", j)->getCString();
    while (userDefault->getBoolForKey(str.c_str(), false) == false) {
        j = (rand() % 6 + 1);
        str = "customeUnlocked_3_";
        str += String::createWithFormat("%d", j)->getCString();
    }

    string str1 = "customeName_";
    str1 += String::createWithFormat("%d", 3)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    str1 += "_1";
    string name = userDefault->getStringForKey(str1.c_str());
    str1 = "customeFrames_";
    str1 += String::createWithFormat("%d", 3)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    int frames = userDefault->getIntegerForKey(str1.c_str());

    string tmp = "customeLove_3_";
    tmp += String::createWithFormat("%d", j)->getCString();
    int love = userDefault->getIntegerForKey(tmp.c_str(), 0);

    string tmp5 = "customeNeeds_";
    tmp5 += String::createWithFormat("%d", j)->getCString();
    int num1 = userDefault->getIntegerForKey(tmp5.c_str(), 312);
    int num2 = num1 % 10;
    num1 /= 10;
    int num3 = num1 % 10;
    int num4 = num1 / 10;

    satis3 = false;
    money3 = 0;

    tmp = "goodsNum_3_";
    tmp += String::createWithFormat("%d", num2)->getCString();
    int good1 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box1;
    money3 = 0;
    if (good1 > 0) {
        good1--;
        satis3 = true;
        box1 = good1 / 50;
        if (good1 % 50) box1++;
        userDefault->setIntegerForKey(tmp.c_str(), good1);
        tmp = "goodsBoxs_3_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box1);
        tmp = "goodProfit_3_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        money3 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    tmp = "goodsNum_3_";
    tmp += String::createWithFormat("%d", num3)->getCString();
    int good2 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box2;
    if (good2 > 0) {
        good2--;
        satis3 = true;
        box2 = good2 / 50;
        if (good2 % 50) box2++;
        userDefault->setIntegerForKey(tmp.c_str(), good2);
        tmp = "goodsBoxs_3_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box2);
        tmp = "goodProfit_3_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        money3 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    if (love >= 5) {
        tmp = "goodsNum_3_";
        tmp += String::createWithFormat("%d", num4)->getCString();
        int good3 = userDefault->getIntegerForKey(tmp.c_str(), 0);
        int box3;
        if (good3 > 0) {
            good3--;
            satis3 = true;
            box3 = good3 / 50;
            if (good3 % 50) box3++;
            userDefault->setIntegerForKey(tmp.c_str(), good3);
            tmp = "goodsBoxs_3_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            userDefault->setIntegerForKey(tmp.c_str(), box3);
            tmp = "goodProfit_3_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            money3 += userDefault->getIntegerForKey(tmp.c_str(), 0);
        }
    }

    Sprite *sprite = Sprite::create();
    str1 = "customeScale_";
    str1 += String::createWithFormat("%d", 3)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    double scale = userDefault->getDoubleForKey(str1.c_str());
    sprite->setScale(scale);
    AnimationCache* cache = AnimationCache::getInstance();
    Animation* animation = cache->getAnimation(name);

    if (animation == NULL) {
        animation = Animation::create();
        for (int i = 1; i < frames; i++) {
            char szName[100] = {0};
            sprintf(szName, "monsters/%s/%s%02d.png", name.c_str(), name.c_str(), i);
            animation->addSpriteFrameWithFile(szName);
        }
        animation->setDelayPerUnit(1.0f / frames);
        animation->setRestoreOriginalFrame(true);
        cache->addAnimation(animation, name);
    }

    sprite->runAction(RepeatForever::create(Animate::create(animation)));

    Size size = view->getSize();
    sprite->setPosition(Vec2(-100, 350));
    view->getChildByName("Panel_1_Copy_0")->addChild(sprite);
    sprite->setName("sprite3");

    char szName2[100] = {0};
    if (satis3) sprintf(szName2, "UI/\Success.png");
    else sprintf(szName2, "UI/\Fail.png");
    Sprite *sprite2 = Sprite::create(szName2);
    view->getChildByName("Panel_1_Copy_0")->addChild(sprite2);
   // sprite2->scheduleOnce(SEL_SCHEDULE(&MyClass::Delay3), 2.0f);
    sprite2->setName("sprite31");
    sprite2->setPosition(Vec2(-100, 550));
    

    Size size1 = sprite2->getContentSize();
    ImageView* image1 = ImageView::create("UI/\Fail.png");
    image1->setOpacity(0);
    image1->setContentSize(size1);
    image1->setPosition(Vec2(size1.width / 2, size1.height / 2));
    image1->setTouchEnabled(true);
    sprite2->addChild(image1);
    bool satis = satis3;
    image1->addClickEventListener(([this, sprite2, satis, j](Ref*) {
        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
        sprite2->setVisible(false);
        if (satis && curHun) {
            curHun--;
            auto loading2 = dynamic_cast<LoadingBar*>(root->getChildByName("LoadingBar_3"));
            loading2->setPercent(curHun*100.0 / maxHun);
            auto textBMLabel4 = dynamic_cast<Text*>(root->getChildByName("Text_1"));
            string curHun_str = String::createWithFormat("%d", curHun)->getCString();
            string maxHun_str = String::createWithFormat("%d", maxHun)->getCString();
            textBMLabel4->setString(curHun_str + "/" + maxHun_str);

            string tmp2 = "customeLove_3_";
            tmp2 += String::createWithFormat("%d", j)->getCString();
            int love2 = userDefault->getIntegerForKey(tmp2.c_str(), 0);
            love2++;
            if (love2 <= 5) userDefault->setIntegerForKey(tmp2.c_str(), love2);

            judge3();
        }
    }));

    sprite2->runAction(Sequence::create(Hide::create(), FadeOut::create(0.0), MoveBy::create(tim+0.5, Vec2(size.width / 2+100, 0)), MoveBy::create(1.5, Vec2(0, 0)), Show::create(), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(size.width / 2-100, 0)), Hide::create(), NULL));
    sprite->runAction(Sequence::create(MoveBy::create(tim+0.5, Vec2(size.width / 2+100, 0)), FadeOut::create(0.5), MoveBy::create(1, Vec2(0, 0)), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(size.width / 2-100, 0)), Hide::create(), NULL));
    sprite->scheduleOnce(SEL_SCHEDULE(&MyClass::Release3), 7.0f);
}

void MyClass::Release1(float t) {
    auto view = dynamic_cast<PageView*>(root->getChildByName("PageView_1"));
    view->getChildByName("Panel_1")->removeChildByName("sprite1");
    view->getChildByName("Panel_1")->removeChildByName("sprite11");
    if (satis1) grow(1, money1);
}

void MyClass::Release2(float t) {
    auto view = dynamic_cast<PageView*>(root->getChildByName("PageView_1"));
    view->getChildByName("Panel_1_Copy")->removeChildByName("sprite2");
    view->getChildByName("Panel_1_Copy")->removeChildByName("sprite21");
    if (satis2) grow(1, money2);
}

void MyClass::Release3(float t) {
    auto view = dynamic_cast<PageView*>(root->getChildByName("PageView_1"));
    view->getChildByName("Panel_1_Copy_0")->removeChildByName("sprite3");
    view->getChildByName("Panel_1_Copy_0")->removeChildByName("sprite31");
    if (satis3) grow(1, money3);
}

void MyClass::onEvent(cocos2d::Ref* object, int eventType) {
}

void MyClass::grow(int exp, int mon) {
    int level = userDefault->getIntegerForKey("level", 1);
    string level_str = String::createWithFormat("%d", level)->getCString();

    int currentExp = userDefault->getIntegerForKey("currentExp", 0);
    currentExp += exp;

    string con = "needExp_";
    con += level_str;

    int count = 0;
    int money = userDefault->getIntegerForKey("money", 1405);
    while (userDefault->getIntegerForKey(con.c_str(), 1) <= currentExp) {
        currentExp -= userDefault->getIntegerForKey(con.c_str(), 1);
        level++;
        count++;
        maxHun += 2;
        level_str = String::createWithFormat("%d", level)->getCString();
        con = "needExp_";
        con += level_str;
        money += 500;
    }
    money += mon;

    int needExp = userDefault->getIntegerForKey(con.c_str(), 25);
    auto loading1 = dynamic_cast<LoadingBar*>(root->getChildByName("LoadingBar_2"));
    loading1->setPercent(currentExp*100.0 / needExp);
   
    userDefault->setIntegerForKey("currentExp", currentExp);
    userDefault->setIntegerForKey("level", level);
    userDefault->setIntegerForKey("money", money);
    level_str = String::createWithFormat("%d", level)->getCString();
    string currentExp_str = String::createWithFormat("%d", currentExp)->getCString();
    string needExp_str = String::createWithFormat("%d", userDefault->getIntegerForKey(con.c_str(), 25))->getCString();
    auto textBMLabel = dynamic_cast<Text*>(root->getChildByName("Text_34"));
    textBMLabel->setString(level_str);
    auto textBMLabel2 = dynamic_cast<Text*>(root->getChildByName("Text_35"));
    textBMLabel2->setString(currentExp_str + "/" + needExp_str);
    auto textBMLabel3 = dynamic_cast<Text*>(root->getChildByName("Text_36"));
    textBMLabel3->setString(String::createWithFormat("%d", money)->_string);
    auto textBMLabel4 = dynamic_cast<Text*>(root->getChildByName("Text_1"));
    string curHun_str = String::createWithFormat("%d", curHun)->getCString();
    string maxHun_str = String::createWithFormat("%d", maxHun)->getCString();
    textBMLabel4->setString(curHun_str + "/" + maxHun_str);

    if (count > 0) {
        auto layer = CSLoader::createNode("Layer71.csb");
        auto bkg = LayerColor::create(Color4B(0, 0, 0, 128));
        Size winSize = Director::getInstance()->getWinSize();
        layer->setPosition(winSize.width * 0.1, winSize.height *0.1);
        bkg->addChild(layer);
        root->addChild(bkg, 3);
        auto btnClose = dynamic_cast<Button*>(layer->getChildByName("Button_5"));
        btnClose->addClickEventListener(([this, bkg](Ref*) {
            if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
            root->removeChild(bkg);
        }));
        auto text = dynamic_cast<Text*>(layer->getChildByName("Text_27"));
        string tmp;
        tmp = IConvConvert_GBKToUTF8("恭喜你的等级升到了");
        tmp += String::createWithFormat("%d", level)->getCString();
        tmp += IConvConvert_GBKToUTF8("级!\n    你已获得500金币！");
        text->setString(tmp);
    }
}

void MyClass::graySprite(Sprite* sprite) {
    if (sprite) {
        GLProgram * p = new GLProgram();
        p->initWithFilenames("gray.vsh", "gray.fsh");
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
        p->link();
        p->updateUniforms();
        sprite->setShaderProgram(p);
    }
}

void MyClass::judge1() {
    for (int i = 4; i <= 6; i++) {
        string tmp = "customeUnlocked_1_";
        tmp += String::createWithFormat("%d", i)->getCString();
        bool flag = userDefault->getBoolForKey(tmp.c_str(), false);
        int count = 0;
        if (flag == false) {
            for (int j = i - 3; j < i; j++) {
                string tmp1 = "customeLove_1_";
                tmp1 += String::createWithFormat("%d", j)->getCString();
                int love = userDefault->getIntegerForKey(tmp1.c_str(), 0);
                if (love >= 5) count++;
            }
            if (count >= 2) {
                userDefault->setBoolForKey(tmp.c_str(), true);
                grow(5, 0);

                auto layer = CSLoader::createNode("Layer9.csb");
                auto bkg = LayerColor::create(Color4B(0, 0, 0, 128));
                Size winSize = Director::getInstance()->getWinSize();
                layer->setPosition(winSize.width * 0.1, winSize.height *0.1);
                bkg->addChild(layer);
                root->addChild(bkg, 3);
                auto btnClose = dynamic_cast<Button*>(layer->getChildByName("Button_5"));
                btnClose->addClickEventListener(([this, bkg](Ref*) {
                    if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                    root->removeChild(bkg);
                }));
               
                auto dt2 = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*) layer, "Text_25"));
                string tmp2 = "ChineseName_1_";
                tmp2 += String::createWithFormat("%d", i)->getCString();
                dt2->setString(userDefault->getStringForKey(tmp2.c_str()));
                auto p = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*) layer, "Image_24"));
                p->setOpacity(0);
                Vec2 position = p->getPosition();

                char szName[100] = {0};
                sprintf(szName, "monsters/\%d/\%d.png", 1, i);
                Sprite *sprite = Sprite::create(szName);
                sprite->setAnchorPoint(Point(0.5, 0.5));
                sprite->setPosition(position);
                layer->getChildByName("Panel_9")->getChildByName("Panel_11")->addChild(sprite);
            }
        }
    }
}

void MyClass::judge2() {
    for (int i = 4; i <= 6; i++) {
        string tmp = "customeUnlocked_2_";
        tmp += String::createWithFormat("%d", i)->getCString();
        bool flag = userDefault->getBoolForKey(tmp.c_str(), false);
        int count = 0;
        if (flag == false) {
            for (int j = i - 3; j < i; j++) {
                string tmp1 = "customeLove_2_";
                tmp1 += String::createWithFormat("%d", j)->getCString();
                int love = userDefault->getIntegerForKey(tmp1.c_str(), 0);
                if (love >= 5) count++;
            }
            if (count >= 2) {
                userDefault->setBoolForKey(tmp.c_str(), true);
                grow(5, 0);

                auto layer = CSLoader::createNode("Layer9.csb");
                auto bkg = LayerColor::create(Color4B(0, 0, 0, 128));
                Size winSize = Director::getInstance()->getWinSize();
                layer->setPosition(winSize.width * 0.1, winSize.height *0.1);
                bkg->addChild(layer);
                root->addChild(bkg, 3);
                auto btnClose = dynamic_cast<Button*>(layer->getChildByName("Button_5"));
                btnClose->addClickEventListener(([this, bkg](Ref*) {
                    if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                    root->removeChild(bkg);
                }));

                auto dt2 = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*) layer, "Text_25"));
                string tmp2 = "ChineseName_2_";
                tmp2 += String::createWithFormat("%d", i)->getCString();
                dt2->setString(userDefault->getStringForKey(tmp2.c_str()));
                auto p = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*) layer, "Image_24"));
                p->setOpacity(0);
                Vec2 position = p->getPosition();

                char szName[100] = {0};
                sprintf(szName, "monsters/\%d/\%d.png", 2, i);
                Sprite *sprite = Sprite::create(szName);
                sprite->setAnchorPoint(Point(0.5, 0.5));
                sprite->setPosition(position);
                layer->getChildByName("Panel_9")->getChildByName("Panel_11")->addChild(sprite);
            }
        }
    }
}

void MyClass::judge3() {
    for (int i = 4; i <= 6; i++) {
        string tmp = "customeUnlocked_3_";
        tmp += String::createWithFormat("%d", i)->getCString();
        bool flag = userDefault->getBoolForKey(tmp.c_str(), false);
        int count = 0;
        if (flag == false) {
            for (int j = i - 3; j < i; j++) {
                string tmp1 = "customeLove_3_";
                tmp1 += String::createWithFormat("%d", j)->getCString();
                int love = userDefault->getIntegerForKey(tmp1.c_str(), 0);
                if (love >= 5) count++;
            }
            if (count >= 2) {
                userDefault->setBoolForKey(tmp.c_str(), true);
                grow(5, 0);

                auto layer = CSLoader::createNode("Layer9.csb");
                auto bkg = LayerColor::create(Color4B(0, 0, 0, 128));
                Size winSize = Director::getInstance()->getWinSize();
                layer->setPosition(winSize.width * 0.1, winSize.height *0.1);
                bkg->addChild(layer);
                root->addChild(bkg, 3);
                auto btnClose = dynamic_cast<Button*>(layer->getChildByName("Button_5"));
                btnClose->addClickEventListener(([this, bkg](Ref*) {
                    if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                    root->removeChild(bkg);
                }));

                auto dt2 = dynamic_cast<Text*>(Helper::seekWidgetByName((Widget*) layer, "Text_25"));
                string tmp2 = "ChineseName_3_";
                tmp2 += String::createWithFormat("%d", i)->getCString();
                dt2->setString(userDefault->getStringForKey(tmp2.c_str()));
                auto p = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*) layer, "Image_24"));
                p->setOpacity(0);
                Vec2 position = p->getPosition();

                char szName[100] = {0};
                sprintf(szName, "monsters/\%d/\%d.png", 3, i);
                Sprite *sprite = Sprite::create(szName);
                sprite->setAnchorPoint(Point(0.5, 0.5));
                sprite->setPosition(position);
                layer->getChildByName("Panel_9")->getChildByName("Panel_11")->addChild(sprite);
            }
        }
    }
}

void MyClass::Check(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
        int index = dynamic_cast<PageView*>(this->getChildByName("PageView_1"))->getCurPageIndex() + 1;

        string key2;
        if (index == 1) {
            key2 = "Image_1";
        } else if (index == 2) {
            key2 = "Image_1_Copy";
        } else if (index == 3) {
            key2 = "Image_1_Copy_0";
        }
        auto image = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*) root, key2.c_str()));
        image->setTouchEnabled(false);

        auto layer = CSLoader::createNode("Layer60.csb");
        auto bkg = LayerColor::create(Color4B(0, 0, 0, 128));
        Size winSize = Director::getInstance()->getWinSize();
        layer->setPosition(winSize.width * 0.1, winSize.height *0.1);
        bkg->addChild(layer);
        addChild(bkg);

        for (int i = 1; i < 5; i++) {
            string key = "goodsBoxs_";
            key += String::createWithFormat("%d", index)->getCString();
            key += "_";
            key += String::createWithFormat("%d", i)->getCString();
            string key3 = "goodsNum_";
            key3 += String::createWithFormat("%d", index)->getCString();
            key3 += "_";
            key3 += String::createWithFormat("%d", i)->getCString();
            string tmp = "Text_";
            tmp += String::createWithFormat("%d", i + 1)->getCString();
            auto text3 = dynamic_cast<Text*>(layer->getChildByName(tmp.c_str()));
            text3->setString(String::createWithFormat("%d", userDefault->getIntegerForKey(key3.c_str()))->getCString());

            string key1 = "Image_";
            key1 += String::createWithFormat("%d", i + 1)->getCString();
            auto image = dynamic_cast<ImageView*>(layer->getChildByName(key1.c_str()));
            Vec2 position = image->getPosition();
            image->setVisible(true);
            image->setOpacity(0);
            image->setTouchEnabled(false);
            char szName[100] = {0};
            sprintf(szName, "goods/\%d/\%d.png", index, i);
            Sprite *sprite = Sprite::create(szName);
            sprite->setScale(0.5);
            sprite->setPosition(position);
            layer->addChild(sprite);

            string tmp2 = "LoadingBar_";
            tmp2 += String::createWithFormat("%d", i)->getCString();
            auto loadingBar = dynamic_cast<LoadingBar*>(layer->getChildByName(tmp2.c_str()));
            loadingBar->setPercent(userDefault->getIntegerForKey(key.c_str())*20);

            auto root1 = root;
            auto btnClose = dynamic_cast<Button*>(layer->getChildByName("Button_1"));
            btnClose->addClickEventListener(([this, bkg, root1, key2](Ref*) {
                if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
                auto image1 = dynamic_cast<ImageView*>(Helper::seekWidgetByName((Widget*) root1, key2.c_str()));
                image1->setTouchEnabled(true);
                this->removeChild(bkg);
            }));
        }
    }
}

void MyClass::ToGroupBuy(float t) {
    string tmp3 = "groupBuyEnabled";
    userDefault->setBoolForKey(tmp3.c_str(), true);
}

void MyClass::NormalBuy(float t) {
    Scene* scene1 = Director::getInstance()->getRunningScene();

    AnimationCache::destroyInstance();
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    TextureCache::getInstance()->removeUnusedTextures();

    if (userDefault->getBoolForKey("buildState_1", false)) {
        root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update1), 5.0f, CC_REPEAT_FOREVER, 0.5);
        root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update11), 5.0f, CC_REPEAT_FOREVER, 1);
    }
    if (userDefault->getBoolForKey("buildState_2", false)) {
        root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update2), 5.0f, CC_REPEAT_FOREVER, 1);
        root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update21), 5.0f, CC_REPEAT_FOREVER, 0.5);
    }
    if (userDefault->getBoolForKey("buildState_3", false)) {
        root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update3), 5.0f, CC_REPEAT_FOREVER, 0.5);
        root->schedule(CC_SCHEDULE_SELECTOR(MyClass::Custom_Update31), 5.0f, CC_REPEAT_FOREVER, 1);
    }
}

void MyClass::Lock() {
    userDefault->setBoolForKey("dicUnlocked", false);
    userDefault->setBoolForKey("relationUnlocked", false);
    userDefault->setBoolForKey("groupUnlocked", false);
    userDefault->setBoolForKey("bookUnlocked", false);
}

void MyClass::Unlock() {
    userDefault->setBoolForKey("dicUnlocked", true);
    userDefault->setBoolForKey("relationUnlocked", true);
    userDefault->setBoolForKey("groupUnlocked", true);
    userDefault->setBoolForKey("bookUnlocked", true);
}

void MyClass::Custom_Update101(float t) {
    auto view = dynamic_cast<PageView*>(root->getChildByName("PageView_1"));

    srand((unsigned) time(NULL));
    int j = (rand() % 6 + 1);
    float tim = (rand() % 5)*1.0 / 10.0 + 2.0;

    string str1 = "customeName_";
    str1 += String::createWithFormat("%d", 1)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    string name = userDefault->getStringForKey(str1.c_str());
    str1 = "customeFrames_";
    str1 += String::createWithFormat("%d", 1)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    int frames = userDefault->getIntegerForKey(str1.c_str());

    string tmp = "customeLove_1_";
    tmp += String::createWithFormat("%d", j)->getCString();
    int love = userDefault->getIntegerForKey(tmp.c_str(), 0);

    string tmp5 = "customeNeeds_";
    tmp5 += String::createWithFormat("%d", j)->getCString();
    int num1 = userDefault->getIntegerForKey(tmp5.c_str(), 312);
    int num2 = num1 % 10;
    num1 /= 10;
    int num3 = num1 % 10;
    int num4 = num1 / 10;

    satis1 = false;
    money1 = 0;

    tmp = "goodsNum_1_";
    tmp += String::createWithFormat("%d", num2)->getCString();
    int good1 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box1;
    money1 = 0;
    if (good1 > 0) {
        good1--;
        satis1 = true;
        box1 = good1 / 50;
        if (good1 % 50) box1++;
        userDefault->setIntegerForKey(tmp.c_str(), good1);
        tmp = "goodsBoxs_1_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box1);
        tmp = "goodProfit_1_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        money1 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    tmp = "goodsNum_1_";
    tmp += String::createWithFormat("%d", num3)->getCString();
    int good2 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box2;
    if (good2 > 0) {
        good2--;
        satis1 = true;
        box2 = good2 / 50;
        if (good2 % 50) box2++;
        userDefault->setIntegerForKey(tmp.c_str(), good2);
        tmp = "goodsBoxs_1_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box2);
        tmp = "goodProfit_1_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        money1 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    if (love >= 5) {
        tmp = "goodsNum_1_";
        tmp += String::createWithFormat("%d", num4)->getCString();
        int good3 = userDefault->getIntegerForKey(tmp.c_str(), 0);
        int box3;
        if (good3 > 0) {
            good3--;
            satis1 = true;
            box3 = good3 / 50;
            if (good3 % 50) box3++;
            userDefault->setIntegerForKey(tmp.c_str(), good3);
            tmp = "goodsBoxs_1_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            userDefault->setIntegerForKey(tmp.c_str(), box3);
            tmp = "goodProfit_1_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            money1 += userDefault->getIntegerForKey(tmp.c_str(), 0);
        }
    }

    Sprite *sprite = Sprite::create();
    str1 = "customeScale_";
    str1 += String::createWithFormat("%d", 1)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    double scale = userDefault->getDoubleForKey(str1.c_str());
    sprite->setScale(scale);
    AnimationCache* cache = AnimationCache::getInstance();
    Animation* animation = cache->getAnimation(name);

    if (animation == NULL) {
        animation = Animation::create();
        for (int i = 1; i < frames; i++) {
            char szName[100] = {0};
            sprintf(szName, "monsters/%s/%s%02d.png", name.c_str(), name.c_str(), i);
            animation->addSpriteFrameWithFile(szName);
        }
        animation->setDelayPerUnit(1.0f / frames);
        animation->setRestoreOriginalFrame(true);
        cache->addAnimation(animation, name);
    }

    sprite->runAction(RepeatForever::create(Animate::create(animation)));

    Size size = view->getSize();
    sprite->setPosition(Vec2(size.width + 100, 300));
    view->getChildByName("Panel_1")->addChild(sprite);
    sprite->setName("sprite1");

    char szName2[100] = {0};
    if (satis1) sprintf(szName2, "UI/\Success.png");
    else sprintf(szName2, "UI/\Fail.png");
    Sprite *sprite2 = Sprite::create(szName2);
    sprite2->runAction(FadeOut::create(0.0));
    view->getChildByName("Panel_1")->addChild(sprite2);

    sprite2->setName("sprite11");

    sprite2->setPosition(Vec2(size.width + 100, 500));

    Size size1 = sprite2->getContentSize();
    ImageView* image1 = ImageView::create("UI/\Fail.png");
    image1->setOpacity(0);
    image1->setContentSize(size1);
    image1->setPosition(Vec2(size1.width / 2, size1.height / 2));
    image1->setTouchEnabled(true);
    sprite2->addChild(image1);
    bool satis = satis1;
    image1->addClickEventListener(([this, sprite2, satis, j](Ref*) {
        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
        sprite2->setVisible(false);
        if (satis && curHun) {
            curHun--;
            auto loading2 = dynamic_cast<LoadingBar*>(root->getChildByName("LoadingBar_3"));
            loading2->setPercent(curHun*100.0 / maxHun);
            auto textBMLabel4 = dynamic_cast<Text*>(root->getChildByName("Text_1"));
            string curHun_str = String::createWithFormat("%d", curHun)->getCString();
            string maxHun_str = String::createWithFormat("%d", maxHun)->getCString();
            textBMLabel4->setString(curHun_str + "/" + maxHun_str);

            string tmp2 = "customeLove_1_";
            tmp2 += String::createWithFormat("%d", j)->getCString();
            int love2 = userDefault->getIntegerForKey(tmp2.c_str(), 0);
            love2++;
            if (love2 <= 5) userDefault->setIntegerForKey(tmp2.c_str(), love2);
            judge1();
        }
    }));


    sprite2->runAction(Sequence::create(MoveBy::create(tim + 0.5, Vec2(-size.width / 2 - 100, 0)), MoveBy::create(1.5, Vec2(0, 0)), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(-size.width / 2 + 100, 0)), Hide::create(), NULL));
    sprite->runAction(Sequence::create(MoveBy::create(tim + 0.5, Vec2(-size.width / 2 - 100, 0)), FadeOut::create(0.5), MoveBy::create(1, Vec2(0, 0)), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(-size.width / 2 + 100, 0)), Hide::create(), NULL));
    sprite->scheduleOnce(SEL_SCHEDULE(&MyClass::Release1), 7.0f);
}

void MyClass::Custom_Update111(float t) {
    auto view = dynamic_cast<PageView*>(root->getChildByName("PageView_1"));

    srand((unsigned) time(NULL));
    int j = (rand() % 6 + 1);
    float tim = (rand() % 5)*1.0 / 10.0 + 2.0;

    string str1 = "customeName_";
    str1 += String::createWithFormat("%d", 1)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    str1 += "_1";
    string name = userDefault->getStringForKey(str1.c_str());
    str1 = "customeFrames_";
    str1 += String::createWithFormat("%d", 1)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    int frames = userDefault->getIntegerForKey(str1.c_str());

    string tmp = "customeLove_1_";
    tmp += String::createWithFormat("%d", j)->getCString();
    int love = userDefault->getIntegerForKey(tmp.c_str(), 0);

    string tmp5 = "customeNeeds_";
    tmp5 += String::createWithFormat("%d", j)->getCString();
    int num1 = userDefault->getIntegerForKey(tmp5.c_str(), 312);
    int num2 = num1 % 10;
    num1 /= 10;
    int num3 = num1 % 10;
    int num4 = num1 / 10;

    satis1 = false;
    money1 = 0;

    tmp = "goodsNum_1_";
    tmp += String::createWithFormat("%d", num2)->getCString();
    int good1 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box1;
    money1 = 0;
    if (good1 > 0) {
        good1--;
        satis1 = true;
        box1 = good1 / 50;
        if (good1 % 50) box1++;
        userDefault->setIntegerForKey(tmp.c_str(), good1);
        tmp = "goodsBoxs_1_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box1);
        tmp = "goodProfit_1_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        money1 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    tmp = "goodsNum_1_";
    tmp += String::createWithFormat("%d", num3)->getCString();
    int good2 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box2;
    if (good2 > 0) {
        good2--;
        satis1 = true;
        box2 = good2 / 50;
        if (good2 % 50) box2++;
        userDefault->setIntegerForKey(tmp.c_str(), good2);
        tmp = "goodsBoxs_1_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box2);
        tmp = "goodProfit_1_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        money1 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    if (love >= 5) {
        tmp = "goodsNum_1_";
        tmp += String::createWithFormat("%d", num4)->getCString();
        int good3 = userDefault->getIntegerForKey(tmp.c_str(), 0);
        int box3;
        if (good3 > 0) {
            good3--;
            satis1 = true;
            box3 = good3 / 50;
            if (good3 % 50) box3++;
            userDefault->setIntegerForKey(tmp.c_str(), good3);
            tmp = "goodsBoxs_1_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            userDefault->setIntegerForKey(tmp.c_str(), box3);
            tmp = "goodProfit_1_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            money1 += userDefault->getIntegerForKey(tmp.c_str(), 0);
        }
    }

    Sprite *sprite = Sprite::create();
    str1 = "customeScale_";
    str1 += String::createWithFormat("%d", 1)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    double scale = userDefault->getDoubleForKey(str1.c_str());
    sprite->setScale(scale);
    AnimationCache* cache = AnimationCache::getInstance();
    Animation* animation = cache->getAnimation(name);

    if (animation == NULL) {
        animation = Animation::create();
        for (int i = 1; i < frames; i++) {
            char szName[100] = {0};
            sprintf(szName, "monsters/%s/%s%02d.png", name.c_str(), name.c_str(), i);
            animation->addSpriteFrameWithFile(szName);
        }
        animation->setDelayPerUnit(1.0f / frames);
        animation->setRestoreOriginalFrame(true);
        cache->addAnimation(animation, name);
    }

    sprite->runAction(RepeatForever::create(Animate::create(animation)));

    Size size = view->getSize();
    sprite->setPosition(Vec2(-100, 300));
    view->getChildByName("Panel_1")->addChild(sprite);
    sprite->setName("sprite1");

    char szName2[100] = {0};
    if (satis1) sprintf(szName2, "UI/\Success.png");
    else sprintf(szName2, "UI/\Fail.png");
    Sprite *sprite2 = Sprite::create(szName2);
    sprite2->runAction(FadeOut::create(0.0));
    view->getChildByName("Panel_1")->addChild(sprite2);

    sprite2->setName("sprite11");
    sprite2->setPosition(Vec2(-100, 500));


    Size size1 = sprite2->getContentSize();
    ImageView* image1 = ImageView::create("UI/\Fail.png");
    image1->setOpacity(0);
    image1->setContentSize(size1);
    image1->setPosition(Vec2(size1.width / 2, size1.height / 2));
    image1->setTouchEnabled(true);
    sprite2->addChild(image1);
    bool satis = satis1;
    image1->addClickEventListener(([this, sprite2, satis, j](Ref*) {
        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
        sprite2->setVisible(false);
        if (satis && curHun) {
            curHun--;
            auto loading2 = dynamic_cast<LoadingBar*>(root->getChildByName("LoadingBar_3"));
            loading2->setPercent(curHun*100.0 / maxHun);
            auto textBMLabel4 = dynamic_cast<Text*>(root->getChildByName("Text_1"));
            string curHun_str = String::createWithFormat("%d", curHun)->getCString();
            string maxHun_str = String::createWithFormat("%d", maxHun)->getCString();
            textBMLabel4->setString(curHun_str + "/" + maxHun_str);

            string tmp2 = "customeLove_1_";
            tmp2 += String::createWithFormat("%d", j)->getCString();
            int love2 = userDefault->getIntegerForKey(tmp2.c_str(), 0);
            love2++;
            if (love2 <= 5) userDefault->setIntegerForKey(tmp2.c_str(), love2);

            judge1();
        }
    }));

    sprite2->runAction(Sequence::create(MoveBy::create(tim + 0.5, Vec2(size.width / 2 + 100, 0)), MoveBy::create(1.5, Vec2(0, 0)), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(size.width / 2 - 100, 0)), Hide::create(), NULL));
    sprite->runAction(Sequence::create(MoveBy::create(tim + 0.5, Vec2(size.width / 2 + 100, 0)), FadeOut::create(0.5), MoveBy::create(1, Vec2(0, 0)), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(size.width / 2 - 100, 0)), Hide::create(), NULL));
    sprite->scheduleOnce(SEL_SCHEDULE(&MyClass::Release1), 7.0f);
}

void MyClass::Custom_Update102(float t) {
    auto view = dynamic_cast<PageView*>(root->getChildByName("PageView_1"));

    srand((unsigned) time(NULL));
    int j = (rand() % 6 + 1);
    float tim = (rand() % 5)*1.0 / 10.0 + 2.0;

    string str1 = "customeName_";
    str1 += String::createWithFormat("%d", 2)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    string name = userDefault->getStringForKey(str1.c_str());
    str1 = "customeFrames_";
    str1 += String::createWithFormat("%d", 2)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    int frames = userDefault->getIntegerForKey(str1.c_str());

    string tmp = "customeLove_2_";
    tmp += String::createWithFormat("%d", j)->getCString();
    int love = userDefault->getIntegerForKey(tmp.c_str(), 0);

    string tmp5 = "customeNeeds_";
    tmp5 += String::createWithFormat("%d", j)->getCString();
    int num1 = userDefault->getIntegerForKey(tmp5.c_str(), 312);
    int num2 = num1 % 10;
    num1 /= 10;
    int num3 = num1 % 10;
    int num4 = num1 / 10;

    satis2 = false;
    money2 = 0;

    tmp = "goodsNum_2_";
    tmp += String::createWithFormat("%d", num2)->getCString();
    int good1 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box1;
    money2 = 0;
    if (good1 > 0) {
        good1--;
        satis2 = true;
        box1 = good1 / 50;
        if (good1 % 50) box1++;
        userDefault->setIntegerForKey(tmp.c_str(), good1);
        tmp = "goodsBoxs_2_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box1);
        tmp = "goodProfit_2_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        money2 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    tmp = "goodsNum_2_";
    tmp += String::createWithFormat("%d", num3)->getCString();
    int good2 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box2;
    if (good2 > 0) {
        good2--;
        satis2 = true;
        box2 = good2 / 50;
        if (good2 % 50) box2++;
        userDefault->setIntegerForKey(tmp.c_str(), good2);
        tmp = "goodsBoxs_2_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box2);
        tmp = "goodProfit_2_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        money2 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    if (love >= 5) {
        tmp = "goodsNum_2_";
        tmp += String::createWithFormat("%d", num4)->getCString();
        int good3 = userDefault->getIntegerForKey(tmp.c_str(), 0);
        int box3;
        if (good3 > 0) {
            good3--;
            satis2 = true;
            box3 = good3 / 50;
            if (good3 % 50) box3++;
            userDefault->setIntegerForKey(tmp.c_str(), good3);
            tmp = "goodsBoxs_2_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            userDefault->setIntegerForKey(tmp.c_str(), box3);
            tmp = "goodProfit_2_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            money2 += userDefault->getIntegerForKey(tmp.c_str(), 0);
        }
    }

    Sprite *sprite = Sprite::create();
    str1 = "customeScale_";
    str1 += String::createWithFormat("%d", 2)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    double scale = userDefault->getDoubleForKey(str1.c_str());
    sprite->setScale(scale);
    AnimationCache* cache = AnimationCache::getInstance();
    Animation* animation = cache->getAnimation(name);

    if (animation == NULL) {
        animation = Animation::create();
        for (int i = 1; i < frames; i++) {
            char szName[100] = {0};
            sprintf(szName, "monsters/%s/%s%02d.png", name.c_str(), name.c_str(), i);
            animation->addSpriteFrameWithFile(szName);
        }
        animation->setDelayPerUnit(1.0f / frames);
        animation->setRestoreOriginalFrame(true);
        cache->addAnimation(animation, name);
    }

    sprite->runAction(RepeatForever::create(Animate::create(animation)));

    Size size = view->getSize();
    sprite->setPosition(Vec2(size.width + 100, 300));
    view->getChildByName("Panel_1_Copy")->addChild(sprite);
    sprite->setName("sprite2");

    char szName2[100] = {0};
    if (satis2) sprintf(szName2, "UI/\Success.png");
    else sprintf(szName2, "UI/\Fail.png");
    Sprite *sprite2 = Sprite::create(szName2);
    view->getChildByName("Panel_1_Copy")->addChild(sprite2);
    //sprite2->scheduleOnce(SEL_SCHEDULE(&MyClass::Delay2), 2.0f);
    sprite2->setName("sprite21");
    sprite2->setPosition(Vec2(size.width + 100, 500));


    Size size1 = sprite2->getContentSize();
    ImageView* image1 = ImageView::create("UI/\Fail.png");
    image1->setOpacity(0);
    image1->setContentSize(size1);
    image1->setPosition(Vec2(size1.width / 2, size1.height / 2));
    image1->setTouchEnabled(true);
    sprite2->addChild(image1);
    bool satis = satis2;
    image1->addClickEventListener(([this, sprite2, satis, j](Ref*) {
        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
        sprite2->setVisible(false);
        if (satis && curHun) {
            curHun--;
            auto loading2 = dynamic_cast<LoadingBar*>(root->getChildByName("LoadingBar_3"));
            loading2->setPercent(curHun*100.0 / maxHun);
            auto textBMLabel4 = dynamic_cast<Text*>(root->getChildByName("Text_1"));
            string curHun_str = String::createWithFormat("%d", curHun)->getCString();
            string maxHun_str = String::createWithFormat("%d", maxHun)->getCString();
            textBMLabel4->setString(curHun_str + "/" + maxHun_str);

            string tmp2 = "customeLove_2_";
            tmp2 += String::createWithFormat("%d", j)->getCString();
            int love2 = userDefault->getIntegerForKey(tmp2.c_str(), 0);
            love2++;
            if (love2 <= 5) userDefault->setIntegerForKey(tmp2.c_str(), love2);

            judge2();
        }
    }));

    sprite2->runAction(Sequence::create(Hide::create(), FadeOut::create(0.0), MoveBy::create(tim + 0.5, Vec2(-size.width / 2 - 100, 0)), MoveBy::create(1.5, Vec2(0, 0)), Show::create(), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(-size.width / 2 + 100, 0)), Hide::create(), NULL));
    sprite->runAction(Sequence::create(MoveBy::create(tim + 0.5, Vec2(-size.width / 2 - 100, 0)), FadeOut::create(0.5), MoveBy::create(1, Vec2(0, 0)), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(-size.width / 2 + 100, 0)), Hide::create(), NULL));
    sprite->scheduleOnce(SEL_SCHEDULE(&MyClass::Release2), 7.0f);
}

void MyClass::Custom_Update121(float t) {
    auto view = dynamic_cast<PageView*>(root->getChildByName("PageView_1"));

    srand((unsigned) time(NULL));
    int j = (rand() % 6 + 1);
    float tim = (rand() % 5)*1.0 / 10.0 + 2.0;

    string str1 = "customeName_";
    str1 += String::createWithFormat("%d", 2)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    str1 += "_1";
    string name = userDefault->getStringForKey(str1.c_str());
    str1 = "customeFrames_";
    str1 += String::createWithFormat("%d", 2)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    int frames = userDefault->getIntegerForKey(str1.c_str());

    string tmp = "customeLove_2_";
    tmp += String::createWithFormat("%d", j)->getCString();
    int love = userDefault->getIntegerForKey(tmp.c_str(), 0);

    string tmp5 = "customeNeeds_";
    tmp5 += String::createWithFormat("%d", j)->getCString();
    int num1 = userDefault->getIntegerForKey(tmp5.c_str(), 312);
    int num2 = num1 % 10;
    num1 /= 10;
    int num3 = num1 % 10;
    int num4 = num1 / 10;

    satis2 = false;
    money2 = 0;

    tmp = "goodsNum_2_";
    tmp += String::createWithFormat("%d", num2)->getCString();
    int good1 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box1;
    money2 = 0;
    if (good1 > 0) {
        good1--;
        satis2 = true;
        box1 = good1 / 50;
        if (good1 % 50) box1++;
        userDefault->setIntegerForKey(tmp.c_str(), good1);
        tmp = "goodsBoxs_2_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box1);
        tmp = "goodProfit_2_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        money2 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    tmp = "goodsNum_2_";
    tmp += String::createWithFormat("%d", num3)->getCString();
    int good2 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box2;
    if (good2 > 0) {
        good2--;
        satis2 = true;
        box2 = good2 / 50;
        if (good2 % 50) box2++;
        userDefault->setIntegerForKey(tmp.c_str(), good2);
        tmp = "goodsBoxs_2_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box2);
        tmp = "goodProfit_2_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        money2 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    if (love >= 5) {
        tmp = "goodsNum_2_";
        tmp += String::createWithFormat("%d", num4)->getCString();
        int good3 = userDefault->getIntegerForKey(tmp.c_str(), 0);
        int box3;
        if (good3 > 0) {
            good3--;
            satis2 = true;
            box3 = good3 / 50;
            if (good3 % 50) box3++;
            userDefault->setIntegerForKey(tmp.c_str(), good3);
            tmp = "goodsBoxs_2_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            userDefault->setIntegerForKey(tmp.c_str(), box3);
            tmp = "goodProfit_2_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            money2 += userDefault->getIntegerForKey(tmp.c_str(), 0);
        }
    }

    Sprite *sprite = Sprite::create();
    str1 = "customeScale_";
    str1 += String::createWithFormat("%d", 2)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    double scale = userDefault->getDoubleForKey(str1.c_str());
    sprite->setScale(scale);
    AnimationCache* cache = AnimationCache::getInstance();
    Animation* animation = cache->getAnimation(name);

    if (animation == NULL) {
        animation = Animation::create();
        for (int i = 1; i < frames; i++) {
            char szName[100] = {0};
            sprintf(szName, "monsters/%s/%s%02d.png", name.c_str(), name.c_str(), i);
            animation->addSpriteFrameWithFile(szName);
        }
        animation->setDelayPerUnit(1.0f / frames);
        animation->setRestoreOriginalFrame(true);
        cache->addAnimation(animation, name);
    }

    sprite->runAction(RepeatForever::create(Animate::create(animation)));

    Size size = view->getSize();
    sprite->setPosition(Vec2(-100, 300));
    view->getChildByName("Panel_1_Copy")->addChild(sprite);
    sprite->setName("sprite2");

    char szName2[100] = {0};
    if (satis2) sprintf(szName2, "UI/\Success.png");
    else sprintf(szName2, "UI/\Fail.png");
    Sprite *sprite2 = Sprite::create(szName2);
    view->getChildByName("Panel_1_Copy")->addChild(sprite2);
    //sprite2->scheduleOnce(SEL_SCHEDULE(&MyClass::Delay2), 2.0f);
    sprite2->setName("sprite21");
    sprite2->setPosition(Vec2(-100, 500));


    Size size1 = sprite2->getContentSize();
    ImageView* image1 = ImageView::create("UI/\Fail.png");
    image1->setOpacity(0);
    image1->setContentSize(size1);
    image1->setPosition(Vec2(size1.width / 2, size1.height / 2));
    image1->setTouchEnabled(true);
    sprite2->addChild(image1);
    bool satis = satis2;
    image1->addClickEventListener(([this, sprite2, satis, j](Ref*) {
        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
        sprite2->setVisible(false);
        if (satis && curHun) {
            curHun--;
            auto loading2 = dynamic_cast<LoadingBar*>(root->getChildByName("LoadingBar_3"));
            loading2->setPercent(curHun*100.0 / maxHun);
            auto textBMLabel4 = dynamic_cast<Text*>(root->getChildByName("Text_1"));
            string curHun_str = String::createWithFormat("%d", curHun)->getCString();
            string maxHun_str = String::createWithFormat("%d", maxHun)->getCString();
            textBMLabel4->setString(curHun_str + "/" + maxHun_str);

            string tmp2 = "customeLove_2_";
            tmp2 += String::createWithFormat("%d", j)->getCString();
            int love2 = userDefault->getIntegerForKey(tmp2.c_str(), 0);
            love2++;
            if (love2 <= 5) userDefault->setIntegerForKey(tmp2.c_str(), love2);

            judge2();
        }
    }));

    sprite2->runAction(Sequence::create(Hide::create(), FadeOut::create(0.0), MoveBy::create(tim + 0.5, Vec2(size.width / 2 + 100, 0)), MoveBy::create(1.5, Vec2(0, 0)), Show::create(), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(size.width / 2 - 100, 0)), Hide::create(), NULL));
    sprite->runAction(Sequence::create(MoveBy::create(tim + 0.5, Vec2(size.width / 2 + 100, 0)), FadeOut::create(0.5), MoveBy::create(1, Vec2(0, 0)), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(size.width / 2 - 100, 0)), Hide::create(), NULL));
    sprite->scheduleOnce(SEL_SCHEDULE(&MyClass::Release2), 7.0f);
}


void MyClass::Custom_Update103(float t) {
    auto view = dynamic_cast<PageView*>(root->getChildByName("PageView_1"));

    srand((unsigned) time(NULL));
    int j = (rand() % 6 + 1);
    float tim = (rand() % 5)*1.0 / 10.0 + 2.0;

    string str1 = "customeName_";
    str1 += String::createWithFormat("%d", 3)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    string name = userDefault->getStringForKey(str1.c_str());
    str1 = "customeFrames_";
    str1 += String::createWithFormat("%d", 3)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    int frames = userDefault->getIntegerForKey(str1.c_str());

    string tmp = "customeLove_3_";
    tmp += String::createWithFormat("%d", j)->getCString();
    int love = userDefault->getIntegerForKey(tmp.c_str(), 0);

    string tmp5 = "customeNeeds_";
    tmp5 += String::createWithFormat("%d", j)->getCString();
    int num1 = userDefault->getIntegerForKey(tmp5.c_str(), 312);
    int num2 = num1 % 10;
    num1 /= 10;
    int num3 = num1 % 10;
    int num4 = num1 / 10;

    satis3 = false;
    money3 = 0;

    tmp = "goodsNum_3_";
    tmp += String::createWithFormat("%d", num2)->getCString();
    int good1 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box1;
    money3 = 0;
    if (good1 > 0) {
        good1--;
        satis3 = true;
        box1 = good1 / 50;
        if (good1 % 50) box1++;
        userDefault->setIntegerForKey(tmp.c_str(), good1);
        tmp = "goodsBoxs_3_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box1);
        tmp = "goodProfit_3_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        money3 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    tmp = "goodsNum_3_";
    tmp += String::createWithFormat("%d", num3)->getCString();
    int good2 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box2;
    if (good2 > 0) {
        good2--;
        satis3 = true;
        box2 = good2 / 50;
        if (good2 % 50) box2++;
        userDefault->setIntegerForKey(tmp.c_str(), good2);
        tmp = "goodsBoxs_3_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box2);
        tmp = "goodProfit_3_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        money3 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    if (love >= 5) {
        tmp = "goodsNum_3_";
        tmp += String::createWithFormat("%d", num4)->getCString();
        int good3 = userDefault->getIntegerForKey(tmp.c_str(), 0);
        int box3;
        if (good3 > 0) {
            good3--;
            satis3 = true;
            box3 = good3 / 50;
            if (good3 % 50) box3++;
            userDefault->setIntegerForKey(tmp.c_str(), good3);
            tmp = "goodsBoxs_3_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            userDefault->setIntegerForKey(tmp.c_str(), box3);
            tmp = "goodProfit_3_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            money3 += userDefault->getIntegerForKey(tmp.c_str(), 0);
        }
    }

    Sprite *sprite = Sprite::create();
    str1 = "customeScale_";
    str1 += String::createWithFormat("%d", 3)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    double scale = userDefault->getDoubleForKey(str1.c_str());
    sprite->setScale(scale);
    AnimationCache* cache = AnimationCache::getInstance();
    Animation* animation = cache->getAnimation(name);

    if (animation == NULL) {
        animation = Animation::create();
        for (int i = 1; i < frames; i++) {
            char szName[100] = {0};
            sprintf(szName, "monsters/%s/%s%02d.png", name.c_str(), name.c_str(), i);
            animation->addSpriteFrameWithFile(szName);
        }
        animation->setDelayPerUnit(1.0f / frames);
        animation->setRestoreOriginalFrame(true);
        cache->addAnimation(animation, name);
    }

    sprite->runAction(RepeatForever::create(Animate::create(animation)));

    Size size = view->getSize();
    sprite->setPosition(Vec2(size.width + 100, 350));
    view->getChildByName("Panel_1_Copy_0")->addChild(sprite);
    sprite->setName("sprite3");

    char szName2[100] = {0};
    if (satis3) sprintf(szName2, "UI/\Success.png");
    else sprintf(szName2, "UI/\Fail.png");
    Sprite *sprite2 = Sprite::create(szName2);
    view->getChildByName("Panel_1_Copy_0")->addChild(sprite2);
    //sprite2->scheduleOnce(SEL_SCHEDULE(&MyClass::Delay3), 2.0f);
    sprite2->setName("sprite31");
    sprite2->setPosition(Vec2(size.width + 100, 550));


    Size size1 = sprite2->getContentSize();
    ImageView* image1 = ImageView::create("UI/\Fail.png");
    image1->setOpacity(0);
    image1->setContentSize(size1);
    image1->setPosition(Vec2(size1.width / 2, size1.height / 2));
    image1->setTouchEnabled(true);
    sprite2->addChild(image1);
    bool satis = satis3;
    image1->addClickEventListener(([this, sprite2, satis, j](Ref*) {
        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
        sprite2->setVisible(false);
        if (satis && curHun) {
            curHun--;
            auto loading2 = dynamic_cast<LoadingBar*>(root->getChildByName("LoadingBar_3"));
            loading2->setPercent(curHun*100.0 / maxHun);
            auto textBMLabel4 = dynamic_cast<Text*>(root->getChildByName("Text_1"));
            string curHun_str = String::createWithFormat("%d", curHun)->getCString();
            string maxHun_str = String::createWithFormat("%d", maxHun)->getCString();
            textBMLabel4->setString(curHun_str + "/" + maxHun_str);

            string tmp2 = "customeLove_3_";
            tmp2 += String::createWithFormat("%d", j)->getCString();
            int love2 = userDefault->getIntegerForKey(tmp2.c_str(), 0);
            love2++;
            if (love2 <= 5) userDefault->setIntegerForKey(tmp2.c_str(), love2);

            judge3();
        }
    }));

    sprite2->runAction(Sequence::create(Hide::create(), FadeOut::create(0.0), MoveBy::create(tim + 0.5, Vec2(-size.width / 2 - 100, 0)), MoveBy::create(1.5, Vec2(0, 0)), Show::create(), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(-size.width / 2 + 100, 0)), Hide::create(), NULL));
    sprite->runAction(Sequence::create(MoveBy::create(tim + 0.5, Vec2(-size.width / 2 - 100, 0)), FadeOut::create(0.5), MoveBy::create(1, Vec2(0, 0)), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(-size.width / 2 + 100, 0)), Hide::create(), NULL));
    sprite->scheduleOnce(SEL_SCHEDULE(&MyClass::Release3), 7.0f);
}

void MyClass::Custom_Update131(float t) {
    auto view = dynamic_cast<PageView*>(root->getChildByName("PageView_1"));

    srand((unsigned) time(NULL));
    int j = (rand() % 6 + 1);
    float tim = (rand() % 5)*1.0 / 10.0 + 2.0;

    string str1 = "customeName_";
    str1 += String::createWithFormat("%d", 3)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    str1 += "_1";
    string name = userDefault->getStringForKey(str1.c_str());
    str1 = "customeFrames_";
    str1 += String::createWithFormat("%d", 3)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    int frames = userDefault->getIntegerForKey(str1.c_str());

    string tmp = "customeLove_3_";
    tmp += String::createWithFormat("%d", j)->getCString();
    int love = userDefault->getIntegerForKey(tmp.c_str(), 0);

    string tmp5 = "customeNeeds_";
    tmp5 += String::createWithFormat("%d", j)->getCString();
    int num1 = userDefault->getIntegerForKey(tmp5.c_str(), 312);
    int num2 = num1 % 10;
    num1 /= 10;
    int num3 = num1 % 10;
    int num4 = num1 / 10;

    satis3 = false;
    money3 = 0;

    tmp = "goodsNum_3_";
    tmp += String::createWithFormat("%d", num2)->getCString();
    int good1 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box1;
    money3 = 0;
    if (good1 > 0) {
        good1--;
        satis3 = true;
        box1 = good1 / 50;
        if (good1 % 50) box1++;
        userDefault->setIntegerForKey(tmp.c_str(), good1);
        tmp = "goodsBoxs_3_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box1);
        tmp = "goodProfit_3_";
        tmp += String::createWithFormat("%d", num2)->getCString();
        money3 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    tmp = "goodsNum_3_";
    tmp += String::createWithFormat("%d", num3)->getCString();
    int good2 = userDefault->getIntegerForKey(tmp.c_str(), 0);
    int box2;
    if (good2 > 0) {
        good2--;
        satis3 = true;
        box2 = good2 / 50;
        if (good2 % 50) box2++;
        userDefault->setIntegerForKey(tmp.c_str(), good2);
        tmp = "goodsBoxs_3_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        userDefault->setIntegerForKey(tmp.c_str(), box2);
        tmp = "goodProfit_3_";
        tmp += String::createWithFormat("%d", num3)->getCString();
        money3 += userDefault->getIntegerForKey(tmp.c_str(), 0);
    }

    if (love >= 5) {
        tmp = "goodsNum_3_";
        tmp += String::createWithFormat("%d", num4)->getCString();
        int good3 = userDefault->getIntegerForKey(tmp.c_str(), 0);
        int box3;
        if (good3 > 0) {
            good3--;
            satis3 = true;
            box3 = good3 / 50;
            if (good3 % 50) box3++;
            userDefault->setIntegerForKey(tmp.c_str(), good3);
            tmp = "goodsBoxs_3_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            userDefault->setIntegerForKey(tmp.c_str(), box3);
            tmp = "goodProfit_3_";
            tmp += String::createWithFormat("%d", num4)->getCString();
            money3 += userDefault->getIntegerForKey(tmp.c_str(), 0);
        }
    }

    Sprite *sprite = Sprite::create();
    str1 = "customeScale_";
    str1 += String::createWithFormat("%d", 3)->getCString();
    str1 += "_";
    str1 += String::createWithFormat("%d", j)->getCString();
    double scale = userDefault->getDoubleForKey(str1.c_str());
    sprite->setScale(scale);
    AnimationCache* cache = AnimationCache::getInstance();
    Animation* animation = cache->getAnimation(name);

    if (animation == NULL) {
        animation = Animation::create();
        for (int i = 1; i < frames; i++) {
            char szName[100] = {0};
            sprintf(szName, "monsters/%s/%s%02d.png", name.c_str(), name.c_str(), i);
            animation->addSpriteFrameWithFile(szName);
        }
        animation->setDelayPerUnit(1.0f / frames);
        animation->setRestoreOriginalFrame(true);
        cache->addAnimation(animation, name);
    }

    sprite->runAction(RepeatForever::create(Animate::create(animation)));

    Size size = view->getSize();
    sprite->setPosition(Vec2(-100, 350));
    view->getChildByName("Panel_1_Copy_0")->addChild(sprite);
    sprite->setName("sprite3");

    char szName2[100] = {0};
    if (satis3) sprintf(szName2, "UI/\Success.png");
    else sprintf(szName2, "UI/\Fail.png");
    Sprite *sprite2 = Sprite::create(szName2);
    view->getChildByName("Panel_1_Copy_0")->addChild(sprite2);
    // sprite2->scheduleOnce(SEL_SCHEDULE(&MyClass::Delay3), 2.0f);
    sprite2->setName("sprite31");
    sprite2->setPosition(Vec2(-100, 550));


    Size size1 = sprite2->getContentSize();
    ImageView* image1 = ImageView::create("UI/\Fail.png");
    image1->setOpacity(0);
    image1->setContentSize(size1);
    image1->setPosition(Vec2(size1.width / 2, size1.height / 2));
    image1->setTouchEnabled(true);
    sprite2->addChild(image1);
    bool satis = satis3;
    image1->addClickEventListener(([this, sprite2, satis, j](Ref*) {
        if (userDefault->getBoolForKey("bgm2", true))  SimpleAudioEngine::getInstance()->playEffect("mp3/zhujiemian.mp3");
        sprite2->setVisible(false);
        if (satis && curHun) {
            curHun--;
            auto loading2 = dynamic_cast<LoadingBar*>(root->getChildByName("LoadingBar_3"));
            loading2->setPercent(curHun*100.0 / maxHun);
            auto textBMLabel4 = dynamic_cast<Text*>(root->getChildByName("Text_1"));
            string curHun_str = String::createWithFormat("%d", curHun)->getCString();
            string maxHun_str = String::createWithFormat("%d", maxHun)->getCString();
            textBMLabel4->setString(curHun_str + "/" + maxHun_str);

            string tmp2 = "customeLove_3_";
            tmp2 += String::createWithFormat("%d", j)->getCString();
            int love2 = userDefault->getIntegerForKey(tmp2.c_str(), 0);
            love2++;
            if (love2 <= 5) userDefault->setIntegerForKey(tmp2.c_str(), love2);

            judge3();
        }
    }));

    sprite2->runAction(Sequence::create(Hide::create(), FadeOut::create(0.0), MoveBy::create(tim + 0.5, Vec2(size.width / 2 + 100, 0)), MoveBy::create(1.5, Vec2(0, 0)), Show::create(), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(size.width / 2 - 100, 0)), Hide::create(), NULL));
    sprite->runAction(Sequence::create(MoveBy::create(tim + 0.5, Vec2(size.width / 2 + 100, 0)), FadeOut::create(0.5), MoveBy::create(1, Vec2(0, 0)), FadeIn::create(0.5),
        MoveBy::create(tim, Vec2(size.width / 2 - 100, 0)), Hide::create(), NULL));
    sprite->scheduleOnce(SEL_SCHEDULE(&MyClass::Release3), 7.0f);
}

void MyClass::savename() {
    string str;
    str = IConvConvert_GBKToUTF8("白泽");
    userDefault->setStringForKey("ChineseName_1_1", str.c_str());
    str = IConvConvert_GBKToUTF8("蝙蝠");
    userDefault->setStringForKey("ChineseName_1_2", str.c_str());
    str = IConvConvert_GBKToUTF8("草帽");
    userDefault->setStringForKey("ChineseName_1_3", str.c_str());
    str = IConvConvert_GBKToUTF8("凤凰");
    userDefault->setStringForKey("ChineseName_1_4", str.c_str());
    str = IConvConvert_GBKToUTF8("鬼车");
    userDefault->setStringForKey("ChineseName_1_5", str.c_str());
    str = IConvConvert_GBKToUTF8("鬼火");
    userDefault->setStringForKey("ChineseName_1_6", str.c_str());

    str = IConvConvert_GBKToUTF8("海蛇");
    userDefault->setStringForKey("ChineseName_2_1", str.c_str());
    str = IConvConvert_GBKToUTF8("僵尸");
    userDefault->setStringForKey("ChineseName_2_2", str.c_str());
    str = IConvConvert_GBKToUTF8("啾啾");
    userDefault->setStringForKey("ChineseName_2_3", str.c_str());
    str = IConvConvert_GBKToUTF8("面具猫");
    userDefault->setStringForKey("ChineseName_2_4", str.c_str());
    str = IConvConvert_GBKToUTF8("无面兽");
    userDefault->setStringForKey("ChineseName_2_5", str.c_str());
    str = IConvConvert_GBKToUTF8("粽子");
    userDefault->setStringForKey("ChineseName_2_6", str.c_str());

    str = IConvConvert_GBKToUTF8("墓碑怪");
    userDefault->setStringForKey("ChineseName_3_1", str.c_str());
    str = IConvConvert_GBKToUTF8("水怪");
    userDefault->setStringForKey("ChineseName_3_2", str.c_str());
    str = IConvConvert_GBKToUTF8("酸与");
    userDefault->setStringForKey("ChineseName_3_3", str.c_str());
    str = IConvConvert_GBKToUTF8("玄武");
    userDefault->setStringForKey("ChineseName_3_4", str.c_str());
    str = IConvConvert_GBKToUTF8("英招");
    userDefault->setStringForKey("ChineseName_3_5", str.c_str());
    str = IConvConvert_GBKToUTF8("幽灵");
    userDefault->setStringForKey("ChineseName_3_6", str.c_str());

    str = IConvConvert_GBKToUTF8("正在努力练习划水\n的祥瑞神兽。");
    userDefault->setStringForKey("ChineseStory_1_1", str.c_str());
    str = IConvConvert_GBKToUTF8("这是一只拥有特别\n的飞行技巧的蝙\n蝠。");
    userDefault->setStringForKey("ChineseStory_1_2", str.c_str());
    str = IConvConvert_GBKToUTF8("“我的名字是草帽，\n不高兴，我也想有\n个高大上的名字，\n我不高兴。”");
    userDefault->setStringForKey("ChineseStory_1_3", str.c_str());
    str = IConvConvert_GBKToUTF8("明明是只凤凰但是\n老被别人当做会飞\n的鸡。");
    userDefault->setStringForKey("ChineseStory_1_4", str.c_str());
    str = IConvConvert_GBKToUTF8("虽然看上去像是可\n爱的小鸟，其实人\n家是蛇啦。");
    userDefault->setStringForKey("ChineseStory_1_5", str.c_str());
    str = IConvConvert_GBKToUTF8("“你能感受到我的\n媚眼了嘛？”");
    userDefault->setStringForKey("ChineseStory_1_6", str.c_str());

    str = IConvConvert_GBKToUTF8("“似魔鬼的脚步，\n摩擦摩擦，摩擦摩\n擦。”总是不由自\n主地愉快唱起了歌。");
    userDefault->setStringForKey("ChineseStory_2_1", str.c_str());
    str = IConvConvert_GBKToUTF8("蹦蹦哒哒蹦蹦哒哒。");
    userDefault->setStringForKey("ChineseStory_2_2", str.c_str());
    str = IConvConvert_GBKToUTF8("“啾啾！啾~~！啾！\n！！~”");
    userDefault->setStringForKey("ChineseStory_2_3", str.c_str());
    str = IConvConvert_GBKToUTF8("自以为走路轻飘飘，\n其实压强很大。");
    userDefault->setStringForKey("ChineseStory_2_4", str.c_str());
    str = IConvConvert_GBKToUTF8("“啦啦啦啦啦啦！”\n不由自主就转起圈\n圈来的小胖墩。");
    userDefault->setStringForKey("ChineseStory_2_5", str.c_str());
    str = IConvConvert_GBKToUTF8("一只找不到汨罗江的\n粽子。");
    userDefault->setStringForKey("ChineseStory_2_6", str.c_str());

    str = IConvConvert_GBKToUTF8("目标是成为跳高选\n手的大块头。");
    userDefault->setStringForKey("ChineseStory_3_1", str.c_str());
    // str = IConvConvert_GBKToUTF8("作为大哥的任务是\n带着弟弟们蹦跶蹦\n跶压马路。");
    str = IConvConvert_GBKToUTF8("作为大哥的任务是\n带着弟弟们压马路。");
    userDefault->setStringForKey("ChineseStory_3_2", str.c_str());
    str = IConvConvert_GBKToUTF8("等身上的小翅膀长\n大那时候就有四个\n大翅膀啦！！但是\n移动还是靠三只脚\n的怪物。");
    userDefault->setStringForKey("ChineseStory_3_3", str.c_str());
    str = IConvConvert_GBKToUTF8("“买一送一了喂！！”");
    userDefault->setStringForKey("ChineseStory_3_4", str.c_str());
    str = IConvConvert_GBKToUTF8("“我…要飞…的更\n高……啊！没力气\n啦呜呜呜！”每天\n都想着减肥结果忍\n不住偷吃的吃货。");
    userDefault->setStringForKey("ChineseStory_3_5", str.c_str());
    str = IConvConvert_GBKToUTF8("行走诡异奇特但是\n完全不在乎的阿飘。");
    userDefault->setStringForKey("ChineseStory_3_6", str.c_str());

    str = IConvConvert_GBKToUTF8("豆腐");
    userDefault->setStringForKey("ChineseName1_1_1", str.c_str());
    str = IConvConvert_GBKToUTF8("干蒸");
    userDefault->setStringForKey("ChineseName1_1_2", str.c_str());
    str = IConvConvert_GBKToUTF8("糖葫芦");
    userDefault->setStringForKey("ChineseName1_1_3", str.c_str());
    str = IConvConvert_GBKToUTF8("汤圆");
    userDefault->setStringForKey("ChineseName1_1_4", str.c_str());

    str = IConvConvert_GBKToUTF8("毛笔");
    userDefault->setStringForKey("ChineseName1_2_1", str.c_str());
    str = IConvConvert_GBKToUTF8("经书");
    userDefault->setStringForKey("ChineseName1_2_2", str.c_str());
    str = IConvConvert_GBKToUTF8("女儿红");
    userDefault->setStringForKey("ChineseName1_2_3", str.c_str());
    str = IConvConvert_GBKToUTF8("扇子");
    userDefault->setStringForKey("ChineseName1_2_4", str.c_str());

    str = IConvConvert_GBKToUTF8("蹴鞠");
    userDefault->setStringForKey("ChineseName1_3_1", str.c_str());
    str = IConvConvert_GBKToUTF8("毽子");
    userDefault->setStringForKey("ChineseName1_3_2", str.c_str());
    str = IConvConvert_GBKToUTF8("陀罗");
    userDefault->setStringForKey("ChineseName1_3_3", str.c_str());
    str = IConvConvert_GBKToUTF8(" 摇鼓");
    userDefault->setStringForKey("ChineseName1_3_4", str.c_str());
    userDefault->flush();
}

void MyClass::StartGame1(cocos2d::Ref* sender) {
    sender1 = sender;
    Scene *scene = Scene::create();
    auto rootNode = CSLoader::createNode("OpenScene.csb");
    ActionTimeline* action = CSLoader::createTimeline("OpenScene.csb");
    scene->addChild(rootNode);

    rootNode->runAction(action);
    action->gotoFrameAndPlay(0, 65, true);
    Director::getInstance()->replaceScene(scene);

    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("mp3/BGM.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("mp3/zhujiemian.mp3");

    TextureCache::sharedTextureCache()->addImageAsync("PageView/beijing1.jpg", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("PageView/beijing2.jpg", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("PageView/beijing3.jpg", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("PageView/Panel1_1.jpg", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("PageView/Panel1_2.jpg", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("PageView/Panel1_3.jpg", CC_CALLBACK_1(MyClass::Callback, this));

    TextureCache::sharedTextureCache()->addImageAsync("PageView/Panel2_1.jpg", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("PageView/Panel2_2.jpg", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("PageView/Panel2_3.jpg", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("PageView/Seed1.png", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("PageView/Seed2.png", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("PageView/Seed3.png", CC_CALLBACK_1(MyClass::Callback, this));

    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/Background.png", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/BGM.png", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/BGM2.png", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/Book.png", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/Buy.png", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/Buy_not.png", CC_CALLBACK_1(MyClass::Callback, this));

    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/GroupBuy_not.png", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/Consumer.png", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/Experience.png", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/GroupBuy.png", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/Level.png", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/Money.png", CC_CALLBACK_1(MyClass::Callback, this));

    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/NavigationBar.png", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/NavigationBar2.png", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/SE.png", CC_CALLBACK_1(MyClass::Callback, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/SE2.png", CC_CALLBACK_1(MyClass::Callback, this));
}

void MyClass::EnterGame1(cocos2d::Ref* sender) {
    sender2 = sender;
    Scene *scene = Scene::create();
    auto rootNode = CSLoader::createNode("OpenScene.csb");
    ActionTimeline* action = CSLoader::createTimeline("OpenScene.csb");
    scene->addChild(rootNode);

    rootNode->runAction(action);
    action->gotoFrameAndPlay(0, 65, true);
    Director::getInstance()->replaceScene(scene);

    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("mp3/BGM.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("mp3/zhujiemian.mp3");

    TextureCache::sharedTextureCache()->addImageAsync("PageView/beijing1.jpg", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("PageView/beijing2.jpg", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("PageView/beijing3.jpg", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("PageView/Panel1_1.jpg", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("PageView/Panel1_2.jpg", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("PageView/Panel1_3.jpg", CC_CALLBACK_1(MyClass::Callback1, this));

    TextureCache::sharedTextureCache()->addImageAsync("PageView/Panel2_1.jpg", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("PageView/Panel2_2.jpg", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("PageView/Panel2_3.jpg", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("PageView/Seed1.png", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("PageView/Seed2.png", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("PageView/Seed3.png", CC_CALLBACK_1(MyClass::Callback1, this));

    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/Background.png", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/BGM.png", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/BGM2.png", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/Book.png", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/Buy.png", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/Buy_not.png", CC_CALLBACK_1(MyClass::Callback1, this));

    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/GroupBuy_not.png", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/Consumer.png", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/Experience.png", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/GroupBuy.png", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/Level.png", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/Money.png", CC_CALLBACK_1(MyClass::Callback1, this));

    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/NavigationBar.png", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/NavigationBar2.png", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/SE.png", CC_CALLBACK_1(MyClass::Callback1, this));
    TextureCache::sharedTextureCache()->addImageAsync("UI/MainScene/SE2.png", CC_CALLBACK_1(MyClass::Callback1, this));
}

void MyClass::Callback(cocos2d::Object* d) {
    call++;
    if (call == 28) StartGame(sender1);
}

void MyClass::Callback1(cocos2d::Object* d) {
    call++;
    if (call == 28) EnterGame(sender2);
}

void MyClass::replaceScene(float dt) {
    Scene *scene1 = Scene::create();
    
    auto rootNode = CSLoader::createNode("OpenScene.csb");
    ActionTimeline* action = CSLoader::createTimeline("OpenScene.csb");
    scene1->addChild(rootNode);

    rootNode->runAction(action);
    action->gotoFrameAndPlay(0, 995, true);
    Director::getInstance()->replaceScene(scene1);
}