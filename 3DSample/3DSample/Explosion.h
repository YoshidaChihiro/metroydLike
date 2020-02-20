#pragma once
#include"GameObject.h"
#include"Resource.h"
#include"Collision2D.h"
#include"Bullet.h"
namespace Framework {
	class Explosion :public Bullet
	{
	public:
		Explosion(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager);
		void Hit(std::shared_ptr<GameObject> other)override;
		void PreInitialize()override;
		void Initialize()override;
		//bool OnUpdate()override;
	private:
	}; 
	class EnemyExplosion :public Bullet
	{
	public:
		EnemyExplosion(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager);
		void Hit(std::shared_ptr<GameObject> other)override;
		void PreInitialize()override;
		void Initialize()override;
		//bool OnUpdate()override;
	private:
	};

}