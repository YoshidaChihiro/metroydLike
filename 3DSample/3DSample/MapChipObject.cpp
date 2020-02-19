#include "MapChipObject.h"
#include"GameObjectManager.h"
#include "Game.h"
#include"Explosion.h"
#include"ParticleEmitter.h"
#include"SlideFAde.h"
Framework::MapChip_Space::MapChip_Space(std::shared_ptr<GameObjectManager> arg_manager):MapChipObject(arg_manager->GetThis<GameObjectManager>())
{
}

Framework::MapChip_Space::MapChip_Space(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_transform,arg_manager->GetThis<GameObjectManager>())
{
}

Framework::MapChip_Test::MapChip_Test(std::shared_ptr<GameObjectManager> arg_manager) :MapChipObject(arg_manager->GetThis<GameObjectManager>())
{
}

std::shared_ptr<Framework::MapChipObject> Framework::MapChip_Test::Clone(Vector3 position)
{
	auto transform = ObjectFactory::Create<Transform>(position);
	return ObjectFactory::Create<MapChip_Test>(transform,manager->GetThis<GameObjectManager>());
}

bool Framework::MapChip_Test::OnUpdate()
{

	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
	return true;
}

void Framework::MapChip_Test::Initialize()
{
	shp_texture = ObjectFactory::Create<Resource_Texture>("block.png", transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(
		Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize(),
		Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize(), 
		transform->GetPosition().GetVector2(), 
		Rectangle::GetRectangleOuterCircleRadius(
			Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize()/2,
			Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize()/2)), GetThis<GameObject>());

	shp_collisionRect->OnUpdate();
}

Framework::MapChip_Test::MapChip_Test(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_transform,arg_manager->GetThis<GameObjectManager>())
{
}

Framework::MapChip_Gate::MapChip_Gate(std::string arg_changeSceneName,Vector2 arg_exitPosition,std::shared_ptr<GameObjectManager> arg_manager)
	: MapChipObject( arg_manager->GetThis<GameObjectManager>())
{
	changeScenesName = arg_changeSceneName;
	exitPosition = arg_exitPosition+Vector2(16,16);
}

std::shared_ptr<Framework::MapChipObject> Framework::MapChip_Gate::Clone(Vector3 position)
{
	auto transform = ObjectFactory::Create<Transform>(position);
	return ObjectFactory::Create<MapChip_Gate>(changeScenesName,exitPosition,
		transform,manager->GetThis<GameObjectManager>())->GetThis<MapChipObject>();
}

bool Framework::MapChip_Gate::OnUpdate()
{
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
	return true;
}

void Framework::MapChip_Gate::Hit(std::shared_ptr<GameObject> other)
{
	if (other->GetObjectTag() != ObjectTag::supporter||isGone) {
		return;
	}
	isGone = true;
	Game::GetInstance()->GetSceneManager()->GetGameMaster()->SetRespawnPosition(Vector3( exitPosition));
	auto sceneOverOgjs = ObjectFactory::Create<SceneOverObjects>();
	sceneOverOgjs->playerPos = exitPosition;
	auto player = manager->SerchGameObject(ObjectTag::player);
	sceneOverOgjs->AddSceneOverGameObject(player);
	auto vec_playersChilds = player->GetChildAndGrandChildObjects();

	for (auto itr = vec_playersChilds.begin(); itr != vec_playersChilds.end(); itr++) {
		//manager->RemoveObject(*itr);
		sceneOverOgjs->AddSceneOverGameObject(*itr);
	}
	//sceneOverOgjs->AddSceneOverGameObject(fade);
	//manager->RemoveObject(player);
	//manager->DeathRemoveGameObjects(ObjectTag::enemy);
	Game::GetInstance()->GetSceneManager()->ChangeScene(changeScenesName, 0, sceneOverOgjs);
}

void Framework::MapChip_Gate::Initialize()
{
	shp_texture = ObjectFactory::Create<Resource_Texture>("sample.png", transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(
		Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize(),
		Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize(),
		transform->GetPosition().GetVector2(),
		Rectangle::GetRectangleOuterCircleRadius(
			Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize() / 2,
			Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize() / 2)), GetThis<GameObject>());

	shp_collisionRect->OnUpdate();
}

void Framework::MapChip_Gate::Replace()
{
	isGone = false;
}

Framework::MapChip_Gate::MapChip_Gate(std::string arg_changeScenesName, Vector2 arg_exitPosition, std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_transform, arg_manager->GetThis<GameObjectManager>())
{
	exitPosition = arg_exitPosition;
	changeScenesName = arg_changeScenesName;
}

