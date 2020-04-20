
/* 
	[ author: Josue Rojas Vega ]
*/

#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <list>
#include <algorithm>
#include <stdio.h>
#include <unordered_map>
#include <algorithm>

#include "TextFormatter.cpp" 
#include "PowerRelationsGraph.cpp"

#define COMPLETE_TEXT_FILENAME "TextToAnalize.txt" 		
#define FIRST_PARAGRAPH_FILENAME "FirstParagraph.txt" 

// StopWords file getted from: https://github.com/Alir3z4/stop-words/blob/master/spanish.txt

void showSentences(std::string);
void showWords(std::string);

int main() {

	/* Idea de trabajo:
			1. Extraer las palabras descartando caracteres innecesarios
			2. Eliminar palabras repetitivas (StopWords)
			3. Generar el grafo, registrando sus apariciones y las relaciones como un arco donde el peso
				representa las veces que se han relacionado esas dos palabras. La relacion entre las dos
				se hara tomando en cuenta alguna de estas alternativas:
					3.1 Palabra anterior y consecutiva
					3.2 Palabras dentro de la misma oracion ###
					3.3 Palabras dentro del mismo parrafo
				(Nota: las relaciones de cada palabra se crearan dentro de un mapa o "tabla hash" al igual
					que el grafo de cada una de ellas, dando como resultado, una mapa de palabras y cada una de 
					ellas con su mapa de relaciones con las otras, como un grafo)
			4. Una vez dada la precarga del grafo de palabras (recorrido y creacion de relaciones de las palabras del texto),
				se podran ejecutar consultas a este para obtener
				las relaciones de poder, cantidad de apariciones, palabras mas poderosas, cuales palabras se relacion
				en mayor y menor cantidad,etc. */

	//auto data = TextFormatter::getWordsFromFile(COMPLETE_TEXT_FILENAME);
	auto data = TextFormatter::getSentencesFromFile(COMPLETE_TEXT_FILENAME);
	PowerRelationsGraph prGraph(data);

	std::list<WordNode> powerWords = prGraph.getPowerWords(15);
	for (auto const &pWord: powerWords)
		std::cout << pWord << std::endl;

	return EXIT_SUCCESS;
} 

void showWords(std::string filename) {
	
	std::list<std::string> wordsBag = TextFormatter::getWordsFromFile(filename);
	int counter = 0;
	for (auto const &word: wordsBag){
		std::cout << counter << ":" << word << std::endl;
		counter++;
	}
	std::cout << " Palabras limpias: " << counter << std::endl;
}

void showSentences(std::string filename){

	std::list< std::list<std::string>> sentencesBag = TextFormatter::getSentencesFromFile(filename);
	for (auto const &sentence: sentencesBag){
		std::cout << "Oracion con " << sentence.size() << " palabras: " << "{ " << std::endl;
		for (auto const &word : sentence){
			std::cout << word << std::endl;
		}
		std::cout << " }\n\n\n";
	}
	std::cout<< "Oraciones encontradas: " << sentencesBag.size() << std::endl;
}

