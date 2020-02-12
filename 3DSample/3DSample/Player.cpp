#include "Player.h"
#include "Child.h"
#include "Game.h"
#include"MapChipObject.h"
#include"Sencer.h"
Framework::Player::Player(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager) :GameObject(shp_arg_transform, shp_arg_gameObjectManager)
{
	velocity = Vector2(0.0f, 0.0f);
	speed = 10.0f;
	gravity = 0.2f;
	maxFallSpeed = 1.0f;
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
	if (other->GetTag() == ObjectTag::playerChild|| other->GetTag() == ObjectTag::sencer) {
		return;
	}
	//
	Vector3 mapchipPos = other->transform->GetPosition();
	auto otherRect= other->GetThis<MapChipObject>()->GetRectangle();
	float overlap = 0.0f;

	//player��
	if (sencerInputs[1]==other) {
		overlap = shp_collisionRect->rect->GetBottom()-otherRect->GetTop() ;
			transform->localPosition.y = (int)(transform->localPosition.y-overlap);
			
			//���n
			//velocity.y = 0.0f;
		
	}
	//player��
	if (sencerInputs[0] == other) {
		overlap = otherRect->GetBottom() - shp_collisionRect->rect->GetTop();
			transform->localPosition.y += overlap;
			velocity.y = 0.0f;
	}
	//player��
	if (sencerInputs[3] == other) {
		overlap = shp_collisionRect->rect->GetRight() - otherRect->GetLeft();
			transform->localPosition.x -= overlap;
		
	}
	//player�E
	if (sencerInputs[2] == other) {
		overlap = shp_collisionRect->rect->GetLeft() - otherRect->GetRight();
			transform->localPosition.x -= overlap;
	}
	
}

void Framework::Player::PreInitialize()
{
	auto handle = Game::GetInstance()->GetResourceController()->GetTexture("apple.png");


	std::vector<ObjectTag> tags;
	tags.push_back(ObjectTag::block);

	sencerInputs.push_back(nullptr);
	sencerInputs.push_back(nullptr);
	sencerInputs.push_back(nullptr);
	sencerInputs.push_back(nullptr);


	auto sencerTransform_top = ObjectFactory::Create<Transform>(Vector3(0, -16, 0));
	sencerTransform_top ->baseTransform = (transform);
	auto sencer_top = ObjectFactory::Create<Sencer>(sencerTransform_top, manager, tags, &sencerInputs.at(0));

	auto sencerTransform_bottom = ObjectFactory::Create<Transform>(Vector3(0, 16, 0));
	sencerTransform_bottom ->baseTransform = (transform);
	auto sencer_bottom = ObjectFactory::Create<Sencer>(sencerTransform_bottom, manager, tags, &sencerInputs.at(1));

	auto sencerTransform_left = ObjectFactory::Create<Transform>(Vector3(-16, 0, 0));
		sencerTransform_left->baseTransform = (transform);
	auto sencer_left = ObjectFactory::Create<Sencer>(sencerTransform_left, manager, tags, &sencerInputs.at(2));

	auto sencerTransform_right = ObjectFactory::Create<Transform>(Vector3(16, 0, 0));
	sencerTransform_right->baseTransform = (transform);
	auto sencer_right = ObjectFactory::Create<Sencer>(sencerTransform_right, manager, tags, &sencerInputs.at(3));


	manager->AddObject_Init(sencer_top);
	manager->AddObject_Init(sencer_bottom);
	manager->AddObject_Init(sencer_left);
	manager->AddObject_Init(sencer_right);



	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(16, 16)), GetThis<GameObject>());
}

bool Framework::Player::Update() {
	Game::GetInstance()->GetResourceController()->GetScreenInformation()->SetScrollModify(transform->GetPosition().GetVector2());
	shp_collisionRect->Update();
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture,1);
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
	
	//�d��
	if (!sencerInputs.at(1))
		velocity.y += gravity;
	//�������x����
	if (velocity.y > maxFallSpeed) {
		velocity.y = maxFallSpeed;
	}
	
	return true;
}

bool Framework::Player::Jump() {
	////////////////////

	//Button[8]�cLB
	if (!(sencerInputs.at(1)) && xinput.Buttons[8] && LBtrigger == false) {
		velocity.y = -3.0f;
		LBtrigger = true;
	}
	if (!xinput.Buttons[8]) {
		LBtrigger = false;
	}
	//�W�����v��
	if (sencerInputs.at(1)) {
		//2�i�W�����v
		if (state == ThrowWaitMode && isSecondJump == false && xinput.Buttons[8] && LBtrigger == false) {
			velocity.y = -3.0f;
			isSecondJump = true;
			state = NormalMode;
			LBtrigger = true;
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