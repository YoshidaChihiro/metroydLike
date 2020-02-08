#pragma once
#include <string>
#include <vector>
namespace Framework {
	class StringHelper
	{
	public:
		~StringHelper();
		static std::vector<std::string> Split(std::string source, std::string cuttingSouece);
	private:
		StringHelper();
	};

}