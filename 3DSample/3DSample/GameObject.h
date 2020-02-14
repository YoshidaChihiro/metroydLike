#pragma once
#include"Transform.h"
#include"RelativeTimer.h"
namespace Framework {
	class GameObjectManager;

	enum class ObjectTag {
		player,enemy,obstacle,none,camera,supporter,sencer,map,playerBullet,item
	};
	class GameObject:public IObject
	{
	public:
		inline
			GameObject(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager) :transform(arg_transform),manager(arg_manager) {
			sucideTimer = new Timer(0);
		}

		virtual ~GameObject() {
			delete sucideTimer;
		};

		virtual bool Release();

		virtual bool Update() = 0;
		virtual bool DeadUpdate() { return true; }

		void DeadCheck();

		virtual void Hit(std::shared_ptr<GameObject> other) {}

		void PreInitialize() override;

		void SetGameObjectManager(std::shared_ptr<GameObjectManager> arg_manager);

		void Initialize()override;

		bool GetIsDead() { return isDead; };

		void SetIsDead(bool arg_isDead);

		bool GetIsRemove() { return isRemove; }

		std::shared_ptr<Transform> transform;

		std::shared_ptr<GameObjectManager> manager;

		ObjectTag GetObjectTag()const {
			return tag;
		}
		void SetObjectTag(ObjectTag arg_tag) {
			tag = arg_tag;
		}
		void AddChildObject(std::shared_ptr<GameObject> arg_chid);
		void RemoveChildObject(std::shared_ptr<GameObject> arg_chid);

		std::vector<std::shared_ptr<GameObject>> GetChildObjects();
		std::vector<std::shared_ptr<GameObject>> GetChildAndGrandChildObjects();
	protected:
		void ChangeTimer(int arg_maxFrame);
		ObjectTag tag = ObjectTag::none;
	private:
		bool isDead;
		bool isRemove;
		Timer* sucideTimer;
		std::vector<std::shared_ptr<GameObject>> childs;
	};
}

