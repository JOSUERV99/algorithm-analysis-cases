#define DELIMITER '.' // for sentence mode
#define STOPWORDS_FILENAME "StopWords(SPANISH).txt"

namespace TextFormatter {

	std::list <std::string> getWordListFromFile(std::string filename) {

		/* 
			Objetivo: obtener caracter a caracter el contenido del archivo de texto, 
			usada par obtener las "stopWords" para tener una mejor fuente de palabras

		Complejidad obtenida: O(n) siendo n la cantidad de caracteres
		*/

		std::ifstream reader (filename, std::ifstream::in);
		std::list <std::string> wordList;
		char characterReaded;

		while (reader.good()) {

			std::string text = "";

			characterReaded = reader.get();
			while ( characterReaded && characterReaded != EOF && !isspace(characterReaded) 
						&& !ispunct(characterReaded) && !isdigit(characterReaded)) {
				
				text += characterReaded;
				characterReaded = reader.get();
			}
			
			if (text != "") {
				transform(text.begin(), text.end(), text.begin(), ::tolower);
				wordList.push_back(text);
			}
		}

		reader.close();
		return wordList;
	}

	std::list < std::list <std::string> > readSentencesListFromFile(std::string filename) {

		/* 
			Objetivo: obtener caracter a caracter el contenido del archivo de texto, 
			tomando en cuenta cada palabra para formar una oracion delimitada por punto '.'

		Complejidad obtenida: O(n) siendo n la cantidad de caracteres
		*/

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

	std::list <std::string> deleteStopWords(std::list <std::string> stopWordsList, std::list <std::string> sentence) {

		/* 
			Objetivo: descartar las palabras "stop" dentro del conjunto de oraciones

		Complejidad obtenida: O(n^2) siendo n la cantidad de palabras por oracion dada
		*/

		std::list <std::string> cleanWords;
		
		for (auto const &word: sentence) {
			bool uselessWordFlag = false;
			for (auto const &stopWord: stopWordsList)
				if (stopWord == word) {
					uselessWordFlag = true;
					break;
				}

			if (!uselessWordFlag) {
				cleanWords.push_back(word);
			}
		}

		return cleanWords;
	}

	std::list < std::list<std::string> > getSentencesFromFile(std::string filename) {

		// TODO:  ---n^3---

		std::list < std::list<std::string> > sentencesWithoutStopWords;
		std::list < std::list<std::string> > sentences = readSentencesListFromFile(filename); // O(n)
		std::list < 	  std::string  	   > stopWordsList = getWordListFromFile( STOPWORDS_FILENAME ); // O(n)
		
		// O(n^3)
		for (auto const &sentence: sentences) { // O(n)
			std::list <std::string> simpleSentence = deleteStopWords(stopWordsList, sentence); // O(n^2)
			if (simpleSentence.size() > 1)
				sentencesWithoutStopWords.push_back(simpleSentence);
		}

		return sentencesWithoutStopWords;
	}

	std::list <std::string> getWordsFromFile(std::string filename) {

		std::list<std::string> wordList = getWordListFromFile( filename );
		std::list<std::string> stopWordsList = getWordListFromFile( STOPWORDS_FILENAME );
		std::list<std::string> allWords =  deleteStopWords(stopWordsList, wordList);

		return allWords;
	}

}