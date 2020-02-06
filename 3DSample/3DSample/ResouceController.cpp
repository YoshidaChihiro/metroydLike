#include "ResouceController.h"

void Framework::ResouceController::Draw()
{
	for (auto itr = vec_textures.begin(); itr != vec_textures.end(); itr++) {
		(*itr)->Draw();
	}
	vec_textures.clear();
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

