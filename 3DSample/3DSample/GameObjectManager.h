#pragma once
#include"GameObject.h"
#include "TestObject.h"
#include "Player.h"
#include "Child.h"
#include "Kuribo.h"
#include "Bat.h"
#include "Teresa.h"
#include "KuriboBullet.h"
#include "BatBullet.h"
#include<vector>
namespace Framework {
	class GameObjectManager:public IObject
	{
	public:

		GameObjectManager();

		~GameObjectManager();

		void AddObject_Init(std::shared_ptr<GameObject> shp_arg_gameObject);

		void AddObject(std::shared_ptr<GameObject> shp_arg_gameObject);

		void InportObject(std::shared_ptr<GameObject> shp_arg_gameObject);

		void RemoveObject(std::shared_ptr<GameObject> shp_arg_removeObject);

		void DeathRemoveGameObjects(ObjectTag tag);

		void Initialize()override {};

		void PreInitialize()override {};

		void Release();

		std::shared_ptr<GameObject> SerchGameObject(ObjectTag serchObjectsTag);

		std::vector<std::shared_ptr<GameObject>>SerchGameObjects(ObjectTag serchObjectsTag);

		bool Update();

		void RemoveCheck();
	private:

		std::vector<std::shared_ptr<GameObject>> vec_shp_gameObjects;
		std::vector<std::shared_ptr<GameObject>> vec_shp_new_gameObjects;
	};

}