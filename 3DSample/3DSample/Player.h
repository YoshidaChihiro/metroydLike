#pragma once
#include "GameObject.h"
#include"Resource.h"
#include"Collision2D.h"
#include"Child.h"
#include "DxLib.h"
#include"Cursol.h"
#include<deque>
#include"MoveHistory.h"
namespace Framework {
	class Player :public GameObject
	{
	public:
		Player(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager);
		~Player();
		void Hit(std::shared_ptr<GameObject> other)override;
		void PreInitialize()override;
		void SetSpawnPoint(Vector3 arg_pos);
		void Initialize()override;
		bool OnUpdate()override;
		bool Release()override;
		void DeletePlayer(int num);
		void AddPlayerChild();
		void UpdateMovingHistory(MoveHistory& arg_playerMoving);
		void UpdateShotHistory(bool arg_shotFlg);
		std::shared_ptr<Resource_Texture> shp_texture;
		std::shared_ptr<Resource_Sound> shp_sound_damage;
		std::shared_ptr<Resource_Sound> shp_sound_jump;
		std::shared_ptr<Resource_Sound> shp_sound_shoot;
		std::shared_ptr<Resource_Sound> shp_sound_throw;
		std::shared_ptr<Resource_Sound> shp_sound_landing;
		std::shared_ptr<Collision2D_Rectangle>shp_collisionRect;

		MoveHistory GetMovingFromHystory(int num);
		bool GetShotHystory(int num);
	private:

		bool Move();
		bool Throw();

		//std::vector< std::shared_ptr<GameObject>> sencerInputs;//0 top, 1 bottom,2 left.3 right

		std::vector< std::shared_ptr<Child>> vec_childs;

		std::shared_ptr<Cursol> shp_cursol;
		std::shared_ptr<Child> shp_throwChild;
		std::deque<MoveHistory>deq_moveHistory;
		std::deque<bool>deq_shotHistory;

		const int HISTORY_COUNT = 300, MAX_PLAYER_COUNT = 10;

	};
}

