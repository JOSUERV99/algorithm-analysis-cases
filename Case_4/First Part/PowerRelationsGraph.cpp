#include "WordNode.cpp"
#include <vector>

#define SENTENCE_MODE 1
#define WORD_MODE 0

class PowerRelationsGraph {
public:

	// struct WordNodeComparator {
 //     	bool operator()(const std::string& left, const string& right) {
 //       		return getNode(left).points < getNode(right).points;
 //     	}
	// };

	std::unordered_map <std::string, WordNode> wordsMap;
	std::list<std::string> wordsBag;
	std::list<std::list<std::string>> sentencesBag;

	std::vector<WordNode> sortedListForQueries;
	int mode;

	PowerRelationsGraph(std::list <std::string>);
	PowerRelationsGraph(std::list <std::list <std::string>>);
	bool existsRelationBetweenTwoWords(std::string, std::string);
	std::list<WordNode> getPowerWords(int);

private:
	void preloadGraph();
	void createWordNodes(std::list< std::string >);
	void showGraph(int);

	std::vector<WordNode> sortWordNodesByPoints();
	void generateWordsGraph();
	void generateSentenceGraph();
	void addEveryWordAtSentences(std::list <std::list <std::string>>);
	
};

bool WordNodeComparator(WordNode a, WordNode b) {
	return a.points < b.points;
}

std::vector<WordNode> PowerRelationsGraph::sortWordNodesByPoints() {

	/*	Objetivo: usar counting sort para generar una lista precarga de los 
		nodos de palabra ordenados por la cantidad de puntos de poder
	
	Complejidad esperada O(n+k) 	n=cantidad de nodos 	k=tamanio de array auxiliar (rango entre menor y mayor)
	*/

	// obtenemos los nodos a ordenar
	std::vector<WordNode> arr;

	for (auto const &pair: wordsMap) // O(n)
		arr.push_back(pair.second);

	// preparamos el array auxiliar para el conteo
    int max = (*max_element(arr.begin(), arr.end(), WordNodeComparator)).points; 
    int min = (*min_element(arr.begin(), arr.end(), WordNodeComparator)).points; 
    int range = max - min + 1; 
      
    vector<int> count(range), output(arr.size()); 
    for(int i = 0; i < arr.size(); i++) 
        count[arr[i].points -min]++; 
          
    for(int i = 1; i < count.size(); i++) 
           count[i] += count[i-1]; 
    
    for(int i = arr.size()-1; i >= 0; i--) {  
        output[ count[arr[i].points-min] -1 ] = arr[i].points;  
        count[arr[i].points-min]--;  
    } 
      
    for(int i=0; i < arr.size(); i++) 
        arr[i].points = output[i]; 

    return arr;
}

PowerRelationsGraph::PowerRelationsGraph(std::list <std::string> wordsListFromFile) {
	this->mode = WORD_MODE;
	wordsBag = wordsListFromFile;
	preloadGraph();
}

PowerRelationsGraph::PowerRelationsGraph(std::list <std::list <std::string>> sentencesListFromFile) {
	this->mode = SENTENCE_MODE;
	addEveryWordAtSentences(sentencesListFromFile);
	sentencesBag = sentencesListFromFile;
	preloadGraph();
	sortedListForQueries = sortWordNodesByPoints();
}

void PowerRelationsGraph::addEveryWordAtSentences(std::list <std::list <std::string>> sentencesListFromFile) {
	for (auto const &sentence: sentencesListFromFile)
		for (auto const &word: sentence)
			wordsBag.push_back(word);
}

void PowerRelationsGraph::showGraph(int quantity=0) {
	// funcion de testing
	int counter = 0;
	for (auto const &word : wordsMap) {
		std::cout << word.second; // to show the wordNode
		if (quantity != 0 && counter++ >= quantity)
			break;
	}
}

bool PowerRelationsGraph::existsRelationBetweenTwoWords(std::string word, std::string anotherWord) {
	/* 	Objetivo: detectar si ya existe una relacion entre la
	 	primera y segunda palabra dada
	
	Complejidad esperada: O(c)
	Complejidad obtenida: O(log2(n)) -> n=cantidad de relaciones de la palabra */
	
	if (wordsMap.count(word) == 1)
		return wordsMap.at(word).existRelation(anotherWord);
	return false;
}

void PowerRelationsGraph::preloadGraph() {

	/*  Objectivo: tomar cada palabra y establecer cada una de las relaciones, tomando en cuenta si hasta
		ese momento existe relacion entre la palabra dada y alguna otra ya existente

	Complejidad esperada: O(n) 
	Complejidad obtenida: O(nlog2(n)) */
	
	createWordNodes(wordsBag);

	if (mode == WORD_MODE) {	
		generateWordsGraph();	
	} else if (mode == SENTENCE_MODE) {
		generateSentenceGraph();
	}

	/* testing graph */
	//showGraph();
}

void PowerRelationsGraph::createWordNodes(std::list< std::string > words) {
	
	/* Objectivo: 
		Crear un nodo para cada palabra dada en la lista "words"

	Complejidad esperada: O(n)
	Complejidad obtenida: O(nlog2(n)) */

	for (auto const &word : words) {
		if (!(wordsMap.count(word) == 1)) { // si no existe
			WordNode newWordNode = WordNode(word);
			wordsMap.insert({word,newWordNode}); 
		} else {
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

	for (auto it = wordsBag.begin(); it != --(wordsBag.end()); ++it) {
		auto currentIt = it; // to back to the currentWord later (iterator)
		std::string currentWord = *it;
		WordNode& currentWordNode = wordsMap.at(currentWord);

		for (int nearIndex = -1; nearIndex <= 2; nearIndex += 3 ) {		
			std::advance(it, nearIndex);
			std::string nearWord = *it;
			currentWordNode.processRelation(nearWord);
		}

		it = currentIt;
	}
}

void PowerRelationsGraph::generateSentenceGraph() {
	/* 	Objectivo: Obtener las C palabras más poderosas del texto, siendo C un entero variable.
		
		Procedimiento: retornar de la lista precargada una lista con c elementos 
			indicando cuales son las palabras mas poderosas, recorriendo cada una de las palabras 
			para encontrar las palabras mas relacionadas o poderosas.

		Complejidad esperada: O(n) 
		Complejidad obtenida: O(n^2) */

	for (auto const &sentence : sentencesBag)
		for (auto const &word : sentence) 
			for (auto const otherWord : sentence) 
				if (word != otherWord) 
					wordsMap.at(word).processRelation(otherWord);
				
}

std::list<WordNode> PowerRelationsGraph::getPowerWords(int c) {
	
	/* 	Objectivo: Obtener las c palabras más poderosas del texto, siendo C un entero variable.
		
		Procedimiento: retornar de la lista precargada una lista con c elementos 
			indicando cuales son las palabras mas poderosas, recorriendo cada una de las palabras 
			para encontrar las palabras mas relacionadas o poderosas.
		
		Complejidad esperada: O(n) 
		Complejidad obtenida: O(c) 

	*/

	std::list<WordNode> powerWords;

	if (c >= 0) {
		for (int counter = sortedListForQueries.size() - 1; counter >= 0 && sortedListForQueries.size() - counter <= c; counter--)
			powerWords.push_back(sortedListForQueries[counter]);
	}
	return powerWords;
}