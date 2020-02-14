#include "MapChipObject.h"
#include"GameObjectManager.h"
#include "Game.h"
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
	auto sceneOverOgjs = ObjectFactory::Create<SceneOverObjects>();
	sceneOverOgjs->AddSceneOverGameObject(manager->SerchGameObject(ObjectTag::player));
	auto vec_playersChilds = manager->SerchGameObject(ObjectTag::player)->GetChildObjects();

	for (auto itr = vec_playersChilds.begin(); itr != vec_playersChilds.end(); itr++) {
		sceneOverOgjs->AddSceneOverGameObject(*itr);
	}

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


Framework::MapChip_Kuribo::MapChip_Kuribo(std::shared_ptr<GameObjectManager> arg_manager) :MapChipObject(arg_manager->GetThis<GameObjectManager>())
{
}
std::shared_ptr<Framework::MapChipObject> Framework::MapChip_Kuribo::Clone(Vector3 position)
{
	auto transform = ObjectFactory::Create<Transform>(position);
	return ObjectFactory::Create<MapChip_Kuribo>(transform, manager->GetThis<GameObjectManager>());
}
bool Framework::MapChip_Kuribo::Update()
{
	return true;
}
void Framework::MapChip_Kuribo::Initialize()
{
}
Framework::MapChip_Kuribo::MapChip_Kuribo(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_transform, arg_manager->GetThis<GameObjectManager>())
{
}


Framework::MapChip_Bat::MapChip_Bat(std::shared_ptr<GameObjectManager> arg_manager) : MapChipObject(arg_manager->GetThis<GameObjectManager>())
{
}
std::shared_ptr<Framework::MapChipObject> Framework::MapChip_Bat::Clone(Vector3 position)
{
	auto transform = ObjectFactory::Create<Transform>(position);
	return ObjectFactory::Create<MapChip_Bat>(transform, manager->GetThis<GameObjectManager>());
}
bool Framework::MapChip_Bat::Update()
{
	return true;
}
void Framework::MapChip_Bat::Initialize()
{
}
Framework::MapChip_Bat::MapChip_Bat(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_transform, arg_manager->GetThis<GameObjectManager>())
{
}


Framework::MapChip_Teresa::MapChip_Teresa(std::shared_ptr<GameObjectManager> arg_manager) : MapChipObject(arg_manager->GetThis<GameObjectManager>())
{
}
std::shared_ptr<Framework::MapChipObject> Framework::MapChip_Teresa::Clone(Vector3 position)
{
	auto transform = ObjectFactory::Create<Transform>(position);
	return ObjectFactory::Create<MapChip_Teresa>(transform, manager->GetThis<GameObjectManager>());
}
bool Framework::MapChip_Teresa::Update()
{
	return true;
}
void Framework::MapChip_Teresa::Initialize()
{
}
Framework::MapChip_Teresa::MapChip_Teresa(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_transform, arg_manager->GetThis<GameObjectManager>())
{
}