#pragma once

#include <iostream>
#include <string>
#include <map>
#include "Hero.h"
#include "enums.h"


class HeroesDB : public JSONBase
{
public:
    HeroesDB();
	virtual ~HeroesDB() {};
    size_t Count() { return _heroes.size(); }

    void SortByNameDescending();
   

    void MergeSort(std::vector<Hero>& heroes, int left, int right, SortBy sortby);
    void Merge(std::vector<Hero>& heroes, int left, int mid, int right, SortBy sortBy);
    void SortByAttribute(SortBy sortBy);
    int BinarySearch(const std::vector<Hero>& _heroes, const std::string& searchTerm, int low, int high);
    void FindHero(const std::string& heroName);
    void GroupHeroes();
    void PrintGroupCounts();
    void FindHeroesByLetter(char letter);
    void RemoveHero(const std::string& heroName);

private:
    std::vector<Hero> _heroes;
    std::map<char, std::vector<Hero>> _groupedHeroes;

    static std::string toUpper(const std::string& str);
    static std::string toUpper2(const std::string& str);
    static bool charComparer(char c1, char c2);
    static bool isPrefix(const std::string& prefix, const std::string& word);

    virtual bool Deserialize(const std::string& s);
    virtual bool Deserialize(const rapidjson::Value& obj) { return false; };
    virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
};
