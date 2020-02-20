#pragma once
#include"GameObjectManager.h"
#include"RelativeTimer.h"
#include"SlideFAde.h"
#include"IScene.h"
namespace Framework {
	template<typename T>
	class ObjectDelayCreater:public GameObject
	{
	public:
		ObjectDelayCreater<T>(int delayFrame, std::shared_ptr<Transform>arg_transform,std::shared_ptr<GameObjectManager> arg_manager)
			: GameObject(arg_transform->GetThis<Transform>(),arg_manager->GetThis<GameObjectManager>()
			),timer(RelativeTimer(delayFrame))
		{
			timer.Start();
		};
		void Initialize()override{}
		void PreInitialize()override{}
		bool OnUpdate()override {
			if (isEnd) {
				if (!timer.Update()) {
					return true;
				}
				manager->AddObject(ObjectFactory::Create<T>(transform, manager));
				SetIsDead(true);
			}
			if (!isEnd&& timer.Update()) {
				isEnd = true;
				timer.Stop();
				timer.Reset();
				timer = RelativeTimer(10);
				timer.Start();
				auto sceneOverOgjs = ObjectFactory::Create<SceneOverObjects>();
				sceneOverOgjs->AddSceneOverGameObject(GetThis<GameObject>());
				sceneOverOgjs->playerPos = transform->GetPosition();
				auto fadeIn = ObjectFactory::Create<SlideFadeIn>(-1, manager);
				auto fadeOut = ObjectFactory::Create<SlideFadeOut>(-1, manager);

				manager->AddObject(fadeIn);

				sceneOverOgjs->AddSceneOverGameObject(fadeOut);

				
				Game::GetInstance()->GetSceneManager()->ChangeScene(Game::GetInstance()->GetSceneManager()->GetSceneName(), 30, sceneOverOgjs);
				Game::GetInstance()->GetGameTime()->Stop(60);
			}
			return true;
		};
		bool Release()override {
			return true;
		};
		RelativeTimer timer;
		bool isEnd;
	};



}