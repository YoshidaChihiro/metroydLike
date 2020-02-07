#pragma once
#include "Util.h"
#include "Transform.h"
#include "DxLib.h"
namespace Framework {
	struct Resource_base:public IObject
	{
		void PreInitialize()override {};
		void Initialize()override {};
	};

	struct Resource_MV1 :Resource_base {
		Resource_MV1(int arg_handle, std::shared_ptr<Transform> arg_transform) :handle(arg_handle), transform(arg_transform->GetThis<Transform>()) {};
		
		bool Draw();
		int handle;
		std::shared_ptr<Transform> transform;
	};
	struct Resource_Texture :Resource_base {
		Resource_Texture(int arg_handle, std::shared_ptr<Transform> arg_transform, bool isXFlip, bool isYFlip);
		Resource_Texture(std::string key, std::shared_ptr<Transform> arg_transform, bool isXFlip, bool isYFlip);
		~Resource_Texture();
		bool Draw();
		int handle;
		std::shared_ptr<Transform> transform;
		int xFlip=0;
		int yFlip=0;
	}; 
	struct Resource_Sound :Resource_base {
		Resource_Sound(int arg_handle) :handle(arg_handle) {};
		
		bool Play() ;
		int handle;
	};
}

