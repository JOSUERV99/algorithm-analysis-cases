
/* 
	[ author: Josue Rojas Vega ]
*/
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include <stdio.h>
#include <map>
#include <algorithm>
#include <ctype.h>
#include <vector>
#include <unordered_map>

#include <wchar.h>
#include <locale.h>

#include "TextFormatter.cpp" 
#include "PowerRelationsGraph.cpp"

#define COMPLETE_TEXT_FILENAME "TextToAnalize.txt" 		
#define FIRST_PARAGRAPH_FILENAME "FirstParagraph.txt" 

int countWords(std::list<std::list<std::string>>);

int main() {

	/* Idea de trabajo:
			[1] Extraer las palabras descartando caracteres innecesarios 						  
			[2] Agregar las palabras que cumpla con el criterio ( TextFormatter::wordAccepted() )   
			[3] Generar el grafo, registrando sus apariciones y las relaciones como un arco 
			donde el peso representa las veces que se han relacionado esas dos palabras. La 
			relacion entre las dos se hara tomando en cuenta alguna de estas alternativas:
					3.1 Palabra anterior y consecutiva
					3.2 Palabras dentro de la misma oracion
			4. Una vez dada la precarga del grafo de palabras (recorrido y creacion de relaciones de las palabras del texto),
				se podran ejecutar consultas a este para obtener
				las relaciones de poder, cantidad de apariciones, palabras mas poderosas, cuales palabras se relacion
				en mayor y menor cantidad,etc. */

	std::cout << "Hello World!" << std::endl;
	return EXIT_SUCCESS;
}

int countWords(std::list<std::list<std::string>> sentences) {
	int counter = 0;
	for(auto const &sentence: sentences){
		for (auto const &word: sentence) {
			counter++;
		}
	}
	return counter;
}



