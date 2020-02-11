#include "Child.h"
#include "Game.h"
#include"GameObjectManager.h"

Framework::Child::Child(int delay,int waitPointDis, std::shared_ptr<Transform> shp_arg_player_transform, std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager)
	:GameObject(shp_arg_transform, shp_arg_gameObjectManager->GetThis<GameObjectManager>()), delay(delay),waitPointDistance(waitPointDis)
{
	shp_player_transform = shp_arg_player_transform->GetThis<Transform>();
	tag = ObjectTag::playerChild;
}

Framework::Child::~Child() {}

void Framework::Child::Hit(std::shared_ptr<GameObject> other)
{
	if (other->GetTag() == ObjectTag::player) {
		return;
	}
	if (other->GetTag() == ObjectTag::playerChild) {
		return;
	}
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
	transform->localPosition = prevPosition;
}

void Framework::Child::PreInitialize()
{
	auto handle = Game::GetInstance()->GetResourceController()->GetTexture("orange.png");
	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(16, 16)), GetThis<GameObject>());
}

void Framework::Child::Initialize()
{
	velocity = Vector2(0.0f, 0.0f);
	prevPosition = Vector2(0.0f, 0.0f);
	throwDirection = Vector2(0.0f, 0.0f);
	speed = 4.0f;
	gravity = 0.2f;
	maxFallSpeed = 1.0f;
	groundHeight = 672.0f;
	LBtrigger = false;
	RBtrigger = false;
	state = NormalMode;
	lastSide = 0;
}

bool Framework::Child::Update() {
	shp_collisionRect->Update();
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect);


	GetJoypadXInputState(DX_INPUT_PAD1, &xinput);
	prevPosition = transform->localPosition;

	if (state == NormalMode) {
		Move();
	}
	Throw();
	transform->localPosition += velocity * speed;

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

bool Framework::Child::Throw() {
	//Button[9]cRB
	if (xinput.Buttons[9] && RBtrigger == false) {
		switch (state)
		{
		case NormalMode:
			state = ThrowWaitMode;
			groundHeight += -32.0f;
			break;
		case ThrowWaitMode:
			state = ThrowMode;
			//“Š‚°•ûŒü
			throwDirection = Vector2(xinput.ThumbRX, -xinput.ThumbRY);
			if (throwDirection.y == 0.0f && throwDirection.x == 0.0f) {
				if (lastSide == 0) {
					throwDirection = Vector2(1.0f, 0.0f);
				}
				if (lastSide == 1) {
					throwDirection = Vector2(-1.0f, 0.0f);
				}
			}
			throwDirection.Normalize();
			break;
		default:
			break;
		}
		RBtrigger = true;
	}
	if (!xinput.Buttons[9]) {
		RBtrigger = false;
	}

	//“Š‚°‘Ò‚¿
	if (state == ThrowWaitMode) {
		transform->localPosition = shp_player_transform->GetPosition().GetVector2() - Vector2(0.0f, 32.0f);
	}
	//“Š‚°
	if (state == ThrowMode) {
		velocity = throwDirection * 2;
	}
	//ŒÅ’è
	if (state == FixMode) {
		velocity = Vector2(0.0f, 0.0f);
	}

	return true;
}