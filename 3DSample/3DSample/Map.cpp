#pragma once
#include "Map.h"
#include"GameObjectManager.h"
#include"Game.h"
Framework::Map::Map(const std::string & filePath, int arg_glidSize, std::shared_ptr<GameObjectManager> arg_manager):GameObject(ObjectFactory::Create<Transform>(Vector3()),arg_manager->GetThis<GameObjectManager>())
{
	auto data = CSVReader::GetMatrixByFile(filePath);
	GenerateMap(data,arg_glidSize);
	tag = ObjectTag::map;
}

void Framework::Map::Reload()
{

	Game::GetInstance()->GetResourceController()->GetScreenInformation()->SetFieldWidth(glidSize*mapWidth);
	Game::GetInstance()->GetResourceController()->GetScreenInformation()->SetFieldHeight(glidSize*mapHeight);

	for (int x = 0; x < mapWidth; x++) {
		for (int y = 0; y < mapHeight; y++) {
			if (mapObjects[x][y] != nullptr&&!mapObjects[x][y]->GetIsDead()) {
				mapObjects[x][y]->GetThis<MapChipObject>()-> Replace();
			}
		}
	}
}

void Framework::Map::Initialize()
{

	shp_collision = ObjectFactory::Create<Collision2D_Terrain>(GetThis<Map>());
}

bool Framework::Map::OnUpdate()
{
	shp_collision->OnUpdate();

	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collision,0);

	for (int x = 0; x < mapWidth; x++) {
		for (int y = 0; y < mapHeight; y++) {
			if (mapObjects[x][y] != nullptr&&mapObjects[x][y]->GetIsDead()) {
				mapObjects[x][y] = nullptr;
			}
		}
	}

	return true;
}

void Framework::Map::ChangeGlid(int x, int y, std::shared_ptr<MapChipObject> arg_mapChipObj)
{
	if (x > mapWidth || y > mapHeight || x < 0 || y < 0)return;
	if (mapObjects[x][y] != nullptr) {
		mapObjects[x][y]->SetIsDead(true);
		mapObjects[x][y] = nullptr;
	}
	mapObjects[x][y] = arg_mapChipObj->GetThis<GameObject>();
	manager->AddObject(mapObjects[x][y]);

}

void Framework::Map::AddMapChip(int x, int y, std::shared_ptr<MapChipObject> arg_mapChipObj)
{
	if (x > mapWidth || y > mapHeight || x < 0 || y < 0)return;
	if (mapObjects[x][y] == nullptr) {
		ChangeGlid(x, y, arg_mapChipObj);
	}
}

void Framework::Map::ChangeGlid(int x, int y, int mapChipNum)
{
	if (mapChipNum <= 0) {
		return;
	}
	auto addObj = mapChips.at(mapChipNum)->Clone(Vector3(glidSize*x, glidSize*y, 0));
	//manager->AddObject(addObj);
	if (x > mapWidth || y > mapHeight || x < 0 || y < 0)return;
	if (mapObjects[x][y] != nullptr) {
		mapObjects[x][y]->SetIsDead(true);
		mapObjects[x][y] = nullptr;
	}
	mapObjects[x][y] = addObj->GetThis<GameObject>();
	manager->AddObject(mapObjects[x][y]);
}

void Framework::Map::AddMapChip(int x, int y, int mapChipNum)
{
	if (mapChipNum <= 0) {
		return;
	}
	auto addObj = mapChips.at(mapChipNum)->Clone(Vector3(glidSize*x,glidSize*y,0));
	manager->AddObject(addObj);
	AddMapChip(x, y, addObj);
}

void Framework::Map::ChangeMapChipBlock(const int & arg_objectID, const int & x, const int & y)
{

}

Framework::Vector2 Framework::Map::GetCenterPosition()
{
	return Vector2(mapWidth*glidSize,mapHeight*glidSize)/2;
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

		ObjectFactory::Create<Medal>(manager),//2

		ObjectFactory::Create<ChildSeedSpawner>(manager),//3


		ObjectFactory::Create<MapChip_CrushBlock>(manager),//4
		ObjectFactory::Create<MapChip_ChildBlock>(manager),//5

		ObjectFactory::Create<MapChip_Space>(manager),//6

		ObjectFactory::Create<MapChip_Kuribo>(manager),//7
		ObjectFactory::Create<MapChip_Kuribo>(manager),//8
		ObjectFactory::Create<MapChip_Bat>(manager),//9
		ObjectFactory::Create<MapChip_Bat>(manager),//10
		ObjectFactory::Create<MapChip_Teresa>(manager),//11
		ObjectFactory::Create<MapChip_Teresa>(manager),//12

		ObjectFactory::Create<MapChip_Gate>("betaScene",Vector2(2 * 32,38 * 32),manager),//13

		ObjectFactory::Create<MapChip_Gate>("TestScene",Vector2(26 * 32,16 * 32),manager),//14
		ObjectFactory::Create<MapChip_Gate>("ClearScene",Vector2(2 * 32,16 * 32),manager),//15
		ObjectFactory::Create<MapChip_reset>(manager),//16

		ObjectFactory::Create<MapChip_Gate>("TitleScene",Vector2(26 * 32,16 * 32),manager),//14


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

std::vector<std::shared_ptr<Framework:: MapChipObject>> Framework::Map::GetAroundObjects_containNullptr(Vector2 point)
{
	int x = point.x / glidSize;
	int y = point.y / glidSize;
	std::vector<std::shared_ptr<MapChipObject>> output;
	for (int i = -1; i < 2; i++) {
		if (i + y < 0 || i + y >= mapHeight) {
			output.push_back(nullptr);
			output.push_back(nullptr);
			output.push_back(nullptr);
			continue;
		}
		for (int j = -1; j < 2; j++) {
			if (j + x < 0 || j + x >= mapWidth) {
				output.push_back(nullptr);
				continue;
			}
			if (mapObjects[j + x][i + y]) {
				output.push_back(mapObjects[j + x][i + y]->GetThis<MapChipObject>());
			}
			else {
				output.push_back(nullptr);
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
