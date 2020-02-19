#include "Teresa.h"
#include "Game.h"
#include"MapChipObject.h"
#include"Sencer.h"

Framework::Teresa::Teresa(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager) :GameObject(shp_arg_transform, shp_arg_gameObjectManager)
{
	velocity = Vector3(0.0f, 0.0f,0.0f);
	speed = 1.0f;
	spaceDistance = 400.0f;
	phisicsForce = Vector3(0,0, 0);
	
	tag = ObjectTag::enemy;
}


Framework::Teresa::~Teresa() {}

void Framework::Teresa::Hit(std::shared_ptr<GameObject> other)
{
	if (other->GetObjectTag() == ObjectTag::playerBullet) {
		SetIsDead(true);
		return;
	}
	return;
}

void Framework::Teresa::PreInitialize()
{
	auto handle = Game::GetInstance()->GetResourceController()->GetTexture("watermelon.png");


	//shp_player_transform = manager->SerchGameObject(ObjectTag::player)->transform->GetThis<Transform>();

	std::vector<ObjectTag> tags;
	tags.push_back(ObjectTag::obstacle);

	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(32, 32)), GetThis<GameObject>());
}

bool Framework::Teresa::OnUpdate() {
	//AI‰ü‘P‚Ì‚½‚ß’âŽ~
	//Move();
	shp_collisionRect->OnUpdate();
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture, 1);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect,2);
	return true;
}

bool Framework::Teresa::Release()
{
	shp_collisionRect->Releace();
	shp_collisionRect = nullptr;
	shp_texture = nullptr;
	return true;
}

bool Framework::Teresa::Move() {
	auto playerPos = shp_player_transform->GetPosition().GetVector2();
	auto direction = transform->GetPosition().GetVector2().GetDistance(playerPos);

	if (direction < spaceDistance) {
		isChase = true;
	}
	else {
		isChase = false;
	}

	if (isChase) {
		velocity = shp_player_transform->GetPosition() - transform->GetPosition();
	}
	else{
		velocity = Vector2(0.0f, 0.0f);
	}
	
	velocity.Normalize();
	velocity *= speed;

	return true;
}