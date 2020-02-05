#pragma once
#include"Game.h"
#include<stdio.h>
#include<time.h>
#include<ctime>
#include <chrono>


int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE HPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	//initMethod
	Game::CreateInstance(720,480,"test",Framework::Color(0xff,0xff,0xff,0));


	timespec befTime;
	timespec nowTime;

	timespec_get(&befTime, TIME_UTC);
	timespec_get(&nowTime, TIME_UTC);


	//mainLoop
	while (1) 
	{
		auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::nanoseconds{ nowTime.tv_nsec - befTime.tv_nsec });
		if (deltaTime.count() > 0 && deltaTime.count() < 20) {
			WaitTimer(20 - deltaTime.count());
		}


		timespec_get(&befTime, TIME_UTC);

		//�X�V����

		Game::GetInstance()->Update();
		//�`�揈��

		Game::GetInstance()->Draw();

		if (ProcessMessage() == -1)
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;


		timespec_get(&nowTime, TIME_UTC);
	}
	//exitMethod
	
	Game::GetInstance()->Exit();

	return 0;

}