#include "Explosion.h"
#include"Game.h"
#include"RelativeTimer.h"
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
}

bool Framework::Explosion::Update()
{
	if (sucide.Update()) {
		SetIsDead(true);
	}
	shp_collisionRect->Update();
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture, 1);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect);
	return true;
}
