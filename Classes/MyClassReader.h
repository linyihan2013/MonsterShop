#ifndef __cocos2d_libs__MyClassReader__
#define __cocos2d_libs__MyClassReader__
#include "cocos2d.h"
#include "cocostudio\CocosStudioExport.h"
#include "cocostudio\WidgetReader\NodeReader\NodeReader.h"

class MyClassReader : public cocostudio::NodeReader {
    public:
        MyClassReader() {};
        ~MyClassReader() {};
        static MyClassReader* getInstance();
        static void purge();
        cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};

#endif