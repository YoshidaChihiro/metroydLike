#pragma once
#include "Collision2D.h"
#include <vector>
namespace Framework {
	class Collision2DManager
	{
	public:
		Collision2DManager();
		~Collision2DManager();
		bool Update();
		void AddCollision(std::shared_ptr<Collision2D_Base> add,int layer=0);
		void Release();
	private:
		std::vector< std::vector<std::shared_ptr< Collision2D_Base>>> vec_collision2Ds;
	};

}