#define DELIMITER '.'
#define STOPWORDS_FILENAME "StopWords(SPANISH).txt"

namespace TextFormatter {

	void showList(std::list<std::string> wordList) {
		for (auto const &element : wordList) {
			std::cout << element << std::endl;
		}
	}

	std::list <std::string> getWordListFromFile(std::string filename) {

		std::ifstream reader (filename, std::ifstream::in);
		std::list <std::string> wordList; 
		std::string text = "";
		char characterReaded;

		while (reader.good()) {

			characterReaded = reader.get();
			while ( characterReaded ) {
				if ( characterReaded != EOF && !isspace(characterReaded) 
						&& !ispunct(characterReaded) && !isdigit(characterReaded)) {
					text += characterReaded;
				} else {
					break;
				}

				characterReaded = reader.get();
			}
			
			if (text != "") {
				transform(text.begin(), text.end(), text.begin(), ::tolower);
				wordList.push_back(text);
			}

			text = "";
		}

		reader.close();
		return wordList;
	}

	std::list < std::list <std::string> > getSentencesListFromFile(std::string filename) {

		std::ifstream reader (filename, std::ifstream::in);
		std::list < std::list <std::string> > sentenceList; 
		std::list<std::string> currentSentence;
		std::string text = "";
		char characterReaded;

		while (reader.good()) {
			
			characterReaded = reader.get();
			while ( characterReaded && characterReaded != DELIMITER 
				&& characterReaded != EOF && !isspace(characterReaded) && !isdigit(characterReaded) && !ispunct(characterReaded)) {
				text += characterReaded;
				characterReaded = reader.get();
			}
			
			if (text != "") {
				transform(text.begin(), text.end(), text.begin(), ::tolower);
				currentSentence.push_back(text);
				text = "";
			}

			if (characterReaded == DELIMITER) {
				if (currentSentence.size() > 1)
					sentenceList.push_back(currentSentence);
				currentSentence.clear();	
			}
		}

		reader.close();
		return sentenceList;
	}

	std::list <std::string> deleteStopWords(std::list <std::string> stopWordsList, std::list <std::string> wordList) {

		std::list <std::string> cleanWords;
		bool repeated = false;
		for (auto const &word: wordList) {
			for (auto const &stopWord: stopWordsList)
				if (stopWord == word) {
					repeated = true;
					break;
				}

			if (!repeated) {
				cleanWords.push_back(word);
			}
			repeated = false;
		}

		return cleanWords;
	}

	std::list < std::list<std::string> > getSentencesFromFile(std::string filename) {
		std::list < std::list<std::string> > sentences = getSentencesListFromFile(filename);
		std::list <std::string> stopWordsList = getWordListFromFile( STOPWORDS_FILENAME );

		std::list < std::list<std::string> > sentencesWithoutStopWords;
		
		for (auto const &sentence: sentences) {
			std::list <std::string> simpleSentence = deleteStopWords(stopWordsList, sentence);
			if (simpleSentence.size() > 1)
				sentencesWithoutStopWords.push_back(simpleSentence);
		}

		return sentencesWithoutStopWords;
	}

	std::list <std::string> getWordsFromFile(std::string filename) {

		std::list<std::string> wordList = getWordListFromFile( filename );
		std::list <std::string> stopWordsList = getWordListFromFile( STOPWORDS_FILENAME );
		std::list<std::string> allWords =  deleteStopWords(stopWordsList, wordList);

		return allWords;
	}

}