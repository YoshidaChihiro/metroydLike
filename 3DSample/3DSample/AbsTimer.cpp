#include "AbsTimer.h"

Framework::AbsTimer::AbsTimer(int max)
{
	maxCountFrame = max;
	nowCountFrame = 0;
}

void Framework::AbsTimer::SetCount(int arg_nowCount)
{
	nowCountFrame = arg_nowCount;
}

void Framework::AbsTimer::ChangeCountFrame(int arg_maxCount)
{
	maxCountFrame = arg_maxCount;
}

void Framework::AbsTimer::Reset()
{
	nowCountFrame;
}
