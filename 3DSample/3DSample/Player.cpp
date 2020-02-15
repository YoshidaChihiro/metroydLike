#include "Player.h"
#include "Game.h"
#include"Sencer.h"
#include"ParticleEmitter.h"
#include"Cameraman.h"
#include"ObjectDelayCreater.h"
Framework::Player::Player(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager) :GameObject(shp_arg_transform, shp_arg_gameObjectManager)
{
	velocity = Vector2(0.0f, 0.0f);
	speed = 5.0f;
	gravity = 0.6f;
	maxFallSpeed = 6.0f;
	isSecondJump = false;

	phisicsForce = Vector2(0,0);

	tag = ObjectTag::player;

	//shp_gameObjectManager = shp_arg_gameObjectManager->GetThis<Transform>();
	//shp_gameObjectManager = ObjectFactory::Create<GameObjectManager>();

}


Framework::Player::~Player() {
}

void Framework::Player::Hit(std::shared_ptr<GameObject> other)
{
	if (other->GetObjectTag() == ObjectTag::playerBullet) {
		return;
	}
	if (other->GetObjectTag() == ObjectTag::enemy) {
		SetIsDead(true);
		return;
	}
	if (other->GetObjectTag() == ObjectTag::obstacle) {
		//
		auto otherRect = other->GetThis<MapChipObject>()->GetRectangle();
		float overlap = 0.0f;

		Vector3 delta = (Vector3)(other->transform->GetPosition()-transform->GetPosition());


		if (abs( delta.x) <abs( delta.y))
		{
			if (delta.y>0) {
				overlap = shp_collisionRect->rect->GetBottom() - otherRect->GetTop();
				overlap = abs(overlap);
				transform->localPosition.y -= overlap;

				isGround = true;
				//���n
				phisicsForce.y = 0.0f;

			}
			else
			if (delta.y < 0) {
				overlap = otherRect->GetBottom() - shp_collisionRect->rect->GetTop();

				overlap = abs(overlap);
				transform->localPosition.y += overlap;
			}
		}
		else if (abs( delta.x) >abs(delta.y)) {
			if (delta.x>0) {
				overlap = shp_collisionRect->rect->GetRight() - otherRect->GetLeft();
				overlap = abs(overlap);
				transform->localPosition.x -= overlap;
				velocity.x = 0;
				phisicsForce.x = 0;
			}
			else
			if (delta.x< 0) {
				overlap = otherRect->GetRight() - shp_collisionRect->rect->GetLeft();
				overlap = abs(overlap);
				transform->localPosition.x += overlap;
				velocity.x = 0;
				phisicsForce.x = 0;
			}
		}
		shp_collisionRect->Update();
	}
}

void Framework::Player::PreInitialize()
{


	std::vector<ObjectTag> tags;
	tags.push_back(ObjectTag::obstacle);



	shp_texture = ObjectFactory::Create<Resource_Texture>("apple.png", transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(32, 32)), GetThis<GameObject>());
	
	shp_cursol = ObjectFactory::Create<Cursol>(ObjectFactory::Create<Transform>(transform->GetPosition()),transform,manager);
	manager->AddObject_Init(shp_cursol);
	AddChildObject(shp_cursol);
}

void Framework::Player::Initialize()
{
	auto camera = manager->SerchGameObject(ObjectTag::camera);
	if (camera) {
		camera->GetThis<Cameraman_Chase>()->SetTarget(transform);
	}
	for (int i = 0; i <
		Game::GetInstance()->GetSceneManager()->GetGameMaster()->GetPlayerChildsCount(); i++) {
		AddPlayerChild();
	}
}

bool Framework::Player::Update() {
	
	Jump();
	Move();
	Throw();
	if (Input::GetKeyDown(KEY_INPUT_A)) {
		AddPlayerChild();
	}
	if (Input::GetKeyDown(KEY_INPUT_D)) {
		SetIsDead(true);
	}
	shp_collisionRect->Update();
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture, 1);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect);
	isGround = false;
	return true;
}

bool Framework::Player::Release()
{

	shp_collisionRect->Releace();
	shp_collisionRect = nullptr;
	shp_cursol =   nullptr;
	shp_texture = nullptr;
	
	manager->AddObject(ObjectFactory::Create<ObjectDelayCreater<Player>>(60,ObjectFactory::Create<Transform>(
		Game::GetInstance()->GetSceneManager()->GetGameMaster()->GetRespawnPoint()
		), manager
		));
	Game::GetInstance()->GetSceneManager()->GetGameMaster()->SetPlayerChildsCount(vec_childs.size());
	return true;
}

void Framework::Player::AddPlayerChild()
{
	//manager->SerchGameObject(ObjectTag::map)->GetThis<Map>()->ChangeGlid(2, 19,26);
	if (vec_childs.size() >Game::GetInstance()->GetSceneManager()->GetGameMaster()->GetChildsMax()) {
		return;
	}

	auto childTransform = ObjectFactory::Create<Transform>(transform->GetPosition());

	auto child = ObjectFactory::Create<Child>(50 + 50 * vec_childs.size(), 40, transform, childTransform, manager);



	AddChildObject(child->GetThis<GameObject>());
	vec_childs.push_back(child->GetThis<Child>());
	manager->AddObject(child);
}


bool Framework::Player::Move() {
	velocity.x = Input::GetLettStickHolizon();
	
	//velocity.y =-1* Input::GetLettStickVertical();
	velocity.Normalize();
	transform->localPosition +=((Vector2) (velocity * speed)) + ((Vector2)(phisicsForce));
	
		phisicsForce.y += gravity;
	if (phisicsForce.y > maxFallSpeed) {
		phisicsForce.y = maxFallSpeed;
	}
	
	return true;
}

bool Framework::Player::Jump() {
	if (
		(isGround) &&
		Input::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER)) {
		phisicsForce.y = -15.0f;
	}
	return true;
}

bool Framework::Player::Throw() {
	if (vec_childs.size() == 0) {
		return true;
	}
	if (Input::GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER)) {
		auto throwChild = vec_childs.begin();
		RemoveChildObject(vec_childs.at(0));
		(*throwChild)->Throw(shp_cursol->GetWorldTransform());
		vec_childs.erase(vec_childs.begin());
		for (int i = 0; i < vec_childs.size(); i++) {
			vec_childs.at(i)->SetDelay(50 + 50 * i);
		}

	}
	return true;
}