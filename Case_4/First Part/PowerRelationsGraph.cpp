#include "WordNode.cpp"

#define SENTENCE_MODE 1
#define WORD_MODE 0

class PowerRelationsGraph {
public:
	std::unordered_map <std::string, WordNode> wordsMap;
	std::list<std::string> wordsBag;
	int mode;

	PowerRelationsGraph(std::list <std::string> wordsListFromFile, int mode);
	void preloadGraph();
	void showGraph(int);
	bool existsRelationBetweenTwoWords(std::string, std::string);
	std::list <WordNode> getPowerWords(int);
	void generateWordsGraph();
};

PowerRelationsGraph::PowerRelationsGraph(std::list <std::string> wordsListFromFile, int mode=WORD_MODE) {
	wordsBag = wordsListFromFile;
	this->mode = mode;
	preloadGraph();
}

void PowerRelationsGraph::showGraph(int quantity) {
	// funcion de testing
	int counter = 0;
	for (auto const &word : wordsMap) {
		std::cout << word.second;
		if (++counter >= quantity)
			break;
	}
}

bool PowerRelationsGraph::existsRelationBetweenTwoWords(std::string word, std::string anotherWord) {
	/* Objetivo: 
		detectar si ya existe una relacion entre la primera y segunda palabra dada
	Complejidad esperada: O(c)
	Complejidad obtenida: O(log2(n)) -> n=cantidad de relaciones de la palabra*/
	
	if (wordsMap.count(word) == 1)
		return wordsMap.at(word).existRelation(anotherWord);
	return false;
}

void PowerRelationsGraph::preloadGraph() {

	/*  Objectivo: tomar cada palabra y establecer cada una de las relaciones, tomando en cuenta si hasta
		ese momento existe relacion entre la palabra dada y alguna otra ya existente

	Complejidad esperada: O(n) 
	Complejidad obtenida: O(nlog2(n)) */
	
	if (mode == WORD_MODE) {
		for (auto const &word : wordsBag) {
			if (!(wordsMap.count(word) == 1)) { // si no existe
				WordNode newWordNode = WordNode(word);
				wordsMap.insert({word,newWordNode}); 
			} else 
				wordsMap.at(word).appearances++; // O(log2(n))
		}	
	} 
}

void PowerRelationsGraph::generateWordsGraph() {
	
	/*  Objetivo: recorrer las palabras obtenidas despues del formateo del texto, crear un diccionario
			con cada una de las palabras con un objeto WordNode asociado con el fin de llevar registro de:
				1. Cantidad de apariciones de las palabras de forma independiente
				2. Crear relacion entre las palabras y aumentando el contador del arco cuando estas
					se relacionen mas de una vez
				3. Crear objectos WordNode cada que se encuentra una nueva palabra que no esta asociada con nadie
				4. Revisar si ya existe relacion entre las dos palabras asociadas

	Complejidad esperada: O(n) 
	Complejidad obtenida: O(n) */
	
	for (auto it = wordsBag.begin(); it != wordsBag.end()--; ++it) {
		std::string currentWord = *it;
		WordNode currentWordNode = wordsMap.at(currentWord);

		for (int nearIndex = -1; nearIndex < 2; nearIndex +=2 ) {	
			std::advance(it, nearIndex);
			std::string nearWord = *it;
			
			if ( !currentWordNode.existRelation( nearWord ))
				currentWordNode.addRelation( nearWord, 1 );
			else
				currentWordNode.relations.at( nearWord )++;
		}
	}
}

std::list <WordNode> PowerRelationsGraph::getPowerWords(int c) {
	
	/* 	Objectivo: Obtener las C palabras más poderosas del texto, siendo C un entero variable.
		
		Procedimiento: retornar de la lista precargada una lista con c elementos 
			indicando cuales son las palabras mas poderosas, recorriendo cada una de las palabras 
			para encontrar las palabras mas relacionadas o poderosas.

		Complejidad esperada: O(n) */

	std::list<WordNode> map;
	return map;
}


