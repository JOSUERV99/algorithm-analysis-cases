#include <unordered_map>
#include "WordNode.cpp"

class WordGraph {
protected:
	std::unordered_map < std::string, WordNode > wordsMap;
	std::list< std::string > wordsBag;
public:
	WordGraph(std::list< std::string > wordsListFromFile ) {
		this.wordsBag = wordsListFromFile;
		preloadText();
	}

	void preloadText(std::string text = this.text);
	std::list<pair<int, std::string>> getPowerWords(int c);

private:
	void insertWordInSortedWay();
	void deleteStopWordsFromText();
	void formatText();
}

void WordGraph::preloadText() {
	if (this.text == NULL)
		return;


}

std::list<pair<int, std::string>> WordGraph::getPowerWords(int c) {
	/* 
		Objectivo: Obtener las C palabras más poderosas del texto, siendo C un entero variable.
		Procedimiento: retornar de la lista precargada una lista con c elementos 
			indicando cuales son las palabras mas poderosas.
	*/
	return NULL;

}



/*
	Objectivo: una vez se estan cargando las palabras 
	 cantidad de relaciones entre ellas para facilitar obtener palabras de poder

	Si ya existe aumentar el valor de relacion en el par ordenado
*/

