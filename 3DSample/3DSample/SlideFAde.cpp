#pragma once
#include "SlideFade.h"
#include"Game.h"
Framework::SlideFadeIn::SlideFadeIn( int direction,std::shared_ptr<GameObjectManager> arg_manager)
	:GameObject(
	ObjectFactory::Create<Transform>(Vector3(480+1000*-1*direction,320,0)),arg_manager->GetThis<GameObjectManager>()
	),sucideTimer(AbsTimer(90)),direction(direction)
{
	sucideTimer.Start();
	movePattern = MovePattern::abs;
	target = Vector3(480, 320, 0);
	tag = ObjectTag::particle;
}

void Framework::SlideFadeIn::Initialize()
{
}

void Framework::SlideFadeIn::PreInitialize()
{
	auto c = GetColor(0,0,0);
	shp_texture = ObjectFactory::Create<Resource_Rect>(1000,640,c,transform,true);
}

bool Framework::SlideFadeIn::OnUpdate()
{
	if (sucideTimer.Update()) {
		SetIsDead(true);
	}
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture, 2);
	if(speed<40)
	speed += 2.0f;
	shp_texture->width += speed;
	velocity =((Vector3)(target- transform->GetPosition())).GetNormalize()*speed;
	return true;
}

bool Framework::SlideFadeIn::Release()
{
	return true;
}

Framework::SlideFadeOut::SlideFadeOut(int direction, std::shared_ptr<GameObjectManager> arg_manager)
	:GameObject(
		ObjectFactory::Create<Transform>(Vector3(480, 320, 0)), arg_manager->GetThis<GameObjectManager>()
	), sucideTimer(AbsTimer(90)), direction(direction)
{
	sucideTimer.Start();
	movePattern = MovePattern::abs;
	target = Vector3(480 + 1000 * -1 * direction, 320, 0); 
	//tag = ObjectTag::particle;
}

void Framework::SlideFadeOut::Initialize()
{
}

void Framework::SlideFadeOut::PreInitialize()
{
	auto c = GetColor(0, 0, 0);
	shp_texture = ObjectFactory::Create<Resource_Rect>(1000, 640, c, transform, true);
}

bool Framework::SlideFadeOut::OnUpdate()
{
	if (sucideTimer.Update()) {
		SetIsDead(true);
	}
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture, 2);
	if (speed < 40)
		speed += 2.0f;
	//shp_texture->width += speed;
	velocity = ((Vector3)(target - transform->GetPosition())).GetNormalize()*speed;
	return true;
}

bool Framework::SlideFadeOut::Release()
{
	return true;
}
