#include "Explosion.h"
#include"Game.h"
#include"RelativeTimer.h"
#include"ParticleEmitter.h"
Framework::Explosion::Explosion(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager)
	:GameObject(shp_arg_transform, shp_arg_gameObjectManager),
	sucide(Timer(60)) {
	tag =ObjectTag::playerBullet;
	sucide.Start();
}

void Framework::Explosion::Hit(std::shared_ptr<GameObject> other)
{

}

void Framework::Explosion::PreInitialize()
{
	shp_texture = ObjectFactory::Create<Resource_Texture>("apple.png", transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(64, 64, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(16, 16)), GetThis<GameObject>());

}

void Framework::Explosion::Initialize()
{
	int handle = Game::GetInstance()->GetResourceController()->GetTexture("orangeParticle.png");

	auto p_param = new ParticleEmitterParameter();
	p_param->graphHandle = handle;
	p_param->layer = 2;
	p_param->range_maxSpeed = 10;
	p_param->range_minSpeed = 5;
	p_param->range_maxLifeSpan = 30;
	p_param->range_minLifeSpan = 10;
	p_param->range_maxRotation.z = 360;
	p_param->range_minRotation.z = 0;
	p_param->range_maxEmitCount = 20;
	p_param->range_minEmitCount = 10;
	p_param->emitSpan = 2;
	p_param->emitterLifeSpan = 10;
	manager->AddObject(ObjectFactory::Create<ParticleEmitter>(transform->GetThis<Transform>(), p_param, manager
		));
}

bool Framework::Explosion::Update()
{
	if (sucide.Update()) {
		SetIsDead(true);
	}
	shp_collisionRect->Update();
	//Game::GetInstance()->GetResourceController()->AddGraph(shp_texture, 1);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect);
	return true;
}
