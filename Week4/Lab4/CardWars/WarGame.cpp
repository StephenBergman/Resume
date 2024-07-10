#include "WarGame.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Input.h"


std::vector<Card> WarGame::_cards;

WarGame::WarGame(std::string cardsFile)
{
    LoadCards(cardsFile);
}

void WarGame::LoadCards(const std::string& filePath) {
    std::ifstream file(filePath);
   
    std::string line;
    std::vector<std::string> suits;
    std::vector<std::string> faces;

    if (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string suit;
        while (std::getline(ss, suit, '?')) {
            suits.push_back(suit);
        }
    }

    if (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string face;
        while (std::getline(ss, face, '?')) {
            faces.push_back(face);
        }
    }

    for (const auto& suit : suits) {
        for (const auto& face : faces) {
            _cards.emplace_back(suit, face);
        }
    }
}

void WarGame::ShowCards() {
    for (auto it = _cards.begin(); it != _cards.end(); ++it) {
        it->Print();
        std::cout << '\n';
    }
}

void WarGame::shuffle()
{
    int ndx1, ndx2;
    srand((unsigned int)time(NULL));

    for (size_t i = 0; i < 52; i++)
    {
        ndx1 = rand() % 52;
        ndx2 = rand() % 52;

        Card temp = _cards[ndx1];
        _cards[ndx1] = _cards[ndx2];
        _cards[ndx2] = temp;
    }
}

void WarGame::PlayGame(const std::string& playerName, std::vector<HighScore>& highScores, const std::string& highScoreFile) {
    bool playAgain = true;

    while (playAgain) {
        shuffle();


        Player npc("NPC", 0);
        Player player("Player", 0);


        bool addToNpc = false;
        for (const auto& card : _cards) {
            if (addToNpc) {
                npc.PushCard(card);
            }
            else {
                player.PushCard(card);
            }
            addToNpc = !addToNpc;
        }

        std::vector<Card> unclaimedPile;


        while (player.HasCards()) {

            Card playerCard = player.PopCard();
            Card npcCard = npc.PopCard();


            playerCard.Print();
            std::cout << "   VS  ";
            npcCard.Print();


            unclaimedPile.push_back(playerCard);
            unclaimedPile.push_back(npcCard);


            int compareResult = playerCard.Compare(npcCard);

            if (compareResult == -1) {

                npc.WonCards(unclaimedPile);
                unclaimedPile.clear();
                std::cout << '\t' << "NPC wins!" << std::endl;
            }
            else if (compareResult == 1) {

                player.WonCards(unclaimedPile);
                unclaimedPile.clear();
                std::cout << '\t' << playerName << " wins!" << std::endl;
            }
            else {

                std::cout << '\t' << "It's a tie!" << std::endl;
            }
        }


        int npcScore = npc.getScore();
        int playerScore = player.getScore();

        std::cout << "Final Scores:" << std::endl;
        std::cout << "NPC: " << npcScore << std::endl;
        std::cout << playerName << ": " << playerScore << std::endl;


        if (npcScore > playerScore) {
            std::cout << "NPC won the round!" << std::endl;
        }
        else if (npcScore == playerScore) {
            std::cout << "It's a tie!" << std::endl;
        }
        else {
            std::cout << playerName << " won the round!" << std::endl;


            if (playerScore > highScores.back().getScore()) {
                std::cout << "Congratulations! You have a new high score!" << std::endl;
                Input::GetString("Enter your name: ");
                std::cout << std::endl;
                player.setName(playerName);

                int insertIndex = 0;
                while (insertIndex < highScores.size() && playerScore <= highScores[insertIndex].getScore()) {
                    insertIndex++;
                }

                HighScore newHighScore(playerName, playerScore);
                highScores.insert(highScores.begin() + insertIndex, newHighScore);

                if (highScores.size() > 10) {
                    highScores.pop_back();
                }

                HighScore::SaveHighScores(highScoreFile, highScores);

                HighScore::ShowHighScores(highScores);
            }


        }
        int playAgainInput;

        playAgainInput = Input::GetInteger("Do you want to play again? (1 for yes, 2 for no): ", 1, 2);
        (playAgainInput != 1 && playAgainInput != 2);

        playAgain = (playAgainInput == 1);
    }

}
