#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<utility>
#include<random>
#include<time.h>
#include<algorithm>

#define ATTEMPTSNUMBER 10000
#define WIDTH  1080
#define HEIGHT 920

#define NUMBERSAMOUNT 10
#define LINESAMOUNT 50

#include"Line.cpp"
#include"Utils.cpp"
#include"LinesGenerator.cpp"
#include"NumberShapeFinder.cpp"

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

	NumberShapeFinder nShapeFinder( lgen.giveMeLines(LINESAMOUNT) );
	nShapeFinder.generateProbabilityDistribution();

	nShapeFinder.lookForNumbers(ATTEMPTSNUMBER);
	nShapeFinder.displayResults();

	nShapeFinder.showDistribution();

	return EXIT_SUCCESS;
}