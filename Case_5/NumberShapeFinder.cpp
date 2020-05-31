#define ATTEMPTSNUMBER 10000
#define NUMBERSAMOUNT 10

class NumberShapeFinder {
private:
	float probabilityDistribution[NUMBERSAMOUNT]; // range 0-9
	int approximateAmount[NUMBERSAMOUNT];
	std::vector<Line> lines;

public:
	NumberShapeFinder(std::vector<Line> lines): lines(lines) {
		for (int counter = 0; counter < NUMBERSAMOUNT; counter++)
			probabilityDistribution[counter] = approximateAmount[counter] = 0;
	}

	void lookForNumbers(int attemptsNumber = ATTEMPTSNUMBER) {
		
		std::cout << "Repeating process: " << attemptsNumber << " times" << std::endl;	

		while (attemptsNumber--) {

		}
	}

	bool perceiveNumber(int number, std::vector<Line> candidateLines) {

		// identifying shape of numbers

		switch(number){

			case 0:

			break;
			case 1:

			break;
			case 2:

			break;	
			case 3:

			break;
			case 4:	

			break;
			case 5:

			break;
			case 6:

			break;
			case 7:

			break;
			case 8:

			break;
			case 9:

			break;
			default:
				std::cout << "?" << std::endl;
			break;
		}

		return false;
	}

private:
	void setResults() {

		// TODO: .... 
	
	}
	
};