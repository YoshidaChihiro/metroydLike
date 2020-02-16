#pragma once
#include"Util.h"
#include "ButiMath.h"
#include"GameComponent.h"
namespace Framework {
	class GameObject;
	class Collision2D_Base :public GameComponent
	{
	public:
		virtual bool IsHit(std::shared_ptr< Collision2D_Base> other) = 0;

		virtual bool OnHit(std::shared_ptr<Collision2D_Base> other);

	};
	class Collision2D_Rectangle :public Collision2D_Base {
	public:
		Collision2D_Rectangle(std::shared_ptr<Rectangle> rect, std::shared_ptr<GameObject> gameObj);
		
		~Collision2D_Rectangle() ;

		void Initialize()override;
		void PreInitialize()override;
		

		void Releace() {
			gameObj = nullptr;
		}

		bool OnUpdate()override;

		inline bool IsHit(std::shared_ptr<Collision2D_Base> other) {
			if (other->IsThis<Collision2D_Rectangle>()) {
				auto otherRect = other->GetThis<Collision2D_Rectangle>()->rect;
				auto result= rect->IsIntersects(otherRect)||otherRect->IsIntersects(rect);
				return result;
			}

			return false;
		}
		std::shared_ptr<Rectangle> rect;
	};
	class Collision2D_Terrain :public Collision2D_Base {
	public:

		Collision2D_Terrain( std::shared_ptr<GameObject> gameObj);
		void Initialize()override;
		void PreInitialize()override;

		bool OnUpdate()override;

		bool IsHit(std::shared_ptr<Collision2D_Base> other);
	};

}