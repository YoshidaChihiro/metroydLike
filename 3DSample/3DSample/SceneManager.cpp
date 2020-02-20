#pragma once
#include"Game.h"
#include "SceneManager.h"

Framework::SceneManager::SceneManager():sceneChangeTimer(AbsTimer(0))
{
	unq_gameMaster = std::make_unique<GameMaster>();
}

Framework::SceneManager::~SceneManager()
{
}

void Framework::SceneManager::Initialize()
{
	Release();
	shp_currentScene = nullptr;
	shp_nextScene = nullptr;
	shp_sceneOverObjects = nullptr;
	map_scenes.clear();
	unq_gameMaster->Initialize();
}

bool Framework::SceneManager::OnUpdate()
{
	if (sceneChangeTimer.Update())
	{
		//shp_currentScene->Release();
		shp_currentScene = shp_nextScene;
		shp_nextScene = nullptr;

		if (shp_sceneOverObjects) {
			shp_currentScene->SetSceneOverObjects(shp_sceneOverObjects);
			shp_sceneOverObjects = nullptr;
		}
		shp_currentScene->OnSet();
		sceneChangeTimer.Stop();
	}
	return shp_currentScene->Update();
}

void Framework::SceneManager::Release()
{
	if(shp_currentScene)
	shp_currentScene->Release();
	for (auto itr = map_scenes.begin(); itr != map_scenes.end(); itr++) {
		itr->second->Release();
	}
}

std::string Framework::SceneManager::GetSceneName()
{
	return shp_currentScene->GetSceneName();
}

void Framework::SceneManager::ChangeScene(std::shared_ptr<IScene> shp_arg_changeScene, int sceneChangeDelay, std::shared_ptr<SceneOverObjects> shp_arg_sceneOverObjects )
{
	sceneChangeTimer = AbsTimer(sceneChangeDelay);
	sceneChangeTimer.Start();
	shp_nextScene = shp_arg_changeScene;
	shp_sceneOverObjects = shp_arg_sceneOverObjects;
	Game::GetInstance()->GetGameTime()->Stop(sceneChangeDelay);
}

void Framework::SceneManager::ChangeScene(std::string changeSceneName, int sceneChangeDelay, std::shared_ptr<SceneOverObjects> shp_arg_sceneOverObjects)
{
	sceneChangeTimer =AbsTimer(sceneChangeDelay);
	sceneChangeTimer.Start();
	shp_sceneOverObjects = shp_arg_sceneOverObjects;
	shp_nextScene = map_scenes.at(changeSceneName);
	Game::GetInstance()->GetGameTime()->Stop(sceneChangeDelay);
}

void Framework::SceneManager::LoadScene(std::shared_ptr<IScene> shp_arg_changeScene)
{
	map_scenes.emplace(shp_arg_changeScene->GetSceneName(), shp_arg_changeScene->GetThis<IScene>());
}
