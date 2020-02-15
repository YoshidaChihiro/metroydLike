#include "Kuribo.h"
#include "Game.h"
#include"MapChipObject.h"
#include"Sencer.h"
Framework::Kuribo::Kuribo(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager) :GameObject(shp_arg_transform, shp_arg_gameObjectManager)
{
	velocity = Vector2(-1.0f, 0.0f);
	prevVelocity = Vector2(0.0f, 0.0f);
	speed = 1.0f;
	gravity = 0.6f;
	maxFallSpeed = 6.0f;
	overlap = 0.0f;

	phisicsForce = Vector2(0, 0);

	tag = ObjectTag::enemy;
}


Framework::Kuribo::~Kuribo() {}

void Framework::Kuribo::Hit(std::shared_ptr<GameObject> other)
{
	if (other->GetObjectTag() == ObjectTag::playerBullet ) {
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
				velocity.x = 0;
				phisicsForce.x = 0;
			}
			else
				if (delta.x < 0) {
					overlap = otherRect->GetRight() - shp_collisionRect->rect->GetLeft();
					overlap = abs(overlap);
					transform->localPosition.x += overlap;
					velocity.x = 0;
					phisicsForce.x = 0;
				}
		}
		shp_collisionRect->Update();
	}
}

void Framework::Kuribo::PreInitialize()
{
	auto handle = Game::GetInstance()->GetResourceController()->GetTexture("pumpkin.png");

	std::vector<ObjectTag> tags;
	tags.push_back(ObjectTag::obstacle);



	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(32, 32)), GetThis<GameObject>());
}

bool Framework::Kuribo::Update() {
	Move();
	shp_collisionRect->Update();
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture, 1);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect);

	isGround = false;
	return true;
}

bool Framework::Kuribo::Release()
{
	shp_collisionRect->Releace();
	shp_collisionRect = nullptr;
	shp_texture = nullptr;
	return true;
}

bool Framework::Kuribo::Move() {

	velocity.Normalize();
	transform->localPosition += ((Vector2)(velocity * speed)) + ((Vector2)(phisicsForce));

	phisicsForce.y += gravity;
	if (phisicsForce.y > maxFallSpeed) {
		phisicsForce.y = maxFallSpeed;
	}
	prevVelocity = velocity;

	return true;
}