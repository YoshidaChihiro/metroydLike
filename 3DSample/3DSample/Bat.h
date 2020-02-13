#pragma once
#include "GameObject.h"
#include"Resource.h"
#include"Collision2D.h"


namespace Framework {
	class Bat :public GameObject
	{
	public:
		Bat(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager);
		~Bat();
		void Hit(std::shared_ptr<GameObject> other)override;
		void PreInitialize()override;
		bool Update()override;

		std::shared_ptr<Resource_Texture> shp_texture;
		std::shared_ptr<Collision2D_Rectangle>shp_collisionRect;

	private:
		std::shared_ptr<Transform> shp_gameObjectManager;

		bool Move();

		std::vector< std::shared_ptr<GameObject>> sencerInputs;//0 top, 1 bottom,2 left.3 right

		Vector2  velocity,
			phisicsForce;
		float speed,
			gravity,
			maxFallSpeed,
			flapCounter,
			huwaCounter;
		bool isGround,
			isBound;

	};
}