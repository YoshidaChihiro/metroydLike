#pragma once
#include "GameObject.h"
#include"Resource.h"
#include"Collision2D.h"


namespace Framework {
	class BatBullet :public GameObject
	{
	public:
		BatBullet(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager);
		~BatBullet();
		void Hit(std::shared_ptr<GameObject> other)override;
		void PreInitialize()override;
		bool OnUpdate()override;

		bool Release()override;
		std::shared_ptr<Resource_Texture> shp_texture;
		std::shared_ptr<Resource_Sound> shp_sound_found;
		std::shared_ptr<Collision2D_Rectangle>shp_collisionRect;

		std::shared_ptr< Rectangle> GetRectangle() { return shp_collisionRect->rect; }
	private:
		bool Move();
		void Dead();
		void DecideTargetPotision();
		void Shot();

		std::shared_ptr<GameObject> player = nullptr;
		//std::vector< std::shared_ptr<GameObject>> sencerInputs;//0 top, 1 bottom,2 left.3 right
		Vector3 floatVec,
			targetPosition;

		float speed, hp,
			gravity,
			maxFallSpeed,
			huwaCounter,
			overlap,
			damage;
		int targetRange,direction;
		bool isGround, isFind,
			isGoalTargetPosition,
			isShot;
		RelativeTimer coolTimer = RelativeTimer(30);

	};
}