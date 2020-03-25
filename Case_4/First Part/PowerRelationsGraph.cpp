#include <unordered_map>
#include "WordNode.cpp"

class PowerRelationsGraph {
protected:
	std::unordered_map <std::string, WordNode> wordsMap;
	bool loaded;
public:
	PowerRelationsGraph(std::list <std::string> wordsListFromFile ) {
		loaded = false;
		generateWordsGraph(wordsListFromFile);
	}

	bool existsRelationBetweenTwoWords(std::string word1, std::string word2);
	bool existsWordInGraph(std::string word);
	std::list <WordNode> getPowerWords(int c);

private:
	void preloadGraph();
	void generateWordsGraph(std::list <std::string> wordsBag);
}

void PowerRelationsGraph::preloadGraph() {
	/* 
		Objectivo: tomar cada palabra y establecer cada una de las relaciones, tomando en cuenta si hasta
		ese momento existe relacion entre la palabra dada y alguna otra ya existente

		Complejidad esperada: O(n)
	*/
}

void PowerRelationsGraph::generateWordsGraph(std::list <std::string> wordsBag) {
	/* 
		Objetivo: recorrer las palabras obtenidas despues del formateo del texto, crear un diccionario
			con cada una de las palabras con un objeto WordNode asociado con el fin de llevar registro de:
				1. Cantidad de apariciones de las palabras de forma independiente
				2. Crear relacion entre las palabras y aumentando el contador del arco cuando estas
					se relacionen mas de una vez
				3. Crear objectos WordNode cada que se encuentra una nueva palabra que no esta asociada con nadie
				4. Revisar si ya existe relacion entre las dos palabras asociadas

		Complejidad esperada: O(n)
	*/
}

bool PowerRelationsGraph::existsWordInGraph(std::string word) {
	/* 
		Objectivo: Revisar si la palabra esta una vez precargado el grafo

		Complejidad esperada: O(c)
	*/
	return false;
}


std::list <WordNode> PowerRelationsGraph::getPowerWords(int c) {
	/* 
		Objectivo: Obtener las C palabras más poderosas del texto, siendo C un entero variable.
		
		Procedimiento: retornar de la lista precargada una lista con c elementos 
			indicando cuales son las palabras mas poderosas, recorriendo cada una de las palabras 
			para encontrar las palabras mas relacionadas o poderosas.

		Complejidad esperada: O(n)
	*/

	return NULL;
}
