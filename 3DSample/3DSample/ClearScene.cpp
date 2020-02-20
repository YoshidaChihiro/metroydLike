#pragma once
#include "ClearScene.h"

#include"ParticleEmitter.h"
#include "Game.h"
#include"Cameraman.h"
Framework::ClearScene::ClearScene()
{
	shp_gameObjectManager = ObjectFactory::Create<GameObjectManager>();
	sceneName = "ClearScene";
}

Framework::ClearScene::~ClearScene()
{
}

void Framework::ClearScene::Initialize()
{
	shp_map = ObjectFactory::Create<Map>("Map_clear.csv", 32, shp_gameObjectManager);
	shp_gameObjectManager->AddObject_Init(shp_map);
	auto shp_transform = ObjectFactory::Create<Transform>(Vector3(300, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	//shp_gameObjectManager->AddObject_Init(ObjectFactory::Create<TestObject>(shp_transform, shp_gameObjectManager));



	shp_gameObjectManager->AddObject_Init(ObjectFactory::Create<Cameraman_Chase>(shp_transform, shp_gameObjectManager));


	auto white = GetColor(255, 255, 255);
	auto black = GetColor(0,0,0);
	
	shp_scoreBoard = ObjectFactory::Create<Board>(320, 320, 5, black, white,
		ObjectFactory::Create<Transform>( Vector3(5*32,32*10,0)),
		shp_gameObjectManager);
	shp_gameObjectManager->AddObject_Init(shp_scoreBoard);
	shp_timeBoard = ObjectFactory::Create<Board>(320,320,5,black,white,
		ObjectFactory::Create<Transform>(Vector3(24 * 32, 32 * 10, 0)), shp_gameObjectManager);

	shp_gameObjectManager->AddObject_Init(shp_timeBoard);
}

void Framework::ClearScene::PreInitialize()
{
}

bool Framework::ClearScene::Update()
{
	auto r = shp_gameObjectManager->Update();
	shp_gameObjectManager->RemoveCheck();
	return r;
}

void Framework::ClearScene::OnSet()
{
	shp_map->Reload();
	shp_gameObjectManager->SerchGameObject(ObjectTag::camera)->GetThis<Cameraman_Chase>()->SetTarget(
		shp_gameObjectManager->SerchGameObject(ObjectTag::player)->transform
	);
	shp_gameObjectManager->SerchGameObject(ObjectTag::camera)->transform->localPosition = shp_gameObjectManager->SerchGameObject(ObjectTag::player)->transform->GetPosition();

	auto white = GetColor(255, 255, 255);
	shp_scoreBoard->AddText(white,"Score::"+std::to_string( Game::GetInstance()->GetSceneManager()->GetGameMaster()->GetScore()),Vector3());
	shp_timeBoard->AddText(white,"Time::" + std::to_string(Game::GetInstance()->GetSceneManager()->GetGameMaster()->GetNowTime().count()),Vector3());
}

void Framework::ClearScene::Release()
{
	shp_gameObjectManager->Release();
}
