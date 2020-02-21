#include "BatBullet.h"
#include "Game.h"
#include"MapChipObject.h"
#include"Sencer.h"
#include"Bullet.h"
#define PI 3.141592654f
#include <cstdlib>
#include <ctime>
#include "ParticleEmitter.h"

Framework::BatBullet::BatBullet(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager) :GameObject(shp_arg_transform, shp_arg_gameObjectManager)
{
	targetPosition = Vector3(1.0f, 0.0f, 0.0f);
	speed = 1.0f;
	gravity = 0.6f;
	maxFallSpeed = 6.0f;
	huwaCounter = 0.0f;
	overlap = 0.0f;
	hp = 5;
	targetRange = 32;
	direction = 1;

	phisicsForce = Vector3(0, 0, 0);

	tag = ObjectTag::enemy;
}


Framework::BatBullet::~BatBullet() {
}

void Framework::BatBullet::Hit(std::shared_ptr<GameObject> other)
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

		isGoalTargetPosition = true;

		if (abs(delta.x) < abs(delta.y))
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
		else if (abs(delta.x) > abs(delta.y)) {
			if (delta.x > 0) {
				overlap = shp_collisionRect->rect->GetRight() - otherRect->GetLeft();
				overlap = abs(overlap);
				transform->localPosition.x -= overlap;

			}
			else
				if (delta.x < 0) {
					overlap = otherRect->GetRight() - shp_collisionRect->rect->GetLeft();
					overlap = abs(overlap);
					transform->localPosition.x += overlap;

				}
		}
		shp_collisionRect->OnUpdate();
	}
}

void Framework::BatBullet::PreInitialize()
{
	auto handle = Game::GetInstance()->GetResourceController()->GetTexture("Bat_1.png");


	shp_sound_found = ObjectFactory::Create<Resource_Sound>("Found.wav", DX_PLAYTYPE_BACK, true);


	isGoalTargetPosition = true;
	isShot = false;

	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(32, 32)), GetThis<GameObject>());
}

bool Framework::BatBullet::OnUpdate() {
	Move();
	if (hp <= 0) {
		Dead();
	}
	shp_collisionRect->OnUpdate();
	if (velocity.x > 0) {
		shp_texture->xFlip = false;
		direction = 1;
	}
	else if (velocity.x < 0) {
		shp_texture->xFlip = true;
		direction = -1;
	}

	if (!coolTimer.Update()) {
		isShot = false;
		coolTimer.Start();
	}
	else {
		isShot = true;
		coolTimer.Stop();
		coolTimer.Reset();
	}

	if (isShot) {
		Shot();
	}


	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture, 1);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect, 2);
	isGround = false;
	return true;
}

bool Framework::BatBullet::Release()
{
	shp_collisionRect->Releace();
	shp_collisionRect = nullptr;
	shp_texture = nullptr;
	shp_sound_found = nullptr;
	return true;
}

bool Framework::BatBullet::Move() {
	velocity = Vector2(0, 0);
	if (!player || player->GetIsDead())
		player = manager->SerchGameObject(ObjectTag::player);
	if (player) {
		auto vec = transform->GetPosition().GetVector2();
		auto dis = (player->transform->GetPosition().GetVector2().GetDistance(vec));

		float range = targetPosition.GetVector2().GetDistance(vec);

		if (dis < 320) {
			if (!isFind)
				Game::GetInstance()->GetResourceController()->AddSound(shp_sound_found);
			velocity = player->transform->GetPosition() - vec;
			isFind = true;
		}
		else {
			//徘徊モード
			DecideTargetPotision();

			velocity = targetPosition - transform->GetPosition();
			if (range <= 32) {
				isGoalTargetPosition = true;
			}
			isFind = false;
		}
	}
	//ふわふわ
	huwaCounter++;
	if (huwaCounter >= 360.0f) {
		huwaCounter = 0.0f;
	}
	floatVec.y = sin(PI * 2 / 60 * huwaCounter);

	velocity + floatVec;

	velocity.Normalize();
	velocity *= speed;
	return true;
}

void Framework::BatBullet::Dead()
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

void Framework::BatBullet::DecideTargetPotision() {
	//目的地を設定
	if (!isGoalTargetPosition) {
		return;
	}

	srand((unsigned int)time(0));
	float posx = rand() % (targetRange * 2);
	posx -= targetRange;
	float posy = rand() % (targetRange * 2);
	posy -= targetRange;

	targetPosition = Vector3(posx, posy, 0) + transform->GetPosition();
	isGoalTargetPosition = false;
}

void Framework::BatBullet::Shot()
{
	auto bulletTransform = ObjectFactory::Create<Transform>(transform->GetPosition());
	manager->AddObject(ObjectFactory::Create<EnemyBullet>(1.0f + damage, 5, direction, bulletTransform, manager));
}