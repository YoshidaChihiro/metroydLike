#pragma once
#include"Util.h"
#include "ButiMath.h"
namespace Framework {
	class GameObject;
	class Collision2D_Base :public IObject
	{
	public:
		virtual bool IsHit(std::shared_ptr< Collision2D_Base> other) = 0;

		virtual bool OnHit(std::shared_ptr<Collision2D_Base> other);

		virtual bool Update()=0;

		std::shared_ptr<GameObject> gameObj;
	};
	class Collision2D_Rectangle :public Collision2D_Base {
	public:
		Collision2D_Rectangle(std::shared_ptr<Rectangle> rect, std::shared_ptr<GameObject> gameObj);
		
		~Collision2D_Rectangle() {};

		void Initialize()override;
		void PreInitialize()override;
		
		bool Update()override;

		inline bool IsHit(std::shared_ptr<Collision2D_Base> other) {
			if (other->IsThis<Collision2D_Rectangle>()) {
				auto otherRect = other->GetThis<Collision2D_Rectangle>()->rect;
				auto result= rect->IsIntersects(otherRect)||otherRect->IsIntersects(rect);
				if (result) { 
					OnHit(other);
					other->OnHit(GetThis<Collision2D_Rectangle>());
				}
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

		bool Update()override;

		bool IsHit(std::shared_ptr<Collision2D_Base> other);
	};

}