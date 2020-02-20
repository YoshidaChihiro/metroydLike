#include "RankingLoader.h"

std::vector<int> Framework::RankingLoader::GetHeigherFromFile(std::string source, int top)
{
	auto rankingVec = GetRankingFromFile(source);
	std::sort(rankingVec.begin(), rankingVec.end());
	std::vector<int> output;

	auto itr = rankingVec.rbegin();

	for (int i = 0; i < top; i++) {
		output.push_back((*(itr + i)));
	}

	
	return output;
}

std::vector<int> Framework::RankingLoader::GetHeigherFromFile(std::vector<int> source, int top)
{
	auto rankingVec = source;
	std::sort(rankingVec.begin(), rankingVec.end());
	std::vector<int> output;

	auto itr = rankingVec.rbegin();

	for (int i = 0; i < top; i++) {
		output.push_back((*(itr + i)));
	}


	return output;
}

std::vector<int> Framework::RankingLoader::GetLowerFromFile(std::string source, int top)
{
	auto rankingVec = GetRankingFromFile(source);
	std::sort(rankingVec.begin(), rankingVec.end());
	std::vector<int> output;
	auto itr = rankingVec.begin();

	for (int i = 0; i < top; i++) {
		output.push_back((*(itr + i)));
	}

	return output;
}

std::vector<int> Framework::RankingLoader::GetLowerFromFile(std::vector<int> source, int top)
{
	auto rankingVec = source;
	std::sort(rankingVec.begin(), rankingVec.end());
	std::vector<int> output;
	auto itr = rankingVec.begin();

	for (int i = 0; i < top; i++) {
		output.push_back((*(itr + i)));
	}

	return output;
}

void Framework::RankingLoader::WriteRanking(std::vector<int> ranking, std::string sourceName, int writeCount)
{
	sourceName= "Resource/Ranking/" + sourceName;
	std::ofstream ofs(sourceName);
	if (!ofs)
		return;
	for (int i = 0; i < writeCount; i++) {
		ofs << std::to_string(ranking.at(i)).c_str();
		if(i!=writeCount-1)
		ofs<<",";
	}
}

std::vector<int> Framework::RankingLoader::GetRankingFromFile(std::string fileSource)
{
	fileSource = "Resource/Ranking/" + fileSource;
	std::ifstream ifs(fileSource);
	std::string source = std::string(std::istreambuf_iterator<char>(ifs),
		std::istreambuf_iterator<char>());

	auto splitedSource = StringHelper::Split(source, ",");

	std::vector<int> output;


	for (int i = 0; i < splitedSource.size(); i++) {
		output.push_back( std::stoi(splitedSource.at(i)));
	}

	return output;
}

