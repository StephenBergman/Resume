#pragma once
#include <string>
#include <vector>
#include "Card.h"

class Player
{
public:
    Player();
    Player(const std::string& name, int score);

    std::string getName() const;
    void setName(const std::string& name);

  
    int getScore() const;
    void setScore(int score);

    bool HasCards() const;

  
    void PushCard(const Card& card);

    Card PopCard();

    void WonCards(const std::vector<Card>& cards);

private:
    std::string _name;
    int _score;
    std::vector<Card> _pile;
    std::vector<Card> _won;
};

