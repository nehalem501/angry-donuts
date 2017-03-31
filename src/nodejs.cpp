#include <nan.h>
#include <iostream>
#include <string>
#include <stdint.h>

#include "index.h"
#include "data.h"

#define _512K 1024*512

using namespace std;
using namespace Nan;
using namespace v8;

static std::string path = "./data";
static AngryB::Index data(path.c_str());

NAN_METHOD(GetSize) {
    if (info.Length() < 1 || !info[0]->IsString())
        return;

    uuid_t uuid;
    Nan::Utf8String uuid_str(info[0]->ToString());
    int res = uuid_parse(*uuid_str, uuid);
    if (res == -1)
        return;

    int size = (int) data.get_size(uuid);
    if (size == -1)
        return;

    Local<Integer> size_js = Nan::New(size);
    info.GetReturnValue().Set(size_js);
}

NAN_METHOD(Read) {
    if (info.Length() < 2 || !info[0]->IsString() || !info[1]-> IsInt32())
        return;

    uuid_t uuid;
    Nan::Utf8String uuid_str(info[0]->ToString());
    int res = uuid_parse(*uuid_str, uuid);
    if (res == -1)
        return;

    uint64_t offset_count = info[1]->IntegerValue();

    AngryB::Data obj;
    if (data.get(uuid, &obj) != Status::Success)
        return;

    std::cout << "count: " << offset_count << std::endl;
    uint64_t buf_size = _512K;
    uint64_t offset = offset_count * buf_size;
    if (obj.length <= offset) {
        delete[] obj.bytes;
        info.GetReturnValue().Set(Nan::Null());
        return;
    }
    
    if (obj.length - offset < buf_size)
        buf_size = obj.length - offset;

    info.GetReturnValue().Set(Nan::CopyBuffer((const char*) obj.bytes + offset, buf_size).ToLocalChecked());
    delete[] obj.bytes;
    std::cout << "deleted!" << std::endl;
}

NAN_METHOD(Open) {
}

NAN_MODULE_INIT(Init) {
   Nan::Set(target, New<String>("getSize").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(GetSize)).ToLocalChecked());

   Nan::Set(target, New<String>("read").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(Read)).ToLocalChecked());
   
   Nan::Set(target, New<String>("open").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(Open)).ToLocalChecked());
}

NODE_MODULE(angry_donuts_addon, Init)
