namespace Utils {

	void showLines(std::vector<Line> lines) {
		std::cout << "Lines: {" << std::endl;
		for (Line l: lines) 
			printf("{ [%4d, %4d], [%4d, %4d] }\n", l[0].first, l[0].second, l[1].first, l[1].second );
		std::cout << "}";
	}

	void showResults(std::string message) {


	}

}