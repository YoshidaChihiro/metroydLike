#pragma once
#include "Resource.h"
#include<vector>
namespace Framework {
	class ResouceController
	{
	public:
		ResouceController() {};
		void Draw();
		void AddGraph(std::shared_ptr< Resource_Texture> shp_arg_resource_textue);
		void AddMV1(std::shared_ptr< Resource_MV1> shp_arg_resource_MV1);
		void AddSound(std::shared_ptr< Resource_Sound> shp_arg_resource_sound);
	private:
		std::vector<std::shared_ptr< Resource_Texture>> vec_textures;
		std::vector< std::shared_ptr<Resource_Sound>> vec_sounds;
		std::vector< std::shared_ptr<Resource_MV1>> vec_mv1s;
	};

}