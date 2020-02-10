#include "SceneManager.h"

Framework::SceneManager::SceneManager()
{
}

Framework::SceneManager::~SceneManager()
{
}

void Framework::SceneManager::Initialize()
{
	shp_currentScene = ObjectFactory::Create<TestScene>();
}

bool Framework::SceneManager::Update()
{
	if (shp_nextScene)
	{
		//shp_currentScene->Release();
		shp_currentScene = shp_nextScene;
		shp_currentScene->OnSet();
		shp_nextScene = nullptr;

		if (shp_sceneOverObjects) {
			shp_currentScene->SetSceneOverObjects(shp_sceneOverObjects);
			shp_sceneOverObjects = nullptr;
		}
	}
	return shp_currentScene->Update();
}

void Framework::SceneManager::Release()
{
	shp_currentScene->Release();
	for (auto itr = map_scenes.begin(); itr != map_scenes.end(); itr++) {
		itr->second->Release();
	}
}

void Framework::SceneManager::ChangeScene(std::shared_ptr<IScene> shp_arg_changeScene,  std::shared_ptr<SceneOverObjects> shp_arg_sceneOverObjects )
{
	shp_nextScene = shp_arg_changeScene;
	shp_sceneOverObjects = shp_arg_sceneOverObjects;
}

void Framework::SceneManager::ChangeScene(std::string changeSceneName, std::shared_ptr<SceneOverObjects> shp_arg_sceneOverObjects)
{
	shp_sceneOverObjects = shp_arg_sceneOverObjects;
	shp_nextScene = map_scenes.at(changeSceneName);
}

void Framework::SceneManager::LoadScene(std::shared_ptr<IScene> shp_arg_changeScene)
{
	map_scenes.emplace(shp_arg_changeScene->GetSceneName(), shp_arg_changeScene->GetThis<IScene>());
}
