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

void Framework::Map::Initialize()
{

	shp_collision = ObjectFactory::Create<Collision2D_Terrain>(GetThis<Map>());
}

bool Framework::Map::Update()
{
	shp_collision->Update();
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collision);
	return true;
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

std::vector<std::shared_ptr<Framework:: MapChipObject>> Framework::Map::GetAroundObjects(Vector2 point)
{
	int x = point.x / glidSize;
	int y = point.y / glidSize;
	std::vector<std::shared_ptr<MapChipObject>> output;
	for (int i = -1; i < 2; i++) {
		if (i + x < 0||i+x>=mapWidth-1) {
			continue;
		}
		for (int j = -1; j < 2; j++) {
			if (j+y < 0|| j + y>=mapHeight-1) {
				continue;
			}
			if (mapObjects[i+x][j+y]) {
				output.push_back(mapObjects[i + x][j + y]->GetThis<MapChipObject>());
			}
		}
	}
	return output;
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
