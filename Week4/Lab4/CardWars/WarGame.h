#pragma once
#include <string>
#include <vector>
#include "Card.h"
#include "HighScore.h"
#include "Player.h"

class WarGame
{

public:
	WarGame(std::string cardsFile);
	static void LoadCards(const std::string& filePath);
	static void ShowCards();
	void PlayGame(const std::string& playerName, std::vector<HighScore>& highScores, const std::string& highScoreFile);


private:
	static std::vector<Card> _cards;
	static void shuffle();
};

