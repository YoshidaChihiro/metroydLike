#pragma once
#include"GameObjectManager.h"
#include"Resource.h"
namespace Framework {
	class Board:public GameObject
	{
	public:
		Board(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager);
		void SetParam(std::string arg_text);
		void Initialize()override;
		void PreInitialize()override;
		bool OnUpdate()override;
	private:
		int color = GetColor(255, 255, 255);
		std::shared_ptr< Resource_Text_String> shp_source;
	};

}