#include "CSVReader.h"

#include <fstream>
#include"StringHelper.h"

std::shared_ptr<Framework::CSVData> Framework::CSVReader::GetMatrixByFile(std::string fileName, std::string filePath)
{
	std::ifstream ifs(filePath+fileName);
	std::string source = std::string(std::istreambuf_iterator<char>(ifs),
		std::istreambuf_iterator<char>());

	auto splitedSource = StringHelper::Split(source, "\n");

	auto spS = StringHelper::Split(splitedSource.at(0), ",");

	auto output = std::make_shared< CSVData>(spS.size(), splitedSource.size());


	for (int i = 0; i < splitedSource.size(); i++) {
		auto row = splitedSource.at(i);
		auto nums = StringHelper::Split(row, ",");
		for (int j = 0; j < nums.size(); j++) {
			output->data[j][i] = std::stoi(nums.at(j));
		}
	}

	return output;
}

std::shared_ptr<Framework::CSVData> Framework::CSVReader::GetMatrixByString(const std::string & source)
{
	auto splitedSource = StringHelper::Split(source, "\n");

	auto spS = StringHelper::Split(splitedSource.at(0), ",");

	auto output = std::make_shared< CSVData>(spS.size(), splitedSource.size());

	for (int i = 0; i < splitedSource.size(); i++) {
		auto row = splitedSource.at(i);
		auto nums = StringHelper::Split(row, ",");
		for (int j = 0; j < nums.size(); j++) {
			output->data[j][i] = std::stoi(nums.at(j));
		}
	}

	return output;
}
