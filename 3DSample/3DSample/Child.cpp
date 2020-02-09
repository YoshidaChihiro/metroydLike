#include "Child.h"
#include "Game.h"
#include "Player.h"

Framework::Child::Child(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager) :GameObject(shp_arg_transform, shp_arg_gameObjectManager)
{
	velocity = Vector2(0.0f, 0.0f);
	speed = 1.0f;
	state = NormalMode;

	handle = LoadGraph("Resource/Texture/orange.png");
	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
}

Framework::Child::~Child() {}

void Framework::Child::Hit(std::shared_ptr<GameObject> other)
{
	int color = GetColor(0, 0, 0);
	auto text = ObjectFactory::Create<Resource_Text_String>("Hit", transform, color, false);
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);

}

void Framework::Child::PreInitialize()
{
	handle = Game::GetInstance()->GetResourceController()->GetTexture("orange.png");
	//shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
	shp_collisionRect = ObjectFactory::Create<Collision2D_Rectangle>(std::make_shared<Rectangle>(16, 16, transform->GetPosition().GetVector2(), Rectangle::GetRectangleOuterCircleRadius(16, 16)), GetThis<GameObject>());
}

bool Framework::Child::Update() {
	shp_collisionRect->Update();
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture);
	Game::GetInstance()->GetCollision2DManager()->AddCollision(shp_collisionRect);

	/*switch (Player::GetState())
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}*/
	transform->localPosition += velocity * speed;

	return true;
}