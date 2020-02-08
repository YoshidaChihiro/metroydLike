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

	shp_collisionRect->Update();
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
	//Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect);
	return true;
}

void Framework::MapChip_Test::Initialize()
{
	shp_texture = ObjectFactory::Create<Resource_Texture>("sample2.png", transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(16, 16, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(16, 16)), GetThis<GameObject>());

}

Framework::MapChip_Test::MapChip_Test(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_transform,arg_manager->GetThis<GameObjectManager>())
{
}

