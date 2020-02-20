#pragma once
#include "Bullet.h"
#include"Game.h"

Framework::Bullet::Bullet(int arg_direction, int arg_speed, std::shared_ptr<Transform> arg_shp_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:GameObject(arg_shp_transform->GetThis<Transform>(),arg_manager->GetThis<GameObjectManager>()),direction(arg_direction),speed(arg_speed)
	,sucideTimer(RelativeTimer(180))
{
	velocity = Vector3(direction*speed, 0, 0);
	sucideTimer.Start();
}

bool Framework::Bullet::Release()
{
	shp_collisionRect->Releace();
	shp_collisionRect = nullptr;
	return true;
}


bool Framework::Bullet::OnUpdate()
{

	shp_collisionRect->OnUpdate();
	if(shp_texture)
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture, 1);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect,collisionLayer);
	if (sucideTimer.Update()) {
		SetIsDead(true);
	}
	return true;
}

void Framework::Bullet::Hit(std::shared_ptr<GameObject> other)
{
	if(other->GetObjectTag()!=ObjectTag::spawner)
	SetIsDead(true);
}


Framework::PlayerBullet::PlayerBullet(float arg_damage, int arg_direction, int arg_speed, std::shared_ptr<Transform> arg_shp_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:Bullet(arg_direction,arg_speed,arg_shp_transform,arg_manager)
{
	damage = arg_damage;
	tag = ObjectTag::playerBullet;
}

Framework::PlayerBullet::~PlayerBullet()
{
}

void Framework::PlayerBullet::Initialize()
{
	auto handle = Game::GetInstance()->GetResourceController()->GetTexture("bullet.png");

	collisionLayer = 3;


	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(8, 8, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(32, 32)), GetThis<GameObject>());
	vec_gameComponents.push_back(shp_collisionRect->GetThis<GameComponent>());
}

void Framework::PlayerBullet::PreInitialize()
{
}


Framework::EnemyBullet::EnemyBullet(float arg_damage, int arg_direction, int arg_speed, std::shared_ptr<Transform> arg_shp_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:Bullet(arg_direction, arg_speed, arg_shp_transform, arg_manager)
{
	damage = arg_damage;
	tag = ObjectTag::enemyBullet;
}

void Framework::EnemyBullet::Initialize()
{
	collisionLayer = 4;
	auto handle = Game::GetInstance()->GetResourceController()->GetTexture("enemyBullet.png");
	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(8, 8, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(32, 32)), GetThis<GameObject>());
	vec_gameComponents.push_back(shp_collisionRect->GetThis<GameComponent>());
}

void Framework::EnemyBullet::PreInitialize()
{
}

Framework::EnemyBomb::EnemyBomb(float arg_damage, int arg_direction, int arg_speed, int arg_force, std::shared_ptr<Transform> arg_shp_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:Bullet(arg_direction, arg_speed, arg_shp_transform, arg_manager)
{
	damage = arg_damage;
	phisicsForce = arg_force;
}

void Framework::EnemyBomb::Initialize()
{
	collisionLayer = 4;
	auto handle = Game::GetInstance()->GetResourceController()->GetTexture("enemyBomb.png");
	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(8, 8, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(32, 32)), GetThis<GameObject>());
	vec_gameComponents.push_back(shp_collisionRect->GetThis<GameComponent>());
}

void Framework::EnemyBomb::PreInitialize()
{
}

bool Framework::EnemyBomb::OnUpdate()
{
	phisicsForce+=0.2f;
	velocity = Vector3(direction*speed, phisicsForce, 0);

	shp_collisionRect->OnUpdate();
	if (shp_texture)
		Game::GetInstance()->GetResourceController()->AddGraph(shp_texture, 1);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect, collisionLayer);
	if (sucideTimer.Update()) {
		SetIsDead(true);
	}
	return true;
}