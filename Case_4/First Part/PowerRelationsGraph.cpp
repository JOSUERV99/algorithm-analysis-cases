#include "WordNode.cpp"
#include <vector>

#define SENTENCE_MODE 1
#define WORD_MODE 0

class PowerRelationsGraph {
public:
	std::unordered_map <std::string, WordNode> wordsMap;
	std::list<std::string> wordsBag;
	std::list<std::list<std::string>> sentencesBag;
	int wordsAmount;
	std::vector<WordNode> sortedListForQueries;

	PowerRelationsGraph(std::list <std::string>, int);
	PowerRelationsGraph(std::list <std::list <std::string>>);
	bool existsRelationBetweenTwoWords(std::string, std::string);
	
	std::list<WordNode> getPowerWords(int);
	std::list<std::list<WordNode>> getPowerGroups(std::string, int);
private:
	void createWordNodes(std::list< std::string >);
	void showGraph(int);

	std::vector<WordNode> sortWordNodesByPoints();
	void generateSentenceGraph();
	void createRelationsMatrix();
};

bool WordNodeComparator(WordNode a, WordNode b) {
	return a.points < b.points;
}

std::vector<WordNode> PowerRelationsGraph::sortWordNodesByPoints() {

	// obtenemos los nodos a ordenar
	std::vector<WordNode> arr;
	for (auto const &pair: wordsMap) // O(n)
		arr.push_back(pair.second);

	// QUICKSORT
	int l = 0, h = arr.size();
	// Create an auxiliary stack 
    int stack[h - l + 1]; 
  
    // initialize top of stack 
    int top = -1; 
  
    // push initial values of l and h to stack 
    stack[++top] = l; 
    stack[++top] = h; 
  
    // Keep popping from stack while is not empty 
    while (top >= 0) { 
        // Pop h and l 
        h = stack[top--]; 
        l = stack[top--]; 
  
        // Set pivot element at its correct position 
        // in sorted array 
        int x = arr[h].points; 
	    int i = (l - 1); 
	  
	    for (int j = l; j <= h - 1; j++) { 
	        if (arr[j].points <= x) { 
	            i++; 
	            WordNode aux = arr[i];
	            arr[i] = arr[j];
	            arr[j] = aux;
	        } 
	    } 

	    WordNode aux = arr[i + 1];
	    arr[i + 1] = arr[h];
	    arr[h] = aux;

        int p = (i + 1); 
  
        // If there are elements on left side of pivot, 
        // then push left side to stack 
        if (p - 1 > l) { 
            stack[++top] = l; 
            stack[++top] = p - 1; 
        } 
  
        // If there are elements on right side of pivot, 
        // then push right side to stack 
        if (p + 1 < h) { 
            stack[++top] = p + 1; 
            stack[++top] = h; 
        } 
    } 

    return arr;
}

PowerRelationsGraph::PowerRelationsGraph(std::list <std::list <std::string>> sentencesListFromFile, int amount) {

	sentencesBag = sentencesListFromFile;
	generateSentenceGraph();
	sortedListForQueries = sortWordNodesByPoints();
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

	/* 	Objectivo: relacionar cada una de las palabras de cada oracion con cada una de las 
			palabras dentro de la misma oracion, exceptuando ella misma

		// Criterio de relacion dentro de la oracion (Cadena)

		Oracion de ejemplo:
			"Un gran número sacerdotes primitivos pertenecían clase denominado paranoica"

		Un -> <- gran -> <- numero -> <- sacerdotes -> <- primitivos ->
		
	Complejidad esperada: O(n) 
	Complejidad obtenida: O(n) */	

	for (auto const &sentence : sentencesBag) {
		// TODO: usar iteradores para acceder a palabras consecutivas
	}		
}

std::list< std::list<WordNode> > getPowerGroups(std::string word, int groupsAmount) {

	std::list< std::list<WordNode> > groups;

	return groups;

}

std::list<WordNode> PowerRelationsGraph::getPowerWords(int c) {
	
	/* 	Objectivo: Obtener las c palabras más poderosas del texto, siendo C un entero variable.
		
		Procedimiento: retornar de la lista precargada una lista con c elementos 
			indicando cuales son las palabras mas poderosas, recorriendo cada una de las palabras 
			para encontrar las palabras mas relacionadas o poderosas.
		
	Complejidad esperada: O(n) 
	Complejidad obtenida: O(c)  */

	std::list<WordNode> powerWords;

	if (c >= 0) {
		for (int counter = sortedListForQueries.size() - 1; counter >= 0 && sortedListForQueries.size() - counter <= c; counter--)
			powerWords.push_back(sortedListForQueries[counter]);
	}
	return powerWords;
}