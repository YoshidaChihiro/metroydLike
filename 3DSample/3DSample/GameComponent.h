#pragma once
#include<memory>
#include"Util.h"
namespace Framework {
	class GameObject;

	class GameComponent:public IObject
	{
	public:
		virtual bool OnUpdate() = 0;

		std::shared_ptr<GameObject> gameObj;
	};

}