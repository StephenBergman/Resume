#include "HeroesDB.h"
#include <iostream>
#include "Console.h"
#include <algorithm> 
#include <locale>



void HeroesDB::AddHero(const Hero& hero) {
    _heroes.push_back(hero);
}

void HeroesDB::ShowHeroes(int count) const {
    if (count == 0) {
        for (const auto& hero : _heroes) {
            Console::WriteLine(std::to_string(hero.Id()) + ": " + hero.Name());
        }
    }
    else {
        int i = 0;
        for (const auto& hero : _heroes) {
            Console::WriteLine( std::to_string(hero.Id()) + ": " +  hero.Name());
            ++i;
            if (i == count) break;
        }
    }
}

bool HeroesDB::FindHero(const std::string& name, Hero& foundHero) const {
    for (const auto& hero : _heroes) {
        if (hero.Name() == name) {
            foundHero = hero;
            return true;
        }
    }
    return false; 
}

bool HeroesDB::RemoveHero(const std::string& name) {
    auto it = std::remove_if(_heroes.begin(), _heroes.end(), [&](const Hero& hero) {
        return hero.Name() == name;
    });

    if (it != _heroes.end()) {
        _heroes.erase(it, _heroes.end());
        return true;
    }

    return false;
}

bool HeroesDB::UpdateHero(const std::string& name, const Hero& updatedHero) {
    auto it = std::find_if(_heroes.begin(), _heroes.end(), [&](const Hero& hero) {
        return hero.Name() == name;
        });

    if (it != _heroes.end()) {
        *it = updatedHero;
        return true;
    }

    return false;
}

void HeroesDB::RemoveAllHeroes(const std::string& prefix, std::vector<Hero>& removedHeroes) {
    removedHeroes.clear(); 
    auto it = std::remove_if(_heroes.begin(), _heroes.end(), [&](const Hero& hero) {
        if (isPrefix(prefix, hero.Name())) {
            removedHeroes.push_back(hero);
            return true; 
        }
        return false;
        });
    _heroes.erase(it, _heroes.end()); 
}

std::vector<Hero> HeroesDB::StartsWith(const std::string& prefix) const
{
    return std::vector<Hero>();
}

void HeroesDB::PrintHero(const Hero& hero) const {
    Console::WriteLine("Id: " + std::to_string(hero.Id()) + ", Name: " + hero.Name(), ConsoleColor::Yellow);

    Console::WriteLine("\tPowerstats:", ConsoleColor::Cyan);
    Console::Write("\t\tIntelligence: ");
    Console::WriteLine(std::to_string(hero.Powerstats().Intelligence));
    Console::Write("\t\tStrength: ");
    Console::WriteLine(std::to_string(hero.Powerstats().Strength));
    Console::Write("\t\tSpeed: ");
    Console::WriteLine(std::to_string(hero.Powerstats().Speed));
    Console::Write("\t\tDurability: ");
    Console::WriteLine(std::to_string(hero.Powerstats().Durability));
    Console::Write("\t\tPower: ");
    Console::WriteLine(std::to_string(hero.Powerstats().Power));
    Console::Write("\t\tCombat: ");
    Console::WriteLine(std::to_string(hero.Powerstats().Combat));

    Console::WriteLine("\tAppearance:", ConsoleColor::Cyan);
    Console::Write("\t\tGender: ");
    Console::WriteLine(hero.Appearance().Gender);
    Console::Write("\t\tRace: ");
    Console::WriteLine(hero.Appearance().Race);
    Console::Write("\t\tHeight: ");
    Console::WriteLine(hero.Appearance().Height[0] + " / " + hero.Appearance().Height[1]);
    Console::Write("\t\tWeight: ");
    Console::WriteLine(hero.Appearance().Weight[0] + " / " + hero.Appearance().Weight[1]);
    Console::Write("\t\tEye color: ");
    Console::WriteLine(hero.Appearance().EyeColor);
    Console::Write("\t\tHair color: ");
    Console::WriteLine(hero.Appearance().HairColor);

    Console::WriteLine("\tBiography:", ConsoleColor::Cyan);
    Console::Write("\t\tFull name: ");
    Console::WriteLine(hero.Biography().FullName);
    Console::Write("\t\tAlter egos: ");
    Console::WriteLine(hero.Biography().AlterEgos);
    Console::Write("\t\tAliases: ");
    for (size_t i = 0; i < hero.Biography().Aliases.size(); ++i) {
        Console::Write(hero.Biography().Aliases[i]);
        if (i < hero.Biography().Aliases.size() - 1) {
            Console::Write(", ");
        }
    }
   
    Console::Write("\t\tPlace of birth: ");
    Console::WriteLine(hero.Biography().PlaceOfBirth);
    Console::Write("\t\tFirst appearance: ");
    Console::WriteLine(hero.Biography().FirstAppearance);
    Console::Write("\t\tPublisher: ");
    Console::WriteLine(hero.Biography().Publisher);
    Console::Write("\t\tAlignment: ");
    Console::WriteLine(hero.Biography().Alignment);

    Console::WriteLine("\tWork:", ConsoleColor::Cyan);
    Console::Write("\t\tOccupation: ");
    Console::WriteLine(hero.Work().Occupation);
    Console::Write("\t\tBase: ");
    Console::WriteLine(hero.Work().Base);

    Console::WriteLine("\tConnections:", ConsoleColor::Cyan);
    Console::Write("\t\tGroup affiliation: ");
    Console::WriteLine(hero.Connections().GroupAffiliation);
    Console::Write("\t\tRelatives: ");
    Console::WriteLine(hero.Connections().Relatives);

    Console::WriteLine("\tImages:", ConsoleColor::Cyan);
    Console::Write("\t\tURL: ");
    Console::WriteLine(hero.Images().XS); 
}
   
//----------------------------------------------------------------
//                                                              //
//		        DO NOT EDIT THE CODE BELOW                      //
//                                                              //

//DEFINE the method in CPP file
//  *** don't forget the "HeroesDB::" in front of the method name.
    Hero HeroesDB::GetBestHero()
{
	return _heroes[51];
}

HeroesDB::HeroesDB()
{
	DeserializeFromFile("heroes.json");
}

bool HeroesDB::charComparer(char c1, char c2)
{
	return std::tolower(c1, std::locale()) == std::tolower(c2, std::locale());
}
bool HeroesDB::isPrefix(const std::string& prefix, const std::string& word)
{
	return  (std::mismatch(prefix.begin(), prefix.end(),
		word.begin(), word.end(),
		charComparer)).first == prefix.end();
}


bool HeroesDB::Deserialize(const std::string& s)
{
	rapidjson::Document doc;
	if (!InitDocument(s, doc))
		return false;

	if (!doc.IsArray())
		return false;


	_heroes.reserve(doc.Size());

	for (rapidjson::SizeType i = 0; i < doc.Size(); ++i)
	{
		rapidjson::Value& node = doc[i];
		Hero myHero(node);
		_heroes.push_back(myHero);
	}

	return true;
}


bool HeroesDB::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{
	return true;
}