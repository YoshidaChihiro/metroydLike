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
	groundHeight = 672;
	isJump = true;
	isSecondJump = false;
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

	Move();
	if (state != FixMode) {
		//Jump();
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

bool Framework::Child::Jump() {
	//仮置き///着地//////
	if (transform->localPosition.y > groundHeight) {
		isJump = false;
		velocity.y = 0.0f;
		if (isSecondJump == true) {
			state = FixMode;
		}
	}
	////////////////////

	//Button[8]…LB
	if (isJump == false && xinput.Buttons[8] && LBtrigger == false) {
		velocity.y = -3.0f;
		isJump = true;
		LBtrigger = true;
	}
	if (!xinput.Buttons[8]) {
		LBtrigger = false;
	}
	//ジャンプ中
	if (isJump == true) {
		//2段ジャンプ
		if (state == ThrowWaitMode && isSecondJump == false && xinput.Buttons[8] && LBtrigger == false) {
			isSecondJump = true;
			LBtrigger = true;
			//下に落ちる
			velocity.y = 2.0f;
			groundHeight = 672 + 32;
		}

		//重力
		velocity.y += gravity;
		//落下速度制限
		if (velocity.y > maxFallSpeed) {
			velocity.y = maxFallSpeed;
		}
	}

	return true;
}

bool Framework::Child::Throw() {
	//Button[9]…RB
	if (xinput.Buttons[9] && RBtrigger == false) {
		switch (state)
		{
		case NormalMode:
			state = ThrowWaitMode;
			transform->localPosition += Vector3(35.0f, -40.0f, 0.0f);
			groundHeight += -32.0f;
			break;
		case ThrowWaitMode:
			state = ThrowMode;
			//投げ方向
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

	//投げ
	if (state == ThrowMode) {
		velocity = throwDirection * 2;
	}
	//固定
	if (state == FixMode) {
		velocity = Vector2(0.0f, 0.0f);
	}

	return true;
}