#pragma once
#include"IScene.h"
namespace Framework {
	class TestScene:public IScene
	{
	public:
		TestScene();
		~TestScene();
		void Initialize()override;

		void PreInitialize()override;

		bool Update()override;

		void Release()override;
	private:
		std::shared_ptr<Player> shp_player;
	};

}