#include "HighScore.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

HighScore::HighScore() : _score(0) {}

HighScore::HighScore(const std::string& name, int score)
    : _name(name), _score(score) {}

std::string HighScore::getName() const {
    return _name;
}

void HighScore::setName(const std::string& name) {
    _name = name;
}

int HighScore::getScore() const {
    return _score;
}

void HighScore::setScore(int score) {
    _score = score;
}

void HighScore::Deserialize(const std::string& csvData, char delimiter) {
    std::stringstream ss(csvData);
    std::getline(ss, _name, delimiter);
    ss >> _score;
}

HighScore::HighScore(const std::string& csvData, char delimiter) {
    Deserialize(csvData, delimiter);
}

std::vector<HighScore> HighScore::LoadHighScores(const std::string& filePath) {
    std::vector<HighScore> highScores;

    std::ifstream file(filePath);
    std::string line;
    while (std::getline(file, line)) {
        highScores.emplace_back(line, '['); 
    }

    file.close(); 

    return highScores;
}

void PrintColoredScore(int score) {
    
    std::cout << "\x1b[33m" << score << "\x1b[0m";
}

void HighScore::ShowHighScores(const std::vector<HighScore>& highScores)
{
    std::cout << "---- High Scores ----" << std::endl;
    for (const auto& score : highScores)
    {
        std::cout << std::left << std::setw(20) << score.getName();
        PrintColoredScore(score.getScore());
        std::cout << std::endl;
    }
}

void HighScore::Serialize(std::ofstream& ofs, char delimiter) const {
    ofs << _name << delimiter << _score << std::endl;
}
   
void HighScore::SaveHighScores(const std::string& filePath, const std::vector<HighScore>& highScores) {
    std::ofstream ofs(filePath);
 
    for (const auto& score : highScores) {
        score.Serialize(ofs, '[');
    }

    ofs.close();
}