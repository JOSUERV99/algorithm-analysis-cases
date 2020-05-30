#define ATTEMPTSNUMBER 10000
#define NUMBERSAMOUNT 10

class NumberShapeFinder {
private:
	float probabilityDistribution[NUMBERSAMOUNT]; // range 0-9
	int approximateAmount[NUMBERSAMOUNT];

public:
	NumberShapeFinder() {
		for (int counter = 0; counter < NUMBERSAMOUNT; counter++)
			probabilityDistribution[counter] = approximateAmount[counter] = 0;
	}

	void lookForNumbers(int attemptsNumber = ATTEMPTSNUMBER) {

	}

	void adjustDistribution(float currentDistribution[NUMBERSAMOUNT]) {

	}

	void shuffle(std::vector<Line> lines) {

	}
};