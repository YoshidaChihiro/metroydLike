#include "MapScene.h"
#include"StringHelper.h"
#include"Cameraman.h"
#include"Game.h"
#include"UI.h"
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

	
	auto shp_objectTransform = ObjectFactory::Create<Transform>(Vector3(32, 32, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	shp_gameObjectManager->AddObject_Init(ObjectFactory::Create<UI>(shp_gameObjectManager));
}

void Framework::MapScene::PreInitialize()
{
	shp_sound_bgm = ObjectFactory::Create<Resource_Sound>("Game_play2.wav", DX_PLAYTYPE_LOOP, false);
	shp_sound_mapmove = ObjectFactory::Create<Resource_Sound>("Mapmove.wav", DX_PLAYTYPE_BACK, true);

}

bool Framework::MapScene::Update()
{
	
	auto r= shp_gameObjectManager->Update();
	shp_gameObjectManager->RemoveCheck();
	return r;
}

void Framework::MapScene::OnSet()
{
	Game::GetInstance()->GetResourceController()->StopSound(shp_sound_bgm);

	Game::GetInstance()->GetResourceController()->AddSound(shp_sound_bgm);
	Game::GetInstance()->GetResourceController()->AddSound(shp_sound_mapmove);

	shp_map->Reload();
	auto player = shp_gameObjectManager->SerchGameObject(ObjectTag::player);
	if(player)
	shp_gameObjectManager->SerchGameObject(ObjectTag::camera)->GetThis<Cameraman_Chase>()->SetTarget(
		player->transform
	); shp_gameObjectManager->SerchGameObject(ObjectTag::camera)->transform->localPosition =Vector3( shp_map->GetCenterPosition());
	//shp_gameObjectManager->SerchGameObject(ObjectTag::camera)->transform->localPosition = shp_gameObjectManager->SerchGameObject(ObjectTag::player)->transform->GetPosition();
	if (!isStart&&sceneName == "Map2Scene") {
		isStart = true;
		Game::GetInstance()->GetSceneManager()->GetGameMaster()->ReStart();
	}
}

void Framework::MapScene::Release()
{
	shp_sound_bgm = nullptr;
	shp_sound_mapmove = nullptr;

	shp_gameObjectManager->Release();
}
