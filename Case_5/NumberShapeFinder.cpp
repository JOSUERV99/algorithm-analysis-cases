#define DEFAULTATTEMPTSNUMBER 10000

// amount of needed lines to create a number (0-9) on 2D
// needed lines to create a sample
const int NEEDEDLINES[] = {
	4, // -> 0
	2, // -> 1
	3, // -> 2
	4, // -> 3
	5, // -> 4
	5, // -> 5
	6, // -> 6
	2, // -> 7
	5, // -> 8
	4, // -> 9
};

class NumberShapeFinder {
private:
	int approximateNumbersAmount[NUMBERSAMOUNT];
	std::vector<Line> lines;
	NumberThinker thinker;

public:
	NumberShapeFinder(std::vector<Line> lines): lines(lines) {
		
		thinker = NumberThinker();
		for (int counter = 0; counter < NUMBERSAMOUNT; counter++)
			approximateNumbersAmount[counter] = 0;

	}

	void lookForNumbers(int attemptsNumber = DEFAULTATTEMPTSNUMBER) {
		
		std::cout << "Repeating process: " << attemptsNumber << " times" << std::endl;	
		std::unordered_map<int, std::unordered_set<std::string>> lineRegistry;

		while (attemptsNumber--) {

			// 1. Elegimos un numero candidato a reconocer
			int candidateToRecognize = rand() % NUMBERSAMOUNT;

			// 2. Elegimos un sample o muestra para probar
			std::vector<Line> randomSelectedLines;
			std::vector<int> linesIndexes;

			int selectCounter = 0;

			while (selectCounter++ != NEEDEDLINES[candidateToRecognize]) {
	
				int lineSelectedIndex = rand() % lines.size();
				randomSelectedLines.push_back( lines[ lineSelectedIndex ] );	
				linesIndexes.push_back(lineSelectedIndex);
			}

			// 3. Checamos que cumpla con las condicion de forma del numero en 2D
			bool recognized = thinker.perceiveNumber(candidateToRecognize, randomSelectedLines);

			// 4. Si, se reconoce como un numero se aumentan las apariciones, en el caso de usar 
			// al menos una linea diferente
			std::string lineKey = getKey(candidateToRecognize, linesIndexes); 

			if (recognized && lineRegistry[ candidateToRecognize ].count( lineKey ) == 0 ) {
				
				approximateNumbersAmount[ candidateToRecognize ]++;
				lineRegistry[ candidateToRecognize ].insert( lineKey );
			}
			
		}
	}

	std::string getKey(int n, std::vector<int> linesIndexes) {

		std::string key = "";

		for (int counter = 0; counter < NEEDEDLINES[n]; counter++) 
			key += linesIndexes[counter];
		
		return key;
	}

	void displayResults() {
		std::cout << "Approximated Amount finded " << std::endl;
		for (int counter = 0; counter < NUMBERSAMOUNT; counter++)
			std::cout << counter << " -> " << approximateNumbersAmount[counter] << std::endl;
	}
	
};