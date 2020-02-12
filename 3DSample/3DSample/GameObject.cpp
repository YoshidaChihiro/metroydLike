#include "GameObject.h"
#include "GameObjectManager.h"

bool Framework::GameObject::Release()
{
	for (auto itr = childs.begin(); itr != childs.end(); itr++) {
		if((*itr)!=nullptr)
		(*itr)->SetIsDead(true);
		(*itr) = nullptr;
	}
	return true;
}


void Framework::GameObject::PreInitialize()
{
}

void Framework::GameObject::SetGameObjectManager(std::shared_ptr<GameObjectManager> arg_manager) {
	manager = arg_manager->GetThis<GameObjectManager>();
	for (auto itr = childs.begin(); itr != childs.end(); itr++) {
		(*itr)->SetGameObjectManager(arg_manager);
	}
}

void Framework::GameObject::Initialize()
{
}

void Framework::GameObject::AddChildObject(std::shared_ptr<GameObject> arg_chid)
{
	childs.push_back(arg_chid->GetThis<GameObject>());
}

std::vector<std::shared_ptr<Framework::GameObject>> Framework::GameObject::GetChildObjects()
{
	return childs;
}
