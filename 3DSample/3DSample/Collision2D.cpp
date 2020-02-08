#pragma once
#include "Collision2D.h"
#include "GameObject.h"
#include"Map.h"
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

Framework::Collision2D_Terrain::Collision2D_Terrain(std::shared_ptr<GameObject> arg_gameObj) 
{
	gameObj = arg_gameObj->GetThis<GameObject>();
}

void Framework::Collision2D_Terrain::Initialize()
{
}

void Framework::Collision2D_Terrain::PreInitialize()
{
}

bool Framework::Collision2D_Terrain::Update()
{
	return true;
}

bool Framework::Collision2D_Terrain::IsHit(std::shared_ptr<Collision2D_Base> other) {
	if (other->IsThis<Collision2D_Rectangle>()) {
		auto objects= gameObj->GetThis<Map>()->GetAroundObjects(other->gameObj->transform->GetPosition().GetVector2());
		for (auto itr = objects.begin(); itr != objects.end(); itr++) {
			(*itr)->GetShpCollision()->IsHit(other);
		}
			return true;
	}

	return true;
}