Framework::MapChip_ChildBlock::MapChip_ChildBlock(std::shared_ptr<GameObjectManager> arg_manager)
	: MapChipObject(arg_manager->GetThis<GameObjectManager>())
{
}

std::shared_ptr<Framework::MapChipObject> Framework::MapChip_ChildBlock::Clone(Vector3 position)
{
	auto transform = ObjectFactory::Create<Transform>(position);
	return ObjectFactory::Create<MapChip_ChildBlock>(transform, manager->GetThis<GameObjectManager>());
}

void Framework::MapChip_ChildBlock::Hit(std::shared_ptr<GameObject> other)
{
	if (!GetIsDead()&& other->GetObjectTag() == ObjectTag::playerBullet&&!other->GetIsDead()) {
		SetIsDead(true);
		manager->AddObject(ObjectFactory::Create<Explosion>(transform,manager));
	}
}

bool Framework::MapChip_ChildBlock::OnUpdate()
{
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
	return true;
}

void Framework::MapChip_ChildBlock::Initialize()
{
	shp_texture = ObjectFactory::Create<Resource_Texture>("child.png", transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(
		Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize(),
		Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize(),
		transform->GetPosition().GetVector2(),
		Rectangle::GetRectangleOuterCircleRadius(
			Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize() / 2,
			Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize() / 2)), GetThis<GameObject>());

	shp_collisionRect->OnUpdate();
}

Framework::MapChip_ChildBlock::MapChip_ChildBlock(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_transform, arg_manager->GetThis<GameObjectManager>())
{}


Framework::MapChip_Kuribo::MapChip_Kuribo(std::shared_ptr<GameObjectManager> arg_manager) :MapChipObject(arg_manager->GetThis<GameObjectManager>())
{
	tag = ObjectTag::spawner;
}
std::shared_ptr<Framework::MapChipObject> Framework::MapChip_Kuribo::Clone(Vector3 position)
{
	auto transform = ObjectFactory::Create<Transform>(position);
	return ObjectFactory::Create<MapChip_Kuribo>(transform, manager->GetThis<GameObjectManager>());
}
bool Framework::MapChip_Kuribo::OnUpdate()
{
	return true;
}
void Framework::MapChip_Kuribo::Initialize()
{
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(16, 16)), GetThis<GameObject>());
	
	
}
void Framework::MapChip_Kuribo::Replace()
{
	if (isClone) {
		auto enemyTransform = ObjectFactory::Create<Transform>(transform->GetPosition());
		manager->AddObject_Init(ObjectFactory::Create<Kuribo>(enemyTransform, manager));
	}
}
Framework::MapChip_Kuribo::MapChip_Kuribo(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_transform, arg_manager->GetThis<GameObjectManager>())
{
	tag = ObjectTag::spawner;
	isClone = true;
}

Framework::MapChip_CrushBlock::MapChip_CrushBlock(std::shared_ptr<GameObjectManager> arg_manager) 
	: MapChipObject( arg_manager->GetThis<GameObjectManager>())
{
}

std::shared_ptr<Framework::MapChipObject> Framework::MapChip_CrushBlock::Clone(Vector3 position)
{
	auto transform = ObjectFactory::Create<Transform>(position);
	return ObjectFactory::Create<MapChip_CrushBlock>(transform, manager->GetThis<GameObjectManager>());
}

void Framework::MapChip_CrushBlock::Hit(std::shared_ptr<GameObject> other)
{
	if (other->GetObjectTag() == ObjectTag::playerBullet) {
		if (other->IsThis<Explosion>()) {
			SetIsDead(true); {

				int handle = Game::GetInstance()->GetResourceController()->GetTexture("yellowParticle.png");

				auto p_param = new ParticleEmitterParameter();
				p_param->graphHandle = handle;
				p_param->layer = 2;
				p_param->range_maxSpeed = 10;
				p_param->range_minSpeed = 5;
				p_param->range_maxScale = 1.5f;
				p_param->range_minSpeed = 0.1f;
				p_param->range_maxLifeSpan = 30;
				p_param->range_minLifeSpan = 10;
				p_param->range_maxRotation.z = 360;
				p_param->range_minRotation.z = 0;
				p_param->range_maxEmitCount = 10;
				p_param->range_minEmitCount = 5;
				p_param->emitSpan = 2;
				p_param->emitterLifeSpan = 10;
				manager->AddObject(ObjectFactory::Create<ParticleEmitter>(transform->GetThis<Transform>(), p_param, manager
					));
			}
		}
	}
}

