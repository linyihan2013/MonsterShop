#ifndef __TestCpp__MyClass__
#define __TestCpp__MyClass__
#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "cocostudio\WidgetCallBackHandlerProtocol.h"
#include "ui\UIButton.h"
#include "ui\UIImageView.h"

class MyClass : public cocos2d::Node, public cocostudio::WidgetCallBackHandlerProtocol {
    public:
        CREATE_FUNC(MyClass)
        MyClass();
        virtual cocos2d::ui::Widget::ccWidgetTouchCallback onLocateTouchCallback(const std::string &callBackName);
        virtual cocos2d::ui::Widget::ccWidgetClickCallback onLocateClickCallback(const std::string &callBackName);
        virtual cocos2d::ui::Widget::ccWidgetEventCallback onLocateEventCallback(const std::string &callBackName);

        void onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
        void ToBuild1(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
        void ToBuild2(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
        void ToBuild3(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
        void ToRelations(cocos2d::Ref* sender);
        void ToDic(cocos2d::Ref* sender);
        void ToBook(cocos2d::Ref* sender);
        void Check(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
        void GroupBuy(cocos2d::Ref* sender);

        void AboutUs(cocos2d::Ref* sender);
        void ReturnToGame(cocos2d::Ref* sender);
        void EnterGame(cocos2d::Ref* sender);
        void StartGame(cocos2d::Ref* sender);
        void EnterGame1(cocos2d::Ref* sender);
        void StartGame1(cocos2d::Ref* sender);
        void Quit(cocos2d::Ref* sender);
        void Close(cocos2d::Ref* sender); 
        void BGM(cocos2d::Ref* sender);
        void SE(cocos2d::Ref* sender);

        void onEvent(cocos2d::Ref* sender, int eventType);
        void Update(float t);
        void Update1(float t);
        void Update2(float t);
        void Update3(float t);

        void Remove(float t);
        void Callback(cocos2d::Object*);
        void Callback1(cocos2d::Object*);
        void Callback3(cocos2d::Object*);

        void Update11(float t);
        void Update111(float t);
        void Update12(float t);
        void Update13(float t);
        void Custom_Update1(float t);
        void Custom_Update2(float t);
        void Custom_Update3(float t);
        void Custom_Update11(float t);
        void Custom_Update21(float t);
        void Custom_Update31(float t);

        void Custom_Update101(float t);
        void Custom_Update102(float t);
        void Custom_Update103(float t);
        void Custom_Update111(float t);
        void Custom_Update121(float t);
        void Custom_Update131(float t);
        void Release1(float t);
        void Release2(float t);
        void Release3(float t);
        void HunUpdate(float t);
        void grow(int exp, int mon);
        void lbar(float t);
        void ToGroupBuy(float t);
        void NormalBuy(float t);
        void Lock();
        void Unlock();

        void lbar1(float);

        void graySprite(cocos2d::Sprite* sprite);
        bool judgeRoom_1();
        bool judgeRoom_2();
        void judge1();
        void judge2();
        void judge3();

        void savename();

        void replaceScene(float);

    private:
        std::vector<std::string> _touchTypes;
        std::string _click;
        std::vector<std::string> _eventTypes;
};

#endif