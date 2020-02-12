#include "Child.h"
#include "Game.h"
#include"GameObjectManager.h"
#include"Sencer.h"

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
	if (other->GetObjectTag() == ObjectTag::player) {
		return;
	}
	if (other->GetObjectTag() == ObjectTag::supporter) {
		return;
	}
	if (isThrown&&other->GetObjectTag() == ObjectTag::obstacle) {

		auto otherRect = other->GetThis<MapChipObject>()->GetRectangle();
		float overlap = 0.0f;

		if (sencerInputs[1] == other) {
			overlap = shp_collisionRect->rect->GetBottom() - otherRect->GetTop();
			overlap = abs(overlap);
			transform->localPosition.y -= overlap;

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
		}

		if (sencerInputs[2] == other) {
			overlap = otherRect->GetRight() - shp_collisionRect->rect->GetLeft();
			overlap = abs(overlap);
			transform->localPosition.x += overlap;
			velocity.x = 0;
		}

		shp_collisionRect->Update();
		CreateBlock();
	}
}

void Framework::Child::PreInitialize()
{
	auto handle = Game::GetInstance()->GetResourceController()->GetTexture("orange.png");
	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(16, 16)), GetThis<GameObject>());

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

bool Framework::Child::Update() {
	shp_collisionRect->Update();
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect);
	if(!isThrown)
	Move();
	else
	{
		Shoot();
	}
	return true;
}

bool Framework::Child::Throw(std::shared_ptr<Transform> arg_target)
{
	isThrown = true;
	velocity = arg_target->GetPosition().GetVector2()- transform->GetPosition().GetVector2();
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
	}

	if (!isChase) {
		return true;
	}
	auto velocity3 = (Vector3)(shp_player_transform->GetPosition() - transform->GetPosition());
	velocity3.Normalize();
	transform->localPosition += velocity3 * speed;

	return true;
}

void Framework::Child::Shoot()
{

	transform->localPosition +=velocity*speed;
}

void Framework::Child::CreateBlock()
{
	if (GetIsDead()) {
		return;
	}
	int x = transform->GetPosition().x / Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize();
	int y = transform->GetPosition().y / Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize();
	manager->SerchGameObject(ObjectTag::map)->GetThis<Map>()->ChangeGlid(x, y, 26);
	SetIsDead(true);
}

