#pragma once
#include"GameObjectManager.h"
#include"Resource.h"
namespace Framework {
	class Board:public GameObject
	{
	public:
		Board(int arg_width,int arg_height,int arg_edgeSize,int arg_boardColor,int arg_edgeColor,std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager);
		void SetText(int  index,std::string arg_text);
		void AddText(int color,std::string, Vector3 pos);
		void Initialize()override;
		void PreInitialize()override;
		bool OnUpdate()override;
	private:
		int baseColor,edgeColor;
		std::vector< std::shared_ptr< Resource_Text_String>> vec_shp_texts;
		std::shared_ptr<Resource_Rect> outRect, inRect;
		int width, height, edgeSize;
	};

}