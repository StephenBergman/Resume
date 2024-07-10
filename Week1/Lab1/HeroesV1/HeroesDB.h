#pragma once
#include <string>
#include "Hero.h"

#include <iostream>

class HeroesDB : public JSONBase
{
public:
    HeroesDB();
	virtual ~HeroesDB() {};
    size_t Count() { return _heroes.size(); }
    Hero GetBestHero();

    void ShowHeroes(int count = 0) const;

    void AddHero(const Hero& hero);

    bool FindHero(const std::string& name, Hero& foundHero) const;

    bool RemoveHero(const std::string& name);

    bool UpdateHero(const std::string& name, const Hero& updatedHero);

    void PrintHero(const Hero& hero) const;

    void RemoveAllHeroes(const std::string& prefix, std::vector<Hero>& removedHeroes);

    std::vector<Hero> StartsWith(const std::string& prefix) const;

    std::vector<Hero> _heroes;

    private:
    static bool charComparer(char c1, char c2);
    static bool isPrefix(const std::string& prefix, const std::string& word);

    virtual bool Deserialize(const std::string& s);
    virtual bool Deserialize(const rapidjson::Value& obj) { return false; };
    virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
};