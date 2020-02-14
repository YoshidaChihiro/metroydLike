#pragma once
#include"GameObject.h"
#include"Resource.h"
namespace Framework {
	class Cursol:public GameObject
	{
	public:

		Cursol(std::shared_ptr<Transform> shp_arg_player_transform, std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager);
		bool Update()override;
		void Initialize()override;
		void PreInitialize()override {};
		std::shared_ptr<Transform> GetWorldTransform();
	private:
		std::shared_ptr<Resource_Texture> shp_texture;
	};

}