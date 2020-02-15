#pragma once
#include "GameObject.h"
#include"Resource.h"
#include"Collision2D.h"
#include "DxLib.h"

namespace Framework {
	class Child :public GameObject
	{
	public:
		Child( int delay,int waitDistance,std::shared_ptr<Transform> shp_arg_player_transform, std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager);
		~Child();
		void Hit(std::shared_ptr<GameObject> other)override;
		bool Release()override;
		void PreInitialize()override;
		void Initialize()override;
		bool Update()override;
		std::shared_ptr<Resource_Texture> shp_texture;
		std::shared_ptr<Collision2D_Rectangle>shp_collisionRect;
		void SetDelay(int arg_delay);
		virtual bool Throw(std::shared_ptr<Transform> arg_target);
	private:

		//std::vector< std::shared_ptr<GameObject>> sencerInputs;//0 top, 1 bottom,2 left.3 right
		bool Move();
		void Shoot();
		void CheckGoal();
		Vector3 velocity,targetPosition;

		std::shared_ptr<Transform> shp_player_transform;

		void CreateBlock();

		int delay,waitPointDistance;

		float speed,
			gravity,
			maxFallSpeed,
			groundHeight;
		bool
			isChase, isThrown;
		int lastSide;
	};
}
