#include "Child.h"
#include "Game.h"
#include"GameObjectManager.h"
#include"Sencer.h"
#include"ParticleEmitter.h"
Framework::Child::Child(int delay,int waitPointDis, std::shared_ptr<Transform> shp_arg_player_transform, std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager)
	:GameObject(shp_arg_transform, shp_arg_gameObjectManager->GetThis<GameObjectManager>()), delay(delay),waitPointDistance(waitPointDis)
{
	shp_player_transform = shp_arg_player_transform->GetThis<Transform>();
	tag = ObjectTag::supporter;
	isThrown = false;
}

Framework::Child::~Child() {}

void Framework::Child::Hit(std::shared_ptr<GameObject> other)
{
	if (GetIsDead()) {
		return;
	}
	if (isThrown&&other->GetObjectTag() == ObjectTag::obstacle) {

		if (other->IsThis<MapChip_ChildBlock>()) {
			SetIsDead(true);
			Game::GetInstance()->GetResourceController()->AddSound(shp_sound_explosion);
			return;
		}

		auto otherRect = other->GetThis<MapChipObject>()->GetRectangle();
		float overlap = 0.0f;

		Vector3 delta = (Vector3)(other->transform->GetPosition() - transform->GetPosition());


		if (abs(delta.x) < abs(delta.y))
		{
			if (delta.y > 0) {
				overlap = shp_collisionRect->rect->GetBottom() - otherRect->GetTop();
				overlap = abs(overlap);
				transform->localPosition.y -= overlap;


			}
			else
				if (delta.y < 0) {
					overlap = otherRect->GetBottom() - shp_collisionRect->rect->GetTop();

					overlap = abs(overlap);
					transform->localPosition.y += overlap;
				}
		}
		 if (abs(delta.x) > abs(delta.y)) {
			if (delta.x > 0) {
				overlap = shp_collisionRect->rect->GetRight() - otherRect->GetLeft();
				overlap = abs(overlap);
				transform->localPosition.x += overlap;
				velocity.x = 0;
			}
			else
				if (delta.x < 0) {
					overlap = otherRect->GetRight() - shp_collisionRect->rect->GetLeft();
					overlap = abs(overlap);
					transform->localPosition.x -= overlap;
					velocity.x = 0;
				}
		}

		shp_collisionRect->OnUpdate();
		CreateBlock();
	}
}

bool Framework::Child::Release()
{
	shp_collisionRect->Releace();
	shp_collisionRect = nullptr;
	shp_texture = nullptr;
	shp_sound_explosion = nullptr;
	return true;
}

void Framework::Child::PreInitialize()
{
	auto handle = Game::GetInstance()->GetResourceController()->GetTexture("child.png");
	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
	shp_sound_explosion = ObjectFactory::Create<Resource_Sound>("Explosion.wav", DX_PLAYTYPE_BACK, true);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(25, 25, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(16, 16)), GetThis<GameObject>());

	std::vector<ObjectTag> tags;
	tags.push_back(ObjectTag::obstacle);



	

}

void Framework::Child::Initialize()
{
	velocity = Vector3(0.0f, 0.0f,0.0f);
	speed = 4.0f;
	gravity = 0.2f;
	maxFallSpeed = 1.0f;
	groundHeight = 672.0f;
	lastSide = 0;
}

bool Framework::Child::OnUpdate() {
	shp_collisionRect->OnUpdate();
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect);
	
	if (!isShoot) {
		Move();
		return true;
	}

	else
	{
		Shoot();
		CheckGoal();
	}
	return true;
}

void Framework::Child::SetDelay(int arg_delay)
{
	delay = arg_delay;
}

bool Framework::Child::Throw(std::shared_ptr<Transform> arg_target)
{
	changeTimer = RelativeTimer(3);
	changeTimer.Start();
	isShoot = true;
	velocity = arg_target->GetPosition().GetVector2()- transform->GetPosition().GetVector2();
	targetPosition = arg_target->GetPosition();
	velocity.Normalize();
	return true;
}

bool Framework::Child::Move() {
	auto playerPos = shp_player_transform->GetPosition().GetVector2();
	auto direction = transform->GetPosition().GetVector2().GetDistance(playerPos);

	if (direction > delay) {
		isChase = true;
	}
	if (direction <= waitPointDistance) {
		isChase = false;
		velocity = Vector3();
	}

	if (!isChase) {
		return true;
	}
	velocity = (Vector3)(shp_player_transform->GetPosition() - transform->GetPosition());
	velocity.Normalize();
	velocity*= speed;

	return true;
}

void Framework::Child::Shoot()
{
	if (!isThrown&& changeTimer.Update()) {

		isThrown = true;
		tag = ObjectTag::playerBullet;
	}
	velocity.Normalize();
	velocity *= speed;
}

void Framework::Child::CheckGoal()
{
	auto targetVec2 = targetPosition.GetVector2();
	auto distance = transform->GetPosition().GetVector2().GetDistance(targetVec2);
	if (distance < 5) {
		CreateBlock();
	}
}

void Framework::Child::CreateBlock()
{
	if (GetIsDead()) {
		return;
	}
	int glidSize = Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize();
	int x = ((transform->GetPosition().x)+glidSize/2) / (float)glidSize;
	int y = (transform->GetPosition().y+glidSize/2 )/(float) glidSize;
	manager->SerchGameObject(ObjectTag::map)->GetThis<Map>()->ChangeGlid(x, y, 5);

	
	SetIsDead(true);
}

