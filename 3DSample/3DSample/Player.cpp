#include "Player.h"
#include "Game.h"
#include"Sencer.h"
#include"ParticleEmitter.h"
#include"Cameraman.h"
#include"ObjectDelayCreater.h"
Framework::Player::Player(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager) :GameObject(shp_arg_transform, shp_arg_gameObjectManager)
{
	velocity = Vector2(0.0f, 0.0f);

	phisicsForce = Vector2(0,0);

	tag = ObjectTag::player;
	for (int i = 0; i < HISTORY_COUNT; i++)
	{
		MoveHistory moveH; 
		moveH.position = transform->GetPosition();
		deq_moveHistory.push_front( moveH);
		deq_shotHistory.push_front(false);
	}
	//shp_gameObjectManager = shp_arg_gameObjectManager->GetThis<Transform>();
	//shp_gameObjectManager = ObjectFactory::Create<GameObjectManager>();

}


Framework::Player::~Player() {
}

void Framework::Player::Hit(std::shared_ptr<GameObject> other)
{
//	if (other->GetObjectTag() == ObjectTag::playerBullet) {
//		return;
//	}
//	if (other->GetObjectTag() == ObjectTag::enemy) {
//		SetIsDead(true);
//		return;
//	}
//	if (other->GetObjectTag() == ObjectTag::obstacle) {
//		//
//		auto otherRect = other->GetThis<MapChipObject>()->GetRectangle();
//		float overlap = 0.0f;
//
//		Vector3 delta = (Vector3)(other->transform->GetPosition()-transform->GetPosition());
//
//
//		if (abs( delta.x) <abs( delta.y))
//		{
//			if (delta.y>0) {
//				overlap = shp_collisionRect->rect->GetBottom() - otherRect->GetTop();
//				overlap = abs(overlap);
//				transform->localPosition.y -= overlap;
//
//				isGround = true;
//				//���n
//				phisicsForce.y = 0.0f;
//
//			}
//			else
//			if (delta.y < 0) {
//				overlap = otherRect->GetBottom() - shp_collisionRect->rect->GetTop();
//
//				overlap = abs(overlap);
//				transform->localPosition.y += overlap;
//			}
//		}
//		else if (abs( delta.x) >abs(delta.y)) {
//			if (delta.x>0) {
//				overlap = shp_collisionRect->rect->GetRight() - otherRect->GetLeft();
//				overlap = abs(overlap);
//				transform->localPosition.x -= overlap;
//				velocity.x = 0;
//				phisicsForce.x = 0;
//			}
//			else
//			if (delta.x< 0) {
//				overlap = otherRect->GetRight() - shp_collisionRect->rect->GetLeft();
//				overlap = abs(overlap);
//				transform->localPosition.x += overlap;
//				velocity.x = 0;
//				phisicsForce.x = 0;
//			}
//		}
//		shp_collisionRect->OnUpdate();
//	}
}

void Framework::Player::PreInitialize()
{


	std::vector<ObjectTag> tags;
	tags.push_back(ObjectTag::obstacle);



	shp_texture = ObjectFactory::Create<Resource_Texture>("robo.png", transform, false, false);
	shp_sound_damage = ObjectFactory::Create<Resource_Sound>("Damage.wav", DX_PLAYTYPE_BACK, true);
	shp_sound_jump = ObjectFactory::Create<Resource_Sound>("Jump.wav", DX_PLAYTYPE_BACK, true);
	shp_sound_shoot = ObjectFactory::Create<Resource_Sound>("Shoot.wav", DX_PLAYTYPE_BACK, true);
	shp_sound_throw = ObjectFactory::Create<Resource_Sound>("Throw.wav", DX_PLAYTYPE_BACK, true);
	shp_sound_landing = ObjectFactory::Create<Resource_Sound>("Landing.wav", DX_PLAYTYPE_BACK, true);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(32, 32)), GetThis<GameObject>());

	
	shp_cursol = ObjectFactory::Create<Cursol>(ObjectFactory::Create<Transform>(transform->GetPosition()),transform,manager);
	manager->AddObject_Init(shp_cursol);
	AddChildObject(shp_cursol);
}

void Framework::Player::SetSpawnPoint(Vector3 arg_pos)
{
	for (auto itr = vec_childs.begin(); itr != vec_childs.end(); itr++) {
		(*itr)->transform->localPosition = arg_pos;
	}
	deq_moveHistory.clear();
	deq_shotHistory.clear();
	for (int i = 0; i < HISTORY_COUNT; i++)
	{
		MoveHistory moveH;
		moveH.position = transform->GetPosition();
		deq_moveHistory.push_front(moveH);
		deq_shotHistory.push_front(false);
	}
}

