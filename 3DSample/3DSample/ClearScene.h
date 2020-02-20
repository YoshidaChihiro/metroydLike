#pragma once
#include"IScene.h"
#include"Map.h"
#include"Board.h"
namespace Framework {
	class ClearScene :public IScene
	{
	public:
		ClearScene();
		~ClearScene();
		void Initialize()override;

		void PreInitialize()override;

		bool Update()override;

		void OnSet()override;

		void Release()override;
	private:
		long long time;
		int score;
		std::shared_ptr<Map> shp_map;
		std::shared_ptr<Board> shp_scoreBoard;
		std::shared_ptr<Board> shp_timeBoard;
		std::vector<int> vec_scoreRanking;
		std::vector<int> vec_timeRanking;
	};

}