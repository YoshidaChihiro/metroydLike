#include "GameObject.h"
#include "GameObjectManager.h"

bool Framework::GameObject::Release()
{
	return false;
}


void Framework::GameObject::PreInitialize()
{
}

void Framework::GameObject::SetGameObjectManager(std::shared_ptr<GameObjectManager> arg_manager) {
	manager = arg_manager->GetThis<GameObjectManager>();
}

void Framework::GameObject::Initialize()
{
}
