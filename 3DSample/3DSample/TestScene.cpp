#include "TestScene.h"

Framework::TestScene::TestScene() {
	shp_gameObjectManager = std::make_shared<GameObjectManager>();

}

Framework::TestScene::~TestScene()
{
}

void Framework::TestScene::Initialize()
{
	auto shp_transform = ObjectFactory::Create<Transform>(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	shp_gameObjectManager->AddObject(ObjectFactory::Create<TestObject>(shp_transform, shp_gameObjectManager));
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
