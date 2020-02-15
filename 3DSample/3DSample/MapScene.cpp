#include "MapScene.h"
#include"StringHelper.h"
#include"Cameraman.h"
#include"Game.h"
Framework::MapScene::MapScene(std::string mapFilePath)
{
	shp_gameObjectManager = ObjectFactory::Create<GameObjectManager>();
	filePath = mapFilePath;
	auto sceneNames = StringHelper::Split(mapFilePath, ".");
	sceneName = sceneNames.at(0) + "Scene";
}

Framework::MapScene::~MapScene()
{
}

void Framework::MapScene::Initialize()
{
	shp_map = ObjectFactory::Create<Map>(filePath, 32, shp_gameObjectManager);
	//shp_gameObjectManager->AddObject(obj);
	shp_gameObjectManager->AddObject_Init(shp_map);
	auto shp_transform = ObjectFactory::Create<Transform>(Vector3(400, -100, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	//shp_gameObjectManager->AddObject_Init(ObjectFactory::Create<TestObject>(shp_transform, shp_gameObjectManager));

	//auto shp_transform2 = ObjectFactory::Create<Transform>(Vector3(67, 650, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	//shp_gameObjectManager->AddObject_Init(ObjectFactory::Create<Player>(shp_transform2, shp_gameObjectManager));

	shp_gameObjectManager->AddObject_Init(ObjectFactory::Create<Cameraman_Chase>( shp_transform, shp_gameObjectManager));

	
	auto shp_objectTransform = ObjectFactory::Create<Transform>(Vector3(64, 32, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

}

void Framework::MapScene::PreInitialize()
{
}

bool Framework::MapScene::Update()
{
	
	auto r= shp_gameObjectManager->Update();
	shp_gameObjectManager->RemoveCheck();
	return r;
}

void Framework::MapScene::OnSet()
{
	shp_map->Reload();
	shp_gameObjectManager->SerchGameObject(ObjectTag::camera)->GetThis<Cameraman_Chase>()->SetTarget(
		shp_gameObjectManager->SerchGameObject(ObjectTag::player)->transform
	); shp_gameObjectManager->SerchGameObject(ObjectTag::camera)->transform->localPosition =Vector3( shp_map->GetCenterPosition());
	//shp_gameObjectManager->SerchGameObject(ObjectTag::camera)->transform->localPosition = shp_gameObjectManager->SerchGameObject(ObjectTag::player)->transform->GetPosition();

}

void Framework::MapScene::Release()
{
	shp_gameObjectManager->Release();
}
