#pragma once
#include "GameObject.h"
#include"Resource.h"
#include"Collision2D.h"

namespace Framework {
	class Child :public GameObject
	{
	public:
		Child(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager);
		~Child();
		void Hit(std::shared_ptr<GameObject> other)override;
		void PreInitialize()override;
		bool Update()override;
		std::shared_ptr<Resource_Texture> shp_texture;
		std::shared_ptr<Collision2D_Rectangle>shp_collisionRect;

	private:
		Vector2 velocity;
		float speed;
		enum State {
			NormalMode,
			ThrowWaitMode,
			FixMode,
		};
		State state;
		int handle;
	};
}
