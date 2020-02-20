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

	struct Resource_Font :Resource_base {
		Resource_Font(int arg_handle,int arg_size) :handle(arg_handle),size(arg_size){};

		int handle;
		int size;
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
		virtual bool Draw();
		int handle;
		std::shared_ptr<Transform> transform;
		int xFlip = 0;
		int yFlip = 0;
		int width = 0;
		int height = 0;
	protected:

		Resource_Texture(std::shared_ptr<Transform> arg_transform);
	};
	struct Resource_UI :Resource_Texture {
		Resource_UI(int arg_handle, std::shared_ptr<Transform> arg_transform, bool isXFlip, bool isYFlip);
		Resource_UI(std::string key, std::shared_ptr<Transform> arg_transform, bool isXFlip, bool isYFlip);
		~Resource_UI();
		bool Draw()override;
	};
	struct Resource_Rect :Resource_Texture {
		Resource_Rect(int arg_width,int arg_height,unsigned int arg_color, std::shared_ptr<Transform> arg_transform,bool arg_isAbs);
		~Resource_Rect();
		bool Draw()override;
		bool isAbs;
		unsigned int color;
	};
	struct Resource_Pixel :Resource_Texture {
		Resource_Pixel( Vector4& arg_color, std::shared_ptr<Transform> arg_transform);
		~Resource_Pixel();
		bool Draw()override;
		int color;
	};
	struct Resource_Text_String :Resource_Texture {
		Resource_Text_String(std::string source, std::shared_ptr<Transform> arg_transform, int color, bool isCenter, std::string fontName);
		~Resource_Text_String();
		bool Draw() override;
		std::string text;
		bool isCenter;
		int color;
		float xModify;
		std::shared_ptr<Resource_Font> shp_resource_font;
	};
	enum class Justification {
		center,left,right
	};
	struct Resource_Text_String_UI :Resource_Texture {
		Resource_Text_String_UI(std::string source, std::shared_ptr<Transform> arg_transform, int color,Justification arg_just, std::string fontName);
		~Resource_Text_String_UI();
		bool Draw() override;
		std::string text;
		Justification just;
		int color;
		float xModify;
		void SetText(std::string arg_text);
		std::shared_ptr<Resource_Font> shp_resource_font;
	};

	struct Resource_Sound :Resource_base {
		Resource_Sound(int arg_handle, int playType, bool topPositionFlag);
		Resource_Sound(std::string key, int playType, bool topPositionFlag);
		~Resource_Sound();
		bool SoundPlay();
		int handle;
		int playType = DX_PLAYTYPE_BACK;
		bool topPositionFlag = true;
	};
}

