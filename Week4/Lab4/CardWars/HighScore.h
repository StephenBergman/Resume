#pragma once
#include <string>
#include <vector>
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"

class HighScore
{
public:
    HighScore();
    HighScore(const std::string& csvData, char delimiter);
    HighScore(const std::string& name, int score);
    static std::vector<HighScore> LoadHighScores(const std::string& filePath);
    static void ShowHighScores(const std::vector<HighScore>& highScores);
    static void SaveHighScores(const std::string& filePath, const std::vector<HighScore>& highScores);

    std::string getName() const;
    void setName(const std::string& name);

    int getScore() const;
    void setScore(int score);
    void Deserialize(const std::string& csvData, char delimiter);

    void Serialize(std::ofstream& ofs, char delimiter) const;


private:
    std::string _name;
    int _score;
};

