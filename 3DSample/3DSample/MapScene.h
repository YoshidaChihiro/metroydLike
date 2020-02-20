#pragma once
#include "IScene.h"
#include"Map.h"
namespace Framework {
	class MapScene:public IScene
	{
	public:
		MapScene(std::string mapFilePath);
		~MapScene();
		void Initialize()override;

		void PreInitialize()override;

		bool Update()override;

		void OnSet()override;

		void Release()override;

		std::shared_ptr<Resource_Sound> shp_sound_bgm;
		std::shared_ptr<Resource_Sound> shp_sound_mapmove;
	private:
		std::string filePath;
		std::shared_ptr<Map> shp_map;
		bool isStart;
	};

}