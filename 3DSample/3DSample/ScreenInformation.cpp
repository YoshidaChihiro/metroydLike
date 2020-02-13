#include "ScreenInformation.h"

void Framework::ScreenInformation::SetScrollModify(Vector2 arg_modify) {
	if (arg_modify.x < screenWidth / 2)
		arg_modify.x = screenWidth / 2;
	if (arg_modify.y < screenHeight / 2)
		arg_modify.y = screenHeight / 2;
	if (arg_modify.x > fieldWidth - screenWidth / 2)
		arg_modify.x = fieldWidth - screenWidth / 2;
	if (arg_modify.y > fieldHeight - screenHeight / 2)
		arg_modify.y = fieldHeight - screenHeight / 2;
	scrollModify = arg_modify - Vector2(screenWidth / 2, screenHeight / 2)+Vector2(-glidSize/2,glidSize/2);
}