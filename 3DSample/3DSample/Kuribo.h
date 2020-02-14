#pragma once
#include "GameObject.h"
#include"Resource.h"
#include"Collision2D.h"


namespace Framework {
	class Kuribo :public GameObject
	{
	public:
		Kuribo(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager);
		~Kuribo();
		void Hit(std::shared_ptr<GameObject> other)override;
		void PreInitialize()override;
		bool Update()override;
		bool Release()override;
		std::shared_ptr<Resource_Texture> shp_texture;
		std::shared_ptr<Collision2D_Rectangle>shp_collisionRect;

		std::shared_ptr< Rectangle> GetRectangle() { return shp_collisionRect->rect; }
	private:

		bool Move();

		std::vector< std::shared_ptr<GameObject>> sencerInputs;//0 top, 1 bottom,2 left.3 right

		Vector2  velocity,
			phisicsForce,
			prevVelocity;
		float speed,
			gravity,
			maxFallSpeed,
			overlap;
		bool isGround;

	};
}