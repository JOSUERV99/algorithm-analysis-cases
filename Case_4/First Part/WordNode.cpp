#include <string>
#include <utility>
#include <iostream>

using namespace std;

class WordNode { 
protected:
	std::string word;
	std::list<pair<int, std::string>> relations;
	int appearances;
public:
	std::list<pair<int, std::string>> getRelatedWords() {return relations;}
	void addIndividualRelation(std::string word);
	bool existRelation (std::string anotherWord);
	void deleteRelation(std::string anotherWord);
};

