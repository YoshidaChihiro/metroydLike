#pragma once
#include "Collision2D.h"
#include "GameObject.h"
#include"Map.h"
Framework::Collision2D_Rectangle::Collision2D_Rectangle(std::shared_ptr<Rectangle> arg_rect, std::shared_ptr<GameObject> arg_gameObj)
{
	gameObj = arg_gameObj->GetThis<GameObject>();
	rect = arg_rect;
}

Framework::Collision2D_Rectangle::~Collision2D_Rectangle()
{
}

void Framework::Collision2D_Rectangle::Initialize()
{
}

void Framework::Collision2D_Rectangle::PreInitialize()
{
}

bool Framework::Collision2D_Rectangle::OnUpdate()
{
	rect->position= gameObj->transform->GetPosition().GetVector2();
	return true;
}


bool Framework::Collision2D_Base::OnHit(std::shared_ptr<Collision2D_Base> other)
{
	if (gameObj == nullptr||other->gameObj == nullptr) {
		return true;
	}
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

bool Framework::Collision2D_Terrain::OnUpdate()
{
	return true;
}

bool Framework::Collision2D_Terrain::IsHit(std::shared_ptr<Collision2D_Base> other) {
	if (other->gameObj == nullptr || gameObj == nullptr) {
		return true;
	}
	if (other->IsThis<Collision2D_Rectangle>()) {
		auto objects= gameObj->GetThis<Map>()->GetAroundObjects(other->gameObj->transform->GetPosition().GetVector2());
		for (auto itr = objects.begin(); itr != objects.end(); itr++) {
			if ((*itr)->GetShpCollision()->IsHit(other)) {
				(*itr)->GetShpCollision()->OnHit(other);
				other->OnHit((*itr)->GetShpCollision());
			}
		}
			return false;
	}

	return false;
}
