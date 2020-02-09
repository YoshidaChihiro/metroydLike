#include "TestScene.h"
#include"Map.h"
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

	auto shp_objectTransform = ObjectFactory::Create<Transform>(Vector3(64, 32, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	shp_gameObjectManager->AddObject_Init(ObjectFactory::Create<Map>("testMap.csv", 16, shp_gameObjectManager));
	
}

void Framework::TestScene::PreInitialize()
{
}

bool Framework::TestScene::Update()
{
	return shp_gameObjectManager->Update();
}

void Framework::TestScene::Release()
{
	shp_gameObjectManager->Release();
}
