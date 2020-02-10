#include "Player.h"
#include "Child.h"
#include "Game.h"

Framework::Player::Player(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager) :GameObject(shp_arg_transform, shp_arg_gameObjectManager)
{
	velocity = Vector2(0.0f, 0.0f);
	speed = 10.0f;
	gravity = 0.2f;
	maxFallSpeed = 1.0f;
	isJump = true;
	isSecondJump = false;
	LBtrigger = false;
	RBtrigger = false;
	state = NormalMode;

	handle = LoadGraph("Resource/Texture/apple.png");
	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
}


Framework::Player::~Player() {}

void Framework::Player::Hit(std::shared_ptr<GameObject> other)
{
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);

}

void Framework::Player::PreInitialize()
{
	handle = Game::GetInstance()->GetResourceController()->GetTexture("apple.png");
	//shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(16, 16)), GetThis<GameObject>());
}

bool Framework::Player::Update() {
	Game::GetInstance()->GetResourceController()->GetScreenInformation()->SetScrollModify(transform->GetPosition().GetVector2());
	shp_collisionRect->Update();
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect);
	GetJoypadXInputState(DX_INPUT_PAD1, &xinput);
	Move();
	Jump();
	Throw();
	return true;
}

bool Framework::Player::Move() {
	if (xinput.ThumbLX > 0) {
		velocity.x = 1.0f;
	}
	else if (xinput.ThumbLX < 0) {
		velocity.x = -1.0f;
	}
	else {
		velocity.x = 0.0f;
	}
	transform->localPosition += velocity * speed;
	return true;
}

bool Framework::Player::Jump() {
	//仮置き///着地//////
	if (transform->localPosition.y > 672) {
		isJump = false;
		//isSecondJump = false;
		velocity.y = 0.0f;
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
			velocity.y = -3.0f;
			isSecondJump = true;
			state = NormalMode;
			LBtrigger = true;
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

bool Framework::Player::Throw() {
	//Button[9]…RB
	if (xinput.Buttons[9] && RBtrigger == false) {
		switch (state)
		{
		case NormalMode:
			state = ThrowWaitMode;
			break;
		case ThrowWaitMode:
			state = ThrowMode;
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
		//投げ方向
		Vector2 throwDirection = Vector2(xinput.ThumbRX, xinput.ThumbRY);
		state = NormalMode;
	}

	return true;
}