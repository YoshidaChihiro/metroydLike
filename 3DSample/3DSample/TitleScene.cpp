#pragma once
#include "TitleScene.h"
#include"ParticleEmitter.h"
#include "Game.h"
#include"Cameraman.h"
#include"Image.h"
Framework::TitleScene::TitleScene() {
	shp_gameObjectManager = ObjectFactory::Create<GameObjectManager>();
	sceneName = "TitleScene";
}

Framework::TitleScene::~TitleScene()
{
}

void Framework::TitleScene::Initialize()
{
	shp_map = ObjectFactory::Create<Map>("Map_title.csv", 32, shp_gameObjectManager);
	shp_gameObjectManager->AddObject_Init(shp_map);
	auto shp_transform = ObjectFactory::Create<Transform>(Vector3(300, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));


	auto shp_transform2 = ObjectFactory::Create<Transform>(Vector3(96, 544, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	auto player = ObjectFactory::Create<Player>(shp_transform2, shp_gameObjectManager);
	shp_gameObjectManager->AddObject_Init(player);


	shp_gameObjectManager->AddObject_Init(ObjectFactory::Create<Cameraman_Chase>(shp_transform, shp_gameObjectManager));



	auto shp_objectTransform = ObjectFactory::Create<Transform>(Vector3(480, 300, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	auto titleImage = ObjectFactory::Create<Image>("title.png", shp_objectTransform, shp_gameObjectManager);
	shp_gameObjectManager->AddObject_Init(titleImage);

}

void Framework::TitleScene::PreInitialize()
{
}

bool Framework::TitleScene::Update()
{
	StopSoundFile();
	auto r = shp_gameObjectManager->Update();
	shp_gameObjectManager->RemoveCheck();
	return r;
}

void Framework::TitleScene::OnSet()
{
	shp_map->Reload();
	shp_gameObjectManager->SerchGameObject(ObjectTag::camera)->GetThis<Cameraman_Chase>()->SetTarget(
		shp_gameObjectManager->SerchGameObject(ObjectTag::player)->transform
	);
	shp_gameObjectManager->SerchGameObject(ObjectTag::camera)->transform->localPosition = shp_gameObjectManager->SerchGameObject(ObjectTag::player)->transform->GetPosition();
}

void Framework::TitleScene::Release()
{
	shp_gameObjectManager->Release();
}
