
// TODO: start here, don't waste time in calculus, put a mark for every line
// and only create the needed functions

//Direction 
const int 
	HORIZONTAL = 0,
	VERTICAL = 1,
	DIAGONAL = 2;

const int 
	BOTTOM_TO_LEFT  = 2,
	BOTTOM_TO_RIGHT = 3,
	TOP_TO_LEFT     = 4,
	TOP_TO_RIGHT    = 5;

class Line {
public:

	int type;

	int xPos1, yPos1,
		 xPos2, yPos2;

	Line(): xPos1(0), yPos1(0), xPos2(0), yPos2(0) {}

	Line(int xPos1, int yPos1, int xPos2, int yPos2):
		xPos1(xPos1), 
		yPos1(yPos1), 
		xPos2(xPos2), 
		yPos2(yPos2) {}

	Line(std::pair<int, int> initialPoint, std::pair<int, int> endPoint, int type):
		xPos1(initialPoint.first),
		yPos1(initialPoint.second),
		xPos2(endPoint.first),
		yPos2(endPoint.second),
		type(type) {}

	void setFirstPoint(std::pair<int, int> point) {
		xPos1 = point.first;
		yPos1 = point.second;
	}

	void setSecondPoint(std::pair<int, int> point) {
	   xPos2 = point.first;
		yPos2 = point.second;
	}

	bool isDiagonal() {
		return type >= 2;
	}

	bool equals(Line otherLine) {
		return xPos1 == otherLine.xPos1 &&
				 xPos2 == otherLine.xPos2 && 
				 yPos1 == otherLine.yPos1 &&
				 yPos2 == otherLine.xPos2 
				 ||
				 xPos1 == otherLine.xPos2 &&
				 xPos2 == otherLine.xPos1 && 
				 yPos1 == otherLine.yPos2 &&
				 yPos2 == otherLine.xPos1; 
 	}

 	void show() {
 		printf("[[%4d, %4d], [%4d, %4d]],\n", xPos1, yPos1, xPos2, yPos2);
 	}
};