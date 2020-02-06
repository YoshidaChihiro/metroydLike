#include "TestObject.h"

#include "Game.h"
Framework::TestObject::TestObject(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager):GameObject(shp_arg_transform,shp_arg_gameObjectManager)
{
}

Framework::TestObject::~TestObject()
{
}

void Framework::TestObject::PreInitialize()
{

	//int handle = LoadGraph("Resource/Texture/sample.png");
	shp_texture = ObjectFactory::Create<Resource_Texture>("sample.png", transform, false, false);
}

bool Framework::TestObject::Update()
{
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
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
		auto scene = ObjectFactory::Create<TestScene>();
		Game::GetInstance()->GetSceneManager()->ChangeScene(scene);
	}
	return true;
}
