#include<vector>
#include<unordered_map>
#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<utility>
#include<random>
#include<time.h>

#define Line std::vector<std::pair<int,int>> // line definition
#define ATTEMPTSNUMBER 10000

#include"NumberShapeFinder.cpp"
#include"NumberThinker.cpp"
#include"LinesGenerator.cpp"
#include"Utils.cpp"

using namespace Utils;

/*
	Ejercicio:
	Dada la lista de las K líneas trazadas
	determine cuáles números de 1 dígito se formaron
	en la visualización 2D de dichas líneas.
*/

int main() {

	// set random seed
	srand(time(NULL));

	LinesGenerator lgen;
	std::vector<Line> lines = lgen.giveMeLines();

	showLines(lines);
	
	// std::default_random_engine generator;
	// std::uniform_int_distribution<int> distribution(1,6);
	// int dice_roll = distribution(generator);

	return EXIT_SUCCESS;
}