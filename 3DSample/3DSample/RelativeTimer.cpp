#pragma
#include "RelativeTimer.h"
#include"Game.h"

Framework::RelativeTimer::RelativeTimer(int max)
{
	maxCountFrame = max;
	nowCountFrame = 0;
}

void Framework::RelativeTimer::SetCount(int arg_nowCount)
{
	nowCountFrame = arg_nowCount;
}

void Framework::RelativeTimer::ChangeCountFrame(int arg_maxCount)
{
	maxCountFrame = arg_maxCount;
}

void Framework::RelativeTimer::Reset()
{
	nowCountFrame=0;
}

bool Framework::RelativeTimer::Update() {
	if (!isActive) {
		return false;
	}
	nowCountFrame+=Game::GetInstance()->GetGameTime()->GetSpeed();
	if (nowCountFrame >= maxCountFrame) {
		nowCountFrame = 0;
		return true;
	}
	return false;
}

