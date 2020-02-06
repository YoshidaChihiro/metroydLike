#pragma once
#include"ButiMath.h"
#include"DxLib.h"
namespace Framework {
	class Input
	{

		
		public:


			~Input() {};

			static void Initialize();

			static void Update();

			static bool GetKeyDown(int keyCode);

			static bool GetKeyUp(int keyCode);

			static bool GetKey(int keyCode);

			static bool GetButtonDown(int code);

			static bool GetButton(int code);

			static float GetLettStickHolizon();

			static float GetLettStickVertical();

			static float GetRightStickHolizon();

			static float GetRightStickVertical();

			static Vector2 GetMousePos();

			static bool GetMouseButton(const unsigned int button);

			static bool GetMouseButtonDown(const unsigned int button);

			static bool GetMouseButtonUp(const unsigned int button);

		private:
			Input() {};
			static XINPUT_STATE buttonState;
			static XINPUT_STATE prevButtonState;
			static char keyState[256], prevKeyState[256];
			static int mouseButtonState, prevMouseButtonState;
	};
}

