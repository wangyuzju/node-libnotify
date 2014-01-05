#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <node.h>
#include <node_object_wrap.h>

using namespace v8;

class MyObject: public node::ObjectWrap {
public:
	static void Init(v8::Handle<v8::Object> target);

private:
	explicit MyObject(double value=0);
	~MyObject();




	static void New(const v8::FunctionCallbackInfo<v8::Value>& info);
	static void Add(const v8::FunctionCallbackInfo<v8::Value>& info);
	static void DesktopNotify(const v8::FunctionCallbackInfo<v8::Value>& info);
	static v8::Persistent<v8::Function> constructor;
	double value_;
};

#endif
