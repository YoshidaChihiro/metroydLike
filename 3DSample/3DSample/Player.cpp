#include "Player.h"

#include "Game.h"

Framework::Player::Player(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager) :GameObject(shp_arg_transform, shp_arg_gameObjectManager)
{
	velocity = *new Vector2(0.0f, 0.0f);
	speed = 1.0f;
	gravity = 0.1f;
	maxFallSpeed = 1.0f;
	isJump = true;
	LBtrigger = false;
	state = NormalMode;

	int handle = LoadGraph("Resource/Texture/apple.png");
	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
}


Framework::Player::~Player()
{
}

bool Framework::Player::Update() {
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
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
	else{
		velocity.x = 0.0f;
	}
	transform->localPosition += velocity * speed;
	return true;
}
bool Framework::Player::Jump() {
	//仮置き////////////
	if (transform->localPosition.y > 200.0f) {
		isJump = false;
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
	if(isJump == true) {
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
	if (xinput.Buttons[9]) {
		switch (state)
		{
		case Framework::Player::NormalMode:
			state = ThrowWaitMode;
			break;
		case Framework::Player::ThrowWaitMode:
			state = ThrowMode;
			break;
		case Framework::Player::ThrowMode:
			state = NormalMode;
			break;
		default:
			break;
		}
	}

	return true;
}