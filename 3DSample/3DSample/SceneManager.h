#pragma once
#include "IScene.h"
#include "TestScene.h"
namespace Framework {
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();
		bool Update();
		void Release();
		void ChangeScene(std::shared_ptr<IScene> shp_arg_changeScene);
		std::shared_ptr<IScene> GetCurrentScene() {
			return shp_currentScene->GetThis<IScene>();
		};
	private:
		std::shared_ptr<IScene> shp_currentScene;
		std::shared_ptr<IScene> shp_nextScene=nullptr;
	};

}