#pragma once
#include "GameObject.h"
#include"Resource.h"
#include"Collision2D.h"
#include "DxLib.h"
#include"MoveHistory.h"
namespace Framework {
	class Player;
	struct MoveHistory;
	class Child :public GameObject
	{
	public:
		Child( std::shared_ptr<Player> shp_arg_player, std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager);
		~Child();
		void Hit(std::shared_ptr<GameObject> other)override;
		void Dead();
		bool Release()override;
		void SetMoveHistory(MoveHistory arg_History);
		void SetFrontPos_dontMove();
		void PreInitialize()override;
		void Initialize()override;
		void SetTop() {
			isTop = true;
			movePattern = MovePattern::relative;
		}
		void Controll();
		bool OnUpdate()override;
		std::shared_ptr<Resource_Texture> shp_texture;
		std::shared_ptr<Collision2D_Rectangle>shp_collisionRect;
		virtual bool Throw(std::shared_ptr<Transform> arg_target);
		void SetNum(int arg_num);
		int GetNum() {
			return num;
		}
		void SetStandby();
	private:

		//std::vector< std::shared_ptr<GameObject>> sencerInputs;//0 top, 1 bottom,2 left.3 right
		bool Move();
		bool Jump();
		void Shoot();
		void Shot();
		void CheckGoal();
		Vector3 targetPosition;
		MoveHistory history;

		const int HISTORY_DELAY = 18;
		std::shared_ptr<Player> shp_player;

		void CreateBlock();

		int direction;

		float speed,damage,
			gravity,
			maxFallSpeed,
			groundHeight;
		bool
			isTop, isThrown,isStandby,isGround,isShot;
		int num;
		RelativeTimer changeTimer=RelativeTimer(0);
		RelativeTimer coolTimer = RelativeTimer(10);
	};
}
