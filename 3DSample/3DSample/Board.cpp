#include "Board.h"
#include"Game.h"
Framework::Board::Board(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:GameObject(arg_transform->GetThis<Transform>(),arg_manager->GetThis<GameObjectManager>())
{
}

void Framework::Board::SetParam(std::string arg_text)
{
	shp_source->text = arg_text;
}

void Framework::Board::Initialize()
{
}

void Framework::Board::PreInitialize()
{
	shp_source = ObjectFactory::Create<Resource_Text_String>("",transform->GetThis<Transform>(),color,true,"testFont");
}

bool Framework::Board::OnUpdate()
{
	Game::GetInstance()->GetResourceController()->AddGraph(shp_source);
	return true;
}
