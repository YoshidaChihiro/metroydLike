#include "Board.h"
#include"Game.h"



Framework::Board::Board(int arg_width, int arg_height, int arg_edgeSize, int arg_boardColor, int arg_edgeColor, std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager)
	:GameObject(arg_transform->GetThis<Transform>(), arg_manager->GetThis<GameObjectManager>())
{
	width = arg_width;
	height = arg_height;
	edgeSize = arg_edgeSize;
	baseColor = arg_boardColor;
	edgeColor = arg_edgeColor;
}

void Framework::Board::SetText(int index, std::string arg_text)
{
	vec_shp_texts.at(index)->text = arg_text;
}

void Framework::Board::AddText(int color, std::string text, Vector3 pos)
{
	auto textTransform = ObjectFactory::Create<Transform>(pos);
	textTransform->baseTransform = transform;
	vec_shp_texts.push_back(ObjectFactory::Create<Resource_Text_String>(text,textTransform,color,true,"simpleBit"));
}

void Framework::Board::Initialize()
{
}

void Framework::Board::PreInitialize()
{
	outRect = ObjectFactory::Create<Resource_Rect>(width, height, edgeColor, transform, false);
	inRect = ObjectFactory::Create<Resource_Rect>(width-edgeSize*2, height-edgeSize*2, baseColor, transform, false);
}

bool Framework::Board::OnUpdate()
{
	Game::GetInstance()->GetResourceController()->AddGraph(outRect,1);
	Game::GetInstance()->GetResourceController()->AddGraph(inRect,1);

	
	for (auto itr = vec_shp_texts.begin(); itr != vec_shp_texts.end(); itr++) {
		Game::GetInstance()->GetResourceController()->AddGraph(*itr,1);
	}

	return true;
}
