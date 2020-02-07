#pragma once
#include "Resource.h"
#include<vector>
#include<map>
namespace Framework {
	class ResouceController
	{
	public:
		ResouceController() {};
		void Draw();
		void LoadTexture(std::string fileName,std::string filePath="Resource/Texture/");
		void LoadSound(std::string fileName, std::string filePath="Resource/Sound/");
		void LoadMV1(std::string fileName, std::string filePath="Resource/MV1/");
		int GetTexture(std::string resourceName);
		int GetSound(std::string resourceName);
		int GetMV1(std::string resourceName);
		void AddGraph(std::shared_ptr< Resource_Texture> shp_arg_resource_textue);
		void AddMV1(std::shared_ptr< Resource_MV1> shp_arg_resource_MV1);
		void AddSound(std::shared_ptr< Resource_Sound> shp_arg_resource_sound);
	private:
		std::vector<std::shared_ptr< Resource_Texture>> vec_textures;
		std::vector< std::shared_ptr<Resource_Sound>> vec_sounds;
		std::vector< std::shared_ptr<Resource_MV1>> vec_mv1s;
		std::map<std::string, int> textureHandleMap;
		std::map<std::string, int> mv1HandleMap;
		std::map<std::string, int> soundHandleMap;


	};

}