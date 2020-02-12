#include "Cameraman.h"
#include"GameObjectManager.h"
#include "Game.h"
Framework::Cameraman::Cameraman(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_manager)
	:GameObject(shp_arg_transform->GetThis<Transform>(),shp_arg_manager->GetThis<GameObjectManager>())
{
	tag = ObjectTag::camera;
}

bool Framework::Cameraman::Update()
{
	SetScrollFocus();
	return true;
}

void Framework::Cameraman::SetScrollFocus()
{
	Game::GetInstance()->GetResourceController()->GetScreenInformation()->SetScrollModify(transform->GetPosition().GetVector2());
}

Framework::Cameraman_Chase::Cameraman_Chase(std::shared_ptr<Transform> shp_target_transform, std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_manager)
	:Cameraman(shp_arg_transform->GetThis<Transform>(), shp_arg_manager->GetThis<GameObjectManager>()),target(shp_target_transform->GetThis<Transform>())
{
}

Framework::Cameraman_Chase::Cameraman_Chase(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_manager)
	: Cameraman(shp_arg_transform->GetThis<Transform>(), shp_arg_manager->GetThis<GameObjectManager>()), target(shp_arg_transform->GetThis<Transform>())
{
}

bool Framework::Cameraman_Chase::Update()
{
	auto v = (target->GetPosition().GetVector2());
	auto distance = transform->GetPosition().GetVector2().GetDistance(v	);
	if (distance > 64)
	{
		auto cameraVeloc = ((Vector3)(target->GetPosition() - transform->GetPosition()));
		cameraVeloc.Normalize();
		transform->localPosition +=cameraVeloc*(distance/24);
	}

	SetScrollFocus();
	return true;
}
