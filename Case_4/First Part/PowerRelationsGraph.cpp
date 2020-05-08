#include "WordNode.cpp"
#include "TextFormatter.cpp"

#define SENTENCE_MODE 1
#define WORD_MODE 0

class PowerRelationsGraph {
public:
	int wordsAmount;
	std::string filename;
	std::vector<WordNode> powerWords;
	std::map <std::string, WordNode> wordsMap;
	std::vector<std::vector<std::string>> sentencesBag;
	
	PowerRelationsGraph(std::string filename) { this->filename = filename; wordsAmount = 0; } 

	void getReady();
	std::vector<WordNode> getPowerWords(int);
	std::vector<std::vector<WordNode>> getPowerGroups(std::string, int);

private:
	void generateSentenceGraph();
	void sortWordByAvailableNodes();
	int getAvailableWordsAmount(WordNode &);
	WordNode& processWordNode(std::string word, int); 
	
	std::vector<WordNode> _merge(std::vector<WordNode>, std::vector<WordNode>);
	std::vector<WordNode> _mergeSort(std::vector<WordNode>, int);
	std::vector<WordNode>& createGroup(std::string, std::vector<WordNode>&, int, std::string, int);
};

void PowerRelationsGraph::sortWordByAvailableNodes() {

	/* 	Objectivo: ordenar la palabras segun el valor de cantidad de nodos disponibles 
	desde el nodo dado (Nota: ya calculado en processWordNode). [Merge Sort]
	------------------------------------------------------------------------------------
	Complejidad obtenida: O(nlog(n)) siendo n la cantidad de palabras */

	std::cout << "Sorting " << powerWords.size() << " words" << std::endl;
	powerWords = _mergeSort(powerWords, powerWords.size());

}

std::vector<WordNode> PowerRelationsGraph::_mergeSort(std::vector<WordNode> elementContainer, int size) {

	/* Objetivo: (MERGE SORT) ordenar el vector de palabras reduciendo el problema por
	la mitad en cada iteracion

	Complejidad: O(nlog(n)) siendo n la cantidad de elementos a ordenar */	

	if (size == 1) {
		return elementContainer;
	} else {

		int middle = (size)/2;
		std::vector<WordNode> firstPart = std::vector<WordNode>(elementContainer.begin(), elementContainer.begin()+middle);
		std::vector<WordNode> secondPart = std::vector<WordNode>(elementContainer.begin()+middle+1, elementContainer.end());
		
		return _merge(firstPart, secondPart);
	}
}

std::vector<WordNode> PowerRelationsGraph::_merge(std::vector<WordNode> subVector1, std::vector<WordNode> subVector2) {

	/* Objetivo: (MERGE SORT) ordenar dos subvectores del vector original para las palabras
	de poder. 

	Complejidad: O(n) siendo n la cantidad de elementos a ordenar */

	std::vector<WordNode> auxiliarVector;

	while (!subVector1.empty() && !subVector2.empty()) {
		if ( subVector1.front().availableWordsAmount > subVector2.front().availableWordsAmount ) {
			auxiliarVector.push_back(subVector2.front());
			subVector2.erase(subVector2.begin());
		} else {
			auxiliarVector.push_back(subVector1.front());
			subVector1.erase(subVector1.begin());
		}
	}

	while (!subVector1.empty()) {
		auxiliarVector.push_back(subVector1.front());
		subVector1.erase(subVector1.begin());
	}

	while (!subVector2.empty()) {
		auxiliarVector.push_back(subVector2.front());
		subVector2.erase(subVector2.begin());
	}
    
	return auxiliarVector;
}

int PowerRelationsGraph::getAvailableWordsAmount(WordNode& pWordNode) {

	/* 	Objectivo: conocer la maxima cantidad de nodos accesibles desde el nodo de la
	palabra p dada como parametro.
	------------------------------------------------------------------------------------
	Complejidad obtenida: O(n) siendo n la cantidad de relaciones de la palabra dada */

	int availableWordsAmount = 0;

	for (auto const &relation : pWordNode.relations)
		availableWordsAmount += wordsMap.at(relation.first).availableWordsAmount;  

	return availableWordsAmount;
}

WordNode& PowerRelationsGraph::processWordNode(std::string word, int sentenceIndex) {

	/* 	Objectivo: Sino existe agrega el nodo dentro del mapa de palabras, si existe aumenta 
		sus apariciones, retorna el nodo existente o creado, agrega el identificador de oracion y
		suma la cantidad de palabras de la oracion para precalcular la cantidad de palabras que
		pueden ser accesadas desde ese nodo
	------------------------------------------------------------------------------------
	Complejidad obtenida: O(log2(n)) siendo n la cantidad de palabras en el mapa */

	if (wordsMap.count(word) <= 0) {

		WordNode newWordNode = WordNode(word);
		wordsMap.insert({word,newWordNode}); 

		WordNode& currentWord = wordsMap.at(word);
		if (currentWord.lastInsertedSentenceIndex != sentenceIndex) {

			 // en caso de que la palabra exista dos veces en la misma oracion
			currentWord.sentencesCodes.push_back(sentenceIndex);
			currentWord.lastInsertedSentenceIndex = sentenceIndex;
		
			// calculando el numero de palabras accesibles del nodo actual
			currentWord.availableWordsAmount += sentencesBag.at(sentenceIndex).size();
		}
	}

	wordsMap.at(word).appearances++; // O(log2(n))
	return wordsMap.at(word); // O(log2(n))
}

