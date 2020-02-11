#include "TestScene.h"
#include"Map.h"
#include "Game.h"

Framework::TestScene::TestScene() {
	shp_gameObjectManager = ObjectFactory::Create<GameObjectManager>();
}

Framework::TestScene::~TestScene()
{
}

void Framework::TestScene::Initialize()
{
	auto shp_transform = ObjectFactory::Create<Transform>(Vector3(300, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	shp_gameObjectManager->AddObject_Init(ObjectFactory::Create<TestObject>(shp_transform, shp_gameObjectManager));


	auto shp_transform2 = ObjectFactory::Create<Transform>(Vector3(105, 650, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	shp_player = ObjectFactory::Create<Player>(shp_transform2, shp_gameObjectManager);
	shp_gameObjectManager->AddObject_Init(shp_player);


	auto shp_transform3 = ObjectFactory::Create<Transform>(Vector3(70, 650, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	shp_gameObjectManager->AddObject_Init(ObjectFactory::Create<Child>(64,50,shp_transform2,shp_transform3, shp_gameObjectManager));

	auto shp_objectTransform = ObjectFactory::Create<Transform>(Vector3(64, 32, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	auto obj = ObjectFactory::Create<Map>("Map1.csv",32,shp_gameObjectManager);
	//shp_gameObjectManager->AddObject(obj);
	shp_gameObjectManager->AddObject_Init(obj);
	
}

void Framework::TestScene::PreInitialize()
{
}

bool Framework::TestScene::Update()
{
	//これをplayerクラスに
	if (Input::GetKeyDown(KEY_INPUT_UP)) {
		auto shp_transform3 = ObjectFactory::Create<Transform>(Vector3(70, 650, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
		auto newChild = ObjectFactory::Create<Child>(130, 50, shp_player->transform, shp_transform3, shp_gameObjectManager);
		shp_gameObjectManager->AddObject(newChild);
	}
	if (Input::GetKeyDown(KEY_INPUT_DOWN)) {

	}

	return shp_gameObjectManager->Update();
}

void Framework::TestScene::Release()
{
	shp_gameObjectManager->Release();
}
