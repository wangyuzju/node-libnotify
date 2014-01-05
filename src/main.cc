#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "myobject.h"

using namespace v8;


//void Print(const v8::FunctionCallbackInfo<Value>& args){
//	Isolate* isolate = Isolate::GetCurrent();
//	HandleScope scope(isolate);
//
//
////	printf("hello C++");
//	args.GetReturnValue().SetEmptyString();
//}
//
//void Init_Hello(Handle<Object> target){
//	NODE_SET_METHOD(target, "print", Print);
//}
//
//NODE_MODULE(hello, Init_Hello)

void Init(Handle<Object> target){
	MyObject::Init(target);
}

NODE_MODULE(addon, Init);
