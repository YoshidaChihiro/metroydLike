#include "GameMaster.h"

Framework::GameMaster::GameMaster()
{
	playerChildsCount = 0;
	playerRespawnPoint = Vector3();
	getedMedalCount = 0;
	medalCountMax=5;
	stopWatch = StopWatch();
	stopWatch.Start();
	playerChildMax = 1;
}

void Framework::GameMaster::Initialize()
{
	playerChildsCount = 0;
	playerRespawnPoint = Vector3();
	getedMedalCount = 0;
	medalCountMax = 5;
	stopWatch = StopWatch();
	stopWatch.Start();
	playerChildMax = 1;
}

void Framework::GameMaster::GetMedal()
{
	getedMedalCount += 1;
}

int Framework::GameMaster::GetMedalCount()
{
	return getedMedalCount;
}

void Framework::GameMaster::GameOver()
{
}

std::chrono::milliseconds Framework::GameMaster::GetNowTime()
{
	return stopWatch.GetTime();
}
