namespace Utils {

	void showLines(std::vector<Line> lines) {
		std::cout << "Lines: {" << std::endl;
		for (Line line: lines) 
			printf("{ [%4d, %4d], [%4d, %4d] }\n", line.xPos1, line.yPos1, line.xPos2, line.yPos2 );
		std::cout << "}";
	}

}