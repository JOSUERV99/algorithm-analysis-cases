
namespace Utils {

	/*
		Funciones para visualizacion de las consultas y resultados obtenidos por el grafo de palabras
	*/

	void show(std::vector<std::vector<WordNode>> groups, std::string theWord, int requestedGroups){
		
		// Complejidad algoritmica: O(n) siendo n la cantidad de nodos de palabra distribuidas en los grupos

		std::cout << "######################################################################" << std::endl;
		// encabezado
		std::cout << "[" << theWord << "]\nRequested Groups [" << requestedGroups << 
			"] => " << groups.size() << " generated" << std::endl;

		int groupCounter = 0;
		for (auto const &wordGroup : groups) {
			std::cout << "===> Group #" << (++groupCounter) << std::endl;
			
			for (auto const &word: wordGroup) 
				std::cout << "[" <<word.word << "]"<< std::endl;
		
			std::cout << "===================================" << std::endl;
		}

		std::cout << "######################################################################" << std::endl;
	}

	void show(std::vector<WordNode> powerWords) {

		// Complejidad algoritmica: O(n) siendo n la cantidad de nodos de palabra de la lista

		std::cout << "######################################################################\n" << std::endl;
		// encabezado
		std::cout << "(" << powerWords.size() << 
			") PowerWords: \n" << std::endl;

		// mostrando nodos de las palabras
		for (auto const &word: powerWords) 
			std::cout << word << std::endl;
		
		std::cout << "######################################################################" << std::endl;
	}

	void show(std::vector<WordNode> dominatedWords, std::string word) {

		// Complejidad algoritmica: O(n) siendo n la cantidad de nodos de palabra de la lista

		std::cout << "######################################################################" << std::endl;
		// encabezado
		std::cout << "(" << word << ") tiene bajo su poder: " << std::endl;

		// mostrando nodos de las palabras
		for (auto const &word: dominatedWords) 
			std::cout << word.word << ": " << word.powerCounter << std::endl;
		
		std::cout << "######################################################################" << std::endl;
	}

}