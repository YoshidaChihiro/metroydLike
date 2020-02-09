#pragma once
#include"GameObject.h"
#include "TestObject.h"
#include "Player.h"
#include "Child.h"
#include<vector>
namespace Framework {
	class GameObjectManager:public IObject
	{
	public:

		GameObjectManager();

		~GameObjectManager();

		void AddObject_Init(std::shared_ptr<GameObject> shp_arg_gameObject);

		void AddObject(std::shared_ptr<GameObject> shp_arg_gameObject);

		void Initialize()override {};

		void PreInitialize()override {};

		void Release();

		bool Update();

	private:

		std::vector<std::shared_ptr<GameObject>> vec_shp_gameObjects;
		std::vector<std::shared_ptr<GameObject>> vec_shp_new_gameObjects;
	};

}