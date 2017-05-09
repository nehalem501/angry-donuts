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
static AngryB::Index stor_index(path);

NAN_METHOD(Read) {
    if (info.Length() < 2 || !info[0]->IsString() || !info[1]-> IsInt32())
        return;

    uuid_t uuid;
    Nan::Utf8String uuid_str(info[0]->ToString());
    int res = uuid_parse(*uuid_str, uuid);
    if (res == -1)
        return;

    uint64_t offset_count = info[1]->IntegerValue();

    AngryB::Data data;
    if (stor_index.get(uuid, &data) != Status::Success)
        return;

    //std::cout << "count: " << offset_count << std::endl;

    uint64_t buf_size = _512K;
    uint64_t offset = offset_count * buf_size;
    if (data.length <= offset) {
        stor_index.close(uuid);
        info.GetReturnValue().Set(Nan::Null());
        return;
    }

    if (data.length - offset < buf_size)
        buf_size = data.length - offset;

    info.GetReturnValue().Set(Nan::CopyBuffer((const char*) data.bytes + offset, buf_size).ToLocalChecked());
}

NAN_METHOD(Open) {
    if (info.Length() < 1 || !info[0]->IsString())
        return;
    
    uuid_t uuid;
    Nan::Utf8String uuid_str(info[0]->ToString());
    int res = uuid_parse(*uuid_str, uuid);
    if (res == -1)
        return;
    
    stor_index.open(uuid);
}

NAN_METHOD(Exists) {
    if (info.Length() < 1 || !info[0]->IsString())
        return;
    
    uuid_t uuid;
    Nan::Utf8String uuid_str(info[0]->ToString());
    int res = uuid_parse(*uuid_str, uuid);
    if (res == -1) {
        Local<Boolean> retval = Nan::New(false);
        info.GetReturnValue().Set(retval);
        return;
    }
    
    bool v = stor_index.exists(uuid);
    Local<Boolean> retval = Nan::New(v);
    //std::cout << "exists: " << v << std::endl;
    info.GetReturnValue().Set(retval);
}

NAN_MODULE_INIT(Init) {
   Nan::Set(target, New<String>("read").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(Read)).ToLocalChecked());

   Nan::Set(target, New<String>("open").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(Open)).ToLocalChecked());
   
   Nan::Set(target, New<String>("exists").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(Exists)).ToLocalChecked());
}

NODE_MODULE(angry_donuts_addon, Init)
