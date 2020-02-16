#include "GameTime.h"

Framework::GameTime::GameTime() :timer(0)
{
	gameSpeed = 1.0f;
	rightSpeed = 1.0f;
}

void Framework::GameTime::ChangeSpeed(float arg_speed)
{
	gameSpeed = arg_speed;
}

void Framework::GameTime::OnUpdate()
{
	if (timer.Update()) {
		gameSpeed = rightSpeed;
		timer.Stop();
	}
}

void Framework::GameTime::Stop(int stopFrame)
{
	gameSpeed = 0;
	timer = AbsTimer(stopFrame);
	timer.Start();
}

void Framework::GameTime::SlowMotion(float arg_speed, int stopFrame)
{
	gameSpeed = arg_speed;
	timer = AbsTimer(stopFrame);
	timer.Start();

}
