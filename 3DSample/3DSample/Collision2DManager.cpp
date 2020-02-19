#include "Collision2DManager.h"
#include"Input.h"]
Framework::Collision2DManager::Collision2DManager()
{
	vec_collision2Ds.push_back(std::vector < std::shared_ptr<Collision2D_Base>>());
	vec_collision2Ds.push_back(std::vector < std::shared_ptr<Collision2D_Base>>());
	vec_collision2Ds.push_back(std::vector < std::shared_ptr<Collision2D_Base>>());
	vec_collision2Ds.push_back(std::vector < std::shared_ptr<Collision2D_Base>>());
	vec_collision2Ds.push_back(std::vector < std::shared_ptr<Collision2D_Base>>());
}

Framework::Collision2DManager::~Collision2DManager()
{
}

bool Framework::Collision2DManager::OnUpdate()
{
	auto vec_objectsCollision = vec_collision2Ds.at(0);
	auto vec_playerCollision = vec_collision2Ds.at(1);
	auto vec_enemyCollision = vec_collision2Ds.at(2);
	auto vec_playerBulletCollision = vec_collision2Ds.at(3);
	auto vec_enemyBulletCollision = vec_collision2Ds.at(4);
	int collisionCount = 0;
	//map、全てのレイヤーと判定をとる
	for (auto itr = vec_objectsCollision.begin(); itr != vec_objectsCollision.end(); itr++) {
		for (auto otherItr = vec_playerCollision.begin(); otherItr != vec_playerCollision.end(); otherItr++) {

			if ((*itr)->IsHit((*otherItr))) {
				(*itr)->OnHit(*otherItr);
				(*otherItr)->OnHit(*itr);
			}
			collisionCount++;
		}
		for (auto otherItr = vec_playerBulletCollision.begin(); otherItr != vec_playerBulletCollision.end(); otherItr++) {

			if ((*itr)->IsHit((*otherItr))) {
				(*itr)->OnHit(*otherItr);
				(*otherItr)->OnHit(*itr);
			}
			collisionCount++;
		}


		for (auto otherItr = vec_enemyCollision.begin(); otherItr != vec_enemyCollision.end(); otherItr++) {

			if ((*itr)->IsHit((*otherItr))) {
				(*itr)->OnHit(*otherItr);
				(*otherItr)->OnHit(*itr);
			}
			collisionCount++;
		}
		for (auto otherItr = vec_enemyBulletCollision.begin(); otherItr != vec_enemyBulletCollision.end(); otherItr++) {

			if ((*itr)->IsHit((*otherItr))) {
				(*itr)->OnHit(*otherItr);
				(*otherItr)->OnHit(*itr);
			}
			collisionCount++;
		}


		if (vec_collision2Ds.size() < 2) {
			break;
		}
		for (auto otherItr = itr+1; otherItr != vec_objectsCollision.end(); otherItr++) {
			if (itr == otherItr)continue;

			if ((*itr)->IsHit((*otherItr))) {
				(*itr)->OnHit(*otherItr);
				(*otherItr)->OnHit(*itr);
			}
			collisionCount++;
		}
	}

	for (auto itr = vec_playerCollision.begin(); itr != vec_playerCollision.end(); itr++) {
		for (auto otherItr = vec_enemyCollision.begin(); otherItr != vec_enemyCollision.end(); otherItr++) {

			if ((*itr)->IsHit((*otherItr))) {
				(*itr)->OnHit(*otherItr);
				(*otherItr)->OnHit(*itr);
			}
			collisionCount++;
		}
		for (auto otherItr = vec_enemyBulletCollision.begin(); otherItr != vec_enemyBulletCollision.end(); otherItr++) {

			if ((*itr)->IsHit((*otherItr))) {
				(*itr)->OnHit(*otherItr);
				(*otherItr)->OnHit(*itr);
			}
			collisionCount++;
		}

	}

	for (auto itr = vec_enemyCollision.begin(); itr != vec_enemyCollision.end(); itr++) {
		for (auto otherItr = vec_playerBulletCollision.begin(); otherItr != vec_playerBulletCollision.end(); otherItr++) {

			if ((*itr)->IsHit((*otherItr))) {
				(*itr)->OnHit(*otherItr);
				(*otherItr)->OnHit(*itr);
			}
			collisionCount++;
		}

	}


	if (Input::GetKeyDown(KEY_INPUT_C)) {
		int i = 0;
	}
	vec_collision2Ds.at(0).clear();
	vec_collision2Ds.at(1).clear();
	vec_collision2Ds.at(2).clear();
	vec_collision2Ds.at(3).clear();
	vec_collision2Ds.at(4).clear();
	return true;
}

void Framework::Collision2DManager::AddCollision(std::shared_ptr<Collision2D_Base> add, int layer)
{
	
	vec_collision2Ds.at(layer).push_back(add->GetThis<Collision2D_Base>());
}


void Framework::Collision2DManager::Release()
{
	for (auto itr = vec_collision2Ds.begin(); itr != vec_collision2Ds.end(); itr++) {
		itr->clear();
	}
	//vec_collision2Ds.clear();
}
