#include "SlideFAde.h"
#include"Util.h"
#include"Game.h"
Framework::SlideFade::SlideFade(std::shared_ptr<GameObjectManager> arg_manager)
	:GameObject(ObjectFactory::Create<Transform>(Vector3 (460,640,0)),arg_manager->GetThis<GameObjectManager>()),timer(AbsTimer(80))
{
	movePattern = MovePattern::abs;
	velocity = Vector3(0, -12, 0);
	timer.Update();
}

Framework::SlideFade::~SlideFade()
{
}

void Framework::SlideFade::PreInitialize()
{
}

void Framework::SlideFade::Initialize()
{
		shp_texture = ObjectFactory::Create<Resource_UI>("cover.png", transform, false, false);
}

bool Framework::SlideFade::OnUpdate()
{
	if (timer.Update()) {
		SetIsDead(true);
	}
	else
	{

		Game::GetInstance()->GetResourceController()->AddGraph(shp_texture, 1);
	}
	return true;
}

bool Framework::SlideFade::Release()
{
	return true;
}

