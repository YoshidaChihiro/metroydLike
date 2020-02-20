#pragma once
#include"GameObjectManager.h"
#include"RelativeTimer.h"
namespace Framework {
	class Bullet:public GameObject
	{
	public:
		Bullet(int arg_direction,int arg_speed,std::shared_ptr<Transform> arg_shp_transform,std::shared_ptr<GameObjectManager> arg_manager);
		
		bool Release()override;
		bool OnUpdate()override;
		void Hit(std::shared_ptr<GameObject>other)override;
		std::shared_ptr<Resource_Texture> shp_texture;
		std::shared_ptr<Collision2D_Rectangle>shp_collisionRect;
		int direction,speed,collisionLayer;
		float damage;
		RelativeTimer sucideTimer;
	};
	class PlayerBullet :public Bullet {
	public:
		PlayerBullet(float arg_damage, int arg_direction, int arg_speed, std::shared_ptr<Transform> arg_shp_transform, std::shared_ptr<GameObjectManager> arg_manager);
		~PlayerBullet();
		void Initialize()override;
		void PreInitialize()override;
	};
	class EnemyBullet :public Bullet {
	public:
		EnemyBullet(float arg_damage, int arg_direction, int arg_speed, std::shared_ptr<Transform> arg_shp_transform, std::shared_ptr<GameObjectManager> arg_manager);
		void Initialize()override;
		void PreInitialize()override;
	};
	class EnemyBomb :public Bullet {
	public:
		EnemyBomb(float arg_damage,int arg_direction, int arg_speed, std::shared_ptr<Transform> arg_shp_transform, std::shared_ptr<GameObjectManager> arg_manager);
		void Initialize()override;
		void PreInitialize()override;
	};
}