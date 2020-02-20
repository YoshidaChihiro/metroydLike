#include "IScene.h"

void Framework::IScene::SetSceneOverObjects(std::shared_ptr<SceneOverObjects> shp_arg_sceneOverObjects)
{
	auto objs = shp_arg_sceneOverObjects->GetSceneOverGameObjects();

	auto beforeManager = (*objs.begin())->manager;



	for (auto itr =objs.begin() ; itr != objs.end(); itr++) {
		beforeManager->RemoveObject(*itr);
		shp_gameObjectManager->InportObject(*itr);
	}
	auto player = shp_gameObjectManager->SerchGameObject(ObjectTag::player);
	if (player) {
		player->GetThis<Player>()->SetSpawnPoint(shp_arg_sceneOverObjects->playerPos);
	}
	beforeManager->DeathRemoveGameObjects(ObjectTag::enemy);
	beforeManager->DeathRemoveGameObjects(ObjectTag::playerBullet);
	beforeManager->DeathRemoveGameObjects(ObjectTag::enemyBullet);
	beforeManager->DeathRemoveGameObjects(ObjectTag::particle);
}

std::vector<std::shared_ptr< Framework::GameObject>> Framework::SceneOverObjects::GetSceneOverGameObjects()
{
	return vec_shp_gameObjects;
}

void Framework::SceneOverObjects::AddSceneOverGameObject(std::shared_ptr<GameObject> arg_gameObject)
{
	vec_shp_gameObjects.push_back(arg_gameObject);
}