void PowerRelationsGraph::generateSentenceGraph() {

	/* 	Objectivo: relacionar cada una de las palabras de cada oracion con cada una de las 
			palabras dentro de la misma oracion, exceptuando ella misma
	------------------------------------------------------------------------------------
		[ Criterio de relacion dentro de la oracion (SENTENCE STRING) ]
		Oracion de ejemplo:
			"Un gran número sacerdotes primitivos pertenecían clase denominado paranoica"
	
		 (gran) => <= (numero) => <= (sacerdotes) => <= (primitivos) => ....
	------------------------------------------------------------------------------------
	Complejidad obtenida: O(nlog2(n)) siendo n la cantidad de palabras distribuidas en la lista de oraciones */	

	int sentenceCounter = 0;
	for (auto &sentence : sentencesBag) {

		auto penultPosition =  --(sentence.end());
		for (auto wordIterator = ++sentence.begin(); wordIterator != penultPosition; ++wordIterator) {
			
			auto currentIt = wordIterator; 
			WordNode& currentWordNode = processWordNode(*wordIterator, sentenceCounter);  // O(log2(n))
			
			// palabra anterior
			std::advance(wordIterator, -1); 	
			WordNode& previousNode = processWordNode(*wordIterator, sentenceCounter);
			currentWordNode.processRelation(previousNode); // O(log2(n))

			// siguiente palabra
			std::advance(wordIterator, 2); 	
			WordNode& nextNode = processWordNode(*wordIterator, sentenceCounter);					
			currentWordNode.processRelation(nextNode); // O(log2(n))

			wordIterator = currentIt;
		}	

		sentenceCounter++;
	}

	/* obtenemos la cantidad de palabras no repetidas del archivo */
	this->wordsAmount = wordsMap.size();

	/* aprovechando que las palabras se encuentran en orden
	 le damos un identificador con tal de sacar ventaja al saber si 
	 es posterior a otra alfabeticamente posteriormente, ademas al haber 
	 procesado cada una de las palabras. Tambien son agregadas a un vector 
	 para luego ser usada para mostrar las c palabras poderosas del texto

	Complejidad obtenida: O(n) siendo n la cantidad de palabras en el mapa */

	int counter = 0;
	for (auto &word: wordsMap) {
		this->powerWords.push_back(word.second);
		word.second.mapIndex = counter++;
	}
 
 }

std::vector<WordNode>& PowerRelationsGraph::createGroup(std::string theWord, std::vector<WordNode> &group, int relationIndex, std::string key, int kAmount) {

	auto relations = wordsMap.at(key).relatedNodes;
	if (kAmount == 0 || relationIndex >= relations.size()) 
		return group;
	else {
		auto possibleWord = relations[relationIndex].word;
		if (possibleWord == theWord || possibleWord == key) {
			return createGroup(theWord, group, relationIndex + 1, key, kAmount);
		} else {
			group.push_back( possibleWord );
			return createGroup(theWord, group, 0, possibleWord, kAmount-1 );
		}
	}
}

std::vector<std::vector<WordNode>> PowerRelationsGraph::getPowerGroups(std::string pWord, int kGroups) {

	/* 	Objectivo: Obtener los k grupos de poder relacionados con la palabra dada
		------------------------------------------------------------------------------------
		Procedimiento: obtener la cantidad de palabras accesibles desde la palabra dada para 
		calcular la cantidad de vertices (WordNode's) por k grupos a crear, recorrido de las relaciones
		de la palabra dada para generar los grupos
	------------------------------------------------------------------------------------
	Complejidad obtenida: .... TODO */

	std::vector<std::vector<WordNode>> groups;

	if (wordsMap.count(pWord) < 1) {
		std::cout << "Palabra no encontrada" << std::endl;

	} else {

		WordNode &pWordNode = wordsMap.at(pWord);

		// calcula la cantidad de palabras por grupo a crear
		int availableWords = pWordNode.availableWordsAmount;
		int sizePerGroup = pWordNode.relatedNodes.size() / kGroups;
		auto relationIter = pWordNode.relatedNodes.begin();

		int groupCounter = 0;
		while ( groups.size() < kGroups  && relationIter != pWordNode.relatedNodes.end() ) {

			std::string key = (*relationIter).word;
			std::vector<WordNode> processedGroup;
			this->createGroup(pWord, processedGroup, 0, key, sizePerGroup);

			if (processedGroup.size() == sizePerGroup) {
				groups.push_back(processedGroup);
			}
			
			++relationIter;
		}
	}

	return groups;
}

std::vector<WordNode> PowerRelationsGraph::getPowerWords(int cWords) {
	
	/* 	Objectivo: Obtener las c palabras más poderosas del texto, siendo C un entero variable.
		------------------------------------------------------------------------------------
		Procedimiento: retornar de la lista precargada una lista con c elementos 
			indicando cuales son las palabras mas poderosas, recorriendo cada una de las palabras 
			para encontrar las palabras mas relacionadas o poderosas.
	------------------------------------------------------------------------------------
	Complejidad obtenida: O(c) siendo c la cantidad de polabras a retornar*/

	std::vector<WordNode> wordsToReturn;

	std::cout << "Here: " << powerWords.size() << std::endl;

	if (cWords > powerWords.size())
		return powerWords;

	while (cWords > 0) {
		wordsToReturn.push_back(powerWords[ cWords-- ]);
	} 

	return wordsToReturn;
}

void PowerRelationsGraph::getReady() {
	
	// aloja el llamado de las funciones principales encargadas de generar el grafo y preparar
	// antes de consultar: maxima complejidad O(nlog2(n))

	// O(n) 
	sentencesBag = TextFormatter::readSentencesListFromFile(filename); 

	// O(nlog2(n))
	generateSentenceGraph();    

	 // O(nlog2(n))
	sortWordByAvailableNodes();

}