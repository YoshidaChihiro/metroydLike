#pragma once
#include"Util.h"
#include "GameObjectManager.h"
namespace Framework {
	class IScene:public IObject
	{
	public:
		virtual void Release() =0;
		virtual bool Update() =0;
	protected:
		std::shared_ptr<GameObjectManager> shp_gameObjectManager;
	};
}
