#include "Game.h"
#include"MapScene.h"
#include <chrono>
#include"ClearScene.h"
#include"TestScene.h"
#include"TutorialScene.h"
std::unique_ptr<Framework::Game> Framework::Game::instance=nullptr;

Framework::Game::Game(int windowWidth, int windowHeight, std::string windowText, Framework::Vector4 color):width(windowWidth),height(windowHeight)
{

	ChangeWindowMode(FALSE);
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetGraphMode(windowWidth, windowHeight,60);
	SetWindowSizeExtendRate(1.0);
	auto colorArray = color.GetData();
	SetBackgroundColor(colorArray[0],colorArray[1],colorArray[2],colorArray[3]);
	SetMainWindowText(windowText.c_str());
	DxLib_Init();

	unq_gameTime = std::make_unique<GameTime>();

	unq_resourceController = std::make_unique<ResouceController>(windowWidth, windowHeight);;
	unq_sceneManager = std::make_unique<SceneManager>();
	unq_collision2DManager = std::make_unique<Collision2DManager>();
	targetScreenHundle = MakeScreen(windowWidth, windowHeight, TRUE);



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

bool Framework::Game::SoundPlay() {
	unq_resourceController->SoundPlay();
	return true;
}

bool Framework::Game::Update()
{
	if (isReset) {
		Reset();
		isReset = false;
	}
		SoundPlay();
		auto result = unq_sceneManager->OnUpdate();
		unq_gameTime->OnUpdate();
		unq_collision2DManager->OnUpdate();
		return result;
	
}


bool Framework::Game::ResourceLoad()
{
	unq_resourceController->AddLayer(4);

	unq_resourceController->LoadTexture("sample.png");

	unq_resourceController->LoadTexture("sample2.png");

	unq_resourceController->LoadTexture("sample3.png");

	unq_resourceController->LoadTexture("sample4.png");

	unq_resourceController->LoadTexture("sample5.png");

	unq_resourceController->LoadTexture("orange.png");
	unq_resourceController->LoadTexture("cursol.png");
	unq_resourceController->LoadTexture("kirari.png");


	unq_resourceController->LoadTexture("child32.png");
	unq_resourceController->LoadTexture("block.png");
	unq_resourceController->LoadTexture("robo.png");
	unq_resourceController->LoadTexture("Kuribo_1.png");
	unq_resourceController->LoadTexture("Bat_1.png");
	unq_resourceController->LoadTexture("Medal_1.png");

	unq_resourceController->LoadTexture("apple.png");
	unq_resourceController->LoadTexture("title.png");
	unq_resourceController->LoadTexture("bullet.png");
	unq_resourceController->LoadTexture("enemyBullet.png");
	unq_resourceController->LoadTexture("enemyBomb.png");


	unq_resourceController->LoadTexture("blackParticle.png");
	unq_resourceController->LoadTexture("cover.png");

	unq_resourceController->LoadTexture("orangeParticle.png");

	unq_resourceController->LoadTexture("yellowParticle.png");

	unq_resourceController->LoadTexture("whiteParticle.png");

	unq_resourceController->LoadCreateFont("testFont", "MS　明朝", 32, -1, DX_FONTTYPE_NORMAL);
	unq_resourceController->LoadCreateFontData("simpleBit", "Resource/4x4bit.dft", 0);
	unq_resourceController->LoadTexture("pumpkin.png");

	unq_resourceController->LoadTexture("potato.png");

	unq_resourceController->LoadTexture("watermelon.png");

	unq_resourceController->LoadTexture("block_horizontal.png");
	unq_resourceController->LoadTexture("block_vertical.png");
	unq_resourceController->LoadTexture("block_top.png");
	unq_resourceController->LoadTexture("block_bottom.png");
	unq_resourceController->LoadTexture("block_left.png");
	unq_resourceController->LoadTexture("block_right.png");
	unq_resourceController->LoadTexture("block_leftTop.png");
	unq_resourceController->LoadTexture("block_leftBottom.png");
	unq_resourceController->LoadTexture("block_rightTop.png");
	unq_resourceController->LoadTexture("block_rightBottom.png");

	unq_resourceController->LoadTexture("gate.png");
	unq_resourceController->LoadTexture("seed.png");

	unq_resourceController->LoadSound("Damage.wav");
	unq_resourceController->LoadSound("Explosion.wav");
	unq_resourceController->LoadSound("Jump.wav");
	unq_resourceController->LoadSound("Shoot.wav");
	unq_resourceController->LoadSound("Throw.wav");
	unq_resourceController->LoadSound("Coin.wav");
	unq_resourceController->LoadSound("Found.wav");
	unq_resourceController->LoadSound("Landing.wav");
	unq_resourceController->LoadSound("Mapmove.wav");
	unq_resourceController->LoadSound("Game_play2.wav");

	return true;
}

void Framework::Game::SceneInitialize()
{
	unq_sceneManager->Initialize();
	unq_sceneManager->LoadScene(ObjectFactory::Create<TestScene>());
	unq_sceneManager->LoadScene(ObjectFactory::Create<ClearScene>());
	unq_sceneManager->LoadScene(ObjectFactory::Create<TitleScene>());
	unq_sceneManager->LoadScene(ObjectFactory::Create<MapScene>("beta.csv"));
	unq_sceneManager->LoadScene(ObjectFactory::Create<MapScene>("Map1.csv"));
	unq_sceneManager->LoadScene(ObjectFactory::Create<MapScene>("Map2.csv"));
	unq_sceneManager->LoadScene(ObjectFactory::Create<MapScene>("Map3.csv"));
	unq_sceneManager->LoadScene(ObjectFactory::Create<MapScene>("Map4.csv"));
	unq_sceneManager->LoadScene(ObjectFactory::Create<MapScene>("Map5.csv"));
	unq_sceneManager->LoadScene(ObjectFactory::Create<MapScene>("Map6.csv"));
	unq_sceneManager->LoadScene(ObjectFactory::Create<MapScene>("Map7.csv"));
	unq_sceneManager->LoadScene(ObjectFactory::Create<MapScene>("Map8.csv"));
	unq_sceneManager->LoadScene(ObjectFactory::Create<MapScene>("Map9.csv"));
	unq_sceneManager->LoadScene(ObjectFactory::Create<TutorialScene>());
	//unq_sceneManager->LoadScene(ObjectFactory::Create<MapScene>("Map_tutorial.csv"));

	unq_sceneManager->ChangeScene("TestScene");
}

void Framework::Game::GameReset()
{
	isReset = true;
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
		unq_sceneManager->Release();
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

std::unique_ptr<Framework::GameTime>& Framework::Game::GetGameTime()
{
	return unq_gameTime;
}

void Framework::Game::Reset()
{
	unq_collision2DManager->Release();
	unq_gameTime->Initilize();
	SceneInitialize();
}
