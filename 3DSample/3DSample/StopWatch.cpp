#include "StopWatch.h"
#include"Util.h"
Framework::StopWatch::StopWatch()
{
}

void Framework::StopWatch::Start()
{
	timespec_get(&startTime, TIME_UTC);
}

std::chrono::milliseconds Framework::StopWatch::GetTime()
{
	timespec_get(&nowTime, TIME_UTC);

	std::chrono::milliseconds deltaMilliSeconds;
	Framework::ButiTime::timespecSubstruction(&nowTime, &startTime, &deltaTime);
	deltaMilliSeconds = std::chrono::seconds{ deltaTime.tv_sec } +std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::nanoseconds{ deltaTime.tv_nsec });
	return deltaMilliSeconds;
}
