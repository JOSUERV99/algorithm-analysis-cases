#include <string>
#include <utility>
#include <iostream>

using namespace std;

class WordNode { 
protected:
	std::string word;
	std::unordered_map <std::string, int> relations;
	int appearances;
public:
	
	WordNode(std::string word = ""){
		this->word = word;
	}

	std::list<pair<int, std::string>> getRelatedWords(int quantity);
	void addRelation(std::string word, int arcWeight = 1);
	bool existRelation (std::string anotherWord);

};

std::list<pair<int, std::string>> WordNode::getRelatedWords(int quantity = relations.size()) {
	/* 
		Objectivo: dada sus relaciones obtener la cantidad de palabras pedidas por parametro

		Complejidad esperada: O(n)
	*/
}

void WordNode::addRelation(std::string word, int arcWeight = 1) {
	/* 
		Objectivo: agregar una nueva relacion dentro del grafo

		Complejidad esperada: O(c)
	*/
}


