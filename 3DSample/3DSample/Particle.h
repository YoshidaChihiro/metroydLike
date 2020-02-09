#pragma once
#include"GameObject.h"
#include "Resource.h"
namespace Framework {
	class Particle:public GameObject
	{

	public:
		Particle(int graphHandle, float layer, std::shared_ptr<Transform> arg_shp_transform,Vector3 arg_moveVelocity, float arg_speed, float arg_rotatePase, float arg_extentionPase, float arg_accelation, Vector3  arg_phisicsForce, size_t lifeSpan,std::shared_ptr<GameObjectManager> arg_manager);
		bool Update()override;
		~Particle()override;
	private:
		Vector3 moveVelocity;
		Vector3 phisicsForce;
		float extentionPase;
		float speed;
		float accelation;
		float rotatePase;
		size_t lifeSpan;
		std::shared_ptr<Resource_Texture>shp_resource_texture;
	};

}