#pragma once
#include "GameObject.h"
#include"Resource.h"
#include"Collision2D.h"


namespace Framework {
	class ChildSeed :public GameObject
	{
	public:
		ChildSeed(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager);
		~ChildSeed();
		void Hit(std::shared_ptr<GameObject> other)override;
		void PreInitialize()override;
		bool OnUpdate()override;

		bool Release()override;
		std::shared_ptr<Resource_Texture> shp_texture;
		std::shared_ptr<Resource_Sound> shp_sound_medal;

		std::shared_ptr<Collision2D_Rectangle>shp_collisionRect;
		std::shared_ptr<Rectangle> GetRectangle() { return shp_collisionRect->rect; }
	private:
		std::shared_ptr<GameObject> player;

		float gravity,
			maxFallSpeed;
		bool isGround;

	};
}
