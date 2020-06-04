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

#define ATTEMPTSNUMBER 1000
#define WIDTH  1080
#define HEIGHT 920

#define NUMBERSAMOUNT 10
#define LINESAMOUNT 5

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
	std::vector<Line> lines = lgen.giveMeLines(LINESAMOUNT);

	NumberShapeFinder nShapeFinder(lines);
	nShapeFinder.generateProbabilityDistribution();


	// {
	// 	Line({ 282,    0}, {   0,  281}, TOP_TO_LEFT),
	// 	Line({   0,  170}, {1080,  170}, HORIZONTAL ),
	// 	Line({ 494,    0}, {   0,  248}, TOP_TO_LEFT),
	// 	Line({ 535,  920}, {1080,   19}, BOTTOM_TO_RIGHT),
	// 	Line({   0,  644}, {1080,  644}, HORIZONTAL)
	// };

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

	// NumberShapeFinder nShapeFinder(lines);
	// nShapeFinder.lookForNumbers(ATTEMPTSNUMBER);

	// showLines(lines);
	// nShapeFinder.displayResults();

	return EXIT_SUCCESS;
}