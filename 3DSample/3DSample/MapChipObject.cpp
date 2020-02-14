#include "MapChipObject.h"
#include"GameObjectManager.h"
#include "Game.h"
#include"Explosion.h"
Framework::MapChip_Space::MapChip_Space(std::shared_ptr<GameObjectManager> arg_manager):MapChipObject(arg_manager->GetThis<GameObjectManager>())
{
}

Framework::MapChip_Space::MapChip_Space(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_transform,arg_manager->GetThis<GameObjectManager>())
{
}

Framework::MapChip_Test::MapChip_Test(std::shared_ptr<GameObjectManager> arg_manager) :MapChipObject(arg_manager->GetThis<GameObjectManager>())
{
}

std::shared_ptr<Framework::MapChipObject> Framework::MapChip_Test::Clone(Vector3 position)
{
	auto transform = ObjectFactory::Create<Transform>(position);
	return ObjectFactory::Create<MapChip_Test>(transform,manager->GetThis<GameObjectManager>());
}

bool Framework::MapChip_Test::Update()
{

	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
	return true;
}

void Framework::MapChip_Test::Initialize()
{
	shp_texture = ObjectFactory::Create<Resource_Texture>("sample2.png", transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(
		Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize(),
		Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize(), 
		transform->GetPosition().GetVector2(), 
		Rectangle::GetRectangleOuterCircleRadius(
			Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize()/2,
			Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize()/2)), GetThis<GameObject>());

	shp_collisionRect->Update();
}

Framework::MapChip_Test::MapChip_Test(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_transform,arg_manager->GetThis<GameObjectManager>())
{
}

Framework::MapChip_Gate::MapChip_Gate(std::string arg_changeSceneName,Vector2 arg_exitPosition,std::shared_ptr<GameObjectManager> arg_manager)
	: MapChipObject( arg_manager->GetThis<GameObjectManager>())
{
	changeScenesName = arg_changeSceneName;
	exitPosition = arg_exitPosition;
}

std::shared_ptr<Framework::MapChipObject> Framework::MapChip_Gate::Clone(Vector3 position)
{
	auto transform = ObjectFactory::Create<Transform>(position);
	return ObjectFactory::Create<MapChip_Gate>(changeScenesName,exitPosition,
		transform,manager->GetThis<GameObjectManager>())->GetThis<MapChipObject>();
}

bool Framework::MapChip_Gate::Update()
{
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
	return true;
}

void Framework::MapChip_Gate::Hit(std::shared_ptr<GameObject> other)
{
	if (other->GetObjectTag() != ObjectTag::player) {
		return;
	}

	other->transform->localPosition = exitPosition;
	Game::GetInstance()->GetSceneManager()->GetGameMaster()->SetRespawnPosition(Vector3( exitPosition));
	auto sceneOverOgjs = ObjectFactory::Create<SceneOverObjects>();
	auto player = manager->SerchGameObject(ObjectTag::player);
	sceneOverOgjs->AddSceneOverGameObject(player);
	auto vec_playersChilds = player->GetChildAndGrandChildObjects();

	for (auto itr = vec_playersChilds.begin(); itr != vec_playersChilds.end(); itr++) {
		manager->RemoveObject(*itr);
		sceneOverOgjs->AddSceneOverGameObject(*itr);
	}

	manager->RemoveObject(player);
	Game::GetInstance()->GetSceneManager()->ChangeScene(changeScenesName, 0, sceneOverOgjs);
}

void Framework::MapChip_Gate::Initialize()
{

	shp_texture = ObjectFactory::Create<Resource_Texture>("sample.png", transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(
		Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize(),
		Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize(),
		transform->GetPosition().GetVector2(),
		Rectangle::GetRectangleOuterCircleRadius(
			Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize() / 2,
			Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize() / 2)), GetThis<GameObject>());

	shp_collisionRect->Update();
}

Framework::MapChip_Gate::MapChip_Gate(std::string arg_changeScenesName, Vector2 arg_exitPosition, std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_transform, arg_manager->GetThis<GameObjectManager>())
{
	exitPosition = arg_exitPosition;
	changeScenesName = arg_changeScenesName;
}

Framework::MapChip_ChildBlock::MapChip_ChildBlock(std::shared_ptr<GameObjectManager> arg_manager)
	: MapChipObject(arg_manager->GetThis<GameObjectManager>())
{
}

std::shared_ptr<Framework::MapChipObject> Framework::MapChip_ChildBlock::Clone(Vector3 position)
{
	auto transform = ObjectFactory::Create<Transform>(position);
	return ObjectFactory::Create<MapChip_ChildBlock>(transform, manager->GetThis<GameObjectManager>());
}

void Framework::MapChip_ChildBlock::Hit(std::shared_ptr<GameObject> other)
{
	if (!GetIsDead()&& other->GetObjectTag() == ObjectTag::playerBullet&&!other->GetIsDead()) {
		SetIsDead(true);
		manager->AddObject(ObjectFactory::Create<Explosion>(transform,manager));
	}
}

