#pragma once
#include "Map.h"
#include"GameObjectManager.h"
#include"Game.h"
Framework::Map::Map(const std::string & filePath, int arg_glidSize, std::shared_ptr<GameObjectManager> arg_manager):GameObject(ObjectFactory::Create<Transform>(Vector3()),arg_manager->GetThis<GameObjectManager>())
{
	auto data = CSVReader::GetMatrixByFile(filePath);
	GenerateMap(data,arg_glidSize);
}

void Framework::Map::Reload()
{
}

void Framework::Map::ChangeMapChipBlock(const int & arg_objectID, const int & x, const int & y)
{
}

void Framework::Map::GenerateMap(std::shared_ptr< CSVData> csvData, int arg_glidSize)
{
	float mapchipOuterCircleRadius = Rectangle::GetRectangleOuterCircleRadius(arg_glidSize, arg_glidSize);
	mapChips = {ObjectFactory::Create<MapChip_Space>(manager),ObjectFactory::Create<MapChip_Test>(manager) };
	glidSize = arg_glidSize;
	mapWidth = csvData->size_x;
	mapHeight = csvData->size_y;

	InitializeArray();

	Vector3 mapChipPos;
	for (int x = 0; x < mapWidth; x++)
	{
		mapChipPos.x = glidSize * x;
		for (int y = 0; y < mapHeight; y++)
		{
			mapChipPos.y = glidSize * y;
			if (csvData->data[x][y] < 0 || csvData->data[x][y] >mapChips.size()) continue;
			mapObjects[x][y] = mapChips[csvData->data[x][y]]->Clone(mapChipPos);
			if(mapObjects[x][y])
			manager->AddObject_Init(mapObjects[x][y]);
		}
	}
}


Framework::Map::~Map()
{
}

void Framework::Map::InitializeArray()
{
	mapObjects =new std::shared_ptr<GameObject>*[mapWidth+1];
	for (int x = 0; x < mapWidth; x++)
	{
		mapObjects[x] =new std::shared_ptr<GameObject>[mapHeight];
	}
}

void Framework::Map::ClearMapChip()
{
}
