#include "Cursol.h"
#include"Game.h"
Framework::Cursol::Cursol(std::shared_ptr<Transform> shp_arg_player_transform, std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_gameObjectManager)
	:GameObject(shp_arg_player_transform,shp_arg_gameObjectManager)
{
	tag = ObjectTag::supporter;
	transform->SetBaseTransform(shp_arg_transform->GetThis<Transform>() );
}

bool Framework::Cursol::OnUpdate()
{
	Vector3 move=
		Vector3(
		Input::GetRightStickHolizon(),
		-1*Input::GetRightStickVertical(),0
		);
	
	//auto modify = Vector3((Vector2)(Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetScrollModify()));
	transform->localPosition += move * 5;

	if (transform->localPosition.GetLengthSqr()>128*128) {
		
		
		transform->localPosition =  transform->localPosition.GetNormalize()*128;
	}

	if (move.GetLength() == 0) {
		transform->localPosition =Vector3();
	}
	else
	{

		Game::GetInstance()->GetResourceController()->AddGraph(shp_texture, 2);
	}
	return true;
}

void Framework::Cursol::Initialize()
{

	shp_texture = ObjectFactory::Create<Resource_Texture>("cursol.png", transform, false, false);
}

std::shared_ptr<Framework::Transform> Framework::Cursol::GetWorldTransform()
{
	
	return transform;
}
