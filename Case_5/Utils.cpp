namespace Utils {

	void showLines(std::vector<Line> lines) {

		// Muestra las lineas siguiendo un formato
		std::cout << "Lines: {" << std::endl;
		for (Line line: lines) 
			line.show();
		std::cout << "}\n";
	}

}