#pragma once
#include "TestScene.h"
#include"ParticleEmitter.h"
#include "Game.h"
#include"Cameraman.h"
#include"UI.h"
#include"Image.h"
Framework::TestScene::TestScene() {
	shp_gameObjectManager = ObjectFactory::Create<GameObjectManager>();
	sceneName = "TestScene";
}

Framework::TestScene::~TestScene()
{
}

void Framework::TestScene::Initialize()
{
	shp_map = ObjectFactory::Create<Map>("Map1.csv", 32, shp_gameObjectManager);
	shp_gameObjectManager->AddObject_Init(shp_map);
	auto shp_transform = ObjectFactory::Create<Transform>(Vector3(300, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	//shp_gameObjectManager->AddObject_Init(ObjectFactory::Create<TestObject>(shp_transform, shp_gameObjectManager));

	auto shp_transform2 = ObjectFactory::Create<Transform>(Vector3(96, 544, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	auto player = ObjectFactory::Create<Player>(shp_transform2, shp_gameObjectManager);
	shp_gameObjectManager->AddObject_Init(player);


	shp_gameObjectManager->AddObject_Init(ObjectFactory::Create<Cameraman_Chase>(shp_transform,shp_gameObjectManager));


	
	auto shp_objectTransform = ObjectFactory::Create<Transform>(Vector3(32, 32, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));


	shp_gameObjectManager->AddObject_Init(ObjectFactory::Create<UI>(shp_gameObjectManager));
	auto shp_imageTransform = ObjectFactory::Create<Transform>(Vector3(480, 300, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	auto titleImage = ObjectFactory::Create<Image>("title.png", shp_imageTransform, shp_gameObjectManager);
	shp_gameObjectManager->AddObject_Init(titleImage);
	//shp_gameObjectManager->AddObject_Init(shp_emitter);
}

void Framework::TestScene::PreInitialize()
{
}

bool Framework::TestScene::Update()
{
	auto r= shp_gameObjectManager->Update();
	shp_gameObjectManager->RemoveCheck();
	return r;
}

void Framework::TestScene::OnSet()
{
	shp_map->Reload();
	shp_gameObjectManager->SerchGameObject(ObjectTag::camera)->GetThis<Cameraman_Chase>()->SetTarget(
		shp_gameObjectManager->SerchGameObject(ObjectTag::player)->transform
	);
	shp_gameObjectManager->SerchGameObject(ObjectTag::camera)->transform->localPosition = shp_gameObjectManager->SerchGameObject(ObjectTag::player)->transform->GetPosition();
}

void Framework::TestScene::Release()
{
	shp_gameObjectManager->Release();
}
