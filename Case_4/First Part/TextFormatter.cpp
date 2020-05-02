#define DELIMITER '.' // for sentence mode

namespace TextFormatter {

	bool wordAccepted(std::string word) {
		// @param word debe tener al menos 4 caracteres
		// criterio segun generalizacion de atributos que normalmente se asocian a los sustantivos
		// O(c)

		return 
			word.size() > 4 &&
			word[0] != 'e' && word[1] != 's' && // empieza con 'es'
			word[0] != 'h' && // empieza con h y sigue a, e, o
				(word[1] != 'a' || word[1] != 'u' || word[1] != 'e') && 
			word[word.size()-1] != 'r' && word[word.size()-1] != 's'; // termina en r
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
			
			characterReaded = tolower(reader.get());
			while ( characterReaded && 
					characterReaded != DELIMITER 
					&& characterReaded != EOF && 
					!isspace(characterReaded) && 
					!isdigit(characterReaded) && 
					!ispunct(characterReaded)
				) {
				text += characterReaded;
				characterReaded = reader.get();
			}
			
			if (text != "") {
				if (wordAccepted(text))
					currentSentence.push_back(text);
				text = "";
			}

			if (characterReaded == DELIMITER) { // end of the sentence
				if (currentSentence.size() > 1)
					sentenceList.push_back(currentSentence);
				currentSentence.clear();	
			}
		}

		reader.close();
		return sentenceList;
	}
}
