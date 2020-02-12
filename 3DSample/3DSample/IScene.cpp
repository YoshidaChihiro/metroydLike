#include "IScene.h"

void Framework::IScene::SetSceneOverObjects(std::shared_ptr<SceneOverObjects> shp_arg_sceneOverObjects)
{
	auto objs = shp_arg_sceneOverObjects->GetSceneOverGameObjects();
	for (auto itr =objs.begin() ; itr != objs.end(); itr++) {
		shp_gameObjectManager->InportObject(*itr);
	}
	
}

std::vector<std::shared_ptr< Framework::GameObject>> Framework::SceneOverObjects::GetSceneOverGameObjects()
{
	return vec_shp_gameObjects;
}

void Framework::SceneOverObjects::AddSceneOverGameObject(std::shared_ptr<GameObject> arg_gameObject)
{
	vec_shp_gameObjects.push_back(arg_gameObject);
}
