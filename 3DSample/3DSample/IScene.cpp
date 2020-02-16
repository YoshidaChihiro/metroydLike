#include "IScene.h"

void Framework::IScene::SetSceneOverObjects(std::shared_ptr<SceneOverObjects> shp_arg_sceneOverObjects)
{
	auto objs = shp_arg_sceneOverObjects->GetSceneOverGameObjects();

	auto manager = (*objs.begin())->manager;



	for (auto itr =objs.begin() ; itr != objs.end(); itr++) {
		manager->RemoveObject(*itr);
		shp_gameObjectManager->InportObject(*itr);
		if ((*itr)->GetObjectTag() == ObjectTag::player) {
			(*itr)->transform->localPosition = shp_arg_sceneOverObjects->playerPos;
		}
	}
	manager->DeathRemoveGameObjects(ObjectTag::enemy);
}

std::vector<std::shared_ptr< Framework::GameObject>> Framework::SceneOverObjects::GetSceneOverGameObjects()
{
	return vec_shp_gameObjects;
}

void Framework::SceneOverObjects::AddSceneOverGameObject(std::shared_ptr<GameObject> arg_gameObject)
{
	vec_shp_gameObjects.push_back(arg_gameObject);
}
