#pragma once
#include "Collision2D.h"
#include "GameObject.h"
Framework::Collision2D_Rectangle::Collision2D_Rectangle(std::shared_ptr<Rectangle> arg_rect, std::shared_ptr<GameObject> arg_gameObj)
{
	gameObj = arg_gameObj->GetThis<GameObject>();
	rect = arg_rect;
}

void Framework::Collision2D_Rectangle::Initialize()
{
}

void Framework::Collision2D_Rectangle::PreInitialize()
{
}

bool Framework::Collision2D_Rectangle::Update()
{
	rect->position= gameObj->transform->GetPosition().GetVector2();
	return true;
}


bool Framework::Collision2D_Base::OnHit(std::shared_ptr<Collision2D_Base> other)
{
	gameObj->Hit(other->gameObj);
	return true;
}

