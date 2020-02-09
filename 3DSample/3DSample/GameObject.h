#pragma once
#include"Transform.h"
namespace Framework {
	class GameObjectManager;
	class GameObject:public IObject
	{
	public:
		inline
			GameObject(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager) :transform(arg_transform),manager(arg_manager) {}

		virtual ~GameObject() {};

		virtual bool Release();

		virtual bool Update()=0;

		virtual void Hit(std::shared_ptr<GameObject> other) {};

		void PreInitialize() override;

		void Initialize()override;

		bool GetIsDead() { return isDead; };

		void SetIsDead(bool arg_isDead) { isDead = arg_isDead; }

		std::shared_ptr<Transform> transform;

		std::shared_ptr<GameObjectManager> manager;

	protected:
		bool isDead;
	};
}

