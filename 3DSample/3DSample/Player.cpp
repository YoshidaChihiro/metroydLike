#include "Player.h"
#include "Child.h"
#include "Game.h"

Framework::Player::Player(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager) :GameObject(shp_arg_transform, shp_arg_gameObjectManager)
{
	velocity = Vector2(0.0f, 0.0f);
	prevPosition = Vector2(0.0f, 0.0f);
	speed = 4.0f;
	gravity = 0.2f;
	maxFallSpeed = 1.0f;
	isJump = true;
	isSecondJump = false;
	LBtrigger = false;
	RBtrigger = false;
	state = NormalMode;

	tag = ObjectTag::player;

	//shp_gameObjectManager = shp_arg_gameObjectManager->GetThis<Transform>();
	//shp_gameObjectManager = ObjectFactory::Create<GameObjectManager>();

}


Framework::Player::~Player() {}

void Framework::Player::Hit(std::shared_ptr<GameObject> other)
{
	if (other->GetTag() == ObjectTag::playerChild) {
		return;
	}
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
	if (transform->localPosition.x != prevPosition.x) {
		if (transform->localPosition.x < prevPosition.x) {
			transform->localPosition.x = prevPosition.x;
		}
		else{
			transform->localPosition.x -= velocity.x * speed;
		}
		transform->localPosition.x /= 32.0f;
		transform->localPosition.x *= 32.0f;
	}
	if (transform->localPosition.y != prevPosition.y) {
		if (transform->localPosition.y < prevPosition.y) {
			transform->localPosition.y = prevPosition.y;
		}
		else{
			transform->localPosition.y -= velocity.y * speed;
		}
		transform->localPosition.y /= 32.0f;
		transform->localPosition.y *= 32.0f;
	}
}

void Framework::Player::PreInitialize()
{
	auto handle = Game::GetInstance()->GetResourceController()->GetTexture("apple.png");

	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(16, 16)), GetThis<GameObject>());
}

bool Framework::Player::Update() {
	shp_collisionRect->Update();
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect);
	GetJoypadXInputState(DX_INPUT_PAD1, &xinput);

	prevPosition = transform->localPosition;
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
	//���u��///���n//////
	if (transform->localPosition.y > 672) {
		isJump = false;
		//isSecondJump = false;
		velocity.y = 0.0f;
	}
	////////////////////

	//Button[8]�cLB
	if (isJump == false && xinput.Buttons[8] && LBtrigger == false) {
		velocity.y = -3.0f;
		isJump = true;
		LBtrigger = true;
	}
	if (!xinput.Buttons[8]) {
		LBtrigger = false;
	}
	//�W�����v��
	if (isJump == true) {
		//2�i�W�����v
		if (state == ThrowWaitMode && isSecondJump == false && xinput.Buttons[8] && LBtrigger == false) {
			velocity.y = -3.0f;
			isSecondJump = true;
			state = NormalMode;
			LBtrigger = true;
		}

		//�d��
		velocity.y += gravity;
		//�������x����
		if (velocity.y > maxFallSpeed) {
			velocity.y = maxFallSpeed;
		}
	}

	return true;
}

bool Framework::Player::Throw() {
	//Button[9]�cRB
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

	//����
	if (state == ThrowMode) {
		//��������
		Vector2 throwDirection = Vector2(xinput.ThumbRX, xinput.ThumbRY);
		state = NormalMode;
	}

	return true;
}