#include "Collision2DManager.h"

Framework::Collision2DManager::Collision2DManager()
{
	vec_collision2Ds.push_back(std::vector < std::shared_ptr<Collision2D_Base>>());
	vec_collision2Ds.push_back(std::vector < std::shared_ptr<Collision2D_Base>>());
}

Framework::Collision2DManager::~Collision2DManager()
{
}

bool Framework::Collision2DManager::Update()
{
	auto vec_objectsCollision = vec_collision2Ds.at(0);
	auto vec_sencersCollision = vec_collision2Ds.at(1);
	for (auto itr = vec_objectsCollision.begin(); itr != vec_objectsCollision.end(); itr++) {
		for (auto otherItr = vec_sencersCollision.begin(); otherItr != vec_sencersCollision.end(); otherItr++) {


			//(*itr)->IsHit((*otherItr)); 
			//(*otherItr)->IsHit((*itr));
			//collisionCount++;
		}
	}
	for (auto itr = vec_objectsCollision.begin(); itr != vec_objectsCollision.end(); itr++) {
		for (auto otherItr = itr+1; otherItr != vec_objectsCollision.end(); otherItr++) {
			if (itr == otherItr)continue;

			if ((*itr)->IsHit((*otherItr))|| (*otherItr)->IsHit((*itr))) {

			}
		}
	}

	vec_collision2Ds.at(0).clear();
	vec_collision2Ds.at(1).clear();
	return true;
}

void Framework::Collision2DManager::AddCollision(std::shared_ptr<Collision2D_Base> add, int layer)
{
	
	vec_collision2Ds.at(layer).push_back(add->GetThis<Collision2D_Base>());
}


void Framework::Collision2DManager::Release()
{
	vec_collision2Ds.clear();
}
