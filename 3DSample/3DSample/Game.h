#pragma once
#include"Library.h"
#include"ResouceController.h"
#include"SceneManager.h"
#include"Collision2DManager.h"
#include "CSVReader.h"
#include"GameTime.h"
namespace Framework {
	class Game
	{
	public:
		Game(int windowWidth, int windowHeight, std::string windowText, Vector4 color);
		bool Draw();
		bool SoundPlay();
		bool Update();
		bool ResourceLoad();
		void SceneInitialize();
		void GameReset();
		static bool CreateInstance(int windowWidth, int windowHeight, std::string windowText, Color color);
		bool Exit();
		static std::unique_ptr<Game>& GetInstance();
		std::unique_ptr<ResouceController>& GetResourceController();
		std::unique_ptr<SceneManager>& GetSceneManager();
		std::unique_ptr<Collision2DManager>& GetCollision2DManager();
		std::unique_ptr<GameTime>& GetGameTime();
	private:
		void Reset();
		int width, height;
		int targetScreenHundle;
		bool isReset;
		std::unique_ptr<ResouceController> unq_resourceController;
		std::unique_ptr<SceneManager> unq_sceneManager;
		std::unique_ptr<Collision2DManager> unq_collision2DManager;
		std::unique_ptr<GameTime> unq_gameTime;
		static std::unique_ptr<Game> instance;
	};
}