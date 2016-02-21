#include "MyClassReader.h"
#include "MyClass.h"
USING_NS_CC;
static MyClassReader* _instanceMyClassReader = nullptr;

MyClassReader* MyClassReader::getInstance() {
    if (!_instanceMyClassReader) {
        _instanceMyClassReader = new MyClassReader();
    }
    return _instanceMyClassReader;
}

void MyClassReader::purge() {
    CC_SAFE_DELETE(_instanceMyClassReader);
}

Node* MyClassReader::createNodeWithFlatBuffers(const flatbuffers::Table * nodeOptions) {
    MyClass* node = MyClass::create();
    setPropsWithFlatBuffers(node, nodeOptions);
    return node;
}