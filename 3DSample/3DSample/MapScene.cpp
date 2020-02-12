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
	auto shp_transform = ObjectFactory::Create<Transform>(Vector3(400, -100, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	//shp_gameObjectManager->AddObject_Init(ObjectFactory::Create<TestObject>(shp_transform, shp_gameObjectManager));

	//auto shp_transform2 = ObjectFactory::Create<Transform>(Vector3(67, 650, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	//shp_gameObjectManager->AddObject_Init(ObjectFactory::Create<Player>(shp_transform2, shp_gameObjectManager));

	shp_gameObjectManager->AddObject_Init(ObjectFactory::Create<Cameraman_Chase>( shp_transform, shp_gameObjectManager));

	
	auto shp_objectTransform = ObjectFactory::Create<Transform>(Vector3(64, 32, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	shp_map = ObjectFactory::Create<Map>(filePath, 32, shp_gameObjectManager);
	//shp_gameObjectManager->AddObject(obj);
	shp_gameObjectManager->AddObject_Init(shp_map);
}

void Framework::MapScene::PreInitialize()
{
}

bool Framework::MapScene::Update()
{
	if (Input::GetKeyDown(KEY_INPUT_SPACE)) {
		auto sceneOverOgjs = ObjectFactory::Create<SceneOverObjects>();
		sceneOverOgjs->AddSceneOverGameObject(shp_gameObjectManager->SerchGameObject(ObjectTag::player));
		Game::GetInstance()->GetSceneManager()->ChangeScene("TestScene",0, sceneOverOgjs);
	}
	return shp_gameObjectManager->Update();
}

void Framework::MapScene::OnSet()
{
	shp_map->Reload();
	shp_gameObjectManager->SerchGameObject(ObjectTag::camera)->GetThis<Cameraman_Chase>()->SetTarget(
		shp_gameObjectManager->SerchGameObject(ObjectTag::player)->transform
	);
	//shp_gameObjectManager->SerchGameObject(ObjectTag::camera)->transform->localPosition = shp_gameObjectManager->SerchGameObject(ObjectTag::player)->transform->GetPosition();

}

void Framework::MapScene::Release()
{
	shp_gameObjectManager->Release();
}
