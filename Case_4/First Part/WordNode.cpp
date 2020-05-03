#include <string>
#include <utility>
#include <iostream>

using namespace std;

class WordNode { 
public:
	std::string word;
	std::map <std::string, int> relations;
	int appearances;

	WordNode(std::string word) { this->word = word; }
	bool existRelation(std::string key);
	void processRelation(std::string);
	
	friend std::ostream& operator << (std::ostream &o,const WordNode &object) {
		o << "***********************" << std::endl << 
			"Word: " << object.word << std::endl <<
			"Relations: " << object.relations.size() << std::endl;

		int counter = 0;
		for (auto const &relation: object.relations) {
			if (relation.second > 1) { // *****************************
				o << "{" << relation.first << "," << relation.second << "}, ";
				if (counter != 0 && counter%4 == 0)
					o << "\n";
				counter++;
			}
		}
		
		o << "\n\nAppearances:" << object.appearances << std::endl <<
		"***********************" << std::endl;
		return o;
	}
};

bool WordNode::existRelation(std::string key) {
	/* 
			Objetivo: obtener caracter a caracter el contenido del archivo de texto, 
			tomando en cuenta cada palabra para formar una oracion delimitada por punto '.'
	------------------------------------------------------------------------------------
	Complejidad obtenida: O(log(n)) siendo n la cantidad de caracteres
	*/

	if (relations.size() == 0)
		return false;
	return relations.count(key) == 1; // O(log(n)) 
}

void WordNode::processRelation(std::string nearWord) {
	/* 
			Objetivo: obtener caracter a caracter el contenido del archivo de texto, 
			tomando en cuenta cada palabra para formar una oracion delimitada por punto '.'
	------------------------------------------------------------------------------------
	// Nota: log(n) y no log(k) porque k en el peor de los casos seria n (almacenando todas las palabras en el mismo contenedor)
	Complejidad obtenida: O(log(n)) siendo n la cantidad de caracteres
	*/

	if ( !existRelation(nearWord) )
		relations.insert( {nearWord, 1} ); // O(n*log(k+n)) siendo n la cantidad de elementos a insertar (1), y k el tamanio del contenedor
	else 
		relations.at( nearWord )++; // O(log(n))
}


