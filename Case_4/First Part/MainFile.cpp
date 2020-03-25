#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <list>
#include <algorithm>
#include <stdio.h>
#include <unordered_map>

#include "TextFormatter.cpp" 
//#include "PowerRelationsGraph.cpp"
#include "WordNode.cpp"

#define POWER_WORDS_QUANTITY 10
#define FILENAME 		    "TextToAnalize.txt"   				// "FirstParagraph.txt"

#define STOPWORDS_FILENAME   "StopWords(SPANISH).txt"
// StopWords file getted from: https://github.com/Alir3z4/stop-words/blob/master/spanish.txt

int main() {

	std::list <std::string> wordsList = TextFormatter::getWordsListFromFile( FILENAME );
	std::list <std::string> stopWordsList = TextFormatter::getWordsListFromFile( STOPWORDS_FILENAME );
	std::list <std::string> cleanWordsList = TextFormatter::deleteStopWords( stopWordsList, wordsList );

	// std::cout << "Quantity of words " << wordsList.size() << std::endl;
	// std::cout << "Quantity of stop words " << stopWordsList.size() << std::endl;
	std::cout << "Quantity of clean words " << cleanWordsList.size() << std::endl;
	
	std::unordered_map <std::string, int> appereances;
	for (auto const &word : cleanWordsList) {
		appereances[word]++;
	}

	// testing
	std::unordered_map<std::string, int>::iterator it = appereances.begin();
	while (it != appereances.end()) {
		if (it->second > 10)
			std::cout << it->first << " : " << it->second << std::endl;
		it++;
	}

	//TextFormatter::showList(cleanWordsList);

	return EXIT_SUCCESS;
}