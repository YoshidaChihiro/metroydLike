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
		void PreInitialize()override;
		void Initialize()override;
		bool Update()override;
		std::shared_ptr<Resource_Texture> shp_texture;
		std::shared_ptr<Collision2D_Rectangle>shp_collisionRect;

	private:

		bool Move();
		bool Throw();

		XINPUT_STATE xinput;
		Vector2 velocity,
			prevPosition,
			throwDirection;

		std::shared_ptr<Transform> shp_player_transform;

		int delay,waitPointDistance;

		float speed,
			gravity,
			maxFallSpeed,
			groundHeight;
		bool
			isChase,
			LBtrigger,
			RBtrigger;
		enum State {
			NormalMode,
			ThrowWaitMode,
			ThrowMode,
			FixMode,
		};
		State state;
		int lastSide;
	};
}
