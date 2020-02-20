﻿#include "Boss.h"
#include "Game.h"
#include"MapChipObject.h"
#include"Sencer.h"

Framework::Boss::Boss(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager, std::shared_ptr<Map> shp_arg_map) :GameObject(shp_arg_transform, shp_arg_gameObjectManager)
{
	velocity = Vector3(0.0f, 0.0f, 0.0f);
	prevVelocity = Vector3(0.0f, 0.0f, 0.0f);
	bombVec = Vector2(0.0f, 0.0f);
	speed = 1.0f;
	gravity = 0.6f;
	maxFallSpeed = 6.0f;
	overlap = 0.0f;
	direction = 1;

	phisicsForce = Vector3(0, 0, 0);
	hp = 5;
	tag = ObjectTag::enemy;
	shp_map = shp_arg_map;
}


Framework::Boss::~Boss() {}

void Framework::Boss::Hit(std::shared_ptr<GameObject> other)
{
	if (other->GetObjectTag() == ObjectTag::playerBullet) {
		hp -= other->GetThis<Bullet>()->damage;
		return;
	}

	if (other->GetObjectTag() == ObjectTag::enemy) {
		return;
	}

	if (other->GetObjectTag() == ObjectTag::obstacle) {
		auto otherRect = other->GetThis<MapChipObject>()->GetRectangle();
		float overlap = 0.0f;

		Vector3 delta = (Vector3)(other->transform->GetPosition() - transform->GetPosition());


		if (abs(delta.x) - abs(delta.y) <= -1)
		{
			if (delta.y > 0) {
				overlap = shp_collisionRect->rect->GetBottom() - otherRect->GetTop();
				overlap = abs(overlap);
				transform->localPosition.y -= overlap;

				isGround = true;
				//���n
				phisicsForce.y = 0.0f;

			}
			else
				if (delta.y < 0) {
					overlap = otherRect->GetBottom() - shp_collisionRect->rect->GetTop();

					overlap = abs(overlap);
					transform->localPosition.y += overlap;
				}
		}
		else if (abs(delta.x) - abs(delta.y) >= 1) {
			if (delta.x > 0) {
				overlap = shp_collisionRect->rect->GetRight() - otherRect->GetLeft();
				overlap = abs(overlap);
				transform->localPosition.x -= overlap;
				if (prevVelocity.x > 0) {
					velocity.x = -1;
				}
			}
			else
				if (delta.x < 0) {
					overlap = otherRect->GetRight() - shp_collisionRect->rect->GetLeft();
					overlap = abs(overlap);
					transform->localPosition.x += overlap;
					if (prevVelocity.x < 0) {
						velocity.x = 1;
					}
				}
		}
		shp_collisionRect->OnUpdate();
	}
}

void Framework::Boss::PreInitialize()
{
	auto handle = Game::GetInstance()->GetResourceController()->GetTexture("robo.png");

	isBombShot = false;

	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(32, 32)), GetThis<GameObject>());
	vec_gameComponents.push_back(shp_collisionRect->GetThis<GameComponent>());
}

bool Framework::Boss::OnUpdate() {
	Move();
	if (hp <= 0) {
		Dead();
	}
	shp_collisionRect->OnUpdate();
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture, 1);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect, 2);

	if (velocity.x < 0) {
		shp_texture->xFlip = true;
		direction = -1;
	}
	else if (velocity.x > 0) {
		shp_texture->xFlip = false;
		direction = 1;
	}

	if (!coolTimer.Update()) {
		isBombShot = false;
		coolTimer.Start();
	}
	else {
		isBombShot = true;
		coolTimer.Stop();
		coolTimer.Reset();
	}

	if (isBombShot) {
		Bomb();
	}

	isGround = false;
	return true;
}

bool Framework::Boss::Release()
{
	shp_collisionRect->Releace();
	shp_collisionRect = nullptr;
	shp_texture = nullptr;
	return true;
}

void Framework::Boss::Dead()
{
	Game::GetInstance()->GetSceneManager()->GetGameMaster()->AddScore(100);
	SetIsDead(true);
}

bool Framework::Boss::Move() {

	if (!player || player->GetIsDead())
		player = manager->SerchGameObject(ObjectTag::player);

	if (player) {
		auto vec = transform->GetPosition().GetVector2();
		auto dis = (player->transform->GetPosition().GetVector2().GetDistance(vec));

		if (dis < 160) {
			velocity.x = player->transform->GetPosition().GetVector2().x - vec.x;
		}
		else {
			//徘徊モード
			auto aroundMap = shp_map->GetAroundObjects_containNullptr(vec);
			if (aroundMap.at(6) == nullptr || aroundMap.at(8) == nullptr) {
				if (prevVelocity.x < 0) {
					velocity.x = 1;
				}
				if (prevVelocity.x > 0) {
					velocity.x = -1;
				}
			}
		}
	}
	velocity.Normalize();
	velocity *= speed;
	phisicsForce.y += gravity;
	if (phisicsForce.y > maxFallSpeed) {
		phisicsForce.y = maxFallSpeed;
	}
	prevVelocity = velocity;

	return true;
}

void Framework::Boss::Bomb()
{
	bombVec = Vector2(GetRand(2) + 3, GetRand(3) + 3);
	auto bulletTransform = ObjectFactory::Create<Transform>(transform->GetPosition());
	manager->AddObject(ObjectFactory::Create<EnemyBomb>(1.0f + damage, direction, bombVec.x, -bombVec.y, bulletTransform, manager));
}