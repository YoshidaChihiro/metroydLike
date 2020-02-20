#include "Resource.h"
#include"Game.h"
bool Framework::Resource_MV1::Draw()
{
	return true;
}

Framework::Resource_Texture::Resource_Texture(int arg_handle, std::shared_ptr<Transform> arg_transform, bool isXFlip, bool isYFlip) :handle(arg_handle), transform(arg_transform->GetThis<Transform>()) {
	if (isXFlip) {
		xFlip = 1;
	}
	if (isYFlip) {
		yFlip = 1;
	}
	GetGraphSize(handle, &width, &height);
}
Framework::Resource_Texture::Resource_Texture(std::string key, std::shared_ptr<Transform> arg_transform, bool isXFlip, bool isYFlip) : transform(arg_transform->GetThis<Transform>()) {
	if (isXFlip) {
		xFlip = 1;
	}
	if (isYFlip) {
		yFlip = 1;
	}
	handle = (Game::GetInstance()->GetResourceController()->GetTexture(key));

	GetGraphSize(handle, &width, &height);
}
Framework::Resource_Texture::~Resource_Texture()
{
}
;

bool Framework::Resource_Texture::Draw()
{
	auto modify = Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetScrollModify();
	auto modifiedPos =(Vector3)( transform->GetPosition()-Vector2(width*transform->scale.x/2,height*transform->scale.y/2)-modify);
	if (modifiedPos.x > 992 || modifiedPos.x < -32 || modifiedPos.y>672, modifiedPos.y < -32) {
		return true;
	}
	if (abs(transform->GetRotation().z) != 0 || transform->scale.x != 0 || transform->scale.y != 0) {
		if (DrawRotaGraph3(modifiedPos.x, modifiedPos.y,0,0, transform->scale.x, transform->scale.y,  transform->GetRotation().z, handle, true, xFlip) == 0)
			return true;
	}
	if (!xFlip)
		DrawGraph(modifiedPos.x, modifiedPos.y, handle, true);
	else
		DrawTurnGraph(modifiedPos.x, modifiedPos.y, handle, true);
	return true;
}

Framework::Resource_Texture::Resource_Texture(std::shared_ptr<Transform> arg_transform) : transform(arg_transform->GetThis<Transform>())
{
}

Framework::Resource_Sound::Resource_Sound(int arg_handle, int playType, bool topPositionFlag) : handle(arg_handle) {
	this->playType = playType;
	this->topPositionFlag = topPositionFlag;
}

Framework::Resource_Sound::Resource_Sound(std::string key, int playType, bool topPositionFlag) {
	handle = (Game::GetInstance()->GetResourceController()->GetSound(key));
	this->playType = playType;
	this->topPositionFlag = topPositionFlag;
}

Framework::Resource_Sound::~Resource_Sound()
{
}

bool Framework::Resource_Sound::SoundPlay()
{
	PlaySoundMem(handle, playType, topPositionFlag);
	return true;
}




Framework::Resource_Text_String::Resource_Text_String(std::string source, std::shared_ptr<Transform> arg_transform, int arg_color, bool arg_isCenter, std::string fontName)
	:Resource_Texture(arg_transform)
{
	text = source;
	color = arg_color;
	isCenter = arg_isCenter;
	shp_resource_font = Game::GetInstance()->GetResourceController()->GetFont(fontName);
	xModify = shp_resource_font->size*(float)text.size() / 4;
}

Framework::Resource_Text_String::~Resource_Text_String()
{
}

bool Framework::Resource_Text_String::Draw()
{
	auto modify = Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetScrollModify();
	if (!isCenter) {
		DrawFormatStringToHandle(transform->GetPosition().GetVector2().x+modify.x, transform->GetPosition().GetVector2().y+modify.y, color, shp_resource_font->handle,text.c_str());
	}
	else
	{
		DrawFormatStringToHandle(transform->GetPosition().GetVector2().x - xModify+modify.x, transform->GetPosition().GetVector2().y+modify.y, color, shp_resource_font->handle, text.c_str());
	}
	return true;
}

Framework::Resource_UI::Resource_UI(int arg_handle, std::shared_ptr<Transform> arg_transform, bool isXFlip, bool isYFlip)
	:Resource_Texture(arg_handle,arg_transform,xFlip,yFlip)
{
}

