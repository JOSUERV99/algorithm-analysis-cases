namespace Utils {

	void showLines(std::vector<Line> lines) {
		std::cout << "Lines: {" << std::endl;
		for (Line line: lines) 
			line.show();
		std::cout << "}\n";
	}

}