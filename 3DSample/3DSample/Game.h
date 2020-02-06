#pragma once
#include"Library.h"
#include"ResouceController.h"
#include"SceneManager.h"
namespace Framework {
	class Game
	{
	public:
		Game(int windowWidth, int windowHeight, std::string windowText, Vector4 color);
		bool Draw();
		bool Update();
		static bool CreateInstance(int windowWidth, int windowHeight, std::string windowText, Color color);
		bool Exit();
		static std::unique_ptr<Game>& GetInstance();
		std::unique_ptr<ResouceController>& GetResourceController();
		std::unique_ptr<SceneManager>& GetSceneManager();
	private:
		int width, height;
		int targetScreenHundle;
		std::unique_ptr<ResouceController> unq_resourceController;
		std::unique_ptr<SceneManager> unq_sceneManager;
		static std::unique_ptr<Game> instance;
	};
}