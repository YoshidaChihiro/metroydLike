#pragma once
#include"AbsTimer.h"
namespace Framework {
	class GameTime
	{
	public:
		GameTime();
		void ChangeSpeed(float arg_speed);
		void Update();
		float GetSpeed()const {
			return gameSpeed;
		}
		void Stop(int stopFrame);
		void SlowMotion(float arg_speed,int stopFrame);
		float gameSpeed;
		float rightSpeed;
		AbsTimer timer;
	private:
	};

}