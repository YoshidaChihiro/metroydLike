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
		bool OnUpdate()override;
		void ChangeGlid(int x, int y, std::shared_ptr<MapChipObject> arg_mapChipObj);
		void AddMapChip(int x, int y, std::shared_ptr<MapChipObject> arg_mapChipObj);
		void ChangeGlid(int x, int y, int mapChipNum);
		void AddMapChip(int x, int y, int mapChipNum);
		void ChangeMapChipBlock(const int& arg_objectID, const int& x, const int& y);
		Vector2 GetCenterPosition();
		void GenerateMap(std::shared_ptr< CSVData> csvData,int glidSize);
		std::vector< std::shared_ptr< MapChipObject>> GetAroundObjects(Vector2 point);
		std::vector< std::shared_ptr< MapChipObject>> GetAroundObjects_containNullptr(Vector2 point);
		~Map();
		std::shared_ptr<GameObject>** mapObjects;
		void InitializeArray();
		void ClearMapChip();
		int mapWidth, mapHeight, glidSize;
		std::vector< std::shared_ptr< MapChipObject>> mapChips;
		std::shared_ptr<Collision2D_Terrain> shp_collision;
	};

}