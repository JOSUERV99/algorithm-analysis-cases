// constructing maps
#include <iostream>
#include <unordered_map>
#include <string>
#include <stdio.h>
#include <list>
#include "WordNode.cpp"

int main () {
/*	std::unordered_map<std::string, WordNode> first;

	WordNode w = WordNode("Hola", 1);
	//first["a"]= w; 
	first.insert({"Hola", w});
	// first["b"]=30;
	// first["c"]=50;
	// first["d"]=70;


	// USO PROPIO
	std::string some_key = "Key";
	first.count(some_key); // existencia de la llave

	w.points = 10;
	first.insert({"Key", w}); // agregar nuevo valor al mapa
	first.at(some_key); // sabiendo que existe se puede obtener de esta forma
	
	// in cicles
	//value.first "Key"
	//value.second "Object"

	std::cout << ( (first.count("Hola") ? "Hola existo" : "Not buddy")) <<std::endl;
	for (auto const &value : first) 
		std::cout << value.second << std::endl;*/

	std::unordered_map<std::string, int> map;
	map.insert({"Hola", 1});
	std::cout << map.at("Hola") << std::endl;

	return 0;
}