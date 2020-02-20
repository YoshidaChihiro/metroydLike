#pragma once
#include "ClearScene.h"

#include"ParticleEmitter.h"
#include "Game.h"
#include"Cameraman.h"
#include"RankingLoader.h"
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
	vec_scoreRanking = RankingLoader::GetHeigherFromFile("scoreRanking.rank", 3);
	vec_timeRanking = RankingLoader::GetLowerFromFile("timeRanking.rank", 3);
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
	auto gold = GetColor(255, 215,0);

	score = Game::GetInstance()->GetSceneManager()->GetGameMaster()->GetScore();
	shp_scoreBoard->AddText(white, "Your Score", Vector3(40, 64, 0));
	vec_scoreRanking.push_back(score);
	vec_scoreRanking = RankingLoader::GetHeigherFromFile(vec_scoreRanking, 3);
	RankingLoader::WriteRanking(vec_scoreRanking, "scoreRanking.rank", 3);
	if (score == vec_scoreRanking.at(0)) {

		shp_scoreBoard->AddText(gold, std::to_string(score), Vector3(40, 88, 0));
	}else
	shp_scoreBoard->AddText(white, std::to_string(score), Vector3(40, 88, 0));

	shp_scoreBoard->AddText(gold, "1st::" + std::to_string(vec_scoreRanking.at(0)), Vector3(40,-48,0));
	shp_scoreBoard->AddText(white, "2nd::" + std::to_string(vec_scoreRanking.at(1)), Vector3(40,-24,0));
	shp_scoreBoard->AddText(white, "3rd::" + std::to_string(vec_scoreRanking.at(2)), Vector3(40,0,0));

	time = Game::GetInstance()->GetSceneManager()->GetGameMaster()->GetNowTime().count();
	shp_timeBoard->AddText(white, "Your Time", Vector3(48, 64, 0));
	
	vec_timeRanking.push_back(time);
	vec_timeRanking = RankingLoader::GetLowerFromFile(vec_timeRanking, 3);
	RankingLoader::WriteRanking(vec_timeRanking,"timeRanking.rank", 3);
	if (time == vec_timeRanking.at(0)) {

		shp_timeBoard->AddText(gold, std::to_string(time), Vector3(40, 88, 0));
	}
	else
	shp_timeBoard->AddText(white, std::to_string(time), Vector3(48, 88, 0));
	shp_timeBoard->AddText(gold, "1st::" + std::to_string(vec_timeRanking.at(0)), Vector3(40,-48,0));
	shp_timeBoard->AddText(white, "2nd::" + std::to_string(vec_timeRanking.at(1)), Vector3(40,-24,0));
	shp_timeBoard->AddText(white,"3rd::" + std::to_string(vec_timeRanking.at(2)),Vector3(40,0,0));


}

void Framework::ClearScene::Release()
{
	shp_gameObjectManager->Release();
}
