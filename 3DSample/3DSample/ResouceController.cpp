#include "ResouceController.h"
Framework::ResouceController::ResouceController(int screenWidth, int screenHeight)
{
	unq_screenInformation = std::make_unique<ScreenInformation>(screenWidth, screenHeight);
	vec_texturesLayers.push_back(std::vector< std::shared_ptr<Resource_Texture>>());
}

void Framework::ResouceController::Draw()
{
	for (int i = 0; i < vec_texturesLayers.size(); i++) {

		for (auto itr = vec_texturesLayers.at(i).begin(); itr != vec_texturesLayers.at(i).end(); itr++) {
			(*itr)->Draw();
		}

		vec_texturesLayers.at(i).clear();
	}

	for (auto itr = vec_texts.begin(); itr != vec_texts.end(); itr++) {
		(*itr)->Draw();
	}
	vec_texts.clear();

	

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

void Framework::ResouceController::LoadCreateFont(std::string fontName, std::string fontSourceName, int size, int thick, int fontType)
{
	int r = CreateFontToHandle(fontSourceName.c_str(), size, thick, fontType);
	if (r != -1) {
		fontResourceMap.emplace(fontName, ObjectFactory::Create<Resource_Font>(r,size));
	}
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

std::shared_ptr<Framework::Resource_Font> Framework::ResouceController::GetFont(std::string fontName)
{
	return fontResourceMap.at(fontName)->GetThis<Resource_Font>();
}

void Framework::ResouceController::AddGraph(std::shared_ptr<Resource_Texture> shp_arg_resource_textue,int layer)
{
	if (layer + 1 > vec_texturesLayers.size()) {
		return;
	}
	vec_texturesLayers.at(layer). push_back(shp_arg_resource_textue->GetThis<Resource_Texture>());
}

void Framework::ResouceController::AddLayer(int addLayerCount)
{
	for (int i = 0; i < addLayerCount; i++) {
		vec_texturesLayers.push_back(std::vector< std::shared_ptr<Resource_Texture>>());
	}

}

void Framework::ResouceController::AddText(std::shared_ptr<Resource_Text_String> shp_arg_resource_text)
{
	vec_texts.push_back(shp_arg_resource_text->GetThis<Resource_Text_String>());
}

void Framework::ResouceController::AddMV1(std::shared_ptr<Resource_MV1> shp_arg_resource_MV1)
{

	vec_mv1s.push_back(shp_arg_resource_MV1->GetThis<Resource_MV1>());
}

void Framework::ResouceController::AddSound(std::shared_ptr<Resource_Sound> shp_arg_resource_sound)
{

	vec_sounds.push_back(shp_arg_resource_sound->GetThis<Resource_Sound>());
}

