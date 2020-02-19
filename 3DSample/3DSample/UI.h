#pragma once
#include"Resource.h"
#include"GameObjectManager.h"
namespace Framework{
class UI:public GameObject
{
public:
	UI(std::shared_ptr<GameObjectManager> arg_manager);
	bool OnUpdate()override;
	void Initialize()override;
	void PreInitialize()override;

private:


	int color = GetColor(255, 255, 255);
	std::shared_ptr<Transform> scorePos;
	std::shared_ptr< Resource_Text_String_UI> score;
	std::shared_ptr<Transform> timePos;
	std::shared_ptr< Resource_Text_String_UI> time;
	
};

}