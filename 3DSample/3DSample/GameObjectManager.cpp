#include "GameObjectManager.h"

Framework::GameObjectManager::GameObjectManager()
{
}

Framework::GameObjectManager::~GameObjectManager()
{
}

void Framework::GameObjectManager::AddObject(std::shared_ptr<GameObject> shp_arg_gameObject)
{
	vec_shp_gameObjects.push_back(shp_arg_gameObject->GetThis<GameObject>());
}

void Framework::GameObjectManager::Release()
{

	auto itr = vec_shp_gameObjects.begin();
	while (itr != vec_shp_gameObjects.end())
	{
		(*itr)->Release();
		itr = vec_shp_gameObjects.erase(itr);
		
	}
}

bool Framework::GameObjectManager::Update()
{
	for (auto itr = vec_shp_gameObjects.begin(); itr != vec_shp_gameObjects.end(); itr++) {
		if (!(*itr)->Update()) {
			return false;
		}
	}


	auto itr = vec_shp_gameObjects.begin();
	while (itr!=vec_shp_gameObjects.end())
	{
		if ((*itr)->GetIsDead()) {
			(*itr)->Release();
			itr = vec_shp_gameObjects.erase(itr);
		}
		else
		{
			itr++;
		}
	}

	return true;

}
