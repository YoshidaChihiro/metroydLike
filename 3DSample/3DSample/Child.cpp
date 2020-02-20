#include "Child.h"
#include "Game.h"
#include"GameObjectManager.h"
#include"Sencer.h"
#include"ParticleEmitter.h"
#include"Bullet.h"
Framework::Child::Child( std::shared_ptr<Player> shp_arg_player, std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager)
	:GameObject(shp_arg_transform, shp_arg_gameObjectManager->GetThis<GameObjectManager>())
{
	shp_player = shp_arg_player->GetThis<Player>();
	movePattern = MovePattern::abs;
	tag = ObjectTag::supporter;
	isThrown = false;
	direction = 1;
}

Framework::Child::~Child() {}

void Framework::Child::Hit(std::shared_ptr<GameObject> other)
{
	if (!isThrown&&other->GetObjectTag() == ObjectTag::enemy) {
		damage += 0.02f;
		return;
	}
	if (other->GetObjectTag() == ObjectTag::enemyBullet) {
		damage += 0.02f;
		return;
	}
	if ((isTop || isThrown) &&other->GetObjectTag() == ObjectTag::obstacle) {

		

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
			//shp_collisionRect->OnUpdate();
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
		shp_collisionRect->OnUpdate();
		if (isThrown) {
			CreateBlock();
		}
	}
}

void Framework::Child::Dead()
{
	SetIsDead(true);
	shp_player->DeletePlayer(num); 
	{

		int handle = Game::GetInstance()->GetResourceController()->GetTexture("orangeParticle.png");
		auto p_param = new ParticleEmitterParameter();
		p_param->graphHandle = handle;
		p_param->range_maxVelocity = Vector3(0.5f, 0, 0);
		p_param->range_minVelocity = Vector3(-0.5f, -1, 0);
		p_param->layer = 2;
		p_param->range_maxSpeed = 10;
		p_param->range_minSpeed = 5;
		p_param->range_maxLifeSpan = 100;
		p_param->range_minLifeSpan = 50;
		p_param->range_maxRotation.z = 360;
		p_param->range_minRotation.z = 0;
		p_param->range_maxEmitCount = 20;
		p_param->range_minEmitCount = 10;
		p_param->range_maxPhisicsForce = Vector3(0, 0.2f, 0);
		p_param->range_minPhisicsForce = Vector3(0, 0.2f, 0);
		p_param->emitSpan = 2;
		p_param->emitterLifeSpan = 10;
		manager->AddObject(ObjectFactory::Create<ParticleEmitter>(transform->GetThis<Transform>(), p_param, manager
			));

	}
}

bool Framework::Child::Release()
{
	shp_collisionRect->Releace();
	shp_collisionRect = nullptr;
	shp_texture = nullptr;
	shp_sound_explosion = nullptr;
	return true;
}

void Framework::Child::SetMoveHistory(MoveHistory arg_History)
{
	history = arg_History;
}


void Framework::Child::SetFrontPos_dontMove()
{
	//frontPos = transform->GetPosition();
}

void Framework::Child::PreInitialize()
{
	auto handle = Game::GetInstance()->GetResourceController()->GetTexture("child.png");
	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(16, 16)), GetThis<GameObject>());

	shp_sound_explosion = ObjectFactory::Create<Resource_Sound>("Explosion.wav", DX_PLAYTYPE_BACK, true);

	

}

void Framework::Child::Initialize()
{
	velocity = Vector3(0.0f, 0.0f,0.0f);
	speed = 4.0f;
	gravity = 0.3f;
	maxFallSpeed = 5.0f;
	collisionLayer = 1;
	//groundHeight = 672.0f;
}

void Framework::Child::Controll()
{
	Jump();
	velocity.x = Input::GetLettStickHolizon();
	
	if (velocity.x < 0) {
		direction = -1;
	}else if (velocity.x > 0) {
		direction = 1;
	}
	

	//velocity.y =-1* Input::GetLettStickVertical();
	velocity.Normalize();
	velocity *= speed;

	if (Input::GetButtonDown(XINPUT_BUTTON_A)) {
		Dead();
	}

	if (Input::GetRightTrigger()) {
		isShot = true;
		coolTimer.Start();
	}
	else {
		coolTimer.Stop();
		coolTimer.Reset();
	}
	

	if (!isGround || velocity.x != 0 || phisicsForce.y != 0) {
		MoveHistory moveHistory = MoveHistory();
		moveHistory.position = transform->localPosition;
		moveHistory.direction = direction;
		shp_player->UpdateMovingHistory(moveHistory);
	}
	shp_player->UpdateShotHistory(isShot);
	phisicsForce.y += gravity;
	if (phisicsForce.y > maxFallSpeed) {
		phisicsForce.y = maxFallSpeed;
	}
}