Framework::Resource_UI::Resource_UI(std::string key, std::shared_ptr<Transform> arg_transform, bool isXFlip, bool isYFlip)
	:Resource_Texture(key, arg_transform, xFlip, yFlip)
{
}

Framework::Resource_UI::~Resource_UI()
{
}

bool Framework::Resource_UI::Draw()
{
	auto modify = Vector2(0,0);
	if (DrawRotaGraph3(transform->GetPosition().x - width / 2 - modify.x, transform->GetPosition().y - height / 2 - modify.y, 0, 0, transform->GetScale().x, transform->GetScale().y, transform->GetRotation().z, handle, true, xFlip, yFlip) == 0)
		return true;
	else {
		return false;
	}
}

Framework::Resource_Pixel::Resource_Pixel(Vector4 & arg_color, std::shared_ptr<Transform> arg_transform)
	:Resource_Texture(arg_transform)
{
	color = GetColor(arg_color.x, arg_color.y, arg_color.z);
}

Framework::Resource_Pixel::~Resource_Pixel()
{
}

bool Framework::Resource_Pixel::Draw()
{
	DrawPixel(transform->GetPosition().x, transform->GetPosition().y, color);
	return true;
}

Framework::Resource_Text_String_UI::Resource_Text_String_UI(std::string source, std::shared_ptr<Transform> arg_transform, int arg_color,Justification arg_just, std::string fontName)
	:Resource_Texture(arg_transform)
{
	text = source;
	color = arg_color;
	just = arg_just;
	shp_resource_font = Game::GetInstance()->GetResourceController()->GetFont(fontName);
} 

Framework::Resource_Text_String_UI::~Resource_Text_String_UI()
{
}

bool Framework::Resource_Text_String_UI::Draw()
{
	switch (just)
	{
	case Justification::center:

		DrawFormatStringToHandle(transform->GetPosition().GetVector2().x - xModify, transform->GetPosition().GetVector2().y , color, shp_resource_font->handle, text.c_str());

		break;
	case Justification::left:

		DrawFormatStringToHandle(transform->GetPosition().GetVector2().x, transform->GetPosition().GetVector2().y, color, shp_resource_font->handle, text.c_str());

			break; 
	case Justification::right:
		DrawFormatStringToHandle(transform->GetPosition().GetVector2().x - xModify, transform->GetPosition().GetVector2().y , color, shp_resource_font->handle, text.c_str());

				break;
	default:
		break;
	}
		
		
	return true;
}

void Framework::Resource_Text_String_UI::SetText(std::string arg_text)
{
	text = arg_text;
	if (just == Justification::center) {
		xModify = shp_resource_font->size*(float)text.size() / 4;
		return;
	}
	else if (just == Justification::left) {

	}
	else if (just == Justification::right) {

		xModify = shp_resource_font-> size*(float)text.size()/2+shp_resource_font->size;
	}
}

//Framework::Resource_Rect::Resource_Rect(int arg_width, int arg_height, int arg_color, std::shared_ptr<Transform> arg_transform, bool isAbs)
//	:Resource_Texture(0,transform,false,false),isAbs(isAbs)
//{
//	width=(arg_width); height=(arg_height);
//	color = arg_color;
//}

Framework::Resource_Rect::Resource_Rect(int arg_width,int arg_height,unsigned int arg_color, std::shared_ptr<Transform> arg_transform,bool arg_isAbs)
	:Resource_Texture(0, arg_transform, false, false) {

	width = arg_width;
	height = arg_height;
	color = arg_color;
	isAbs = arg_isAbs;
}

Framework::Resource_Rect::~Resource_Rect()
{
}

bool Framework::Resource_Rect::Draw()
{
	if (isAbs) {
		 DrawBox(transform->GetPosition().x - width / 2, transform->GetPosition().y - height / 2, transform->GetPosition().x + width / 2, transform->GetPosition().y + height / 2, color, true);
		
		return true;
	}

	auto modify = Game::GetInstance()->GetResourceController()->GetScreenInformation()->GetScrollModify();
	auto modifiedPos = (Vector3)(transform->GetPosition() - modify);
	if (modifiedPos.x > width+960 || modifiedPos.x < -width || modifiedPos.y>640+height, modifiedPos.y < -height) {
		return true;
	}
	DrawBox(modifiedPos.x - width / 2, modifiedPos.y - height / 2, modifiedPos.x + width / 2, modifiedPos.y + height / 2, color, true);


	return true;
}
