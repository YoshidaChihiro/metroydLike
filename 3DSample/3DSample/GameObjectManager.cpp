#include "GameObjectManager.h"
Framework::GameObjectManager::GameObjectManager()
{
}

Framework::GameObjectManager::~GameObjectManager()
{
}

void Framework::GameObjectManager::AddObject_Init(std::shared_ptr<GameObject> shp_arg_gameObject)
{
	vec_shp_gameObjects.push_back(shp_arg_gameObject->GetThis<GameObject>());
}

void Framework::GameObjectManager::AddObject(std::shared_ptr<GameObject> shp_arg_gameObject)
{

	vec_shp_new_gameObjects.push_back(shp_arg_gameObject);
}

void Framework::GameObjectManager::InportObject(std::shared_ptr<GameObject> shp_arg_gameObject)
{
	shp_arg_gameObject->SetGameObjectManager(GetThis<GameObjectManager>());
	for (auto itr = vec_shp_gameObjects.begin(); itr != vec_shp_gameObjects.end(); itr++) {
		if ((*itr) == shp_arg_gameObject)
			return;
	}
	AddObject_Init(shp_arg_gameObject);
}

void Framework::GameObjectManager::RemoveObject(std::shared_ptr<GameObject> shp_arg_removeObject)
{
	for (auto itr = vec_shp_gameObjects.begin(); itr != vec_shp_gameObjects.end(); itr++) {
		if ((*itr) == shp_arg_removeObject) {
			vec_shp_gameObjects.erase(itr);
			break;
		}
	}
}

void Framework::GameObjectManager::DeathRemoveGameObjects(ObjectTag tag)
{
	auto itr = vec_shp_gameObjects.begin();
	while (itr!=vec_shp_gameObjects.end())
	{
		if ((*itr)->GetObjectTag() == tag) {
			(*itr)->SetIsDead(true);
			(*itr)->Release();
			itr = vec_shp_gameObjects.erase(itr);
		}
		else {
			itr++;
		}
	}

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

std::shared_ptr<Framework::GameObject> Framework::GameObjectManager::SerchGameObject(ObjectTag serchObjectsTag)
{
	for (auto itr = vec_shp_gameObjects.begin(); itr != vec_shp_gameObjects.end(); itr++) {
		if ((*itr)->GetObjectTag() == serchObjectsTag) {
			return (*itr)->GetThis<GameObject>();
		}
	}
	return nullptr;
}

std::vector<std::shared_ptr<Framework::GameObject>> Framework::GameObjectManager::SerchGameObjects(ObjectTag serchObjectsTag)
{
	std::vector< std::shared_ptr<GameObject>> objects;
	for (auto itr = vec_shp_gameObjects.begin(); itr != vec_shp_gameObjects.end(); itr++) {
		if ((*itr)->GetObjectTag() == serchObjectsTag) {
			objects.push_back( (*itr)->GetThis<GameObject>());
		}
	}
	return objects;
}

bool Framework::GameObjectManager::Update()
{

	for (auto itr = vec_shp_new_gameObjects.begin(); itr != vec_shp_new_gameObjects.end(); itr++) {
		vec_shp_gameObjects.push_back(*itr);
	}

	vec_shp_new_gameObjects.clear();

	auto itr = vec_shp_gameObjects.begin();
	while (itr != vec_shp_gameObjects.end())
	{
			(*itr)->Update();
		
		itr++;
	}

	return true;

}

void Framework::GameObjectManager::RemoveCheck()
{
	auto itr = vec_shp_gameObjects.begin();
	while (itr != vec_shp_gameObjects.end())
	{
		
		(*itr)->DeadCheck();
		if ((*itr)->GetIsRemove()) {
			(*itr)->Release();
			itr = vec_shp_gameObjects.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}
