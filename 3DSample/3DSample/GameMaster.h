#pragma once
#include"ButiMath.h"
#include"StopWatch.h"
namespace Framework{
class GameMaster
{
public:
	GameMaster();
	void Initialize();
	void GetMedal();
	int GetChildsMax() {
		return playerChildMax + getedMedalCount;
	};
	void SetRespawnPosition(Vector3 arg_respawn) {
		playerRespawnPoint = arg_respawn;
	}
	int GetMedalCount();
	void GameOver();
	void SetPlayerChildsCount(int setCount) {
		playerChildsCount = setCount;
	}
	int GetPlayerChildsCount() {
		return playerChildsCount ;
	}
	Vector3 GetRespawnPoint() {
		return playerRespawnPoint;
	}
	std::chrono::milliseconds GetNowTime();
private:
	int getedMedalCount;
	int medalCountMax;
	int playerChildsCount;
	int playerChildMax;
	Vector3 playerRespawnPoint;
	StopWatch stopWatch;
};

}