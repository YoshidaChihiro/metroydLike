#pragma once
#include"AbsTimer.h"
namespace Framework {
	class GameTime
	{
	public:
		GameTime();
		void Initilize();
		void ChangeSpeed(float arg_speed);
		void OnUpdate();
		float GetSpeed()const {
			return gameSpeed;
		}
		void Stop(int stopFrame);
		void SlowMotion(float arg_speed,int stopFrame);
	private:
		float gameSpeed;
		float rightSpeed;
		AbsTimer timer;
	};

}