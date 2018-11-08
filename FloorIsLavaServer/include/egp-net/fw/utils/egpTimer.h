/*
	egpTimer.h
	By Dan Buckstein (c) 2017

	Simple timer structure and functions for Windows.
*/

#ifndef __EGP_TIMER_H_
#define __EGP_TIMER_H_


#include <Windows.h>


#ifdef __cplusplus
extern "C"
{
#else
typedef struct egpTimer egpTimer;
#endif	// __cplusplus


//-----------------------------------------------------------------------------

// simple timer structure
struct egpTimer
{
	unsigned int started;
	unsigned int ticks;
	double totalTime;
	double currentTick;
	double secondsPerTick;

	// internal
	LARGE_INTEGER tf[1], t0[1], t1[1];
};


//-----------------------------------------------------------------------------

// timer controls: return 1 if success, -1 if invalid params
int egpTimerStart(egpTimer *timer);
int egpTimerStop(egpTimer *timer);
int egpTimerSet(egpTimer *timer, double ticksPerSecond);

// update timer: returns 1 if ticked, 0 if did not tick, -1 if invalid param
int egpTimerUpdate(egpTimer *timer);


//-----------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif	// __cplusplus


#include "_inl/egpTimer.inl"


#endif	// !__EGP_TIMER_H_