bool Framework::MapChip_CrushBlock::OnUpdate()
{
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
	return true;
}

void Framework::MapChip_CrushBlock::Initialize()
{
	shp_texture = ObjectFactory::Create<Resource_Texture>("sample3.png", transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(
		Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize(),
		Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize(),
		transform->GetPosition().GetVector2(),
		Rectangle::GetRectangleOuterCircleRadius(
			Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize() / 2,
			Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetGlidSize() / 2)), GetThis<GameObject>());

	shp_collisionRect->OnUpdate();
}

Framework::MapChip_CrushBlock::MapChip_CrushBlock(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_transform, arg_manager->GetThis<GameObjectManager>()) 
{
}

Framework::Medal::Medal(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_transform->GetThis<Transform>(), arg_manager->GetThis<GameObjectManager>())
{
	tag = ObjectTag::item;
}

Framework::Medal::Medal(std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_manager->GetThis<GameObjectManager>())
{
	tag = ObjectTag::spawner;
}

Framework::Medal::~Medal()
{
}

void Framework::Medal::Hit(std::shared_ptr<GameObject> other)
{
	if (other->GetObjectTag() == ObjectTag::supporter) {
		SetIsDead(true);
		Game::GetInstance()->GetSceneManager()->GetGameMaster()->GetMedal(); 
		int handle = Game::GetInstance()->GetResourceController()->GetTexture("kirari.png");

		auto p_param = new ParticleEmitterParameter();
		p_param->graphHandle = handle;
		p_param->layer = 2;
		p_param->range_maxSpeed = 10;
		p_param->range_minSpeed = 5;
		p_param->range_maxLifeSpan = 30;
		p_param->range_minLifeSpan = 10;
		p_param->range_maxEmitCount = 20;
		p_param->range_minEmitCount = 10;
		p_param->emitSpan = 2;
		p_param->emitterLifeSpan = 10;
		manager->AddObject(ObjectFactory::Create<ParticleEmitter>(transform->GetThis<Transform>(), p_param, manager
			));
		Game::GetInstance()->GetSceneManager()->GetGameMaster()->AddScore(1000);
	}
}



void Framework::Medal::PreInitialize()
{
}

std::shared_ptr<Framework::MapChipObject> Framework::Medal::Clone(Vector3 position)
{
	auto transform = ObjectFactory::Create<Transform>(position);
	return ObjectFactory::Create<Medal>(
		transform, manager->GetThis<GameObjectManager>())->GetThis<MapChipObject>();
}

void Framework::Medal::Initialize()
{
	texture = ObjectFactory::Create<Resource_Texture>("Medal_1.png", transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(16, 16)), GetThis<GameObject>());

}

bool Framework::Medal::OnUpdate()
{
	Game::GetInstance()->GetResourceController()->AddGraph(texture);
	return true;
}

bool Framework::MapChipObject::Release()
{
	shp_collisionRect->Releace();
	shp_collisionRect = nullptr;
	return true;
}

Framework::ChildSeedSpawner::ChildSeedSpawner(std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_manager->GetThis<GameObjectManager>())
{
	tag = ObjectTag::item;
}

Framework::ChildSeedSpawner::~ChildSeedSpawner()
{
}

void Framework::ChildSeedSpawner::Hit(std::shared_ptr<GameObject> other)
{
	if (other->GetObjectTag() == ObjectTag::player) {
		other->GetThis<Player>()->AddPlayerChild();
	}
}

void Framework::ChildSeedSpawner::PreInitialize()
{
}

std::shared_ptr<Framework::MapChipObject> Framework::ChildSeedSpawner::Clone(Vector3 position)
{
	auto transform = ObjectFactory::Create<Transform>(position);
	return ObjectFactory::Create<ChildSeedSpawner>(
		transform, manager->GetThis<GameObjectManager>())->GetThis<MapChipObject>();

}

void Framework::ChildSeedSpawner::Initialize()
{
	texture = ObjectFactory::Create<Resource_Texture>("sample5.png", transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(16, 16)), GetThis<GameObject>());

}

bool Framework::ChildSeedSpawner::OnUpdate()
{
	Game::GetInstance()->GetResourceController()->AddGraph(texture);
	return true;
}

Framework::ChildSeedSpawner::ChildSeedSpawner(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)

	:MapChipObject(arg_transform->GetThis<Transform>(), arg_manager->GetThis<GameObjectManager>()) {
	tag = ObjectTag::item;
}

