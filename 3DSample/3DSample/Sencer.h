#pragma once
#include "GameObject.h"
#include"Resource.h"
#include"Collision2D.h"
namespace Framework {
	class Sencer:public GameObject
	{
	public:
		Sencer(std::shared_ptr<Transform> arg_transform,std::shared_ptr< GameObjectManager> arg_manager, std::vector< ObjectTag> arg_vec_checkTags, std::shared_ptr<GameObject>* arg_output);
		~Sencer();
		void Initialize()override;
		bool Update()override;
		void Hit(std::shared_ptr<GameObject> other)override;
	private:
		std::shared_ptr<GameObject>* output;
		std::vector< ObjectTag> vec_checkTags;
		std::shared_ptr<Resource_Texture> shp_texture;
		std::shared_ptr<Collision2D_Rectangle>shp_collisionRect;
	};
}

