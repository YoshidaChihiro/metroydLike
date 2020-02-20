#pragma once
#include<vector>
#include<iostream>
#include<string>
#include"StringHelper.h"
#include<fstream>
#include<algorithm>
namespace Framework {
	class RankingLoader
	{
	public:
		static std::vector<int>GetHeigherFromFile(std::string source, int top);
		static std::vector<int>GetHeigherFromFile(std::vector<int> source, int top);
		static std::vector<int>GetLowerFromFile(std::string source, int top);
		static std::vector<int>GetLowerFromFile(std::vector<int> source, int top);
		static void WriteRanking(std::vector<int> ranking, std::string sourceName, int writeCount);
	private:
		static std::vector<int>GetRankingFromFile(std::string source);
	};

}