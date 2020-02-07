#pragma once
#include "GameObject.h"
#include"Resource.h"

#include "DxLib.h"
namespace Framework {
	class Player:public GameObject
	{
	public:
		Player(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager);
		~Player();
		bool Update()override;
		std::shared_ptr<Resource_Texture> shp_texture;
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
			LBtrigger;
		enum State
		{
			NormalMode,
			ThrowWaitMode,
			ThrowMode,
		};
		State state;
	};
}

