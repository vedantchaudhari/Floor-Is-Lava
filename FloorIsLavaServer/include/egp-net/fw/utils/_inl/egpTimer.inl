/*
	egpTimer.inl
	By Dan Buckstein (c) 2017

	Simple timer structure and functions for Windows.
*/

#ifdef __EGP_TIMER_H_
#ifndef __EGP_TIMER_INL_
#define __EGP_TIMER_INL_


// timer controls
inline int egpTimerStart(egpTimer *timer)
{
	if (timer)
	{
		timer->started = 1;
		QueryPerformanceFrequency(timer->tf);
		QueryPerformanceCounter(timer->t0);
		return 1;
	}
	return -1;
}

inline int egpTimerStop(egpTimer *timer)
{
	if (timer)
	{
		timer->started = 0;
		QueryPerformanceFrequency(timer->tf);
		QueryPerformanceCounter(timer->t1);
		return 1;
	}
	return -1;
}

inline int egpTimerSet(egpTimer *timer, double ticksPerSecond)
{
	if (timer)
	{
		timer->secondsPerTick = ticksPerSecond > 0.0 ? 1.0 / ticksPerSecond : 0.0;
		return 1;
	}
	return -1;
}


// update timer: returns 1 if ticked, 0 if did not tick, -1 if invalid param
inline int egpTimerUpdate(egpTimer *timer)
{
	int tick = 0;
	if (timer)
	{
		if (timer->started)
		{
			QueryPerformanceFrequency(timer->tf);
			QueryPerformanceCounter(timer->t1);
			timer->currentTick = (double)(timer->t1->QuadPart - timer->t0->QuadPart) / (double)(timer->tf->QuadPart);
			if (timer->secondsPerTick > 0.0)
			{
				while (timer->currentTick >= timer->secondsPerTick)
				{
					// update time step
					*(timer->t0) = *(timer->t1);

					// update ticker
					timer->totalTime += timer->secondsPerTick;
					timer->currentTick -= timer->secondsPerTick;
					++timer->ticks;
					++tick;
				}
			}
			else
			{
				// "continuous" update: always tick
				*(timer->t0) = *(timer->t1);
				timer->totalTime += timer->currentTick;
				++timer->ticks;
				++tick;
			}
		}
		return tick;
	}
	return -1;
}


#endif	// !__EGP_TIMER_INL_
#endif	// __EGP_TIMER_H_