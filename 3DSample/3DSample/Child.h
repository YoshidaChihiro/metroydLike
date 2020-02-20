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
		std::shared_ptr<Resource_Sound> shp_sound_damage;
		std::shared_ptr<Resource_Sound> shp_sound_jump;
		std::shared_ptr<Resource_Sound> shp_sound_shoot;
		std::shared_ptr<Resource_Sound> shp_sound_throw;
		std::shared_ptr<Resource_Sound> shp_sound_landing;
		std::shared_ptr<Resource_Sound> shp_sound_change;
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
		void Animation();
		Vector3 targetPosition;
		MoveHistory history;

		const int HISTORY_DELAY = 6;
		std::shared_ptr<Player> shp_player;

		void CreateBlock();

		int direction;

		float verticalExt = 1.0f;
		float horizontalExt = 1.0f;
		float speed,damage,
			gravity,
			maxFallSpeed,
			groundHeight;
		bool
			isTop, isThrown,isStandby,isGround,isShot,isLeftWall,isRightWall;
		int animDirection=1;
		int num,collisionLayer;
		RelativeTimer changeTimer=RelativeTimer(3);
		RelativeTimer coolTimer = RelativeTimer(10);
	};
}
