#pragma once
#include <iostream>
#include <fstream>
#include "vector"
#include "include/nlohmann/json.hpp"

using json = nlohmann::json;
class DataSave {
public:
	json jsonData;
	void SaveScore(int score);
	std::vector<int> LoadScore();

};