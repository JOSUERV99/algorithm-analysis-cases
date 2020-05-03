#include "WordNode.cpp"

#define SENTENCE_MODE 1
#define WORD_MODE 0

class PowerRelationsGraph {
public:
	std::map <std::string, WordNode> wordsMap;
	std::list<std::list<std::string>> sentencesBag;
	int amount;
	
	PowerRelationsGraph(std::list <std::list <std::string>> sentencesListFromFile) 
	{  sentencesBag = sentencesListFromFile;	}
	PowerRelationsGraph(std::list <std::list <std::string>> sentencesListFromFile, int amount) 
	{  sentencesBag = sentencesListFromFile; this->amount = amount;  }

	void generateSentenceGraph();
	WordNode& addWordNode(std::string word); 
	std::list<WordNode> getPowerWords(int);
	std::list<std::list<WordNode>> getPowerGroups(std::string, int);

private:
	void showGraph(int);
};

void PowerRelationsGraph::showGraph(int quantity=0) {
	// metodo de testing
	int counter = 0;
	for (auto const &word : wordsMap) {
		std::cout << word.second; // to show the wordNode
		if (quantity != 0 && counter++ >= quantity)
			break;
	}
}

WordNode& PowerRelationsGraph::addWordNode(std::string word) {

	/* 	Objectivo: 
		agregar el nodo dentro del mapa de palabras
	------------------------------------------------------------------------------------
	Complejidad obtenida: O(log2(n)) siendo n la cantidad de palabras en el mapa */

	if (!(wordsMap.count(word) == 1)) { // si no existe
		WordNode newWordNode = WordNode(word);
		wordsMap.insert({word,newWordNode}); 
	} else 
		wordsMap.at(word).appearances++; // O(log2(n))

	return wordsMap.at(word); // O(log2(n))
}

void PowerRelationsGraph::generateSentenceGraph() {

	/* 	Objectivo: relacionar cada una de las palabras de cada oracion con cada una de las 
			palabras dentro de la misma oracion, exceptuando ella misma
	------------------------------------------------------------------------------------
		[ Criterio de relacion dentro de la oracion (Cadena) ]
		Oracion de ejemplo:
			"Un gran número sacerdotes primitivos pertenecían clase denominado paranoica"
	
		 gran -> <- numero -> <- sacerdotes -> <- primitivos
	------------------------------------------------------------------------------------
	Complejidad obtenida: O(nlog2(n)) siendo n la cantidad de palabras distribuidas en la lista de oraciones */	

	for (auto &sentence : sentencesBag) {
		for (auto wordIterator = ++sentence.begin(); wordIterator != --(sentence.end()); ++wordIterator) {
			
			auto currentIt = wordIterator; 

			// agrega la palabra y retorna el nodo
			WordNode& currentWordNode = addWordNode(*wordIterator); // O(log2(n))

			std::advance(wordIterator, -1); // palabra anterior
			currentWordNode.processRelation(*wordIterator); // O(log2(n))
			wordIterator = currentIt;
			std::advance(wordIterator, 1); // siguiente palabra
			currentWordNode.processRelation(*wordIterator); // O(log2(n))

			wordIterator = currentIt;
		}	
	}
}

std::list<std::list<WordNode>> getPowerGroups(std::string word, int groupsAmount) {

	/* 	Objectivo: Obtener las c palabras más poderosas del texto, siendo C un entero variable.
		------------------------------------------------------------------------------------
		Procedimiento: retornar de la lista precargada una lista con c elementos 
			indicando cuales son las palabras mas poderosas, recorriendo cada una de las palabras 
			para encontrar las palabras mas relacionadas o poderosas.
	------------------------------------------------------------------------------------
	Complejidad obtenida: O(c)  */

	std::list< std::list<WordNode> > groups;
	return groups;
}

std::list<WordNode> PowerRelationsGraph::getPowerWords(int c) {
	
	/* 	Objectivo: Obtener las c palabras más poderosas del texto, siendo C un entero variable.
		------------------------------------------------------------------------------------
		Procedimiento: retornar de la lista precargada una lista con c elementos 
			indicando cuales son las palabras mas poderosas, recorriendo cada una de las palabras 
			para encontrar las palabras mas relacionadas o poderosas.
	------------------------------------------------------------------------------------
	Complejidad obtenida: O(c)  */

	std::list<WordNode> powerWords;
	return powerWords;
}