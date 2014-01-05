#include <node.h>
#include <libnotify/notify.h>
#include "notification.h"

Notification::Notification(){
	notify_init ("Hello world!");
	NotifyNotification* N = notify_notification_new("Hello world", "example", "dialog-information");
//	notify_notification_show(N, NULL);
	pNotify_= static_cast<void*>(N);
}
Notification::~Notification() {
}

void Notification::New(const v8::FunctionCallbackInfo<Value>& info){
	if (info.IsConstructCall()){
//		return ThrowError("Must call this function as a constructor.");
		Notification* notify = new Notification();

		// link notify to the returned instance
		notify->Wrap(info.This());

//		NotifyNotification * Hello = notify_notification_new ("Hellexio world", "This is an example notification.", "dialog-information");
//		notify_notification_show (Hello, NULL);
//		g_object_unref(G_OBJECT(Hello));
//		notify_uninit();
	}
}

void Notification::Update(const v8::FunctionCallbackInfo<Value>&info ){
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	Local<Value> JsSummary = info[0];
	Local<Value> JsBody = info[1];
	String::Utf8Value summary(JsSummary);
	String::Utf8Value body(JsBody);

	Notification* notify = ObjectWrap::Unwrap<Notification>(info.This());
	notify->Show(*summary, *body);
//	NotifyNotification* N = static_cast<NotifyNotification*>(notify->pNotify_);
//	notify_notification_update(N, "Hi", *content, "call-start");
//	notify_notification_show(N, NULL);
}

void Notification::Show(const char* summary, const char* body, const char* icon){
	NotifyNotification* N = static_cast<NotifyNotification*>(pNotify_);
	notify_notification_update(N, summary, body, icon);
	notify_notification_show(N, NULL);
}
