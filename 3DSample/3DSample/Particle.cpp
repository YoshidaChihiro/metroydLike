#include "Particle.h"
#include"GameObjectManager.h"
#include "Game.h"

Framework::Particle::Particle(int graphHandle, float layer, std::shared_ptr<Transform> arg_shp_transform, Vector3 arg_moveVelocity, float arg_speed,Vector3 arg_rotatePase,Vector3 arg_extentionPase, float arg_accelation, Vector3 arg_phisicsForce, size_t lifeSpan, std::shared_ptr<GameObjectManager> arg_manager)
	:GameObject(arg_shp_transform->GetThis<Transform>(),arg_manager),
	rotatePase(arg_rotatePase), moveVelocity(arg_moveVelocity), speed(arg_speed), phisicsForce(arg_phisicsForce), extentionPase(arg_extentionPase), lifeSpan(lifeSpan), accelation(arg_accelation)
{
	shp_resource_texture = ObjectFactory::Create<Resource_Texture>(graphHandle,transform,false,false);
}

Framework::Particle::Particle(Vector4 color, float layer, std::shared_ptr<Transform> arg_shp_transform, Vector3 arg_moveVelocity, float arg_speed, Vector3 arg_rotatePase, Vector3 arg_extentionPase, float arg_accelation, Vector3 arg_phisicsForce, size_t lifeSpan, std::shared_ptr<GameObjectManager> arg_manager)
	:GameObject(arg_shp_transform->GetThis<Transform>(), arg_manager),
	rotatePase(arg_rotatePase), moveVelocity(arg_moveVelocity), speed(arg_speed), phisicsForce(arg_phisicsForce), extentionPase(arg_extentionPase), lifeSpan(lifeSpan), accelation(arg_accelation)
{
	shp_resource_texture = ObjectFactory::Create<Resource_Pixel>(color, transform);
}

bool Framework::Particle::Update()
{
	lifeSpan--;
	if (lifeSpan <= 0) {
		SetIsDead( true);
	}
	transform->localPosition += moveVelocity*speed+phisicsForce;
	transform->rotation += rotatePase;
	transform->scale += extentionPase;
	Game::GetInstance()->GetResourceController()->AddGraph(shp_resource_texture);
	speed *= accelation;
	return true;
}

Framework::Particle::~Particle()
{
}
