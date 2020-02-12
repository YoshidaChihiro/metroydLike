#include "Game.h"
#include"MapScene.h"
#include <chrono>
std::unique_ptr<Framework::Game> Framework::Game::instance=nullptr;

Framework::Game::Game(int windowWidth, int windowHeight, std::string windowText, Framework::Vector4 color):width(windowWidth),height(windowHeight)
{

	ChangeWindowMode(TRUE);
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetGraphMode(windowWidth, windowHeight,60);
	SetWindowSizeExtendRate(1.0);
	auto colorArray = color.GetData();
	SetBackgroundColor(colorArray[0],colorArray[1],colorArray[2],colorArray[3]);
	SetMainWindowText(windowText.c_str());
	DxLib_Init();

	unq_resourceController = std::make_unique<ResouceController>(windowWidth, windowHeight);;
	unq_sceneManager = std::make_unique<SceneManager>();
	unq_collision2DManager = std::make_unique<Collision2DManager>();

	targetScreenHundle = MakeScreen(windowWidth, windowHeight, TRUE);

	auto data = CSVReader::GetMatrixByFile("testMap.csv");


}

bool Framework::Game::Draw()
{
	timespec befTime;
	timespec nowTime;
	timespec delta;

	timespec_get(&befTime, TIME_UTC);
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	unq_resourceController->Draw();

	//ClearDrawScreen();
	ScreenFlip();

	timespec_get(&nowTime, TIME_UTC);
	ButiTime::timespecSubstruction(&nowTime, &befTime, &delta);
	auto deltaMiliTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::nanoseconds{ delta.tv_nsec });

	return true;
}

bool Framework::Game::Update()
{
	unq_collision2DManager->Update();
	return unq_sceneManager->Update();

}

bool Framework::Game::ResourceLoad()
{
	unq_resourceController->LoadTexture("sample.png");

	unq_resourceController->LoadTexture("sample2.png");

	unq_resourceController->LoadCreateFont("testFont", "�l�r ����", 32, -1, DX_FONTTYPE_NORMAL);
	return true;
}

void Framework::Game::SceneInitialize()
{
	unq_sceneManager->Initialize();
	unq_sceneManager->LoadScene(ObjectFactory::Create<TestScene>());
	unq_sceneManager->LoadScene(ObjectFactory::Create<MapScene>("Map1.csv"));
	unq_sceneManager->LoadScene(ObjectFactory::Create<MapScene>("Map2.csv"));
	unq_sceneManager->LoadScene(ObjectFactory::Create<MapScene>("Map3.csv"));
	unq_sceneManager->LoadScene(ObjectFactory::Create<MapScene>("Map4.csv"));
	unq_sceneManager->LoadScene(ObjectFactory::Create<MapScene>("Map5.csv"));
	unq_sceneManager->LoadScene(ObjectFactory::Create<MapScene>("Map6.csv"));
	unq_sceneManager->LoadScene(ObjectFactory::Create<MapScene>("Map7.csv"));
	unq_sceneManager->LoadScene(ObjectFactory::Create<MapScene>("Map8.csv"));
	unq_sceneManager->LoadScene(ObjectFactory::Create<MapScene>("Map9.csv"));

	unq_sceneManager->ChangeScene("TestScene");
}

bool Framework::Game::CreateInstance(int windowWidth, int windowHeight, std::string windowText, Framework::Color color)
{
	if (instance) {
		return false;
	}
	instance = std::make_unique<Framework::Game>(windowWidth, windowHeight, windowText, color);
	Framework::ButiRandom::Initialize();
	Framework::Input::Initialize();
	return true;
}

bool Framework::Game::Exit()
{
	if (DxLib_End() == -1) {
		return false;
	}
	else
	{
		return true;
	}
}

std::unique_ptr<Framework::Game>& Framework::Game::GetInstance()
{
	if (instance.get() == 0) {
		throw Framework:: ButiException(L"Didn't Create instance", L"if (instance.get() == 0)", L"Game::GetInstance()");
	}
	return instance;
}

std::unique_ptr<Framework::ResouceController>& Framework::Game::GetResourceController()
{
	return unq_resourceController;
}

std::unique_ptr<Framework::SceneManager>& Framework::Game::GetSceneManager()
{
	return unq_sceneManager;
}

std::unique_ptr<Framework::Collision2DManager>& Framework::Game::GetCollision2DManager()
{
	return unq_collision2DManager;
}
