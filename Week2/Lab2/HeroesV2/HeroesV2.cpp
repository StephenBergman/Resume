#include <iostream>
#include "HeroesDB.h"
#include "Console.h"
#include "Input.h"
#include <locale>
#include "Tester.h"

int main()
{
    Tester v2Test;
    Console::ResizeWindow(150, 30);

    HeroesDB heroDB;

    int menuSelection = 0;
    std::vector<std::string> menuOptions{ "1. Sort by Name (descending)", "2. Sort By", "3. Find Hero (Binary Search)", "4. Print Group Counts", "5. Find All Heroes by first letter", "6. Remove Hero", "7. Exit" };
    std::vector<std::string> sortByOptions{ "1. Intelligence", "2. Strength", "3. Speed", "4. Durability", "5. Power", "6. Combat" };

    do
    {
        Console::Clear();
        menuSelection = Input::GetMenuSelection(menuOptions);
        Console::Clear();


        //----------------------------------------------------------------
        //                                                              //
        //    Call your methods in the appropriate case statement       //
        //                                                              //
        switch (menuSelection)
        {
        case 1:
        {
            heroDB.SortByNameDescending();
            break;
        }
        case 2:
        {
            int sortBySelection = Input::GetMenuSelection(sortByOptions, "Sort by? ");
            if (sortBySelection < 0 || sortBySelection >= sortByOptions.size())
            {
                std::cout << "Invalid choice!" << std::endl;
                break;
            }
            SortBy sortByChoice = static_cast<SortBy>(sortBySelection);
            heroDB.SortByAttribute(sortByChoice);
            break;
        }
        case 3:
        {
           
            std::string heroName;
            std::cout << "Enter the name to find: ";
            std::getline(std::cin, heroName);
            heroDB.FindHero(heroName);
            break;
        }
        case 4:
        {
            heroDB.PrintGroupCounts();
            break;
        }
        case 5:
        {
            std::string letter;
            std::cout << "Enter the letter to find: ";
            std::getline(std::cin, letter);
            if (letter.length() == 1) {
                char searchLetter = letter[0];
                heroDB.FindHeroesByLetter(searchLetter);
            }
            else {
                std::cout << "Invalid input. Please enter a single letter." << std::endl;
            }
            break;
        }
        case 6:
        {
            std::string heroName;
            std::cout << "Enter name to remove: ";
            std::getline(std::cin, heroName);
            heroDB.RemoveHero(heroName);
            break;
        }
      
        }

        Input::PressEnter();
    } while (menuSelection != menuOptions.size());
}
