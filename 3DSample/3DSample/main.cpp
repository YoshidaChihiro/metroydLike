#pragma once
#include"Game.h"
#include<stdio.h>
#include<time.h>
#include<ctime>
#include <chrono>
#include <DxLib.h>

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE HPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	int win_width = 960,
		win_height = 640;
	SetGraphMode(win_width, win_height, 32);

	//initMethod
	Framework::Game::CreateInstance(win_width, win_height,"test",Framework::Color(0x00,0x00,0x00,0));
	int i = 0;
	Framework::Game::GetInstance()->ResourceLoad();
	Framework::Game::GetInstance()->SceneInitialize();

	timespec befTime;
	timespec nowTime;
	timespec deltaTime;

	timespec_get(&befTime, TIME_UTC);
	timespec_get(&nowTime, TIME_UTC);

	std::chrono::milliseconds deltaMilliSeconds;

	//mainLoop
	while (1) 
	{
		
		//auto miliDelta = std::chrono::milliseconds{ nowTime.tv_sec - befTime.tv_sec };
		//deltaTime += miliDelta;

		

		if (deltaMilliSeconds .count()> 0&&deltaMilliSeconds.count()<16 ) {
			//WaitTimer(16 - deltaMilliSeconds.count());
		}



		Framework::Input::Update();

		//XV‹——£

		timespec_get(&befTime, TIME_UTC);
		Framework::Game::GetInstance()->Update();

		//•`‰æˆ—

		Framework::Game::GetInstance()->Draw();
		timespec_get(&nowTime, TIME_UTC);

		if (ProcessMessage() == -1)
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;

		Framework::ButiTime::timespecSubstruction(&nowTime, &befTime, &deltaTime);
		deltaMilliSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::nanoseconds{ deltaTime.tv_nsec });


	}
	//exitMethod
	
	Framework::Game::GetInstance()->Exit();

	return 0;

}