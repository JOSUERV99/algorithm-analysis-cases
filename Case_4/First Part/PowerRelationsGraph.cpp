#include "WordNode.cpp"
#include "TextFormatter.cpp"

#define SENTENCE_MODE 1
#define WORD_MODE 0

class PowerRelationsGraph {
public:
	std::map <std::string, WordNode> wordsMap;
	std::vector<std::vector<std::string>> sentencesBag;
	int wordsAmount;
	
	void getReady();
	void generateSentenceGraph();
	int getAvailableWordsAmount(WordNode &);
	std::vector<WordNode> getPowerWords(int);
	WordNode& processWordNode(std::string word, int); 
	std::vector<std::vector<WordNode>> getPowerGroups(std::string, int);

	PowerRelationsGraph(std::string filename) {
		sentencesBag = TextFormatter::readSentencesListFromFile(filename);
		wordsAmount = 0;
	} 

private:
	void showGraph(int);	
	std::vector<WordNode>& createGroup(std::string, std::vector<WordNode>&, std::string, int);
};

void PowerRelationsGraph::showGraph(int quantity = -1) {
	
	// metodo de prueba
	if (quantity < 0)
		quantity = wordsAmount;

	std::cout << "Amount of words: " << wordsMap.size() << std::endl;
	for (auto const &word : wordsMap) {
		if (quantity-- <= 0)
			break;
		std::cout << word.second; // to show the wordNode
		//std::cout << word.second.word << ": " << word.second.appearances << std::endl;
	}
}

int PowerRelationsGraph::getAvailableWordsAmount(WordNode& pWordNode) {

	/* 	Objectivo: conocer la maxima cantidad de nodos accesibles desde el nodo de la
	palabra p dada como parametro.
	------------------------------------------------------------------------------------
	Complejidad obtenida: O(n) siendo n la cantidad de relaciones de la palabra dada */

	int availableWordsAmount = 0;
	for (auto const &relation : pWordNode.relations)

	// O(log(n)) siendo n la cantidad de relaciones
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
			currentWordNode.processRelation(*wordIterator); // O(log2(n))

			// siguiente palabra
			std::advance(wordIterator, 2); 						
			currentWordNode.processRelation(*wordIterator); // O(log2(n))

			wordIterator = currentIt;
		}	

		sentenceCounter++;
	}

	/* obtenemos la cantidad de palabras no repetidas del archivo */
	this->wordsAmount = wordsMap.size();

	/* aprovechando que las palabras se encuentran en orden
	 le damos un identificador con tal de sacar ventaja al saber si 
	 es posterior a otra alfabeticamente posteriormente, ademas al haber 
	 procesado cada una de las palabras 

	Complejidad obtenida: O(n) siendo n la cantidad de palabras en el mapa */

	int counter = 0;
	for (auto &word: wordsMap) 
		word.second.mapIndex = counter++;
 
 }

std::vector<WordNode>& PowerRelationsGraph::createGroup(std::string theWord, std::vector<WordNode> &group, std::string key, int kAmount) {

	if (kAmount < 0 || key == "" || wordsMap.count(key) < 1) 
		return group;
	else {
		WordNode &currentWordNode =  wordsMap.at(key);
		std::map< std::string, int > relations = currentWordNode.relations;
		auto choosedNode = (*relations.begin()).first == theWord ? relations.end() : ++relations.begin() ;
		key = (choosedNode != relations.end()) ? (*choosedNode).first : "";
		group.push_back( currentWordNode.word );

		return createGroup(theWord, group, key, kAmount-1 );

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

	std::vector< std::vector<WordNode> > groups;

	if (wordsMap.count(pWord) < 1) {
		std::cout << "Palabra no encontrada" << std::endl;
		return groups;
	}

	WordNode &pWordNode = wordsMap.at(pWord);

	// calcula la cantidad de palabras por grupo a crear
	//int availableWords = this->getAvailableWordsAmount(pWordNode);
	int availableWords = pWordNode.availableWordsAmount;
	int sizePerGroup = availableWords / kGroups;

	auto relationsOfGivenWord = pWordNode.relations;
	auto relationIter = relationsOfGivenWord.begin();

	int groupCounter = 0;
	while ( kGroups != groupCounter++  && relationIter != relationsOfGivenWord.end() ) {

		std::string key = (*relationIter).first;
		std::vector<WordNode> processedGroup;
		std::vector<WordNode> newGroup = this->createGroup(key, processedGroup, key, sizePerGroup);

		if (newGroup.size() >= sizePerGroup) {
			groups.push_back(newGroup);
		}

		++relationIter;
	}

	return groups;
}

std::vector<WordNode> PowerRelationsGraph::getPowerWords(int c) {
	
	/* 	Objectivo: Obtener las c palabras más poderosas del texto, siendo C un entero variable.
		------------------------------------------------------------------------------------
		Procedimiento: retornar de la lista precargada una lista con c elementos 
			indicando cuales son las palabras mas poderosas, recorriendo cada una de las palabras 
			para encontrar las palabras mas relacionadas o poderosas.
	------------------------------------------------------------------------------------
	Complejidad obtenida: O(c)  */

	std::vector<WordNode> powerWords;
	return powerWords;
}

void PowerRelationsGraph::getReady() {
	// TODO: realizar el precargado de estructuras y demas aca
}