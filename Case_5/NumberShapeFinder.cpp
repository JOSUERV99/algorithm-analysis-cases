#define DEFAULTATTEMPTSNUMBER 10000
#define DEFAULTDISTANCECALCULUSAMOUNT 100

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
	int totalPoints;

	int probabilityDistribution[NUMBERSAMOUNT];

public:
	NumberShapeFinder(std::vector<Line> lines): lines(lines), totalPoints(0) {
		
		thinker = NumberThinker();
		for (int counter = 0; counter < NUMBERSAMOUNT; counter++)
			approximateNumbersAmount[counter] = probabilityDistribution[counter] = 0;

	}

	void generateProbabilityDistribution() {

		adjustPDByLinesDirection();
		adjustPBByDistanceBetweenLines();
		setTotalPoints();

		showDistribution();

	}

	void setTotalPoints() {
		for (int counter = 0; counter < NUMBERSAMOUNT; counter++) {
			totalPoints += probabilityDistribution[counter];
		}
	}

	void showDistribution() {

		float sum = 0;
		for (int counter = 0; counter < NUMBERSAMOUNT; counter++) {

			float currentProbability = (float) probabilityDistribution[ counter ] / (float) totalPoints;
			std::cout << "Number: [ " << counter << " ] : " << currentProbability << std::endl; 
			sum += currentProbability;
		}

		std::cout << "\n\n Prob -> " << sum << std::endl;

	}

	void adjustPBByDistanceBetweenLines( ) {

		int linesAmount = 2; // cantidad de lineas para medir distancias

		for (int counter= 0; counter < DEFAULTDISTANCECALCULUSAMOUNT; counter++) {

			std::vector<Line> choosedLines;

			for (int counter = 0; counter < linesAmount; counter++) {
				choosedLines.push_back( lines[rand() % lines.size()] );
			}

			if ( choosedLines[0].isVertical() && choosedLines[1].isVertical() ||
				choosedLines[1].isVertical() && choosedLines[0].isVertical() ) 
			{
				if ( abs(choosedLines[0].xPos1 - choosedLines[0].xPos2) < 200  ) {
					
					// aumentamos la probabilidad de las lineas que necesitan
					// dos lineas verticales a cierta distancia

					for (int i=0; i<NUMBERSAMOUNT; i++)
						if (i != 1 && i != 7) 
							probabilityDistribution[i]++;
				}
			}
			else if (choosedLines[0].isHorizontal() && choosedLines[1].isHorizontal() ) {

				for (int i=0; i<NUMBERSAMOUNT; i++)
						if (i != 1 && i != 7) 
							probabilityDistribution[i]++;
			}
			else if ( choosedLines[0].isDiagonal() && choosedLines[1].isHorizontal() ||
				choosedLines[1].isDiagonal() && choosedLines[0].isHorizontal()) {

				if ( abs(choosedLines[0].yPos1 - choosedLines[0].yPos2) < 300  ) {
					probabilityDistribution[7];
				}

			}
			else if ( choosedLines[0].isDiagonal() && choosedLines[1].isVertical() ||
				choosedLines[1].isDiagonal() && choosedLines[0].isVertical()) {

				if ( abs(choosedLines[0].xPos1 - choosedLines[0].xPos2) < 300  ) {
					probabilityDistribution[1]++;
				}
			}
		}
	}

	void adjustPDByLinesDirection() {
		for (Line line: lines) {
			if ( line.isDiagonal() && line.type == BOTTOM_TO_RIGHT ) {				
				// aumentamos la probabilidad de los numeros que tienen diagonales
				probabilityDistribution[7]++;
				probabilityDistribution[1]++;
			} 
			else if ( line.isVertical() ) {
				// aumentamos la probabilidad de los numeros que tienen verticales
				for (int i=0; i<NUMBERSAMOUNT; i++)
					if (i != 7) // unico numero que no tiene verticales
						probabilityDistribution[i]++;

			} else if ( line.isHorizontal() ) {
				// aumentamos la probabilidad de los numeros que tienen horizontales
				for (int i=0; i<NUMBERSAMOUNT; i++)
					if (i != 1) // unico numero que no tiene verticales
						probabilityDistribution[i]++;
			}
		}
	}

	void lookForNumbers(int attemptsNumber = DEFAULTATTEMPTSNUMBER) {
		
		std::cout << "Repeating process: " << attemptsNumber << " times" << std::endl;	
		std::unordered_map<int, std::unordered_set<std::string>> lineRegistry;

		while (attemptsNumber--) {

			// 1. Elegimos un numero candidato a reconocer
			int candidateToRecognize = chooseNumber( rand() );

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

	int chooseNumber(float randomNumber) {
		float accrued = 0;

		for (int counter = 0; counter < NUMBERSAMOUNT; counter++) {
			if ( accrued + probabilityDistribution[counter] < randomNumber) {
				return counter;
			} 
			else {
				accrued += probabilityDistribution[counter];
			}
		}

		return -1;
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