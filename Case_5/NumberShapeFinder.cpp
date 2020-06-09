
#define DEFAULTATTEMPTSNUMBER 10000
#define DIRECTIONMODES 3

// minimo de lineas necesarias para poder
// representar un numero entre 0 y 10 en 2D
const int NEEDEDLINES[] = {
	4, // -> 0
	2, // -> 1
	3, // -> 2
	4, // -> 3
	5, // -> 4
	5, // -> 5
	6, // -> 6
	2, // -> 7
	5, // -> 8
	4, // -> 9
};

class NumberShapeFinder {
private:

	// atributos
	int approximateNumbersAmount[NUMBERSAMOUNT]; // registra la cantidad de numeros aproximados encontrados
	std::vector<Line> lines; 							// contiene las lineas generadas por LineGenerator 
	NumberThinker thinker;								// se encarga de tomar en cuenta la formas absolutas de un numero
	int totalPoints;										// cantidad de puntos totales (Distribucion de probabilidad)

	int numbersProbDistribution[NUMBERSAMOUNT];    // registra la cantidad de puntos de posible aparicion 
																  // segun el set de lineas dadas
	int directionProbDistribution[DIRECTIONMODES]; // almacena la distribucion de las lineas

public:
	// constructor
	NumberShapeFinder(std::vector<Line> lines): lines(lines), totalPoints(0) {
		
		thinker = NumberThinker();
		for (int counter = 0; counter < NUMBERSAMOUNT; counter++)
			approximateNumbersAmount[counter] = numbersProbDistribution[counter] = 0;

		for (int counter=0;  
				counter < DIRECTIONMODES; 
				directionProbDistribution[counter] = 0, 
				counter++);

	}

	void generateProbabilityDistribution() {

		/* 
			Basada en la distribucion de las lineas segun la distancia entre ellas y la direccion que toman
			busca generar una distribucion de probabilidades para ser usada como generador a la hora de aproximar 
			la cantidad de numeros y cual porcentaje de posible aparicion tiene en el set de lineas dado

			Complejidad: O(c)
		*/

		adjustPDByLinesDirection();
		setTotalPoints();

		std::sort( 
			lines.begin(), 
			lines.end(), 
			[&] (const Line& l1, const Line& l2) {
				return l1.type < l2.type;
			} 
		);

		Utils::showLines(lines);

	}

	float randomFloat() {
		
		/* 
			Retorna un numero random entre 0 y 1 
			Complejidad: O(c)
		*/

		return ( (float) rand() ) / (float) RAND_MAX;
	}

	void setTotalPoints() {

		/* 
			Segun los puntos acumulados de encontrar los numeros, suma estos para posteriores calculos de
			para la distribucion de probabilidad a la hora de guiar al algoritmo

			Complejidad: O(c) siendo c igual a NUMBERSAMOUNT
		*/

		for (int counter = 0; counter < NUMBERSAMOUNT; counter++) 
			totalPoints += numbersProbDistribution[counter];

	}

	void showDistribution() {

		/* 
			#Util : mostrar la distribucion de probabilidad generada

			Complejidad: O(c) siendo c igual a NUMBERSAMOUNT
		*/
		
		for (int counter = 0; counter < DIRECTIONMODES; counter++) {

			float currentProbability = (float) directionProbDistribution[ counter ] / (float) lines.size();
			std::cout << "Direccion: [ " << counter << " ] : " << currentProbability << std::endl; 
		}

		for (int counter = 0; counter < NUMBERSAMOUNT; counter++) {

			float currentProbability = (float) numbersProbDistribution[ counter ] / (float) totalPoints;
			std::cout << "Number: [ " << counter << " ] : " << currentProbability << std::endl; 
		}

	}

	void adjustPDByLinesDirection() {

		/* 
			Aumenta valores en el arreglo de puntos por numero tomando en
			cuenta la direccion de las lineas

			Complejidad: O(c) siendo c igual a DEFAULTDISTANCECALCULUSAMOUNT
		*/

		for (Line line: lines) {

			if ( line.isDiagonal() ) {

				directionProbDistribution[DIAGONAL]++;

					// aumentamos la probabilidad de los numeros que tienen diagonales
					numbersProbDistribution[7]++;
					numbersProbDistribution[1]++;
			} 
			else if ( line.isVertical() ) {

				directionProbDistribution[VERTICAL]++;

				// aumentamos la probabilidad de los numeros que tienen verticales
				for (int i=0; i<NUMBERSAMOUNT; i++)
					if (i != 7) // unicos numeros que no tienen verticales
						numbersProbDistribution[i]++;
			
			} else {

				directionProbDistribution[HORIZONTAL]++;

				// aumentamos la probabilidad de los numeros que tienen horizontales
				for (int i=0; i<NUMBERSAMOUNT; i++)
					if (i != 1) // unico numero que no tiene verticales
						numbersProbDistribution[i]++;
			}
		}
	}

