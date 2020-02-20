#include "Image.h"
#include"Game.h"
Framework::Image::Image(std::string resource_Name, std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:GameObject(arg_transform->GetThis<Transform>(), arg_manager->GetThis<GameObjectManager>())
{
	source = resource_Name;
}

void Framework::Image::Initialize()
{
	auto handle = Game::GetInstance()->GetResourceController()->GetTexture(source);
	shp_texture = ObjectFactory::Create<Resource_Texture>(handle, transform, false, false);
}

void Framework::Image::PreInitialize()
{
}

bool Framework::Image::OnUpdate()
{
	Game::GetInstance()->GetResourceController()->AddGraph(shp_texture, 1);
	return true;
}
