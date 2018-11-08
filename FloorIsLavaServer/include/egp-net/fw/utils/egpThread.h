/*
	egpThread.h
	By Dan Buckstein (c) 2017

	Simple thread structure and functions for Windows.
*/

#ifndef __EGP_THREAD_H_
#define __EGP_THREAD_H_


#ifdef __cplusplus
extern "C"
{
#else
typedef struct egpThread egpThread;
#endif	// __cplusplus


// thread launcher function pointer
typedef int(*egpThreadFunc)(void *);

// thread descriptor
struct egpThread
{
	void *handle;
	unsigned long threadID;
	int result;
	int running;
	void *args;
	egpThreadFunc func;
};


int egpCreateThread(egpThread *thread_out, const egpThreadFunc func, void *args);

int egpTerminateThread(egpThread *thread);


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// !__EGP_THREAD_H_