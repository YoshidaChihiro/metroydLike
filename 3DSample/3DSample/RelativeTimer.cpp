#include "RelativeTimer.h"

Framework::Timer::Timer(int max)
{
	maxCountFrame = max;
	nowCountFrame = 0;
}

void Framework::Timer::SetCount(int arg_nowCount)
{
	nowCountFrame = arg_nowCount;
}

void Framework::Timer::ChangeCountFrame(int arg_maxCount)
{
	maxCountFrame = arg_maxCount;
}

void Framework::Timer::Reset()
{
	nowCountFrame;
}

