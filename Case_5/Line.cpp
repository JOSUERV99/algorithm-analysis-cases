


const int DIAGONAL_LEFT_TO_TOP     = 1;
const int DIAGONAL_LEFT_TO_BOTTOM  = 2;
const int DIAGONAL_TOP_TO_RIGHT    = 3;
const int DIAGONAL_TOP_TO_LEFT     = 4;

class Line {
public:
	int xPos1, yPos1,
		 xPos2, yPos2;

	int xLimit = WIDTH, yLimit = HEIGHT;

	Line(): xPos1(0), yPos1(0), xPos2(0), yPos2(0) {}

	Line(int xLimit, int yLimit, int xPos1, int yPos1, int xPos2, int yPos2):
		xPos1(xPos1), 
		yPos1(yPos1), 
		xPos2(xPos2), 
		yPos2(yPos2), 
		xLimit(xLimit), 
		yLimit(yLimit) {}

	void setFirstPoint(std::pair<int, int> point) {
		xPos1 = point.first;
		yPos1 = point.second;
	}

	void setSecondPoint(std::pair<int, int> point) {
	   xPos2 = point.first;
		yPos2 = point.second;
	}

	bool isHorizontal() {
		return yPos1 != yPos2 && 
				(yPos1 == yLimit && yPos2 == 0 || yPos1 == 0 && yPos2 == yLimit);
	}

	bool isVertical() {
		return xPos1 != xPos2 && 
				(xPos1 == xLimit && xPos2 == 0 || xPos1 == 0 && xPos2 == xLimit);
	}

	bool isDiagonal(int &direction) {

		bool diagonalState = 
			xPos1 > xPos2 && yPos1 != yPos2;
		
		if (diagonalState) {

			if (xPos1 == 0 ) {
				direction = yPos2 < yPos1 ? DIAGONAL_LEFT_TO_TOP: DIAGONAL_LEFT_TO_BOTTOM;
			} else if (yPos1 == 0) {
				direction = xPos1 < xPos2 ? DIAGONAL_TOP_TO_RIGHT: DIAGONAL_TOP_TO_LEFT;
			}

		} else
			direction = -1;

		return diagonalState;
	}

	bool isParallel(Line otherLine) {
		return 
			(yPos2 - yPos1) == (xPos2 - xPos1);
	}

	bool isPerpendicular() {
		return
			xPos1 != xPos2 &&
			yPos1 != yPos2 &&
			(xPos1 == xPos2 && yPos1 == yPos2);
	}

};