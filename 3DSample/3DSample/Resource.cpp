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
}
Framework::Resource_Texture::Resource_Texture(std::string key, std::shared_ptr<Transform> arg_transform, bool isXFlip, bool isYFlip) : transform(arg_transform->GetThis<Transform>()) {
	if (isXFlip) {
		xFlip = 1;
	}
	if (isYFlip) {
		yFlip = 1;
	}
	handle = (Game::GetInstance()->GetResourceController()->GetTexture(key));
}
Framework::Resource_Texture::~Resource_Texture()
{
}
;

bool Framework::Resource_Texture::Draw()
{
	if(DrawRotaGraph3(transform->GetPosition().x,transform->GetPosition().y,0,0,transform->GetScale().x,transform->GetScale().y,transform->GetRotation().z,handle,true,xFlip,yFlip)==0)
	return true;
	else {
		return false;
	}
}

bool Framework::Resource_Sound::Play()
{
	return false;
}
