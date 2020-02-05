#pragma once
#include"Library.h"
	class Game
	{
	public:
		Game(int windowWidth, int windowHeight, std::string windowText, Framework::Vector4 color);
		bool Draw();
		bool Update();
		static bool CreateInstance(int windowWidth, int windowHeight, std::string windowText, Framework::Color color);
		bool Exit();
		static std::unique_ptr<Game>& GetInstance() ;
	private:
		static std::unique_ptr<Game> instance;
	};
