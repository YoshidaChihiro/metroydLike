#pragma once
#include "GameObject.h"
#include"Resource.h"
#include"Collision2D.h"

#include "DxLib.h"
namespace Framework {
	enum State
	{
		NormalMode,
		ThrowWaitMode,
		ThrowMode,
	};

	class Player :public GameObject
	{
	public:
		Player(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager);
		~Player();
		void Hit(std::shared_ptr<GameObject> other)override;
		void PreInitialize()override;
		bool Update()override;

		std::shared_ptr<Resource_Texture> shp_texture;
		std::shared_ptr<Collision2D_Rectangle>shp_collisionRect;

	private:
		bool Move();
		bool Jump();
		bool Throw();

		XINPUT_STATE xinput;
		Vector2 velocity;
		float speed,
			gravity,
			maxFallSpeed;
		bool isJump,
			isSecondJump,
			LBtrigger,
			RBtrigger;
		State state;
		int handle;

	};
}

