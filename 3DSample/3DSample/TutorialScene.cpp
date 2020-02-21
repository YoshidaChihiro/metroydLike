#pragma once
#include "TutorialScene.h"
#include"ParticleEmitter.h"
#include "Game.h"
#include"Cameraman.h"
#include"UI.h"
#include"Image.h"
#include"Board.h"
Framework::TutorialScene::TutorialScene() {
	shp_gameObjectManager = ObjectFactory::Create<GameObjectManager>();
	sceneName = "TutorialScene";
}

Framework::TutorialScene::~TutorialScene()
{
}

void Framework::TutorialScene::Initialize()
{
	shp_map = ObjectFactory::Create<Map>("Map_tutorial.csv", 32, shp_gameObjectManager);
	shp_gameObjectManager->AddObject_Init(shp_map);
	auto shp_transform = ObjectFactory::Create<Transform>(Vector3(300, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	//shp_gameObjectManager->AddObject_Init(ObjectFactory::Create<TestObject>(shp_transform, shp_gameObjectManager));



	shp_gameObjectManager->AddObject_Init(ObjectFactory::Create<Cameraman_Chase>(shp_transform, shp_gameObjectManager));



	auto shp_objectTransform = ObjectFactory::Create<Transform>(Vector3(32, 32, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));


	shp_gameObjectManager->AddObject_Init(ObjectFactory::Create<UI>(shp_gameObjectManager));
	auto shp_startBoardTransform = ObjectFactory::Create<Transform>(Vector3(840, 480, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	int cyanColor = GetColor(0, 0, 0);
	int blackColor = GetColor(0, 255, 255);

	auto startBoard = ObjectFactory::Create<Board>(120, 32, 5, cyanColor, blackColor, shp_startBoardTransform, shp_gameObjectManager);
	shp_gameObjectManager->AddObject_Init(startBoard);

	auto shp_tutorialBoardTransform = ObjectFactory::Create<Transform>(Vector3(104, 480, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));


	auto tutorialBoard = ObjectFactory::Create<Board>(120, 32, 5, cyanColor, blackColor, shp_tutorialBoardTransform, shp_gameObjectManager);
	shp_gameObjectManager->AddObject_Init(tutorialBoard);
	//shp_gameObjectManager->AddObject_Init(shp_emitter);
}

void Framework::TutorialScene::PreInitialize()
{
}

bool Framework::TutorialScene::Update()
{
	auto r = shp_gameObjectManager->Update();
	shp_gameObjectManager->RemoveCheck();
	return r;
}

void Framework::TutorialScene::OnSet()
{
	shp_map->Reload();
	shp_gameObjectManager->SerchGameObject(ObjectTag::camera)->GetThis<Cameraman_Chase>()->SetTarget(
		shp_gameObjectManager->SerchGameObject(ObjectTag::player)->transform
	);
	Game::GetInstance()->GetSceneManager()->GetGameMaster()->ReStart();
	Game::GetInstance()->GetSceneManager()->GetGameMaster()->Initialize();
	shp_gameObjectManager->SerchGameObject(ObjectTag::camera)->transform->localPosition = shp_gameObjectManager->SerchGameObject(ObjectTag::player)->transform->GetPosition();
}

void Framework::TutorialScene::Release()
{
	shp_gameObjectManager->Release();
}
