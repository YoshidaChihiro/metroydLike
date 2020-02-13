#include "Bat.h"
#include "Game.h"
#include"MapChipObject.h"
#include"Sencer.h"
#define PI 3.141592654f

Framework::Bat::Bat(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager) :GameObject(shp_arg_transform, shp_arg_gameObjectManager)
{
	velocity = Vector2(0.0f, 0.0f);
	speed = 2.0f;
	gravity = 0.6f;
	maxFallSpeed = 6.0f;
	flapCounter = 0.0f;
	huwaCounter = 0.0f;
	isBound = false;

	phisicsForce = Vector2(0, 0);

	tag = ObjectTag::enemy;
}


Framework::Bat::~Bat() {}

void Framework::Bat::Hit(std::shared_ptr<GameObject> other)
{
	if (other->GetObjectTag() == ObjectTag::supporter || other->GetObjectTag() == ObjectTag::sencer) {
		return;
	}
	if (other->GetObjectTag() == ObjectTag::player) {
		return;
	}
	if (other->GetObjectTag() == ObjectTag::enemy) {
		return;
	}
	//
	Vector3 mapchipPos = other->transform->GetPosition();
	auto otherRect = other->GetThis<MapChipObject>()->GetRectangle();
	float overlap = 0.0f;

	if (sencerInputs[1] == other) {
		overlap = shp_collisionRect->rect->GetBottom() - otherRect->GetTop();
		overlap = abs(overlap);
		transform->localPosition.y -= overlap;
		isGround = true;
		//���n
		phisicsForce.y = 0.0f;

	}
	if (sencerInputs[0] == other) {
		overlap = otherRect->GetBottom() - shp_collisionRect->rect->GetTop();

		overlap = abs(overlap);
		transform->localPosition.y += overlap;
	}

	shp_collisionRect->Update();
	if (sencerInputs[3] == other) {
		overlap = shp_collisionRect->rect->GetRight() - otherRect->GetLeft();
		overlap = abs(overlap);
		transform->localPosition.x -= overlap;
		velocity.x = 0;
		phisicsForce.x = 0;
		isBound = false;
	}

	if (sencerInputs[2] == other) {
		overlap = otherRect->GetRight() - shp_collisionRect->rect->GetLeft();
		overlap = abs(overlap);
		transform->localPosition.x += overlap;
		velocity.x = 0;
		phisicsForce.x = 0;
		isBound = true;
	}

	shp_collisionRect->Update();
}

void Framework::Bat::PreInitialize()
{
	auto handle = Game::GetInstance()->GetResourceController()->GetTexture("potato.png");

	std::vector<ObjectTag> tags;
	tags.push_back(ObjectTag::obstacle);

	sencerInputs.push_back(nullptr);
	sencerInputs.push_back(nullptr);
	sencerInputs.push_back(nullptr);
	sencerInputs.push_back(nullptr);


	auto sencerTransform_top = ObjectFactory::Create<Transform>(Vector3(0, -16, 0));
	sencerTransform_top->baseTransform = (transform);
	auto sencer_top = ObjectFactory::Create<Sencer>(sencerTransform_top, manager, tags, &sencerInputs.at(0), 1, 8);

	auto sencerTransform_bottom = ObjectFactory::Create<Transform>(Vector3(0, 16, 0));
	sencerTransform_bottom->baseTransform = (transform);
	auto sencer_bottom = ObjectFactory::Create<Sencer>(sencerTransform_bottom, manager, tags, &sencerInputs.at(1), 1, 8);

	auto sencerTransform_left = ObjectFactory::Create<Transform>(Vector3(-16, 0, 0));
	sencerTransform_left->baseTransform = (transform);
	auto sencer_left = ObjectFactory::Create<Sencer>(sencerTransform_left, manager, tags, &sencerInputs.at(2), 8, 1);

	auto sencerTransform_right = ObjectFactory::Create<Transform>(Vector3(16, 0, 0));
	sencerTransform_right->baseTransform = (transform);
	auto sencer_right = ObjectFactory::Create<Sencer>(sencerTransform_right, manager, tags, &sencerInputs.at(3), 8, 1);


	manager->AddObject_Init(sencer_top);
	manager->AddObject_Init(sencer_bottom);
	manager->AddObject_Init(sencer_left);
	manager->AddObject_Init(sencer_right);

	AddChildObject(sencer_top);
	AddChildObject(sencer_bottom);
	AddChildObject(sencer_left);
	AddChildObject(sencer_right);

	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(32, 32)), GetThis<GameObject>());
}

bool Framework::Bat::Update() {
	Move();
	shp_collisionRect->Update();
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture, 1);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect);
	for (int i = 0; i < 4; i++) {
		sencerInputs[i] = nullptr;
	}
	isGround = false;
	return true;
}

bool Framework::Bat::Move() {
	if (isBound) {
		velocity.x = 1;
	}
	else {
		velocity.x = -1;
	}

	//ふわふわ
	huwaCounter++;
	if (huwaCounter >= 360.0f) {
		huwaCounter = 0.0f;
	}
	velocity.y = sin(PI * 2 / 60 * huwaCounter);

	velocity.Normalize();
	transform->localPosition += ((Vector2)(velocity * speed)) + ((Vector2)(phisicsForce));

	//float flapMax = 2.0f;
	//flapCounter++;
	//if (flapCounter > flapMax) {
	//	gravity *= -1;
	//	flapCounter = 0.0f;
	//}
	//phisicsForce.y += gravity;
	//if (phisicsForce.y > maxFallSpeed) {
	//	phisicsForce.y = maxFallSpeed;
	//}

	return true;
}