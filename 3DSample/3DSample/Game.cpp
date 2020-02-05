#include "Game.h"

std::unique_ptr<Game> Game::instance=nullptr;

Game::Game(int windowWidth, int windowHeight, std::string windowText, Framework::Vector4 color)
{

	ChangeWindowMode(TRUE);
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetGraphMode(windowWidth, windowHeight,60);
	SetWindowSizeExtendRate(1.0);
	auto colorArray = color.GetData();
	SetBackgroundColor(colorArray[0],colorArray[1],colorArray[2],colorArray[3]);
	SetMainWindowText(windowText.c_str());
	DxLib_Init();

}

bool Game::Draw()
{
	return true;
}

bool Game::Update()
{

	return true;
}

bool Game::CreateInstance(int windowWidth, int windowHeight, std::string windowText, Framework::Color color)
{
	if (instance) {
		return false;
	}
	instance = std::make_unique<Game>(windowWidth, windowHeight, windowText, color);
	return true;
}

bool Game::Exit()
{
	if (DxLib_End() == -1) {
		return false;
	}
	else
	{
		true;
	}
}

std::unique_ptr<Game>& Game::GetInstance()
{
	if (instance.get() == 0) {
		throw Framework:: ButiException(L"Didn't Create instance", L"if (instance.get() == 0)", L"Application::GetApplication()");
	}
	return instance;
}
