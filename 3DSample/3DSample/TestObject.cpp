#include "TestObject.h"

#include "Game.h"
#include"Particle.h"
Framework::TestObject::TestObject(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager):GameObject(shp_arg_transform,shp_arg_gameObjectManager)
{
	auto a =std::make_shared< Rectangle>(100, 100, Vector2(0,0));
	auto b = std::make_shared< Rectangle>(100, 100, Vector2(50,-50));
	if (a->IsIntersects(b)) {
		int i = 0;
	}
}

Framework::TestObject::~TestObject()
{
}

void Framework::TestObject::Hit(std::shared_ptr<GameObject> other)
{
}

void Framework::TestObject::PreInitialize()
{
	handle = Game::GetInstance()->GetResourceController()->GetTexture("sample.png");
	shp_texture = ObjectFactory::Create<Resource_Texture>("sample.png", transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(16,16,transform->GetPosition().GetVector2(),Rectangle::GetRectangleOuterCircleRadius(16,16)),GetThis<GameObject>());
}

bool Framework::TestObject::OnUpdate()
{
	shp_collisionRect->OnUpdate();
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect,1);

	
	if (Input::GetKey(KEY_INPUT_D)) {
		transform->localPosition.x++;
	}
	if (Input::GetKey(KEY_INPUT_A)) {
		transform->localPosition.x--;
	}
	if (Input::GetKey(KEY_INPUT_W)) {
		transform->localPosition.y--;
	}
	if (Input::GetKey(KEY_INPUT_S)) {
		transform->localPosition.y++;
	}
	if (Input::GetKeyDown(KEY_INPUT_SPACE)) {
		auto scene = ObjectFactory::Create<TitleScene>();
		Game::GetInstance()->GetSceneManager()->ChangeScene(scene);
	}
	return true;
}
