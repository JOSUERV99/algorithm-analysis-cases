#include <string>
#include <utility>
#include <iostream>

using namespace std;

class WordNode { 
public:
	std::string word;
	std::unordered_map <std::string, int> relations;
	int appearances, points;

	WordNode(std::string word){
		this->word = word;
		this->appearances = this->points = 1;
	}

	std::list<std::pair<int, std::string>> getRelatedWords(int quantity);
	void addRelation(std::string word, int arcWeight);
	bool existRelation(std::string key);
	
	friend std::ostream& operator << (std::ostream &o,const WordNode &object) {
		o << "***********************" << std::endl << 
			"Word: " << object.word << std::endl <<
			"Relations: " << object.relations.size() << std::endl;

		for (auto const &relation: object.relations)
			o << "Rel.Word: " << relation.first << std::endl <<
				 "Times: " << relation.second << std::endl;
		
		o << "Appearances:" << object.appearances << std::endl <<
			"Score: "<< object.points << " pts" << std::endl <<
		"***********************" << std::endl;
		return o;
	}

};

bool WordNode::existRelation(std::string key) {
	if (relations.size() == 0)
		return false;
	return relations.count(key) == 1;
}

std::list<std::pair<int, std::string>> WordNode::getRelatedWords(int quantity) {
	/* 
		Objectivo: dada sus relaciones obtener la cantidad de palabras pedidas por parametro
		Complejidad esperada: O(c)
	*/

	std::list<pair<int, std::string>> listReturned;
	return listReturned;
}

void WordNode::addRelation(std::string word, int arcWeight = 1) {
	/* 
		Objectivo: agregar una nueva relacion dentro del grafo
		Complejidad esperada: O(c)
		Complejidad obtenida: O(c)
	*/
	relations.insert({word, arcWeight});
}


