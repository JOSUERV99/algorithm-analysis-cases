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
#define LINESAMOUNT 30

#include"Line.cpp"
#include"Utils.cpp"
#include"LinesGenerator.cpp"
#include"NumberThinker.cpp"
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
	nShapeFinder.showDistribution();

	/*
	[[ 458,  920], [1080,  423]],
	[[1069,  920], [1080,  845]],
	[[  41,  920], [1080,  494]],
	[[ 988,    0], [ 988,  920]],
	[[   0,  801], [1080,  801]]

	0 -> 0
	1 -> 1
	2 -> 0
	3 -> 0
	4 -> 1
	5 -> 0
	6 -> 0
	7 -> 1
	8 -> 0
	9 -> 0
	*/

	nShapeFinder.lookForNumbers(ATTEMPTSNUMBER);
	nShapeFinder.displayResults();

	return EXIT_SUCCESS;
}