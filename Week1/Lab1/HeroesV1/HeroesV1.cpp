#include <iostream>
#include "HeroesDB.h"
#include "Console.h"
#include "Input.h"
#include "Tester.h"


int main()
{
    Tester v1Test;
    /*
        NOTE: if you're having problems with the menu showing, it could be because you're using Windows Terminal.
        Go here to learn how to change Windows to use the Console window instead. 
        https://discord.com/channels/446669518593327105/1151952874012688384/1153398632763097212
    
    */
    Console::ResizeWindow(150, 30);

    HeroesDB heroDB;

    /*
        Here are some examples.
            - how to call methods
            - how to use the Console Write methods
            - how to access the data values of a Hero.
    */
    Hero theBest = heroDB.GetBestHero(); //how to call a non-static method
    Console::Write("The best hero is "); //how to call a static method

    //how to call the Write method and change the foreground color
    Console::Write(theBest.Name(), ConsoleColor::Yellow);

    Console::Write("! (of course).\nThe Id of the hero is ");
    Console::Write(std::to_string(theBest.Id()), ConsoleColor::Green);
    Console::Write(".\nHis combat level is ");

    //how to access the members of a Hero object
    //how to print a number using the Console::Write using the std::to_string method
    Console::Write(std::to_string(theBest.Powerstats().Combat), ConsoleColor::Red);
    Console::WriteLine("!");
    Input::PressEnter();


    int menuSelection = 0;
    std::vector<std::string> menuOptions { "1. Show Heroes", "2. Remove Hero", "3. Starts With", "4. Find Hero", "5. Remove All Heroes", "6. Show Top x", "7. Exit" };
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
       
        case 1: {
            heroDB.ShowHeroes();
            break;
        }

        case 2: {
            std::string nameToRemove;
            Console::Write("Enter the name of the hero to remove: ");
            std::getline(std::cin, nameToRemove);
            if (heroDB.RemoveHero(nameToRemove)) {
                Console::WriteLine("Hero removed.", ConsoleColor::Green);
            }
            else {
                Console::WriteLine("Hero not found.", ConsoleColor::Red);
            }
            break;
        }


        case 3: {
            std::string prefix;
            Console::Write("Enter the prefix: ");
            std::getline(std::cin, prefix);
            std::vector<Hero> heroes = heroDB.StartsWith(prefix);
            Console::WriteLine("Found " + std::to_string(heroes.size()) + " heroes:");
            for (const auto& hero : heroes) {
                Console::WriteLine(std::to_string(hero.Id()) + ": " + hero.Name());
            }
            break;
        }
        case 4: {
            std::string name;
            Console::Write("Enter the name of the hero to find: ");
            std::getline(std::cin, name);
            Hero foundHero;
            if (heroDB.FindHero(name, foundHero)) {
                Console::WriteLine("Hero found:");
                heroDB.PrintHero(foundHero);
            }
            else {
                Console::WriteLine("Hero not found.", ConsoleColor::Red);
            }
            break;
        }
        case 5:
         {
            std::string prefix;
            Console::Write("Enter the first part of the names to remove: ");
            std::getline(std::cin, prefix);

            std::vector<Hero> removedHeroes;
            heroDB.RemoveAllHeroes(prefix, removedHeroes);

            if (removedHeroes.empty()) {
                Console::WriteLine("No heroes found that start with '" + prefix + "'.");
            }
            else {
                Console::WriteLine("The following heroes were removed:");
                for (const auto& hero : removedHeroes) {
                    heroDB.PrintHero(hero);
                }
            }
            break;
        }
        case 6: {
            int numToShow = Input::GetInteger("Enter the number of top heroes to show: ", 0, heroDB.Count());
            Console::WriteLine("Top " + std::to_string(numToShow) + " heroes:");
            heroDB.ShowHeroes(numToShow);
            break;
        }
        default:
            break;
        }

        Input::PressEnter();

    } while (menuSelection != menuOptions.size());
}


