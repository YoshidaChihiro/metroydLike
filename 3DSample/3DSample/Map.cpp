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
	if (mapObjects[x][y] == nullptr|| mapObjects[x][y]->GetObjectTag()!=ObjectTag::obstacle) {
		//manager->AddObject(arg_mapChipObj);
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

	auto blockHandle = Game::GetInstance()->GetResourceController()->GetTexture("block.png");
	auto blockHandle_horizontal = Game::GetInstance()->GetResourceController()->GetTexture("block_horizontal.png");
	auto blockHandle_vertical = Game::GetInstance()->GetResourceController()->GetTexture("block_vertical.png");
	auto blockHandle_top = Game::GetInstance()->GetResourceController()->GetTexture("block_top.png");
    auto blockHandle_bottom = Game::GetInstance()->GetResourceController()->GetTexture("block_bottom.png");
	auto blockHandle_left = Game::GetInstance()->GetResourceController()->GetTexture("block_left.png");
    auto blockHandle_right = Game::GetInstance()->GetResourceController()->GetTexture("block_right.png");
	auto blockHandle_leftTop = Game::GetInstance()->GetResourceController()->GetTexture("block_leftTop.png");
	auto blockHandle_leftBottom = Game::GetInstance()->GetResourceController()->GetTexture("block_leftBottom.png");
	auto blockHandle_rightTop = Game::GetInstance()->GetResourceController()->GetTexture("block_rightTop.png");
	auto blockHandle_rightBottom = Game::GetInstance()->GetResourceController()->GetTexture("block_rightBottom.png");

	mapChips = {
		ObjectFactory::Create<MapChip_Space>(manager),//0
		ObjectFactory::Create<MapChip_Test>(blockHandle_horizontal,manager),//1

		ObjectFactory::Create<Medal>(manager),//2

		ObjectFactory::Create<ChildSeedSpawner>(manager),//3


		ObjectFactory::Create<MapChip_CrushBlock>(manager),//4
		ObjectFactory::Create<MapChip_ChildBlock>(manager),//5

		ObjectFactory::Create<MapChip_Space>(manager),//6

		ObjectFactory::Create<MapChip_Kuribo>(manager),//7
		ObjectFactory::Create<MapChip_KuriboBullet>(manager),//8
		ObjectFactory::Create<MapChip_Bat>(manager),//9
		ObjectFactory::Create<MapChip_BatBullet>(manager),//10
		ObjectFactory::Create<MapChip_Teresa>(manager),//11
		ObjectFactory::Create<MapChip_Teresa>(manager),//12
		//ok
		ObjectFactory::Create<MapChip_Gate>("Map2Scene",Vector2(32 * 1,32 * 36),manager),//13
		ObjectFactory::Create<MapChip_Gate>("Map1Scene",Vector2(32 * 25,32 * 16),manager),//14
		//ok
		ObjectFactory::Create<MapChip_Gate>("Map3Scene",Vector2(32 * 1,32 * 3),manager),//15
		ObjectFactory::Create<MapChip_Gate>("Map2Scene",Vector2(32 * 26,32 * 3),manager),//16
		//ok
		ObjectFactory::Create<MapChip_Gate>("Map4Scene",Vector2(32 * 1,32 * 3),manager),//17
		ObjectFactory::Create<MapChip_Gate>("Map3Scene",Vector2(32 * 42,32 * 1),manager),//18
		//ok
		ObjectFactory::Create<MapChip_Gate>("Map5Scene",Vector2(32 * 3,32 * 36),manager),//19		
		ObjectFactory::Create<MapChip_Gate>("Map4Scene",Vector2(32 * 42,32 * 2),manager),//20
		//ok
		ObjectFactory::Create<MapChip_Gate>("Map6Scene",Vector2(32 * 37,32 * 18),manager),//21
		ObjectFactory::Create<MapChip_Gate>("Map5Scene",Vector2(32 * 27,32 * 2),manager),//22
		//ok
		ObjectFactory::Create<MapChip_Gate>("Map7Scene",Vector2(32 * 27,32 * 3),manager),//23
		ObjectFactory::Create<MapChip_Gate>("Map6Scene",Vector2(32 * 2,32 * 2),manager),//24
		//ok
		ObjectFactory::Create<MapChip_Gate>("Map9Scene",Vector2(32 * 41,32 * 3),manager),//25
		ObjectFactory::Create<MapChip_Gate>("Map7Scene",Vector2(32 * 3,32 * 3),manager),//26

		ObjectFactory::Create<MapChip_Gate>("Map8Scene",Vector2(32 * 18,32 * 18),manager),//27
		ObjectFactory::Create<MapChip_Gate>("Map9Scene",Vector2(32 * 25,32 * 2),manager),//28
		
		ObjectFactory::Create<MapChip_Space>(manager),//29 lastMap => gameClear
		ObjectFactory::Create<MapChip_Space>(manager),//30 gameClear => gameTitle

			
		ObjectFactory::Create<MapChip_Gate>("Map8Scene",Vector2(32 * 17,32 * 18),manager),//27
		ObjectFactory::Create<MapChip_Gate>("Map6Scene",Vector2(32 * 22,32 * 1),manager),//30

		

		ObjectFactory::Create<MapChip_reset>(manager),//33

		ObjectFactory::Create<MapChip_Space>(manager),//34 for boss

		ObjectFactory::Create<MapChip_Test>(blockHandle_vertical,manager),//35
		ObjectFactory::Create<MapChip_Test>(blockHandle_top,manager),//36
		ObjectFactory::Create<MapChip_Test>(blockHandle_bottom,manager),//37
		ObjectFactory::Create<MapChip_Test>(blockHandle_left,manager),//38
		ObjectFactory::Create<MapChip_Test>(blockHandle_right,manager),//39
		ObjectFactory::Create<MapChip_Test>(blockHandle_leftTop,manager),//40
		ObjectFactory::Create<MapChip_Test>(blockHandle_leftBottom,manager),//41
		ObjectFactory::Create<MapChip_Test>(blockHandle_rightTop,manager),//42
		ObjectFactory::Create<MapChip_Test>(blockHandle_rightBottom,manager),//43

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
