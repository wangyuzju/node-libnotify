#include <node.h>
#include <v8.h>
#include <sys/types.h>
#include <stdio.h>

using namespace v8;
//http://bespin.cz/~ondras/html/classv8_1_1FunctionCallbackInfo.html
Handle<Value> SayHello(const Arguments& args){
    HandleScope scope;

    if (args.Length() > 0 ){
    	if(!args[0]->IsString()){
    		ThrowException(Exception::TypeError(String::New("only string is allowed!")));
    		return scope.Close(Undefined());
    	}else {
    		Local<String> s = String::New("hello world ");
    		s = String::Concat(s,args[0]->ToString());
    		return scope.Close(s);
    	}
    }else{
    	ThrowException(Exception::TypeError(String::New("Please provide more information!")));
    	return scope.Close(Undefined());
    }

//    return scope.Close(String::New("hello world!"));
}

// Callbacks， invoking js in V8
Handle<Value> Run(const Arguments& args){
	HandleScope scope;

	Local<Function> fn = Local<Function>::Cast(args[0]);

	// prepare arguments for invoking JS function from c++
	const unsigned argc = 2;
	// the declaration for an array of pointers is in the {e1, e2, e3} form
	// reference : The C 5.9, argv is actually a pointer
	Local<Value> argv2 = String::New("arguments 2");
	Local<Value> argv[argc] = {
			Local<Value>::New(String::New("1. I'm String one from C++ part!")),
			argv2
	};
	fn->Call(Context::GetCurrent()->Global(), argc, argv);

	return scope.Close(Undefined());
}


// Object Factory, return JS Object
Handle<Value> NewPeople(const Arguments& args){
	HandleScope scope;

	Local<Object> p = Object::New();
	p->Set(String::NewSymbol("name"), args[0]->ToString());

	return scope.Close(p);
}


void PrintHello(const FunctionCallbackInfo<Value>& args) {
	//printf("hello C++!");
	HandleScope scope;


}


// Function Factory, return JS function implemented by C++
Handle<Value> Print (const Arguments& args){
	HandleScope scope;

	Local<FunctionTemplate> fnTmpl = FunctionTemplate::New();
//	Local<Function> fn = fnTmpl->GetFunction();
	Local<Object> o = Object::New();
//	fn->SetName(String::NewSymbol("print"));
	NODE_SET_METHOD(o, "print", PrintHello);
	return scope.Close(o);
}


void Init_Hello(Handle<Object> target){
    Local<FunctionTemplate> func_tmpl = FunctionTemplate::New(SayHello);
	target->Set(String::NewSymbol("greet"), func_tmpl->GetFunction());
	target->Set(String::NewSymbol("run"), FunctionTemplate::New(Run)->GetFunction());
	target->Set(String::NewSymbol("newPeople"), FunctionTemplate::New(NewPeople)->GetFunction());
	target->Set(String::NewSymbol("getFn"), FunctionTemplate::New(Print)->GetFunction());
}


NODE_MODULE(hello, Init_Hello)
