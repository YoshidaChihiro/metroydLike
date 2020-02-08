#include "ResouceController.h"

void Framework::ResouceController::Draw()
{
	for (auto itr = vec_textures.begin(); itr != vec_textures.end(); itr++) {
		(*itr)->Draw();
	}
	vec_textures.clear();
}

void Framework::ResouceController::LoadTexture(std::string fileName, std::string filePath)
{

	textureHandleMap.emplace(fileName, LoadGraph((filePath + fileName).c_str()));
}

void Framework::ResouceController::LoadSound(std::string fileName, std::string filePath)
{
	soundHandleMap.emplace(fileName, LoadSoundMem((filePath + fileName).c_str()));
}

void Framework::ResouceController::LoadMV1(std::string fileName, std::string filePath)
{
	mv1HandleMap.emplace(fileName, MV1LoadModel((filePath+fileName).c_str()));
}


int Framework::ResouceController::GetTexture(std::string resourceName)
{
	for (auto itr = textureHandleMap.begin(); itr != textureHandleMap.end(); itr++) {
		if (itr->first == resourceName) {
			return itr->second;
		}
	}
	return 0;
}

int Framework::ResouceController::GetSound(std::string resourceName)
{
	for (auto itr = soundHandleMap.begin(); itr != soundHandleMap.end(); itr++) {
		if (itr->first == resourceName) {
			return itr->second;
		}
	}
	return 0;
}

int Framework::ResouceController::GetMV1(std::string resourceName)
{
	for (auto itr = mv1HandleMap.begin(); itr != mv1HandleMap.end(); itr++) {
		if (itr->first == resourceName) {
			return itr->second;
		}
	}
	return 0;
}

void Framework::ResouceController::AddGraph(std::shared_ptr<Resource_Texture> shp_arg_resource_textue)
{
	vec_textures.push_back(shp_arg_resource_textue->GetThis<Resource_Texture>());
}

void Framework::ResouceController::AddMV1(std::shared_ptr<Resource_MV1> shp_arg_resource_MV1)
{

	vec_mv1s.push_back(shp_arg_resource_MV1->GetThis<Resource_MV1>());
}

void Framework::ResouceController::AddSound(std::shared_ptr<Resource_Sound> shp_arg_resource_sound)
{

	vec_sounds.push_back(shp_arg_resource_sound->GetThis<Resource_Sound>());
}

