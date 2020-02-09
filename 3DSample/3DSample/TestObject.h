#pragma once
#include "GameObject.h"
#include"Resource.h"
#include"Collision2D.h"
namespace Framework {
	class TestObject:public GameObject
	{
	public:
		TestObject(std::shared_ptr<Transform> shp_arg_transform,std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager);
		~TestObject();
		void Hit(std::shared_ptr<GameObject> other)override;
		void PreInitialize()override;
		bool Update()override;
		std::shared_ptr<Resource_Texture> shp_texture;
		std::shared_ptr<Collision2D_Rectangle>shp_collisionRect;
		int anotherHandle,handle;
		int c = 60;
	};
}

