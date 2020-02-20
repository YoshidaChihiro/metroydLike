#include "ChildSeed.h"
#include "Game.h"
#include"MapChipObject.h"
#include"Sencer.h"

Framework::ChildSeed::ChildSeed(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager) :GameObject(shp_arg_transform, shp_arg_gameObjectManager)
{
	gravity = 0.3f;
	maxFallSpeed = 3.0f;

	phisicsForce = Vector3(0, 0, 0);
	sucideTimer.Start();
	tag = ObjectTag::seed;
}


Framework::ChildSeed::~ChildSeed() {
}

void Framework::ChildSeed::Hit(std::shared_ptr<GameObject> other)
{
	if (other->GetObjectTag() == ObjectTag::supporter) {
		SetIsDead(true);
		Game::GetInstance()->GetSceneManager()->GetGameMaster()->AddScore(100);
		Game::GetInstance()->GetResourceController()->AddSound(shp_sound_medal);
		player = manager->SerchGameObject(ObjectTag::player);
		if (player)
			player->GetThis<Player>()->AddPlayerChild();
		return;
	}

	if (other->GetObjectTag() == ObjectTag::obstacle) {
		auto otherRect = other->GetThis<MapChipObject>()->GetRectangle();
		float overlap = 0.0f;

		Vector3 delta = (Vector3)(other->transform->GetPosition() - transform->GetPosition());

		if (abs(delta.x) < abs(delta.y))
		{
			if (delta.y > 0) {
				overlap = shp_collisionRect->rect->GetBottom() - otherRect->GetTop();
				overlap = abs(overlap);
				transform->localPosition.y -= overlap;

				isGround = true;
				phisicsForce.y = 0.0f;

			}
			else
				if (delta.y < 0) {
					overlap = otherRect->GetBottom() - shp_collisionRect->rect->GetTop();

					overlap = abs(overlap);
					transform->localPosition.y += overlap;
				}
		}
		else if (abs(delta.x) > abs(delta.y)) {
			if (delta.x > 0) {
				overlap = shp_collisionRect->rect->GetRight() - otherRect->GetLeft();
				overlap = abs(overlap);
				transform->localPosition.x -= overlap;

			}
			else
				if (delta.x < 0) {
					overlap = otherRect->GetRight() - shp_collisionRect->rect->GetLeft();
					overlap = abs(overlap);
					transform->localPosition.x += overlap;

				}
		}
		shp_collisionRect->OnUpdate();
	}
}

void Framework::ChildSeed::PreInitialize()
{
	auto handle = Game::GetInstance()->GetResourceController()->GetTexture("seed.png");
	shp_sound_medal = ObjectFactory::Create<Resource_Sound>("Coin.wav", DX_PLAYTYPE_BACK, true);


	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(8, 8, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(8, 8)), GetThis<GameObject>());
}

bool Framework::ChildSeed::OnUpdate() {
	if (sucideTimer.Update()) {
		SetIsDead(true);
	}
	shp_collisionRect->OnUpdate();

	phisicsForce.y += gravity;
	if (phisicsForce.y > maxFallSpeed) {
		phisicsForce.y = maxFallSpeed;
	}

	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture, 1);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect, 2);
	isGround = false;
	return true;
}

bool Framework::ChildSeed::Release()
{

	shp_collisionRect->Releace();
	shp_collisionRect = nullptr;
	shp_texture = nullptr;
	shp_sound_medal = nullptr;
	player = nullptr;
	return true;
}
