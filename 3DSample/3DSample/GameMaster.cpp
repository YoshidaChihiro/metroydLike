#include "GameMaster.h"

Framework::GameMaster::GameMaster()
{
	playerChildsCount = 0;
	playerRespawnPoint = Vector3();
	getedMedalCount = 0;
	medalCountMax=5;
	stopWatch = StopWatch();
	stopWatch.Start();
	playerChildMax = 2;
	score = 0;
}

void Framework::GameMaster::Initialize()
{
	playerChildsCount = 0;
	playerRespawnPoint = Vector3();
	getedMedalCount = 0;
	medalCountMax = 5;
	stopWatch = StopWatch();
	stopWatch.Start();
	playerChildMax = 2;
	score = 0;
}

void Framework::GameMaster::GetMedal()
{
	getedMedalCount += 1;
}

void Framework::GameMaster::ReStart()
{
	stopWatch.Start();
}

int Framework::GameMaster::GetMedalCount()
{
	return getedMedalCount;
}

void Framework::GameMaster::GameOver()
{
}

void Framework::GameMaster::AddScore(int arg_addScore)
{
	score += arg_addScore;
	auto sec = GetNowTime();
}

std::chrono::milliseconds Framework::GameMaster::GetNowTime()
{
	return stopWatch.GetTime();
}
