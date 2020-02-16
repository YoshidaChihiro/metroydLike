#pragma once
#include "GameObject.h"
#include "GameObjectManager.h"
#include"Game.h"

bool Framework::GameObject::Release()
{
	
	return true;
}

void Framework::GameObject::DeadCheck()
{
	if (isDead) {
		sucideTimer->Start();
	}
	if (sucideTimer->Update()) {
		isRemove = true;
	}
}


void Framework::GameObject::PreInitialize()
{
}

void Framework::GameObject::SetGameObjectManager(std::shared_ptr<GameObjectManager> arg_manager) {
	manager = arg_manager->GetThis<GameObjectManager>();
	for (auto itr = childs.begin(); itr != childs.end(); itr++) {
		(*itr)->SetGameObjectManager(arg_manager);
	}
}

void Framework::GameObject::Initialize()
{
}

void Framework::GameObject::AbsMove()
{
	transform->localPosition +=( velocity+phisicsForce);
}

void Framework::GameObject::RelativeMove()
{
	transform->localPosition +=((Vector3) (velocity + phisicsForce))*Game::GetInstance()-> GetGameTime()->GetSpeed();
}

void Framework::GameObject::SetIsDead(bool arg_isDead)
{
	isDead = arg_isDead;
	for (auto itr = childs.begin(); itr != childs.end(); itr++) {
		if ((*itr) != nullptr)
			(*itr)->SetIsDead(arg_isDead);
		(*itr) = nullptr;
	}
}

void Framework::GameObject::AddChildObject(std::shared_ptr<GameObject> arg_chid)
{
	childs.push_back(arg_chid->GetThis<GameObject>());
}

void Framework::GameObject::RemoveChildObject(std::shared_ptr<GameObject> arg_chid)
{
	for (auto itr = childs.begin(); itr != childs.end(); itr++) {
		if ((*itr) == arg_chid) {
			childs.erase(itr);
			break;
		}
	}
}

std::vector<std::shared_ptr<Framework::GameObject>> Framework::GameObject::GetChildObjects()
{
	return childs;
}

std::vector<std::shared_ptr<Framework::GameObject>> Framework::GameObject::GetChildAndGrandChildObjects()
{
	auto output = std::vector<std::shared_ptr<GameObject>>();
	auto o_childs = GetChildObjects();
	for (auto itr = o_childs.begin(); itr != o_childs.end(); itr++) {
		output.push_back(*itr);
		auto o_grandChilds = (*itr)->GetChildObjects();
		for (auto itr = o_grandChilds.begin(); itr != o_grandChilds.end(); itr++) {
			output.push_back(*itr);
		}
	}
	return output;
}

void Framework::GameObject::ChangeTimer(int arg_maxFrame)
{
	sucideTimer->ChangeCountFrame(arg_maxFrame);
}
