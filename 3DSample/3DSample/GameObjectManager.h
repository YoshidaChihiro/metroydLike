#pragma once
#include"GameObject.h"
#include "TestObject.h"
#include<vector>
namespace Framework {
	class GameObjectManager
	{
	public:

		GameObjectManager();

		~GameObjectManager();

		void AddObject(std::shared_ptr<GameObject> shp_arg_gameObject);

		void Release();

		bool Update();

	private:

		std::vector<std::shared_ptr<GameObject>> vec_shp_gameObjects;
	};

}