class WordNode { 
public:

	std::string word;
	int appearances, lastInsertedSentenceIndex, powerCounter, powerIndex;
	std::unordered_map <std::string, int> relations;
	std::vector<WordNode> relatedNodes;

	WordNode(std::string word): word(word){ 
		appearances = powerCounter = 0;
		lastInsertedSentenceIndex = powerIndex = -1;
	}

	bool existRelation( std::string key );
	void processRelation( WordNode& );

	// sobreescritura de operador para stream de salida por pantalla
	friend std::ostream& operator << (std::ostream &o,const WordNode &object) {
		o << "***********************" << std::endl << 
			"Word: [" << object.word << "] " <<std::endl <<
			"Relations: " << object.relations.size() << "\n\t";

		int counter = 0; // para formateo en vista en pantalla
		for (auto const &relation: object.relations) 
			if (relation.second > 0) { 
				o << "{" << relation.first << "," << relation.second << "}, ";
				if (counter != 0 && counter % 4 == 0)
					o << "\n\t";
				counter++;
			}
				
		o << "\nAppearances:" << object.appearances <<
		"\n***********************" << std::endl;
		return o;
	}
};

bool WordNode::existRelation(std::string key) {
	/* 
			Objetivo: verificar si la palabra tiene relacion con este nodo
	------------------------------------------------------------------------------------
	Complejidad obtenida: O(c)
	*/

	if (relations.size() == 0)
		return false;
	return relations.count(key) == 1;
}

void WordNode::processRelation(WordNode& nearWordNode) {
	/* 
			Objetivo: obtener caracter a caracter el contenido del archivo de texto, 
			tomando en cuenta cada palabra para formar una oracion delimitada por punto '.'
	------------------------------------------------------------------------------------
	Complejidad obtenida: O(c)
	*/

	if ( !existRelation(nearWordNode.word) ) { // O(c)
		relatedNodes.push_back(nearWordNode);
		relations.insert( {nearWordNode.word, 1} );
	}
	else 
		relations.at( nearWordNode.word )++;
}