#include "SceneManager.h"

Framework::SceneManager::SceneManager()
{
	shp_currentScene = ObjectFactory::Create<TestScene>();
}

Framework::SceneManager::~SceneManager()
{
}

bool Framework::SceneManager::Update()
{
	if (shp_nextScene)
	{
		shp_currentScene->Release();
		shp_currentScene = shp_nextScene;
		shp_nextScene = nullptr;
	}
	return shp_currentScene->Update();
}

void Framework::SceneManager::Release()
{
	shp_currentScene->Release();
}

void Framework::SceneManager::ChangeScene(std::shared_ptr<IScene> shp_arg_changeScene)
{
	shp_nextScene = shp_arg_changeScene;
}
