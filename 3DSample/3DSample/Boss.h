#pragma once
#include "GameObject.h"
#include"Resource.h"
#include"Collision2D.h"
#include"Bullet.h"
#include "Map.h"

namespace Framework {
	class Boss :public GameObject
	{
	public:
		Boss(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager, std::shared_ptr<Map> shp_arg_map);
		~Boss();
		void Hit(std::shared_ptr<GameObject> other)override;
		void PreInitialize()override;
		bool OnUpdate()override;
		bool Release()override;
		std::shared_ptr<Resource_Texture> shp_texture;
		std::shared_ptr<Collision2D_Rectangle>shp_collisionRect;

	private:
		void Dead();

		bool Move();
		void Bomb();
		void Call();

		std::shared_ptr<GameObject> player = nullptr;
		std::shared_ptr<Map> shp_map;

		Vector2 kuriVec,bombVec;
		Vector3 prevVelocity;

		float speed,
			gravity,
			maxFallSpeed,
			overlap, hp,
			damage;
		bool isGround, isBombShot, isCall;
		int direction;
		RelativeTimer selectTimer = RelativeTimer(60 * 5);
		RelativeTimer bombTimer = RelativeTimer(30);
		RelativeTimer callTimer = RelativeTimer(60);

	};
}