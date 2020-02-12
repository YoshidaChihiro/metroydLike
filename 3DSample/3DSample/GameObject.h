#pragma once
#include"Transform.h"
namespace Framework {
	class GameObjectManager;

	enum class ObjectTag {
		player,enemy,obstacle,none,camera,supporter,sencer
	};
	class GameObject:public IObject
	{
	public:
		inline
			GameObject(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager) :transform(arg_transform),manager(arg_manager) {

		}

		virtual ~GameObject() {};

		virtual bool Release();

		virtual bool Update()=0;

		virtual void Hit(std::shared_ptr<GameObject> other) {};

		void PreInitialize() override;

		void SetGameObjectManager(std::shared_ptr<GameObjectManager> arg_manager);

		void Initialize()override;

		bool GetIsDead() { return isDead; };

		void SetIsDead(bool arg_isDead) { isDead = arg_isDead; }

		std::shared_ptr<Transform> transform;

		std::shared_ptr<GameObjectManager> manager;

		ObjectTag GetObjectTag()const {
			return tag;
		}
		void SetObjectTag(ObjectTag arg_tag) {
			tag = arg_tag;
		}
		void AddChildObject(std::shared_ptr<GameObject> arg_chid);

		std::vector<std::shared_ptr<GameObject>> GetChildObjects();
	protected:
		ObjectTag tag = ObjectTag::none;
	private:
		bool isDead;
		std::vector<std::shared_ptr<GameObject>> childs;
	};
}

