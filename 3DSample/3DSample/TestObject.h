#pragma once
#include "GameObject.h"
#include"Resource.h"
namespace Framework {
	class TestObject:public GameObject
	{
	public:
		TestObject(std::shared_ptr<Transform> shp_arg_transform,std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager);
		~TestObject();
		bool Update()override;
		std::shared_ptr<Resource_Texture> shp_texture;
	};
}

