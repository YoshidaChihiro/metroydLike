#pragma once
#include "UI.h"
#include"Game.h"
Framework::UI::UI(std::shared_ptr<GameObjectManager> arg_manager)
	:GameObject(
		ObjectFactory::Create<Transform>(),arg_manager->GetThis<GameObjectManager>()
	)
{
}

bool Framework::UI::OnUpdate()
{
	
	score->SetText( "Score::" +std::to_string( (Game::GetInstance()->GetSceneManager()->GetGameMaster()->GetScore())));
	time->SetText("Time::" + std::to_string((Game::GetInstance()->GetSceneManager()->GetGameMaster()->GetNowTime().count())));
	Game::GetInstance()->GetResourceController()->AddGraph(score);
	Game::GetInstance()->GetResourceController()->AddGraph(time);
	return true;
}

void Framework::UI::Initialize()
{
}

void Framework::UI::PreInitialize()
{
	scorePos = ObjectFactory::Create<Transform>(Vector3(960, 0, 0));
	score = ObjectFactory::Create<Resource_Text_String_UI>("Score::", scorePos, color, Justification::right, "testFont");
	timePos = ObjectFactory::Create<Transform>(Vector3(0, 0, 0));
	time = ObjectFactory::Create<Resource_Text_String_UI>("Time::", timePos, color, Justification::left, "testFont");

}
