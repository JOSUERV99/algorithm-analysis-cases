#define DELIMITER '.' // delimiter '.' of the sentence

namespace TextFormatter {

	/* 
		Extraccion de caracteres del archivo para crear palabras, y con estas crear oraciones siguiendo
		el criterio de la function 'wordAccepted'
	*/

	bool wordAccepted(std::string word) {

		// Criterio segun generalizacion de caracteristicas que normalmente se asocian a los sustantivos
		// Complejidad obtenida: O(c)

		if (word.size() <= 4)
			return false; 

		// empieza con h y sigue a, e, o
		if ( word[0] == 'h' && (word[1] == 'a' || word[1] == 'u' || word[1] == 'e'))
			return false;

		if (word[word.size()-3] == 'n' &&  word[word.size()-2] == 'd' && word[word.size()-1] == 'o')
			return false;

		if (word[word.size()-3] == 's' &&  word[word.size()-2] == 't' && (word[word.size()-1] == 'o' || word[word.size()-1] == 'a' || word[word.size()-1] == 'e')  )
			return false;

		if (word[word.size()-3] == 'r' &&  (word[word.size()-2] == 'o' || word[word.size()-2] == 'a') && word[word.size()-1] == 'n')
			return false;

		if (word[word.size()-3] == 'a' &&  word[word.size()-2] == 'b' && word[word.size()-1] == 'a'
			|| word[word.size()-4] == 'a' &&  word[word.size()-3] == 'b' && word[word.size()-2] == 'a' && word[word.size()-1] == 'n') {
			return false;
		}

		return word[0] != 'e' && word[1] != 's' && word[word.size()-1] != 'r' && word[word.size()-1] != 's' &&  
			word[word.size()-3] != 'n' &&  word[word.size()-2] != 'd' && word[word.size()-1] != 'o';
	}

	bool charAccepted(char characterReaded) {

		// Filtro de caracteres para delimitar a una palabra
		// Complejidad obtenida: O(c)

		return characterReaded && 
			characterReaded != DELIMITER && 
			characterReaded != EOF && 
			!isspace(characterReaded) && 
			!isdigit(characterReaded) && 
			!ispunct(characterReaded);
	}

	std::vector<std::vector<std::string>> readSentencesListFromFile(std::string filename) {

		/* 
			Objetivo: obtener caracter a caracter el contenido del archivo de texto, 
			tomando en cuenta cada palabra para formar una oracion delimitada por punto '.'

		Complejidad obtenida: O(n) siendo n la cantidad de caracteres */

		std::ifstream reader (filename, std::ifstream::in);
		std::vector <std::vector<std::string>> sentenceList; 
		std::vector<std::string> currentSentence;
		
		while (reader.good()) {

			std::string text = "";
			char characterReaded = tolower(reader.get());

			while ( charAccepted(characterReaded) ) {
				text += characterReaded;
				characterReaded = reader.get();
			}
			
			if (text != "") {
				if (wordAccepted(text))
					currentSentence.push_back(text);
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
}
