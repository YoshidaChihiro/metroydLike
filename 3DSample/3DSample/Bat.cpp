#include "Bat.h"
#include "Game.h"
#include"MapChipObject.h"
#include"Sencer.h"
#define PI 3.141592654f

Framework::Bat::Bat(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager) :GameObject(shp_arg_transform, shp_arg_gameObjectManager)
{
	velocity = Vector2(1.0f, 0.0f);
	prevVelocity = Vector2(0.0f, 0.0f);
	speed = 1.0f;
	gravity = 0.6f;
	maxFallSpeed = 6.0f;
	huwaCounter = 0.0f;
	overlap = 0.0f;

	phisicsForce = Vector2(0, 0);

	tag = ObjectTag::bat;
}


Framework::Bat::~Bat() {}

void Framework::Bat::Hit(std::shared_ptr<GameObject> other)
{
	if (other->GetObjectTag() == ObjectTag::supporter || other->GetObjectTag() == ObjectTag::sencer 
		|| other->GetObjectTag() == ObjectTag::player || other->GetObjectTag() == ObjectTag::teresa) {
		return;
	}

	if (other->GetObjectTag() == ObjectTag::kuribo) {
		auto otherRect = other->GetThis<Kuribo>()->GetRectangle();
		overlap = 0.0f;

		if (sencerInputs_kuribo[3] == other) {
			overlap = shp_collisionRect->rect->GetRight() - otherRect->GetLeft();
			overlap = abs(overlap);
			transform->localPosition.x -= overlap;
			if (prevVelocity.x > 0) {
				velocity.x = -1;
			}
			if (prevVelocity.x < 0) {
				velocity.x = 1;
			}
		}

		if (sencerInputs_kuribo[2] == other) {
			overlap = otherRect->GetRight() - shp_collisionRect->rect->GetLeft();
			overlap = abs(overlap);
			transform->localPosition.x += overlap;
			if (prevVelocity.x > 0) {
				velocity.x = -1;
			}
			if (prevVelocity.x < 0) {
				velocity.x = 1;
			}
		}
		shp_collisionRect->Update();
		return;
	}
	if (other->GetObjectTag() == ObjectTag::bat) {
		auto otherRect = other->GetThis<Bat>()->GetRectangle();
		overlap = 0.0f;

		if (sencerInputs_bat[3] == other) {
			overlap = shp_collisionRect->rect->GetRight() - otherRect->GetLeft();
			overlap = abs(overlap);
			transform->localPosition.x -= overlap;
			if (prevVelocity.x > 0) {
				velocity.x = -1;
			}
			if (prevVelocity.x < 0) {
				velocity.x = 1;
			}
		}

		if (sencerInputs_bat[2] == other) {
			overlap = otherRect->GetRight() - shp_collisionRect->rect->GetLeft();
			overlap = abs(overlap);
			transform->localPosition.x += overlap;
			if (prevVelocity.x > 0) {
				velocity.x = -1;
			}
			if (prevVelocity.x < 0) {
				velocity.x = 1;
			}
		}
		shp_collisionRect->Update();
		return;
	}

	Vector3 mapchipPos = other->transform->GetPosition();
	auto otherRect = other->GetThis<MapChipObject>()->GetRectangle();
	overlap = 0.0f;

	if (sencerInputs[1] == other) {
		overlap = shp_collisionRect->rect->GetBottom() - otherRect->GetTop();
		overlap = abs(overlap);
		transform->localPosition.y -= overlap;
		isGround = true;
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
		if (prevVelocity.x > 0) {
			velocity.x = -1;
		}
		if (prevVelocity.x < 0) {
			velocity.x = 1;
		}
	}

	if (sencerInputs[2] == other) {
		overlap = otherRect->GetRight() - shp_collisionRect->rect->GetLeft();
		overlap = abs(overlap);
		transform->localPosition.x += overlap;
		if (prevVelocity.x > 0) {
			velocity.x = -1;
		}
		if (prevVelocity.x < 0) {
			velocity.x = 1;
		}
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

#pragma region kuribo
	std::vector<ObjectTag> tags_kuribo;
	tags_kuribo.push_back(ObjectTag::kuribo);

	sencerInputs_kuribo.push_back(nullptr);
	sencerInputs_kuribo.push_back(nullptr);
	sencerInputs_kuribo.push_back(nullptr);
	sencerInputs_kuribo.push_back(nullptr);

	auto sencer_top_kuribo = ObjectFactory::Create<Sencer>(sencerTransform_top, manager, tags_kuribo, &sencerInputs_kuribo.at(0), 1, 8);
	auto sencer_bottom_kuribo = ObjectFactory::Create<Sencer>(sencerTransform_bottom, manager, tags_kuribo, &sencerInputs_kuribo.at(1), 1, 8);
	auto sencer_left_kuribo = ObjectFactory::Create<Sencer>(sencerTransform_left, manager, tags_kuribo, &sencerInputs_kuribo.at(2), 8, 1);
	auto sencer_right_kuribo = ObjectFactory::Create<Sencer>(sencerTransform_right, manager, tags_kuribo, &sencerInputs_kuribo.at(3), 8, 1);

	manager->AddObject_Init(sencer_top_kuribo);
	manager->AddObject_Init(sencer_bottom_kuribo);
	manager->AddObject_Init(sencer_left_kuribo);
	manager->AddObject_Init(sencer_right_kuribo);

	AddChildObject(sencer_top_kuribo);
	AddChildObject(sencer_bottom_kuribo);
	AddChildObject(sencer_left_kuribo);
	AddChildObject(sencer_right_kuribo);
#pragma endregion

#pragma region bat
	std::vector<ObjectTag> tags_bat;
	tags_bat.push_back(ObjectTag::bat);

	sencerInputs_bat.push_back(nullptr);
	sencerInputs_bat.push_back(nullptr);
	sencerInputs_bat.push_back(nullptr);
	sencerInputs_bat.push_back(nullptr);

	auto sencer_top_bat = ObjectFactory::Create<Sencer>(sencerTransform_top, manager, tags_kuribo, &sencerInputs_bat.at(0), 1, 8);
	auto sencer_bottom_bat = ObjectFactory::Create<Sencer>(sencerTransform_bottom, manager, tags_kuribo, &sencerInputs_bat.at(1), 1, 8);
	auto sencer_left_bat = ObjectFactory::Create<Sencer>(sencerTransform_left, manager, tags_kuribo, &sencerInputs_bat.at(2), 8, 1);
	auto sencer_right_bat = ObjectFactory::Create<Sencer>(sencerTransform_right, manager, tags_kuribo, &sencerInputs_bat.at(3), 8, 1);

	manager->AddObject_Init(sencer_top_bat);
	manager->AddObject_Init(sencer_bottom_bat);
	manager->AddObject_Init(sencer_left_bat);
	manager->AddObject_Init(sencer_right_bat);

	AddChildObject(sencer_top_bat);
	AddChildObject(sencer_bottom_bat);
	AddChildObject(sencer_left_bat);
	AddChildObject(sencer_right_bat);
#pragma endregion

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
		sencerInputs_kuribo[i] = nullptr;
		sencerInputs_bat[i] = nullptr;
	}
	isGround = false;
	return true;
}

bool Framework::Bat::Move() {
	//ふわふわ
	huwaCounter++;
	if (huwaCounter >= 360.0f) {
		huwaCounter = 0.0f;
	}
	velocity.y = sin(PI * 2 / 60 * huwaCounter);

	velocity.Normalize();
	prevVelocity = velocity;
	transform->localPosition += ((Vector2)(velocity * speed)) + ((Vector2)(phisicsForce));

	return true;
}