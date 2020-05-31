#define DefaultAttemptsNumber 10000

class NumberShapeFinder {
private:
	float probabilityDistribution[NumbersAmount]; // range 0-9
	int approximateNumbersAmount[NumbersAmount];
	std::vector<Line> lines;
	NumberThinker thinker;

public:
	NumberShapeFinder(std::vector<Line> lines): lines(lines) {
		
		thinker = NumberThinker();
		for (int counter = 0; counter < NumbersAmount; counter++)
			probabilityDistribution[counter] = approximateNumbersAmount[counter] = 0;
	}

	void lookForNumbers(int attemptsNumber = DefaultAttemptsNumber) {
		
		std::cout << "Repeating process: " << attemptsNumber << " times" << std::endl;	

		while (attemptsNumber--) {

			// 1. Choose some lines to proove
			std::vector<Line> randomSelectedLines;

			int selectCounter = 0;
			while (selectCounter++ != CandidateLinesAmount)
				randomSelectedLines.push_back( lines[ rand() % lines.size() ] );

			// // 2. Choose a random number between 0-9
			// int candidateToRecognize = rand() % NumbersAmount;

			// 3. Try to recognize any number
			for (int counter = 0; counter < NumbersAmount; counter++) {
				int candidateToRecognize = counter;`
				bool recognized = thinker.perceiveNumber(candidateToRecognize, randomSelectedLines);

				// 4. If we recognize something, register it
				if (recognized) 
					approximateNumbersAmount[candidateToRecognize]++;
			}
		}
	}

	void displayResults() {

		std::cout << "Approximated Amount finded " << std::endl;
		for (int counter = 0; counter < NumbersAmount; counter++)
			std::cout << counter << " -> " << approximateNumbersAmount[counter] << std::endl;
	
	}
	
};