#pragma once
#include "IScene.h"
#include "TestScene.h"
#include<map>
namespace Framework {
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();
		void Initialize();
		bool Update();
		void Release();
		void ChangeScene(std::shared_ptr<IScene> shp_arg_changeScene,int sceneChangeDelay=0, std::shared_ptr<SceneOverObjects> shp_sceneOverObjects = nullptr);
		void ChangeScene(std::string changeSceneName, int sceneChangeDelay=0, std::shared_ptr<SceneOverObjects> shp_sceneOverObjects=nullptr);
		void LoadScene(std::shared_ptr<IScene> shp_arg_changeScene);
		std::shared_ptr<IScene> GetCurrentScene() {
			return shp_currentScene->GetThis<IScene>();
		};
	private:
		std::shared_ptr<IScene> shp_currentScene;
		std::shared_ptr<IScene> shp_nextScene=nullptr;
		std::shared_ptr<SceneOverObjects> shp_sceneOverObjects = nullptr;
		std::map<std::string, std::shared_ptr<IScene>> map_scenes;
		Timer sceneChangeTimer;
	};

}