bool Framework::Child::OnUpdate() {
	if (isTop) {
		Controll();
	}
	else
	if (!isStandby) {
		Move();
	}

	else if(isThrown)
	{
		Shoot();
		CheckGoal();
	}

	if (damage > 2.0f) {
		Dead();
	}

	if (direction>0) {
		shp_texture->xFlip = false;
	}
	else if (direction<0) {
		shp_texture->xFlip = true;

	}
	if (isShot) {
		Shot();
	}
	shp_collisionRect->OnUpdate();
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
	if (changeTimer.Update()) {
		collisionLayer = 5;
		shp_collisionRect->SetRect(20, 20);
	}
	if(isThrown||isTop)
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect,collisionLayer);
	isGround = false;
	return true;
}


bool Framework::Child::Throw(std::shared_ptr<Transform> arg_target)
{
	changeTimer = RelativeTimer(5);
	changeTimer.Start();
	isThrown = true;
	collisionLayer = 3;
	velocity = arg_target->GetPosition().GetVector2()- transform->GetPosition().GetVector2();
	targetPosition = arg_target->GetPosition();
	velocity.Normalize();
	transform->localPosition = transform->GetPosition();
	transform->baseTransform = nullptr;
	return true;
}

void Framework::Child::SetNum(int arg_num) {
	num = arg_num;
	if (num == 0) {
		SetTop();
		transform = shp_player->transform;
		shp_texture->transform = transform;
	}
}

void Framework::Child::SetStandby() {
	isStandby = true;
	transform->localPosition = Vector3(0, -40, 0);
	transform->baseTransform = shp_player->transform;
}

bool Framework::Child::Move() {
	history = shp_player->GetMovingFromHystory(num*HISTORY_DELAY);
	isShot = shp_player->GetShotHystory(num*HISTORY_DELAY);
	transform->localPosition = history.position ;
	direction = history.direction;

	if (isShot) {
		isShot = true;
		coolTimer.Start();
	}
	else {
		coolTimer.Stop();
		coolTimer.Reset();
	}
	return true;
}

bool Framework::Child::Jump()
{
	if (
		(isGround) &&
		Input::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER)) {
		phisicsForce.y = -9.0f;
		
	}
	return true;
}

void Framework::Child::Shoot()
{
	if (!isThrown&& changeTimer.Update()) {

		isThrown = true;
		tag = ObjectTag::none;
	}
	velocity.Normalize();
	velocity *= speed;
}

void Framework::Child::Shot()
{
	if (!coolTimer.Update()) {
		isShot = false;
		return;

	}
	auto bulletTransform = ObjectFactory::Create<Transform>(transform->GetPosition());
	manager->AddObject(ObjectFactory::Create<PlayerBullet>(1.0f+damage,5,direction,bulletTransform,manager));
}

void Framework::Child::CheckGoal()
{
	auto targetVec2 = targetPosition.GetVector2();
	auto distance = transform->GetPosition().GetVector2().GetDistance(targetVec2);
	if (distance < 5) {
		CreateBlock();
	}
}

void Framework::Child::CreateBlock()
{
	if (GetIsDead()) {
		return;
	}
	int glidSize = Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize();
	int x = ((transform->GetPosition().x)+glidSize/2) / (float)glidSize;
	int y = (transform->GetPosition().y+glidSize/2 )/(float) glidSize;

	int playerX = (shp_player->transform->GetPosition().x / (float)32);
	int playerY = (shp_player->transform->GetPosition().y / (float)32);

	if (playerX == x && playerY == y) {
		y -= 1;
	}

	manager->SerchGameObject(ObjectTag::map)->GetThis<Map>()->ChangeGlid(x, y, 5);

	
	SetIsDead(true);
}

