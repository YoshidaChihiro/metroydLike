#pragma once
#include"Transform.h"
#include"RelativeTimer.h"
#include"GameComponent.h"
namespace Framework {
	class GameObjectManager;
	enum class MovePattern {
		abs,relative,fleeze
	};
	enum class ObjectTag {
		player,enemy,obstacle,none,camera,supporter,sencer,map,playerBullet,item, enemyBullet,spawner,particle
	};
	class GameObject:public IObject
	{
	public:
		inline
			GameObject(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager) :transform(arg_transform),manager(arg_manager) {
			sucideTimer = new RelativeTimer(0);
		}

		virtual ~GameObject() {
			delete sucideTimer;
		};

		virtual bool Release();

		inline bool Update() {
			
			if (!isDead) {

				OnUpdate();
				ComponentUpdate();
			}
			else {
				DeadUpdate();
			}

			switch (movePattern)
			{
			case MovePattern::relative:
				RelativeMove();
				break;
			case MovePattern::abs:
				AbsMove();
				break;
			default:
				break;
			}
			return true;
		}

		virtual bool OnUpdate() = 0;
		virtual bool DeadUpdate() { return true; }

		void DeadCheck();

		inline void ComponentUpdate() {
			for (auto itr = vec_gameComponents.begin(); itr != vec_gameComponents.end(); itr++) {
				(*itr)->OnUpdate();
			}
		}

		virtual void Hit(std::shared_ptr<GameObject> other) {}

		void PreInitialize() override;

		void SetGameObjectManager(std::shared_ptr<GameObjectManager> arg_manager);

		void Initialize()override;

		void AbsMove();

		void RelativeMove();

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
		Vector3 velocity;
		Vector3 phisicsForce;
		MovePattern movePattern = MovePattern::relative;
		std::vector<std::shared_ptr<GameComponent>> vec_gameComponents;
	private:
		bool isDead;
		bool isRemove;
		RelativeTimer* sucideTimer;
		std::vector<std::shared_ptr<GameObject>> childs;
	};
}

