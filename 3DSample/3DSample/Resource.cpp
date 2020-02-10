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
	if(DrawRotaGraph3(transform->GetPosition().x-width/2-modify.x,transform->GetPosition().y-height/2-modify.y,0,0,transform->GetScale().x,transform->GetScale().y,transform->GetRotation().z,handle,true,xFlip,yFlip)==0)
	return true;
	else {
		return false;
	}
}

Framework::Resource_Texture::Resource_Texture(std::shared_ptr<Transform> arg_transform) : transform(arg_transform->GetThis<Transform>())
{
}

bool Framework::Resource_Sound::Play()
{
	return false;
}





Framework::Resource_Text_String::Resource_Text_String(std::string source, std::shared_ptr<Transform> arg_transform, int arg_color, bool arg_isCenter, std::string fontName)
	:Resource_Texture(arg_transform)
{
	text = source;
	color = arg_color;
	isCenter = arg_isCenter;
	shp_resource_font = Game::GetInstance()->GetResourceController()->GetFont(fontName);
}

Framework::Resource_Text_String::~Resource_Text_String()
{
}

bool Framework::Resource_Text_String::Draw()
{
	if (!isCenter) {
		DrawFormatStringToHandle(transform->GetPosition().GetVector2().x, transform->GetPosition().GetVector2().y, color, shp_resource_font->handle,text.c_str());
	}
	else
	{
		float xModify = shp_resource_font->size*(float)text.size() / 4;
		DrawFormatStringToHandle(transform->GetPosition().GetVector2().x-xModify, transform->GetPosition().GetVector2().y-shp_resource_font->size/2, color, shp_resource_font->handle, text.c_str());
	}
	return true;
}
