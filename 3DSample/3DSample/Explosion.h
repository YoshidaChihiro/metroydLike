#pragma once
#include"GameObject.h"
#include"Resource.h"
#include"Collision2D.h"
namespace Framework {
	class Explosion:public GameObject
	{
	public:
		Explosion(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager);
		void Hit(std::shared_ptr<GameObject> other)override;
		void PreInitialize()override;
		void Initialize()override;
		bool Update()override;
	private:
		Timer sucide;
		std::shared_ptr<Resource_Texture> shp_texture;
		std::shared_ptr<Collision2D_Rectangle>shp_collisionRect;
	};

}