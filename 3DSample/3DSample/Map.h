#pragma once
#include<string>
#include "GameObject.h"
#include "Collision2D.h"
#include "MapChipObject.h"
#include "CSVReader.h"
#include <vector>
namespace Framework {
	class Map:public GameObject
	{
	public:
		Map(const std::string& filePath, int glidSize, std::shared_ptr<GameObjectManager> arg_manager);
		//Map(const MapData& mapData, int glidSize);
		void Reload();
		void Initialize()override;
		bool Update()override;
		void ChangeMapChipBlock(const int& arg_objectID, const int& x, const int& y);
		void GenerateMap(std::shared_ptr< CSVData> csvData,int glidSize);
		std::vector< std::shared_ptr< MapChipObject>> GetAroundObjects(Vector2 point);
		~Map();
		std::shared_ptr<GameObject>** mapObjects;
		void InitializeArray();
		void ClearMapChip();
		int mapWidth, mapHeight, glidSize;
		std::vector< std::shared_ptr< MapChipObject>> mapChips;
		std::shared_ptr<Collision2D_Terrain> shp_collision;
	};

}