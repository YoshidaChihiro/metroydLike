#pragma once
#include"GameObjectManager.h"
#include"RelativeTimer.h"
namespace Framework {
	template<typename T>
	class ObjectDelayCreater:public GameObject
	{
	public:
		ObjectDelayCreater<T>(int delayFrame, std::shared_ptr<Transform>arg_transform,std::shared_ptr<GameObjectManager> arg_manager)
			: GameObject(arg_transform->GetThis<Transform>(),arg_manager->GetThis<GameObjectManager>()
			),timer(Timer(delayFrame))
		{
			timer.Start();
		};
		void Initialize()override{}
		void PreInitialize()override{}
		bool Update()override {
			if (timer.Update()) {
				manager->AddObject( ObjectFactory::Create<T>(transform,manager));
				SetIsDead(true);
			}
			return true;
		};
		bool Release()override {
			return true;
		};
		Timer timer;
	};



}