void Framework::Player::Initialize()
{
	
	for (int i = 0; i <
		Game::GetInstance()->GetSceneManager()->GetGameMaster()->GetPlayerChildsCount(); i++) {
		AddPlayerChild();
	}
	AddPlayerChild();
	AddPlayerChild();
	AddPlayerChild(); 
	auto camera = manager->SerchGameObject(ObjectTag::camera);
	if (camera) {
		camera->GetThis<Cameraman_Chase>()->SetTarget((*vec_childs.begin())->transform);
	}
	(*vec_childs.begin())->SetTop();
}

bool Framework::Player::OnUpdate() {
	
	if (vec_childs.size() == 0) {
		SetIsDead(true);
	}
	Throw();
	if (Input::GetKeyDown(KEY_INPUT_A)) {
		AddPlayerChild();
	}
	return true;
}

bool Framework::Player::Release()
{
	vec_childs.clear(); 
	//shp_collisionRect->Releace();
	//shp_collisionRect = nullptr;
	shp_cursol =   nullptr;
	shp_texture = nullptr;
	shp_sound_damage = nullptr;
	shp_sound_jump = nullptr;
	shp_sound_shoot = nullptr;
	shp_sound_throw = nullptr;
	shp_sound_landing = nullptr;
	
	Game::GetInstance()->GetGameTime()->SlowMotion(0.5f,30);

	manager->AddObject(ObjectFactory::Create<ObjectDelayCreater<Player>>(60,ObjectFactory::Create<Transform>(
		Game::GetInstance()->GetSceneManager()->GetGameMaster()->GetRespawnPoint()
		), manager
		));
	Game::GetInstance()->GetSceneManager()->GetGameMaster()->SetPlayerChildsCount(vec_childs.size());
	return true;
}

void Framework::Player::DeletePlayer(int num)
{
	auto itr = vec_childs.begin() + num;
	RemoveChildObject(*itr);
	vec_childs.erase(itr);
	for (int i = 0; i < vec_childs.size(); i ++) {
		vec_childs.at(i)->SetNum(i);
	}
}

void Framework::Player::AddPlayerChild()
{
	//manager->SerchGameObject(ObjectTag::map)->GetThis<Map>()->ChangeGlid(2, 19,26);
	if (vec_childs.size() >Game::GetInstance()->GetSceneManager()->GetGameMaster()->GetChildsMax()) {
		return;
	}

	auto childTransform = ObjectFactory::Create<Transform>(transform->GetPosition() );

	auto child = ObjectFactory::Create<Child>( GetThis<Player>(), childTransform, manager);

	child->SetNum(vec_childs.size());

	AddChildObject(child->GetThis<GameObject>());
	vec_childs.push_back(child->GetThis<Child>());
	manager->AddObject(child);
}

void Framework::Player::UpdateMovingHistory(MoveHistory & arg_playerMoving)
{
	deq_moveHistory.push_front(arg_playerMoving);
	deq_moveHistory.pop_back();
}

void Framework::Player::UpdateShotHistory(bool arg_shotFlg)
{
	deq_shotHistory.push_front(arg_shotFlg);
	deq_shotHistory.pop_back();
}

Framework::MoveHistory Framework::Player::GetMovingFromHystory(int num)
{
	return deq_moveHistory.at(num);
}

bool Framework::Player::GetShotHystory(int num)
{
	return deq_shotHistory.at(num);
}


bool Framework::Player::Move() {
	
	return true;
}

bool Framework::Player::Jump() {
	if (
		(isGround) &&
		Input::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER)) {
		Game::GetInstance()->GetResourceController()->AddSound(shp_sound_jump);
		phisicsForce.y = -15.0f;
	}
	return true;
}

bool Framework::Player::Throw() {
	if (vec_childs.size() == 0) {
		return true;
	}
	if (Input::GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER) && vec_childs.size() >= 2) {
		shp_throwChild = *(vec_childs.begin() + 1);

		shp_throwChild->SetStandby();
	}else
	if (Input::GetButtonUp(XINPUT_BUTTON_RIGHT_SHOULDER) && vec_childs.size() >= 2) {
		
		RemoveChildObject(shp_throwChild);

		shp_throwChild->Throw(shp_cursol->GetWorldTransform());
		vec_childs.erase(vec_childs.begin() + 1);
		for (int i = 0; i < vec_childs.size(); i++) {
			vec_childs.at(i)->SetNum(i);
		}
		shp_throwChild = nullptr;
	}
	return true;
}