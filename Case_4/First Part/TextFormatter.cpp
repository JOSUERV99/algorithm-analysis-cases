namespace TextFormatter {

	void showList(std::list<std::string> wordList) {
		for (auto const &element : wordList) {
			std::cout << element << std::endl;
		}
	}

	std::list <std::string> getWordsListFromFile(std::string filename) {

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

}