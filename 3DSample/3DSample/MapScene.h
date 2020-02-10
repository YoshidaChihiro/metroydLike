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
	private:
		std::string filePath;
		std::shared_ptr<Map> shp_map;
	};

}