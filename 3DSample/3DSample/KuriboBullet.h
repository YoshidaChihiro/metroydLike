#pragma once
#include "GameObject.h"
#include"Resource.h"
#include"Collision2D.h"
#include"Bullet.h"
#include "Map.h"

namespace Framework {
	class KuriboBullet :public GameObject
	{
	public:
		KuriboBullet(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager, std::shared_ptr<Map> shp_arg_map);
		~KuriboBullet();
		void Hit(std::shared_ptr<GameObject> other)override;
		void PreInitialize()override;
		bool OnUpdate()override;
		bool Release()override;
		std::shared_ptr<Resource_Texture> shp_texture;
		std::shared_ptr<Resource_Sound> shp_sound_found;
		std::shared_ptr<Collision2D_Rectangle>shp_collisionRect;

		//std::shared_ptr< Rectangle> GetRectangle() { return shp_collisionRect->rect; }
	private:
		void Dead();

		bool Move();
		void Shot();

		std::shared_ptr<GameObject> player = nullptr;
		std::shared_ptr<Map> shp_map;


		//std::vector< std::shared_ptr<GameObject>> sencerInputs;//0 top, 1 bottom,2 left.3 right

		Vector2 kuriVec;
		Vector3 prevVelocity;

		float speed,
			gravity,
			maxFallSpeed,
			overlap, hp,
			damage;
		bool isGround, isFind,isShot;
		int direction;
		RelativeTimer coolTimer = RelativeTimer(30);

	};
}