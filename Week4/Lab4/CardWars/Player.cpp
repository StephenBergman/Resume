#include "Player.h"

Player::Player() : _score(0) {}

Player::Player(const std::string& name, int score)
    : _name(name), _score(score) {}

std::string Player::getName() const {
    return _name;
}

void Player::setName(const std::string& name) {
    _name = name;
}

int Player::getScore() const {
    return _score;
}

void Player::setScore(int score) {
    _score = score;
}

bool Player::HasCards() const {
    return !_pile.empty();
}

void Player::PushCard(const Card& card) {
    _pile.push_back(card);
}

Card Player::PopCard() {
    if (!_pile.empty()) {
        Card topCard = _pile.back();
        _pile.pop_back();
        return topCard;
    }
}

void Player::WonCards(const std::vector<Card>& cards) {
    _won.insert(_won.end(), cards.begin(), cards.end());
    _score += static_cast<int>(cards.size());
}
