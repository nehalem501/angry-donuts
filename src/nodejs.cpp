#include <nan.h>
#include <iostream>
#include <string>
using namespace std;
using namespace Nan;
using namespace v8;

NAN_METHOD(MyTestMethod) {
    if ( info.Length() < 1 ) {
        return;
    }
    if ( !info[0]->IsString()) {
        return;
    }
    v8::String::Utf8Value val(info[0]->ToString());
    
    std::string str (*val);
    std::reverse(str.begin(), str.end());
    
    info.GetReturnValue().Set(Nan::New<String>(str.c_str()).ToLocalChecked()); 
}

NAN_MODULE_INIT(Init) {
   Nan::Set(target, New<String>("test").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(MyTestMethod)).ToLocalChecked());
}

NODE_MODULE(angry_donuts_addon, Init)
