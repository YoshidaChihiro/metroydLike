#include "Sencer.h"
#include"Game.h"
#include"GameObjectManager.h"

Framework::Sencer::Sencer(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager, std::vector<ObjectTag> arg_vec_checkTags, std::shared_ptr<GameObject>* arg_output, int arg_width, int arg_height)
	:GameObject(arg_transform->GetThis<Transform>(), arg_manager->GetThis<GameObjectManager>()), vec_checkTags(arg_vec_checkTags),width(arg_width),height(arg_height)
{
	tag = ObjectTag::sencer;
	output = (arg_output);
}

Framework:: Sencer::~Sencer()
{
}

void Framework::Sencer::Initialize()
{
	auto handle = Game::GetInstance()->GetResourceController()->GetTexture("orange.png");

	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(width, height, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(16, 16)), GetThis<GameObject>());

}

bool Framework::Sencer::Update()
{
	shp_collisionRect->Update();
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect);

	return true;
}

void Framework::Sencer::Hit(std::shared_ptr<GameObject> other)
{
	for (auto itr = vec_checkTags.begin(); itr != vec_checkTags.end(); itr++) {
		if ((*itr) == other->GetObjectTag()) {
			*output = other;
		}
	}
}
