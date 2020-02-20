#pragma once
#include"GameObjectManager.h"
#include"Resource.h"
#include"AbsTimer.h"
namespace Framework {
	class SlideFadeIn :public GameObject
	{
	public:
		SlideFadeIn(int direction, std::shared_ptr<GameObjectManager> arg_manager);
		void Initialize()override;
		void PreInitialize()override;
		bool OnUpdate()override;
		bool Release()override;
	private:
		AbsTimer sucideTimer;
		std::shared_ptr<Resource_Rect> shp_texture;
		int speed,
			direction;
		Vector3 target;
	}; 
	class SlideFadeOut :public GameObject
	{
	public:
		SlideFadeOut(int direction, std::shared_ptr<GameObjectManager> arg_manager);
		void Initialize()override;
		void PreInitialize()override;
		bool OnUpdate()override;
		bool Release()override;
	private:
		AbsTimer sucideTimer;
		std::shared_ptr<Resource_Rect> shp_texture;
		int speed,
			direction;
		Vector3 target;
	};

}