	void lookForNumbers(int attemptsNumber = DEFAULTATTEMPTSNUMBER) {

		/* 
			Aproxima la cantidad de numeros encontrados en las lineas 
			basandose en un random que usa la distribucion de probabilidad 

			Complejidad: O(c) siendo c igual a attemptsNumber
		*/
			
		std::unordered_map<int, std::unordered_set<std::string>> lineRegistry;

		while (attemptsNumber--) {

			// 1. Elegimos un numero candidato a reconocer en base a la distribucion
			int candidateToRecognize = 
				chooseBetweenDistribution ( randomFloat(), numbersProbDistribution, totalPoints, NUMBERSAMOUNT );

			// 2. Elegimos un sample o muestra para probar
			std::vector<Line> selectedLines;
			std::vector<int>  linesIndexes;

			int selectCounter = 0;

			while ( selectCounter++ != NEEDEDLINES[candidateToRecognize] ) {
				
				int randomType = 
					chooseBetweenDistribution ( randomFloat(), directionProbDistribution, lines.size(), DIRECTIONMODES );

				// elegir linea segun el tipo elegido
				int accrued = 0;
				for (int counter = 0; counter < DIRECTIONMODES && counter != randomType; counter++) 
					accrued += directionProbDistribution[counter];
				
				int lineIndex = accrued + rand() % directionProbDistribution[ randomType ];

				selectedLines.push_back( lines[ lineIndex ] );
				linesIndexes .push_back(      lineIndex     );

			}

			// 3. Checamos que cumpla con las condicion de forma del numero en 2D
			bool recognized = thinker.perceiveNumber(candidateToRecognize, selectedLines);

			// 4. Si, se reconoce como un numero se aumentan las apariciones, en el caso de usar 
			// al menos una linea diferente
			auto lineKey = getKey(linesIndexes); 

			if (recognized && lineRegistry[ candidateToRecognize ].count( lineKey ) == 0 ) {
				
				approximateNumbersAmount[ candidateToRecognize ]++;
				lineRegistry[ candidateToRecognize ].insert( lineKey );
			}
		}
	}

	int chooseBetweenDistribution(float randomNumber, int* distribution, int totalDistribution, int limit) {

		/* 
			Tomando en cuenta el valor random generado, toma en cuenta un valor acumulado 
			de la distribucion de probabilidad para saber cual sera el numero a probar

			Complejidad: O(c) siendo c igual a NUMBERSAMOUNT
		*/

		float accrued = 0;

		for (int counter = 0; counter < limit; counter++) {

			float currentProbability = 
				(float) distribution[ counter ] / (float) totalDistribution;

			if ( accrued + currentProbability > randomNumber) 
				return counter;
			else 
				accrued += currentProbability;
			
		}

		return 0;
	}

	std::string getKey(std::vector<int> linesIndexes) {

		/* 
			#Util: para registrar la cantidad de numeros generados, toma en cuenta 
			los indices de las lineas generadas para que de forma aproximada sepa distinguir
			si un set de lineas ya fue tomado en cuenta para un numero

			Complejidad: O(c) siendo c igual a NEEDEDLINES *ver constante arriba*
		*/

		std::string key;

		for (int value: linesIndexes)
			key += value;

		return key;
	}

	void displayResults() {

		/* 
			#Util: desplega los resultados de cantidades aproximadas despues de haber
			ejecutado *lookForNumbers*

			Complejidad: O(c) siendo c igual a NEEDEDLINES *ver constante arriba*
		*/

		std::cout << "Approximated Amount finded " << std::endl;
		for (int counter = 0; counter < NUMBERSAMOUNT; counter++)
			printf("(%1.3f%) -> %d : %d appearances approximately \n", numbersProbDistribution[counter] / (float) totalPoints, counter, approximateNumbersAmount[counter]);
	}
	
};