#include "StringHelper.h"

Framework::StringHelper::~StringHelper()
{
}

std::vector<std::string> Framework::StringHelper::Split(std::string source, std::string cuttingSouece)
{
	auto output = std::vector<std::string>();
	int first = 0;
	int last = source.find_first_of(cuttingSouece);
	while (first < source.size())
	{
		auto subString = source.substr(first, last - first);
		output.push_back(subString);
		first = last + 1;
		last = source.find_first_of(cuttingSouece, first);
		if (last == std::string::npos) {
			last = source.size();
		}
	}
	return output;
}
