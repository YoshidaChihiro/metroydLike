#include "Teresa.h"
#include "Game.h"
#include"MapChipObject.h"
#include"Sencer.h"

Framework::Teresa::Teresa(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager) :GameObject(shp_arg_transform, shp_arg_gameObjectManager)
{
	velocity = Vector2(0.0f, 0.0f);
	speed = 1.0f;
	spaceDistance = 400.0f;
	phisicsForce = Vector2(0, 0);
	
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

bool Framework::Teresa::Update() {
	//AI‰ü‘P‚Ì‚½‚ß’âŽ~
	//Move();
	shp_collisionRect->Update();
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture, 1);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect);
	for (int i = 0; i < 4; i++) {
		sencerInputs[i] = nullptr;
	}
	return true;
}

bool Framework::Teresa::Release()
{
	shp_collisionRect->Releace();
	sencerInputs.clear();
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
	transform->localPosition += ((Vector2)(velocity * speed)) + ((Vector2)(phisicsForce));

	return true;
}