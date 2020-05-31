#include<vector>
#include<unordered_map>
#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<utility>
#include<random>
#include<time.h>

#define ATTEMPTSNUMBER 70000
#define WIDTH  1080
#define HEIGHT 920

#define NumbersAmount 10
#define CandidateLinesAmount 5

#include"Line.cpp"
#include"LinesGenerator.cpp"
#include"NumberThinker.cpp"
#include"NumberShapeFinder.cpp"
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
	auto lines = lgen.giveMeLines();

	NumberShapeFinder nShapeFinder(lines);
	nShapeFinder.lookForNumbers(ATTEMPTSNUMBER);

	nShapeFinder.displayResults();

	return EXIT_SUCCESS;
}