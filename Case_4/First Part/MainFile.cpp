#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <list>
#include <algorithm>
#include <stdio.h>

#include "TextFormatter.cpp" //#include "WordGraph.cpp" TODO: reestructurate the class
#include "WordNode.cpp"

#define POWER_WORDS_QUANTITY 10
#define FILENAME 		     "TxtText.txt"  				// "TextToAnalize.txt"
#define STOPWORDS_FILENAME   "StopWords(SPANISH).txt"

// To use the MakeFile in Windows: "nmake -f compile_and_run.mk"
// StopWords file getted from: https://github.com/Alir3z4/stop-words/blob/master/spanish.txt

int main() {

	std::list <std::string> wordsList = TextFormatter::getWordsListFromFile( FILENAME );
	std::list <std::string> stopWordsList = TextFormatter::getWordsListFromFile( STOPWORDS_FILENAME );
	std::list <std::string> cleanWordsList = TextFormatter::deleteStopWords( stopWordsList, wordsList );

	//WordGraph wordGraph(cleanWordsList);
	//wordGraph.generateGraph();
	//wordGraph.getPowerWords(POWER_WORDS_QUANTITY);

	std::cout << "Hello World!" << std::endl;

	return EXIT_SUCCESS;
}