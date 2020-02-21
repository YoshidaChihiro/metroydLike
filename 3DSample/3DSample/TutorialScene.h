#pragma once
#include"IScene.h"
#include"Map.h"
namespace Framework {
	class TutorialScene :public IScene
	{
	public:
		TutorialScene();
		~TutorialScene();
		void Initialize()override;

		void PreInitialize()override;

		bool Update()override;

		void OnSet()override;

		void Release()override;
	private:
		std::shared_ptr<Map> shp_map;
	};

}