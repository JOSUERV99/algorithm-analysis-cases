#include "WordNode.cpp"
#include "TextFormatter.cpp"

#define SENTENCE_MODE 1
#define WORD_MODE 0

class PowerRelationsGraph {
public:
	std::map <std::string, WordNode> wordsMap;
	std::vector<std::vector<std::string>> sentencesBag;
	int wordsAmount;
	
	void generateSentenceGraph();
	std::vector<WordNode> getPowerWords(int);
	WordNode& processWordNode(std::string word, int); 
	std::vector<std::vector<WordNode>> getPowerGroups(std::string, int);

	PowerRelationsGraph(std::string filename) {
		sentencesBag = TextFormatter::readSentencesListFromFile(filename);
		wordsAmount = 0;
	} 

private:
	void showGraph(int);
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

WordNode& PowerRelationsGraph::processWordNode(std::string word, int sentenceIndex) {

	/* 	Objectivo: Sino existe agrega el nodo dentro del mapa de palabras, si existe aumenta 
		sus apariciones, retorna el nodo existente o creado, agrega el identificador de oracion y
		suma la cantidad de palabras de la oracion para precalcular la cantidad de palabras que
		pueden ser accesadas desde ese nodo
	------------------------------------------------------------------------------------
	Complejidad obtenida: O(log2(n)) siendo n la cantidad de palabras en el mapa */

	if (!(wordsMap.count(word) > 1)) { // si no existe
		WordNode newWordNode = WordNode(word);
		wordsMap.insert({word,newWordNode}); 

		WordNode& currentWord = wordsMap.at(word);
		if (currentWord.lastInsertedSentenceIndex != sentenceIndex) {

			 // en caso de que la palabra exista dos veces en la misma oracion
			currentWord.sentencesCodes.push_back(sentenceIndex);
			currentWord.lastInsertedSentenceIndex = sentenceIndex;
		
			// calculando el numero de palabras accesibles desde este nodo
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
			std::advance(++wordIterator, 1); 						
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
	
	return;
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

	// obtener la cantidad de palabras que se pueden acceder desde esta palabra (obtenida en metodo processWordNode)
	WordNode &pWordNode = wordsMap.at(pWord);

	// calcula la cantidad de palabras por grupo a crear
	int sizePerGroup = pWordNode.availableWordsAmount / kGroups;

	std::cout << pWordNode.availableWordsAmount << " palabras accesibles desde \"" << pWord << "\"\n";

	// std::map<std::string, int> relationsOfGivenWord = wordsMap.at(pWord).relations;
	// std::string currentWord;
	// while (groups.size() < m) {


	// }

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