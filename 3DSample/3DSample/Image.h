#pragma once
#include"GameObjectManager.h"
#include"Resource.h"
namespace Framework {
	class Image:public GameObject
	{
	public:
		Image(std::string resource_Name, std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager);

		void Initialize()override;
		void PreInitialize()override;
		bool OnUpdate()override;
		std::string source;
		std::shared_ptr< Resource_Texture> shp_texture;
	};
}

