#pragma once
#include "ButiMath.h"
namespace Framework {
	class ScreenInformation
	{
	public:
		ScreenInformation(int arg_width, int arg_height):screenWidth(arg_width),screenHeight(arg_height) {

		};
		Vector2 GetScrollModify()const {
			return scrollModify;
		}
		int  GetScreenWidth()const {
			return screenWidth;
		}
		int GetScreenHeight()const {
			return screenHeight;
		}
		int GetGlidSize()const {
			return glidSize;
		}

		void SetWidth(int arg_width) { screenWidth = arg_width; }
		void SetHighr(int arg_height) { screenHeight = arg_height; }
		void SetGlidSize(int arg_glidSize) { glidSize = arg_glidSize; }
		void SetScrollModify(Vector2  arg_modify) { scrollModify = arg_modify; }
	private:
		Vector2 scrollModify;
		int screenWidth, screenHeight, glidSize;
	};

}