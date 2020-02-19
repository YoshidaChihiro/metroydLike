#pragma once
#include "Resource.h"
#include<vector>
#include<map>
#include "ScreenInformation.h"
namespace Framework {
	class ResouceController
	{
	public:
		ResouceController(int screenWidth,int screenHeight) ;
		void Draw();
		void SoundPlay();
		void LoadTexture(std::string fileName,std::string filePath="Resource/Texture/");
		void LoadSound(std::string fileName, std::string filePath="Resource/Sound/");
		void LoadMV1(std::string fileName, std::string filePath="Resource/MV1/");
		void LoadCreateFont(std::string fontName,std::string fontSourceName,int size,int thick,int fontType);
		int GetTexture(std::string resourceName);
		int GetSound(std::string resourceName);
		int GetMV1(std::string resourceName);
		std::shared_ptr<Resource_Font> GetFont(std::string fontName);
		void AddGraph(std::shared_ptr< Resource_Texture> shp_arg_resource_textue, int i = 0);
		void AddLayer(int addLayerCount);
		void AddText(std::shared_ptr< Resource_Text_String> shp_arg_resource_text);
		void AddMV1(std::shared_ptr< Resource_MV1> shp_arg_resource_MV1);
		void AddSound(std::shared_ptr< Resource_Sound> shp_arg_resource_sound);

		std::unique_ptr<ScreenInformation>& GetScreenInformation() {
			return unq_screenInformation;
		};

	private:
		std::vector<std::vector<std::shared_ptr< Resource_Texture>>> vec_texturesLayers;
		std::vector<std::shared_ptr< Resource_Text_String>> vec_texts;
		std::vector< std::shared_ptr<Resource_Sound>> vec_sounds;
		std::vector< std::shared_ptr<Resource_MV1>> vec_mv1s;
		std::map<std::string, int> textureHandleMap;
		std::map<std::string, int> mv1HandleMap;
		std::map<std::string, int> soundHandleMap;
		std::map<std::string, std::shared_ptr<Resource_Font>> fontResourceMap;

		std::unique_ptr<ScreenInformation> unq_screenInformation;
	};

}