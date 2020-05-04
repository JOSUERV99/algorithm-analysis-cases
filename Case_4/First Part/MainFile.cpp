
/*  [ author: Josue Rojas Vega ]  */

#include <fstream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <map>
#include <algorithm>
#include <ctype.h>
#include <vector>
#include <unordered_map>
#include <exception>

#include "PowerRelationsGraph.cpp"
#include "Utils.cpp"

#define COMPLETE_TEXT_FILENAME "TextToAnalize.txt" 		
#define FIRST_PARAGRAPH_FILENAME "FirstParagraph.txt" 

using namespace Utils;

int main() {

	/* Idea de trabajo:
			[1] Extraer las palabras descartando caracteres innecesarios 						  
			[2] Agregar las palabras que cumpla con el criterio ( TextFormatter::wordAccepted() )   
			[3] Generar el grafo, registrando sus apariciones y las relaciones como un arco 
			donde el peso representa las veces que se han relacionado esas dos palabras. La 
			relacion entre las dos se hara tomando en cuenta alguna de estas alternativas:
					- Palabra anterior y consecutiva
					- Palabras dentro de la misma oracion
			4. Una vez dada la precarga del grafo de palabras (recorrido y creacion de relaciones de las palabras del texto),
				se podran ejecutar consultas a este para obtener
				las relaciones de poder, cantidad de apariciones, palabras mas poderosas, cuales palabras se relacion
				en mayor y menor cantidad,etc. */

	PowerRelationsGraph graph(COMPLETE_TEXT_FILENAME); 
	graph.getReady(); // O(nlog(n))

	// Querying for groups
	std::string queryedWord = "sacerdote";
	int requestedGroups = 4;
	auto groups = graph.getPowerGroups( queryedWord, requestedGroups );
	show( groups, queryedWord, requestedGroups );

	// Querying for power words
	int requestedPowerWords = 2;
	auto powerWords = graph.getPowerWords( requestedPowerWords );
	show( powerWords );

	return EXIT_SUCCESS;
}