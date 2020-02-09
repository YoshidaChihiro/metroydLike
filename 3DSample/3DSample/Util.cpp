#include "Util.h"

void Framework::Util::WStringtoMultiByte(const std::wstring & src, std::string & dest) {
	size_t i;
	char *pMBstr = new char[src.length() * MB_CUR_MAX + 1];
	wcstombs_s(
		&i,
		pMBstr,
		src.length() * MB_CUR_MAX + 1,
		src.c_str(),
		_TRUNCATE	//‚·‚×‚Ä•ÏŠ·‚Å‚«‚È‚©‚Á‚½‚çØ‚èÌ‚Ä
	);
	dest = pMBstr;
	delete[] pMBstr;
}

void Framework::ThrowButiException_Runtime(const std::wstring & message1, const std::wstring & message2, const std::wstring & message3)
{
	std::wstring outputMessage = message1;
	outputMessage += L"\n";
	outputMessage += message2;
	outputMessage += L"\n";
	outputMessage += message3;
	std::string Dest;
	Util::WStringtoMultiByte(outputMessage, Dest);
	throw std::runtime_error(Dest);
}

void Framework::ThrowButiException_Runtime(const std::string & meesage1, const std::string & message2, const std::string & message3) {
	//throw runtime_error function
	std::string outputMessage = meesage1;
	outputMessage += "\n";
	outputMessage += message2;
	outputMessage += "\n";
	outputMessage += message3;
	throw std::runtime_error(outputMessage);
}

void Framework::IObject::SetCreated(bool b) {
	isCreated = b;
};
template<typename T>
std::shared_ptr<void> Framework::SharedPtrToVoid(const std::shared_ptr<T>& srcPtr) {

};
template<typename T>
std::shared_ptr<T> Framework::VoidToShared(const std::shared_ptr<void>& SrcPtr) {

}
std::shared_ptr< std::random_device> Framework::ButiRandom::shp_rnd_device=nullptr;
std::shared_ptr<std::mt19937>Framework::ButiRandom::shp_mt=nullptr;// 
std::shared_ptr< std::uniform_int_distribution<>> Framework::ButiRandom::shp_randRange=nullptr;

void Framework::ButiRandom::Initialize()
{
	 shp_rnd_device = std::make_shared<std::random_device>();
	shp_mt= std::make_shared<std::mt19937>((*shp_rnd_device)());
	 shp_randRange = std::make_shared< std::uniform_int_distribution<>>(0, 1);

}
