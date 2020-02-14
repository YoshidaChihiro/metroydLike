#pragma once
#include "GameObject.h"
#include"Resource.h"
#include"Collision2D.h"
#include"Child.h"
#include "DxLib.h"
#include"Cursol.h"
namespace Framework {

	class Player :public GameObject
	{
	public:
		Player(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager);
		~Player();
		void Hit(std::shared_ptr<GameObject> other)override;
		void PreInitialize()override;
		void Initialize()override;
		bool Update()override;
		bool Release()override;
		void AddPlayerChild();
		std::shared_ptr<Resource_Texture> shp_texture;
		std::shared_ptr<Collision2D_Rectangle>shp_collisionRect;

	private:
		std::shared_ptr<Transform> shp_gameObjectManager;

		bool Move();
		bool Jump();
		bool Throw();

		std::vector< std::shared_ptr<GameObject>> sencerInputs;//0 top, 1 bottom,2 left.3 right

		std::vector< std::shared_ptr<Child>> vec_childs;

		std::shared_ptr<Cursol> shp_cursol;

		Vector2  velocity,
			phisicsForce;
		float speed,
			gravity,
			maxFallSpeed;
		bool isGround,
			isSecondJump;

	};
}

