/*
 * myobject.cc
 *
 *  Created on: Dec 26, 2013
 *      Author: wangyu
 */

#include <node.h>
#include "myobject.h"
#include "notification.h"

//using namespace v8;

Persistent<Function> MyObject::constructor;

MyObject::MyObject(double value) : value_(value) {
//	init value_ with args value
}

MyObject::~MyObject() {
}
void Plus(const v8::FunctionCallbackInfo<Value>& args);

void MyObject::Init(Handle<Object> target){
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
//	target->Set(String::NewSymbol("name"), String::NewSymbol("wangyu"));

	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::New("Counter"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	tpl->PrototypeTemplate()->Set(String::New("add"), FunctionTemplate::New(Add)->GetFunction());

	Local<Function> fn = tpl->GetFunction();
	constructor.Reset(isolate, fn);
	target->Set(String::NewSymbol("MyObject"), fn);

	Local<FunctionTemplate> nTpl = FunctionTemplate::New(Notification::New);
	nTpl->SetClassName(String::NewSymbol("Desktop Notification"));
	// for wrap notification instance in memory;
	nTpl->InstanceTemplate()->SetInternalFieldCount(1);
	// prototype
	nTpl->PrototypeTemplate()->Set(String::NewSymbol("show"), FunctionTemplate::New(Notification::Update)->GetFunction());

	target->Set(String::NewSymbol("notify"), nTpl->GetFunction());
	target->Set(String::NewSymbol("updateNotify"), FunctionTemplate::New(Notification::Update)->GetFunction());
}

void MyObject::New(const v8::FunctionCallbackInfo<Value>& args){
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	if (args.IsConstructCall()){
		double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
//		printf("%f", value);
		MyObject* obj = new MyObject(value);
		Local<Object> instance = args.This();
		instance->Set(String::NewSymbol("name"), String::New("wangyu!"));
		// make returned instance can access add function
		obj->Wrap(instance);
//		args.GetReturnValue().Set();
	}else {
		const int argc = 1;
		Local<Value> argv[argc] = {
				args[0]
		};
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		args.GetReturnValue().Set(cons->NewInstance(argc, argv));
	}
}

void MyObject::Add(const v8::FunctionCallbackInfo<Value>& args){
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	MyObject *obj = ObjectWrap::Unwrap<MyObject>(args.This());
	obj->value_ += 1;
	args.GetReturnValue().Set(Number::New(obj->value_));
}


//void MyObject::DesktopNotify(const v8::FunctionCallbackInfo<Value>& info){
//	// notify_init (const char *app_name)
//	notify_init ("Hello world!");
//	NotifyNotification * Hello = notify_notification_new ("Hello world", "This is an example notification.", "dialog-information");
//	notify_notification_show (Hello, NULL);
//	// Gnome Object decrease reference!
//	g_object_unref(G_OBJECT(Hello));
//	notify_uninit();
//}

void Plus(const v8::FunctionCallbackInfo<Value>& info){
//	printf("hello C++!");
	info.GetReturnValue().Set(String::New("hello C++!"));
}
