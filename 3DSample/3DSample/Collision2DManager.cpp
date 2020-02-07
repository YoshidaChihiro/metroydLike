#include "Collision2DManager.h"

Framework::Collision2DManager::Collision2DManager()
{
}

Framework::Collision2DManager::~Collision2DManager()
{
}

bool Framework::Collision2DManager::Update()
{
	for (auto itr = vec_collision2Ds.begin(); itr != vec_collision2Ds.end(); itr++) {
		for (auto otherItr = vec_collision2Ds.begin(); otherItr != vec_collision2Ds.end(); otherItr++) {
			if (itr == otherItr)continue;

			if ((*itr)->IsHit((*otherItr))|| (*otherItr)->IsHit((*itr))) {
				(*itr)->OnHit((*otherItr));
			}
		}
	}
	vec_collision2Ds.clear();
	return true;
}

void Framework::Collision2DManager::AddCollision(std::shared_ptr<Collision2D_Base> add)
{
	vec_collision2Ds.push_back(add);
}

void Framework::Collision2DManager::Release()
{
	vec_collision2Ds.clear();
}
