#include "DataSave.h"

// スコアを保存する関数
void DataSave::SaveScore(int score) {

    // ファイルストリームを開く
    std::ifstream file("SaveData.json");

    if (!file.is_open()) {
        jsonData["scores"] = json::array();  // 空の配列を作成
    }
    else {
        file >> jsonData;
        file.close();
    }

    if (jsonData["scores"].size() >= 3) {
        if (jsonData["scores"][2] < score) {
            jsonData["scores"].erase(jsonData["scores"].begin() + 2);
            jsonData["scores"].push_back(score);
            std::sort(jsonData["scores"].rbegin(), jsonData["scores"].rend());
        }
    }
    else {
        jsonData["scores"].push_back(score);
        std::sort(jsonData["scores"].rbegin(), jsonData["scores"].rend());
    }
        
    std::ofstream outputFile("SaveData.json");
    if (outputFile.is_open()) {
        outputFile << jsonData.dump(4);  
        outputFile.close();              
    }
    else {
        std::cerr << "ファイルの書き込みに失敗しました。" << std::endl;
    }
    
}

// スコアを読み込む関数
std::vector<int> DataSave::LoadScore() {
    std::ifstream file("SaveData.json");

    if (file.is_open()) {
        json scoreData;
        file >> scoreData;
        file.close();
        if (scoreData.contains("scores") && scoreData["scores"].is_array()) {
            return scoreData["scores"].get<std::vector<int>>();
        }
        else {
            return {};
        }
    }
    else {
        std::cerr << "Failed to open saveData.json for reading.\n";
        return {};
    }

    return {};
}