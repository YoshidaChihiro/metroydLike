﻿#include "Kuribo.h"
#include "Game.h"
#include"MapChipObject.h"
#include"Sencer.h"
#include "ParticleEmitter.h"

Framework::Kuribo::Kuribo(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager, std::shared_ptr<Map> shp_arg_map) :GameObject(shp_arg_transform, shp_arg_gameObjectManager)
{
	velocity = Vector3(-1.0f, 0.0f, 0.0f);
	prevVelocity = Vector3(0.0f, 0.0f, 0.0f);
	speed = 1.0f;
	gravity = 0.6f;
	maxFallSpeed = 6.0f;
	overlap = 0.0f;

	phisicsForce = Vector3(0,0, 0);
	hp = 5;
	tag = ObjectTag::enemy;
	shp_map = shp_arg_map;
}


Framework::Kuribo::~Kuribo() {}

void Framework::Kuribo::Hit(std::shared_ptr<GameObject> other)
{
	if (other->GetObjectTag() == ObjectTag::playerBullet) {
		hp -= other->GetThis<Bullet>()->damage;
		return;
	}

	if (other->GetObjectTag() == ObjectTag::enemy) {
		//敵同士の当たり判定、いる？
		return;
		
	}

	if (other->GetObjectTag() == ObjectTag::obstacle) {
		auto otherRect = other->GetThis<MapChipObject>()->GetRectangle();
		float overlap = 0.0f;

		Vector3 delta = (Vector3)(other->transform->GetPosition() - transform->GetPosition());


		if (abs(delta.x) - abs(delta.y)<=-1)
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
		else if (abs(delta.x) - abs(delta.y)>=1) {
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

void Framework::Kuribo::PreInitialize()
{
	auto handle = Game::GetInstance()->GetResourceController()->GetTexture("Kuribo_1.png");


	shp_sound_found = ObjectFactory::Create<Resource_Sound>("Found.wav", DX_PLAYTYPE_BACK, true);


	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(32, 32)), GetThis<GameObject>());
	vec_gameComponents.push_back(shp_collisionRect->GetThis<GameComponent>());
}

bool Framework::Kuribo::OnUpdate() {
	Move();
	if (hp <= 0) {
		Dead();
	}
	shp_collisionRect->OnUpdate();
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture, 1);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect,2);

	if (velocity.x > 0) {
		shp_texture->xFlip = true;
	}
	else if (velocity.x < 0) {
		shp_texture->xFlip = false;

	}
	isGround = false;
	return true;
}

bool Framework::Kuribo::Release()
{
	shp_collisionRect->Releace();
	shp_collisionRect = nullptr;
	shp_texture = nullptr;
	shp_sound_found = nullptr;
	return true;
}

void Framework::Kuribo::Dead()
{
	Game::GetInstance()->GetSceneManager()->GetGameMaster()->AddScore(100);
	auto seedTransform = ObjectFactory::Create<Transform>(transform->GetPosition());
	manager->AddObject_Init(ObjectFactory::Create<ChildSeed>(seedTransform, manager));
	SetIsDead(true);
	int handle = Game::GetInstance()->GetResourceController()->GetTexture("whiteParticle.png");
	auto p_param = new ParticleEmitterParameter();
	p_param->graphHandle = handle;
	p_param->range_maxVelocity = Vector3(0.5f, 0, 0);
	p_param->range_minVelocity = Vector3(-0.5f, -1, 0);
	p_param->layer = 2;
	p_param->range_maxSpeed = 10;
	p_param->range_minSpeed = 5;
	p_param->range_maxLifeSpan = 100;
	p_param->range_minLifeSpan = 50;
	p_param->range_maxRotation.z = 360;
	p_param->range_minRotation.z = 0;
	p_param->range_maxEmitCount = 20;
	p_param->range_minEmitCount = 10;
	p_param->range_maxPhisicsForce = Vector3(0, 0.2f, 0);
	p_param->range_minPhisicsForce = Vector3(0, 0.2f, 0);
	p_param->emitSpan = 2;
	p_param->emitterLifeSpan = 10;
	manager->AddObject(ObjectFactory::Create<ParticleEmitter>(transform->GetThis<Transform>(), p_param, manager
		));
}

bool Framework::Kuribo::Move() {

	if (!player || player->GetIsDead())
	player = manager->SerchGameObject(ObjectTag::player);

	if (player) {
		auto vec = transform->GetPosition().GetVector2();
		auto dis = (player->transform->GetPosition().GetVector2().GetDistance(vec));

		if (dis < 160) {
			if(!isFind)
			Game::GetInstance()->GetResourceController()->AddSound(shp_sound_found);
			velocity.x = player->transform->GetPosition().GetVector2().x - vec.x;
			isFind = true;
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
			isFind = false;
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