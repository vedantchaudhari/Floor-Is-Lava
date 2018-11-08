/*
	egpThread.c
	By Dan Buckstein (c) 2017

	Simple thread for Windows.
*/

#include "egp-net/fw/utils/egpThread.h"


#include <Windows.h>


//-----------------------------------------------------------------------------
// internal thread launcher

long __stdcall egpThreadLaunch_internal(egpThread *thread)
{
	thread->running = 1;
	thread->result = thread->func(thread->args);
	thread->running = 0;
	return (thread->result);
}


//-----------------------------------------------------------------------------
// thread functions

int egpCreateThread(egpThread *thread_out, const egpThreadFunc func, void *args)
{
	if (thread_out && !thread_out->handle && func)
	{
		thread_out->result = 0;
		thread_out->running = 0;
		thread_out->args = args;
		thread_out->func = func;

		// launch thread
		thread_out->handle = CreateThread(0, 0, egpThreadLaunch_internal, thread_out, 0, &thread_out->threadID);

		return (thread_out->threadID);
	}
	return -1;
}


int egpTerminateThread(egpThread *thread)
{
	if (thread && thread->handle)
	{
		int success = TerminateThread(thread->handle, (unsigned long)(-1));
		if (success)
		{
			success = CloseHandle(thread->handle);
			if (success)
			{
				thread->handle = 0;
				thread->threadID = 0;
				thread->result = 0;
				thread->running = 0;
				return 1;
			}
		}
	}
	return -1;
}


//-----------------------------------------------------------------------------
