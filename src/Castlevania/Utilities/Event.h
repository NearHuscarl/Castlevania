#pragma once

#define EVENT_SOURCE [event_source(native)]
#define EVENT_RECEIVER [event_receiver(native)]

#define EVENT __event
#define HOOK_EVENT __hook
#define UNHOOK_EVENT __unhook
#define RAISE_EVENT __raise

// Sample code for C++ native event
// See more at https://msdn.microsoft.com/en-us/library/ee2k0a7d.aspx

// // evh_native.cpp
// #include <stdio.h>
//
// [event_source(native)]
// class CSource {
// public:
// 	__event void MyEvent(int nValue);
// };
//
// [event_receiver(native)]
// class CReceiver {
// public:
// 	void MyHandler1(int nValue) {
// 		printf_s("MyHandler1 was called with value %d.\n", nValue);
// 	}
//
// 	void MyHandler2(int nValue) {
// 		printf_s("MyHandler2 was called with value %d.\n", nValue);
// 	}
//
// 	void hookEvent(CSource* pSource) {
// 		__hook(&CSource::MyEvent, pSource, &CReceiver::MyHandler1);
// 		__hook(&CSource::MyEvent, pSource, &CReceiver::MyHandler2);
// 	}
//
// 	void unhookEvent(CSource* pSource) {
// 		__unhook(&CSource::MyEvent, pSource, &CReceiver::MyHandler1);
// 		__unhook(&CSource::MyEvent, pSource, &CReceiver::MyHandler2);
// 	}
// };
//
// int main() {
// 	CSource source;
// 	CReceiver receiver;
//
// 	receiver.hookEvent(&source);
// 	__raise source.MyEvent(123);
// 	receiver.unhookEvent(&source);
// }
