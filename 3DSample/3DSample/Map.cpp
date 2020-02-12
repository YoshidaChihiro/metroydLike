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

	Game::GetInstance()->GetResourceController()->GetScreenInformation()->SetFieldWidth(glidSize*mapWidth);
	Game::GetInstance()->GetResourceController()->GetScreenInformation()->SetFieldHeight(glidSize*mapHeight);
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
	glidSize = arg_glidSize;
	mapWidth = csvData->size_x;
	mapHeight = csvData->size_y;

	Game::GetInstance()->GetResourceController()->GetScreenInformation()->SetFieldWidth(glidSize*mapWidth);
	Game::GetInstance()->GetResourceController()->GetScreenInformation()->SetFieldHeight(glidSize*mapHeight);
	Game::GetInstance()->GetResourceController()->GetScreenInformation()->SetGlidSize(glidSize);

	mapChips = { 
		ObjectFactory::Create<MapChip_Space>(manager),//0
		ObjectFactory::Create<MapChip_Test>(manager),//1

		ObjectFactory::Create<MapChip_Gate>("Map2Scene",Vector2(32 * 3,32 * 20),manager),//2
		ObjectFactory::Create<MapChip_Gate>("Map1Scene",Vector2(32 * 28,32 * 21),manager),//3

		ObjectFactory::Create<MapChip_Gate>("Map3Scene",Vector2(32 * 3,32 * 3),manager),//4
		ObjectFactory::Create<MapChip_Gate>("Map2Scene",Vector2(32 * 27,32 * 3),manager),//5

		ObjectFactory::Create<MapChip_Gate>("Map4Scene",Vector2(32 * 3,32 * 3),manager),//6
		ObjectFactory::Create<MapChip_Gate>("Map2Scene",Vector2(32 * 27,32 * 36),manager),//7

		ObjectFactory::Create<MapChip_Gate>("Map5Scene",Vector2(32 * 3,32 * 10),manager),//8
		ObjectFactory::Create<MapChip_Gate>("Map3Scene",Vector2(32 * 27,32 * 2),manager),//9

		ObjectFactory::Create<MapChip_Gate>("Map5Scene",Vector2(32 * 3,32 * 30),manager),//10
		ObjectFactory::Create<MapChip_Gate>("Map4Scene",Vector2(32 * 28,32 * 4),manager),//11

		ObjectFactory::Create<MapChip_Gate>("Map6Scene",Vector2(32 * 39,32 * 18),manager),//12
		ObjectFactory::Create<MapChip_Gate>("Map5Scene",Vector2(32 * 27,32 * 3),manager),//13

		ObjectFactory::Create<MapChip_Gate>("Map7Scene",Vector2(32 * 27,32 * 3),manager),//14
		ObjectFactory::Create<MapChip_Gate>("Map6Scene",Vector2(32 * 3,32 * 3),manager),//15

		ObjectFactory::Create<MapChip_Gate>("Map9Scene",Vector2(32 * 27,32 * 3),manager),//16
		ObjectFactory::Create<MapChip_Gate>("Map7Scene",Vector2(32 * 3,32 * 3),manager),//17

		ObjectFactory::Create<MapChip_Gate>("Map8Scene",Vector2(32 * 71,32 * 19),manager),//18
		ObjectFactory::Create<MapChip_Gate>("Map6Scene",Vector2(32 * 22,32 * 3),manager),//19

		ObjectFactory::Create<MapChip_Gate>("Map8Scene",Vector2(32 * 17,32 * 18),manager),//20
		ObjectFactory::Create<MapChip_Gate>("Map9Scene",Vector2(32 * 25,32 * 2),manager),//21

		ObjectFactory::Create<MapChip_Gate>("Map7Scene",Vector2(32 * 15,32 * 3),manager),//22
		
		ObjectFactory::Create<MapChip_Gate>("Map2Scene",Vector2(32 * 15,32 * 3),manager),//23

		ObjectFactory::Create<MapChip_Gate>("Map9Scene",Vector2(32 * 5,32 * 18),manager),//24
		ObjectFactory::Create<MapChip_Gate>("Map1Scene",Vector2(32 * 2,32 * 2),manager),//25

	};

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
		if (i + x < 0||i+x>=mapWidth) {
			continue;
		}
		for (int j = -1; j < 2; j++) {
			if (j+y < 0|| j + y>=mapHeight) {
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