bool Framework::MapChip_ChildBlock::Update()
{
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
	return true;
}

void Framework::MapChip_ChildBlock::Initialize()
{
	shp_texture = ObjectFactory::Create<Resource_Texture>("orange.png", transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(
		Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize(),
		Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize(),
		transform->GetPosition().GetVector2(),
		Rectangle::GetRectangleOuterCircleRadius(
			Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize() / 2,
			Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize() / 2)), GetThis<GameObject>());

	shp_collisionRect->Update();
}

Framework::MapChip_ChildBlock::MapChip_ChildBlock(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_transform, arg_manager->GetThis<GameObjectManager>())
{
}

Framework::MapChip_CrushBlock::MapChip_CrushBlock(std::shared_ptr<GameObjectManager> arg_manager) 
	: MapChipObject( arg_manager->GetThis<GameObjectManager>())
{
}

std::shared_ptr<Framework::MapChipObject> Framework::MapChip_CrushBlock::Clone(Vector3 position)
{
	auto transform = ObjectFactory::Create<Transform>(position);
	return ObjectFactory::Create<MapChip_CrushBlock>(transform, manager->GetThis<GameObjectManager>());
}

void Framework::MapChip_CrushBlock::Hit(std::shared_ptr<GameObject> other)
{
	if (other->GetObjectTag() == ObjectTag::playerBullet) {
		if (other->IsThis<Explosion>()) {
			SetIsDead(true);
		}
	}
}

bool Framework::MapChip_CrushBlock::Update()
{
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
	return true;
}

void Framework::MapChip_CrushBlock::Initialize()
{
	shp_texture = ObjectFactory::Create<Resource_Texture>("sample3.png", transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(
		Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize(),
		Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize(),
		transform->GetPosition().GetVector2(),
		Rectangle::GetRectangleOuterCircleRadius(
			Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize() / 2,
			Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize() / 2)), GetThis<GameObject>());

	shp_collisionRect->Update();
}

Framework::MapChip_CrushBlock::MapChip_CrushBlock(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_transform, arg_manager->GetThis<GameObjectManager>()) 
{
}

Framework::Medal::Medal(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_transform->GetThis<Transform>(), arg_manager->GetThis<GameObjectManager>())
{
	tag = ObjectTag::item;
}

Framework::Medal::Medal(std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_manager->GetThis<GameObjectManager>())
{
	tag = ObjectTag::none;
}

Framework::Medal::~Medal()
{
}

void Framework::Medal::Hit(std::shared_ptr<GameObject> other)
{
	if (other->GetObjectTag() == ObjectTag::player) {
		SetIsDead(true);
		Game::GetInstance()->GetSceneManager()->GetGameMaster()->GetMedal();
	}
}



void Framework::Medal::PreInitialize()
{
}

std::shared_ptr<Framework::MapChipObject> Framework::Medal::Clone(Vector3 position)
{
	auto transform = ObjectFactory::Create<Transform>(position);
	return ObjectFactory::Create<Medal>(
		transform, manager->GetThis<GameObjectManager>())->GetThis<MapChipObject>();
}

void Framework::Medal::Initialize()
{
	texture = ObjectFactory::Create<Resource_Texture>("sample4.png", transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(16, 16)), GetThis<GameObject>());

}

bool Framework::Medal::Update()
{
	Game::GetInstance()->GetResourceController()->AddGraph(texture);
	return true;
}

bool Framework::MapChipObject::Release()
{
	shp_collisionRect->Releace();
	shp_collisionRect = nullptr;
	return true;
}

Framework::ChildSeedSpawner::ChildSeedSpawner(std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_manager->GetThis<GameObjectManager>())
{
	tag = ObjectTag::item;
}

Framework::ChildSeedSpawner::~ChildSeedSpawner()
{
}

void Framework::ChildSeedSpawner::Hit(std::shared_ptr<GameObject> other)
{
	if (other->GetObjectTag() == ObjectTag::player) {
		other->GetThis<Player>()->AddPlayerChild();
	}
}

void Framework::ChildSeedSpawner::PreInitialize()
{
}

std::shared_ptr<Framework::MapChipObject> Framework::ChildSeedSpawner::Clone(Vector3 position)
{
	auto transform = ObjectFactory::Create<Transform>(position);
	return ObjectFactory::Create<ChildSeedSpawner>(
		transform, manager->GetThis<GameObjectManager>())->GetThis<MapChipObject>();

}

void Framework::ChildSeedSpawner::Initialize()
{
	texture = ObjectFactory::Create<Resource_Texture>("sample5.png", transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(16, 16)), GetThis<GameObject>());

}

bool Framework::ChildSeedSpawner::Update()
{
	Game::GetInstance()->GetResourceController()->AddGraph(texture);
	return true;
}

Framework::ChildSeedSpawner::ChildSeedSpawner(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)

	:MapChipObject(arg_transform->GetThis<Transform>(), arg_manager->GetThis<GameObjectManager>()) {
	tag = ObjectTag::item;
}
