#include "Input.h"

XINPUT_STATE Framework::Input::buttonState;
XINPUT_STATE Framework::Input::prevButtonState;
char Framework::Input::keyState[256];
char Framework::Input::prevKeyState[256];
int Framework::Input::mouseButtonState;
int Framework::Input::prevMouseButtonState;

void Framework::Input::Initialize()
{
	mouseButtonState = GetMouseInput();
	GetHitKeyStateAll(keyState);
	GetJoypadXInputState(DX_INPUT_PAD1, &buttonState);
}

void Framework::Input::Update()
{
	memcpy(prevKeyState, keyState, sizeof(keyState));
	GetHitKeyStateAll(keyState);
	prevMouseButtonState = mouseButtonState;
	mouseButtonState = GetMouseInput();
	prevButtonState = buttonState;
	GetJoypadXInputState(DX_INPUT_PAD1, &buttonState);
}

bool Framework::Input::GetKeyDown(int keyCode)
{
	return keyState[keyCode] == 1 && prevKeyState[keyCode] == 0;
}

bool Framework::Input::GetKeyUp(int keyCode)
{
	return keyState[keyCode] == 0 && prevKeyState[keyCode] == 1;
}

bool Framework::Input::GetKey(int keyCode)
{
	return keyState[keyCode] == 1;
}

bool Framework::Input::GetButtonDown(int code)
{
	return buttonState.Buttons[code] == TRUE && prevButtonState.Buttons[code] == FALSE;
}

bool Framework::Input::GetButton(int code)
{
	return buttonState.Buttons[code] == TRUE;
}

float Framework::Input::GetLettStickHolizon()
{
	return (float)buttonState.ThumbLX / (float)32767;
}

float Framework::Input::GetLettStickVertical()
{
	return (float)buttonState.ThumbLY/(float)32767;
}

float Framework::Input::GetRightStickHolizon()
{
	return (float)buttonState.ThumbRX / (float)32767;
}

float Framework::Input::GetRightStickVertical()
{
	return (float)buttonState.ThumbRY / (float)32767;
}

Framework::Vector2 Framework::Input::GetMousePos()
{
	int x = 0, y = 0;
	GetMousePoint(&x, &y);
	Vector2 mousePos(x, y);
	return mousePos;
}

bool Framework::Input::GetMouseButton(const unsigned int button)
{
	if (button & mouseButtonState == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Framework::Input::GetMouseButtonDown(const unsigned int button)
{
	if (button & mouseButtonState == 1 && button & prevMouseButtonState == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Framework::Input::GetMouseButtonUp(const unsigned int button)
{
	if (button & mouseButtonState == 0 && button & prevMouseButtonState == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