Framework::MapChip_Bat::MapChip_Bat(std::shared_ptr<GameObjectManager> arg_manager) : MapChipObject(arg_manager->GetThis<GameObjectManager>())
{
	tag = ObjectTag::spawner;
}
std::shared_ptr<Framework::MapChipObject> Framework::MapChip_Bat::Clone(Vector3 position)
{
	auto transform = ObjectFactory::Create<Transform>(position);
	return ObjectFactory::Create<MapChip_Bat>(transform, manager->GetThis<GameObjectManager>());
}
bool Framework::MapChip_Bat::OnUpdate()
{
	return true;
}
void Framework::MapChip_Bat::Initialize()
{
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(16, 16)), GetThis<GameObject>());

	
}
void Framework::MapChip_Bat::Replace()
{
	if (isClone) {
		auto enemyTransform = ObjectFactory::Create<Transform>(transform->GetPosition());
		manager->AddObject_Init(ObjectFactory::Create<Bat>(enemyTransform, manager));
	}
}
Framework::MapChip_Bat::MapChip_Bat(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_transform, arg_manager->GetThis<GameObjectManager>())
{
	tag = ObjectTag::spawner;
	isClone = true;
}


Framework::MapChip_Teresa::MapChip_Teresa(std::shared_ptr<GameObjectManager> arg_manager) : MapChipObject(arg_manager->GetThis<GameObjectManager>())
{
	tag = ObjectTag::none;
}
std::shared_ptr<Framework::MapChipObject> Framework::MapChip_Teresa::Clone(Vector3 position)
{
	auto transform = ObjectFactory::Create<Transform>(position);
	return ObjectFactory::Create<MapChip_Teresa>(transform, manager->GetThis<GameObjectManager>());
}
bool Framework::MapChip_Teresa::OnUpdate()
{
	return true;
}
void Framework::MapChip_Teresa::Initialize()
{
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(16, 16)), GetThis<GameObject>());

	
}
void Framework::MapChip_Teresa::Replace()
{
	if (isClone) {
		auto enemyTransform = ObjectFactory::Create<Transform>(transform->GetPosition());
		manager->AddObject_Init(ObjectFactory::Create<Teresa>(enemyTransform, manager));
	}
}
Framework::MapChip_Teresa::MapChip_Teresa(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_transform, arg_manager->GetThis<GameObjectManager>())
{
	tag = ObjectTag::none;
	isClone = true;
}

Framework::MapChip_reset::MapChip_reset(std::shared_ptr<GameObjectManager> arg_manager)
	:MapChipObject(arg_manager->GetThis<GameObjectManager>())
{
	tag = ObjectTag::spawner;
}

Framework::MapChip_reset::~MapChip_reset()
{
}

void Framework::MapChip_reset::Hit(std::shared_ptr<GameObject> other)
{
	if (other->GetObjectTag() == ObjectTag::supporter) {
		SetIsDead(true);
		Game::GetInstance()->GetSceneManager()->GetGameMaster()->GetMedal();
		int handle = Game::GetInstance()->GetResourceController()->GetTexture("kirari.png");

		auto p_param = new ParticleEmitterParameter();
		p_param->graphHandle = handle;
		p_param->layer = 2;
		p_param->range_maxSpeed = 10;
		p_param->range_minSpeed = 5;
		p_param->range_maxLifeSpan = 30;
		p_param->range_minLifeSpan = 10;
		p_param->range_maxEmitCount = 20;
		p_param->range_minEmitCount = 10;
		p_param->emitSpan = 2;
		p_param->emitterLifeSpan = 10;
		manager->AddObject(ObjectFactory::Create<ParticleEmitter>(transform->GetThis<Transform>(), p_param, manager
			));
		Game::GetInstance()->GameReset();
	}
}

void Framework::MapChip_reset::PreInitialize()
{
}

std::shared_ptr<Framework::MapChipObject> Framework::MapChip_reset::Clone(Vector3 position)
{
	auto transform = ObjectFactory::Create<Transform>(position);
	return ObjectFactory::Create<MapChip_reset>(
		transform, manager->GetThis<GameObjectManager>())->GetThis<MapChipObject>();
}

void Framework::MapChip_reset::Initialize()
{
	texture = ObjectFactory::Create<Resource_Texture>("Medal_1.png", transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(32, 32, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(16, 16)), GetThis<GameObject>());

}

bool Framework::MapChip_reset::OnUpdate()
{
	Game::GetInstance()->GetResourceController()->AddGraph(texture);
	return true;
}

Framework::MapChip_reset::MapChip_reset(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager) :MapChipObject(arg_transform->GetThis<Transform>(), arg_manager->GetThis<GameObjectManager>())
{
	tag = ObjectTag::item;
}
