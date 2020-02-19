#pragma once
#include "IScene.h"
#include "TitleScene.h"
#include"AbsTimer.h"
#include<map>
#include"GameMaster.h"
namespace Framework {
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();
		void Initialize();
		bool OnUpdate();
		void Release();
		void ChangeScene(std::shared_ptr<IScene> shp_arg_changeScene,int sceneChangeDelay=0, std::shared_ptr<SceneOverObjects> shp_sceneOverObjects = nullptr);
		void ChangeScene(std::string changeSceneName, int sceneChangeDelay=0, std::shared_ptr<SceneOverObjects> shp_sceneOverObjects=nullptr);
		void LoadScene(std::shared_ptr<IScene> shp_arg_changeScene);
		std::shared_ptr<IScene> GetCurrentScene() {
			return shp_currentScene->GetThis<IScene>();
		};
		std::unique_ptr<GameMaster>& GetGameMaster() {
			return unq_gameMaster;
		}
	private:
		std::shared_ptr<IScene> shp_currentScene;
		std::shared_ptr<IScene> shp_nextScene=nullptr;
		std::shared_ptr<SceneOverObjects> shp_sceneOverObjects = nullptr;
		std::map<std::string, std::shared_ptr<IScene>> map_scenes;
		std::unique_ptr<GameMaster> unq_gameMaster;
		AbsTimer sceneChangeTimer;
	};

}