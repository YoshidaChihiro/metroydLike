#pragma once
#include"GameObjectManager.h"
#include"AbsTimer.h"
namespace Framework {
	class SlideFade:public GameObject
	{
	public:
		SlideFade(std::shared_ptr<GameObjectManager> manager);
		~SlideFade();

		void PreInitialize()override;
		void Initialize()override;
		bool OnUpdate()override;
		bool Release()override;
		std::shared_ptr<Resource_Texture> shp_texture;
		AbsTimer timer;
	};
}

