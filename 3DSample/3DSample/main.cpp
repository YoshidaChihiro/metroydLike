#include "DxLib.h"
#define BLOCK_SIZE
const int WIN_WIDTH = 650;
const int WIN_HEIGHT = 450;


int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE HPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	//initMethod
	ChangeWindowMode(TRUE);
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	SetWindowSizeExtendRate(1.0);
	SetBackgroundColor(0xff, 0xff, 0xff);
	SetMainWindowText("title");
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	//mainLoop
	while (1) 
	{

		WaitTimer(20);
		if (ProcessMessage() == -1)
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;
	}
	//exitMethod
	DxLib_End();

	return 0;

}