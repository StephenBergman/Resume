#include "HeroesDB.h"
#include <iostream>
#include "Console.h"
#include <algorithm> 
#include <string_view>
#include <locale>
#include <cctype>






void HeroesDB::Merge(std::vector<Hero>& heroes, int left, int mid, int right, SortBy sortBy)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;

	std::vector<Hero> leftArray(n1);
	std::vector<Hero> rightArray(n2);
		for (int i = 0; i < n1; i++)
			leftArray[i] = heroes[left + i];
	for (int j = 0; j < n2; j++)
		rightArray[j] = heroes[mid + 1 + j];

	int i = 0, j = 0, k = left;

	while (i < n1 && j < n2)
	{
		if (Hero::Compare(leftArray[i], rightArray[j], sortBy) <= 0)
		{
			heroes[k] = leftArray[i];
			i++;
		}
		else
		{
			heroes[k] = rightArray[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{

		heroes[k] = leftArray[i];
		i++;
		k++;
	}

	while (j < n2)
	{

		heroes[k] = rightArray[j];
		j++;
		k++;
	}

}

void HeroesDB::MergeSort(std::vector<Hero>& heroes, int left, int right, SortBy sortBy)
{

	if (left < right)
	{

		int mid = left + (right - left) / 2;

		MergeSort(heroes, left, mid, sortBy);
		MergeSort(heroes, mid + 1, right, sortBy);

		Merge(heroes, left, mid, right, sortBy);
	}
}

void HeroesDB::SortByAttribute(SortBy sortBy)
{

	std::vector<Hero> sortedHeroes = _heroes;
	MergeSort(sortedHeroes, 0, sortedHeroes.size() - 1, sortBy);
	for (const Hero& hero : sortedHeroes)
	{

		std::string attribute = hero.GetSortByAttribute(sortBy);
		std::cout << hero.Id() << ": " << attribute << " - " << hero.Name() << std::endl;
	}
}
std::string toLower(const std::string& str) {
	std::string lowerStr = str;
	std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), [](unsigned char c) { return std::tolower(c); });
	return lowerStr;
}

int HeroesDB::BinarySearch(const std::vector<Hero>& heroes, const std::string& searchTerm, int low, int high) {
	std::string lowerSearchTerm = toLower(searchTerm);

	if (high < low) {
		return -1; 
	}

	int mid = (low + high) / 2;
	std::string lowerMid = toLower(heroes[mid].Name()); 

	if (lowerSearchTerm < lowerMid) {
		return BinarySearch(heroes, lowerSearchTerm, low, mid - 1);
	}
	else if (lowerSearchTerm > lowerMid) {
		return BinarySearch(heroes, lowerSearchTerm, mid + 1, high);
	}
	else {
		return mid; 
	}
}


void HeroesDB::FindHero(const std::string& heroName) {
	int index = BinarySearch(_heroes, heroName, 0, _heroes.size() - 1);
	if (index == -1) {
		std::cout << heroName << " was not found" << std::endl;
	}
	else {
		std::cout << heroName << " was found at index " << index << std::endl;
	}
}

void HeroesDB::GroupHeroes() {
	_groupedHeroes.clear();

	for (const auto& hero : _heroes) {
		if (!hero.Name().empty()) {
			char firstLetter = std::tolower(hero.Name()[0]);
			auto it = _groupedHeroes.find(firstLetter);
			if (it == _groupedHeroes.end()) {
				std::vector<Hero> heroesVector;
				heroesVector.push_back(hero);
				_groupedHeroes[firstLetter] = heroesVector;
			}
			else {
				it->second.push_back(hero);
			}
		}
	}
}

void HeroesDB::PrintGroupCounts() {
	if (_groupedHeroes.empty()) {
		GroupHeroes();
	}
	for (const auto& pair : _groupedHeroes) {
		char firstLetter = pair.first;
		const std::vector<Hero>& heroesStartingWithLetter = pair.second;
		std::cout <<  firstLetter << ": " << heroesStartingWithLetter.size() << std::endl;
	}
 }

void HeroesDB::FindHeroesByLetter(char letter) {
	if (_groupedHeroes.empty()) {
		GroupHeroes();
	}
	char lowercaseLetter = std::tolower(letter);
	auto it = _groupedHeroes.find(lowercaseLetter);
	if (it == _groupedHeroes.end()) {
		std::cout << "No heroes found whose names start with '" << letter << "'" << std::endl;
	}
	else {
		const std::vector<Hero>& heroesStartingWithLetter = it->second;
		for (const auto& hero : heroesStartingWithLetter) {
			std::cout << hero.Id() << ": " << hero.Name() << std::endl;
		}
	}
}

void HeroesDB::RemoveHero(const std::string& heroName) {
	
	if (_groupedHeroes.empty()) {
		GroupHeroes();
	}
	char firstLetter = std::tolower(heroName[0]);
	auto it = _groupedHeroes.find(firstLetter);
	if (it == _groupedHeroes.end()) {
		std::cout << heroName << " was not found." << std::endl;
	}
	else {
		std::vector<Hero>& heroesStartingWithLetter = it->second;
		int index = BinarySearch(heroesStartingWithLetter, heroName, 0, heroesStartingWithLetter.size() - 1);
		if (index != -1) {

	heroesStartingWithLetter.erase(heroesStartingWithLetter.begin() + index);
auto iter = std::remove_if(_heroes.begin(), _heroes.end(), [&](const Hero& hero) {
				return hero.Name() == heroName;
				});
			_heroes.erase(iter, _heroes.end());
std::cout << heroName << " was removed." << std::endl;
			if (heroesStartingWithLetter.empty()) {
				_groupedHeroes.erase(it);
			}
		}
		else {
			
			std::cout << heroName << " was not found." << std::endl;
		}
	}
}

//----------------------------------------------------------------
//                                                              //
//		        DO NOT EDIT THE CODE BELOW                      //
//                                                              //


HeroesDB::HeroesDB()
{
	DeserializeFromFile("heroes.json");
}

std::string HeroesDB::toUpper(const std::string& str)
{
	std::string copy = str;
	std::transform(copy.begin(),
		copy.end(),
		copy.begin(),
		[](unsigned char c) { return std::toupper(c); });
	return copy;
}

std::string HeroesDB::toUpper2(const std::string& str)
{
	std::string copy = str;
	for (auto& c : copy) c = toupper(c);
	return copy;
}

void HeroesDB::SortByNameDescending()
{
	std::vector<Hero> sorted(_heroes); //clone the list

	size_t n = sorted.size();
	bool swapped;
	do
	{
		swapped = false;
		for (size_t i = 1; i <= n - 1; i++)
		{
			int compResult = _stricmp(sorted[i - 1].Name().c_str(), sorted[i].Name().c_str());
			//int compResult = toUpper(sorted[i - 1].Name()).compare(toUpper(sorted[i].Name()));
			if (compResult < 0)
			{
				swapped = true;
				std::swap(sorted[i - 1], sorted[i]);

				//int temp = vec[i - 1];
				//vec[i - 1] = vec[i];
				//vec[i] = temp;
			}
		}
		--n;
	} while (swapped);

	for (auto& hero : sorted)
	{
		std::cout << hero.Id() << ": " << hero.Name() << std::endl;
	}
	std::cout << std::endl;
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