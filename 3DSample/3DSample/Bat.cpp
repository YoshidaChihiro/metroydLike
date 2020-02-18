#include "Bat.h"
#include "Game.h"
#include"MapChipObject.h"
#include"Sencer.h"
#define PI 3.141592654f
#include <cstdlib>
#include <ctime>

Framework::Bat::Bat(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager) :GameObject(shp_arg_transform, shp_arg_gameObjectManager)
{
	targetPosition = Vector3(1.0f, 0.0f,0.0f);
	speed = 1.0f;
	gravity = 0.6f;
	maxFallSpeed = 6.0f;
	huwaCounter = 0.0f;
	overlap = 0.0f;
	targetRange = 64;

	phisicsForce = Vector3(0, 0,0);

	tag = ObjectTag::enemy;
}


Framework::Bat::~Bat() {}

void Framework::Bat::Hit(std::shared_ptr<GameObject> other)
{
	if (other->GetObjectTag() == ObjectTag::playerBullet) {
		SetIsDead(true);
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

void Framework::Bat::PreInitialize()
{
	auto handle = Game::GetInstance()->GetResourceController()->GetTexture("Bat_1.png");

	std::vector<ObjectTag> tags;
	tags.push_back(ObjectTag::obstacle);

	isGoalTargetPosition = true;


	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(32, 32)), GetThis<GameObject>());
}

bool Framework::Bat::OnUpdate() {
	Move();
	shp_collisionRect->OnUpdate();
	if (velocity.x > 0) {
		shp_texture->xFlip = false;
	}
	else if (velocity.x < 0) {
		shp_texture->xFlip = true;

	}
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture, 1);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect);
	isGround = false;
	return true;
}

bool Framework::Bat::Release()
{
	shp_collisionRect->Releace();
	shp_collisionRect = nullptr;
	shp_texture = nullptr;
	return true;
}

bool Framework::Bat::Move() {
	velocity = Vector2(0, 0);
	if (!player||player->GetIsDead())
		player = manager->SerchGameObject(ObjectTag::player);
	if (player) {
		auto vec = transform->GetPosition().GetVector2();
		auto dis = (player->transform->GetPosition().GetVector2().GetDistance(vec));

		float range = targetPosition.GetVector2().GetDistance(vec);

		if (dis < 320) {
			velocity = player->transform->GetPosition() - vec;
		}
		else {
			//徘徊モード
			DecideTargetPotision();
			
			velocity = targetPosition - transform->GetPosition();
			if (range <= 32) {
				isGoalTargetPosition = true;
			}

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

void Framework::Bat::DecideTargetPotision() {
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