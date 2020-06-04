#define DEFAULTATTEMPTSNUMBER 10000
#define DEFAULTDISTANCECALCULUSAMOUNT 100

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

	int probabilityDistribution[NUMBERSAMOUNT];  // registra la cantidad de puntos de posible aparicion 
																// segun el set de lineas dadas

public:
	// constructor
	NumberShapeFinder(std::vector<Line> lines): lines(lines), totalPoints(0) {
		
		thinker = NumberThinker();
		for (int counter = 0; counter < NUMBERSAMOUNT; counter++)
			approximateNumbersAmount[counter] = probabilityDistribution[counter] = 0;

	}

	void generateProbabilityDistribution() {

		/* 
			Basada en la distribucion de las lineas segun la distancia entre ellas y la direccion que toman
			busca generar una distribucion de probabilidades para ser usada como generador a la hora de aproximar 
			la cantidad de numeros y cual porcentaje de posible aparicion tiene en el set de lineas dado

			Complejidad: O(c)
		*/

		adjustPDByLinesDirection();
		
		adjustPBByDistanceBetweenLines();
		
		setTotalPoints();
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

		for (int counter = 0; counter < NUMBERSAMOUNT; counter++) {
			totalPoints += probabilityDistribution[counter];
		}
	}

	void showDistribution() {

		/* 
			#Util : mostrar la distribucion de probabilidad generada

			Complejidad: O(c) siendo c igual a NUMBERSAMOUNT
		*/

		float sum = 0;
		for (int counter = 0; counter < NUMBERSAMOUNT; counter++) {

			float currentProbability = (float) probabilityDistribution[ counter ] / (float) totalPoints;
			std::cout << "Number: [ " << counter << " ] : " << currentProbability << std::endl; 
			sum += currentProbability;
		}

		std::cout << "\n\n Prob -> " << sum << std::endl;

	}

	void adjustPBByDistanceBetweenLines( ) {

		/* 
			Aumenta valores en el arreglo de puntos por numero tomando en
			cuenta la distancia entre las lineas

			Complejidad: O(c) siendo c igual a DEFAULTDISTANCECALCULUSAMOUNT
		*/

		int linesAmount = 2; // cantidad de lineas para medir distancias

		for (int counter= 0; counter < DEFAULTDISTANCECALCULUSAMOUNT; counter++) {

			std::vector<Line> choosedLines;

			for (int counter = 0; counter < linesAmount; counter++) {
				choosedLines.push_back( lines[rand() % lines.size()] );
			}

			if ( choosedLines[0].isVertical() && choosedLines[1].isVertical() ||
				choosedLines[1].isVertical() && choosedLines[0].isVertical() ) 
			{
				if ( abs(choosedLines[0].xPos1 - choosedLines[0].xPos2) < 200  ) {
					
					// aumentamos la probabilidad de las lineas que necesitan
					// dos lineas verticales a cierta distancia

					for (int i=0; i<NUMBERSAMOUNT; i++)
						if (i != 1 && i != 7) 
							probabilityDistribution[i]++;
				}
			}
			else if (choosedLines[0].isHorizontal() && choosedLines[1].isHorizontal() ) {

				// aumentamos la probabilidad de las lineas que necesitan
				// dos lineas horizontales a cierta distancia

				for (int i=0; i<NUMBERSAMOUNT; i++)
						if (i != 1 && i != 7) 
							probabilityDistribution[i]++;
			}
			else if ( choosedLines[0].isDiagonal() && choosedLines[1].isHorizontal() ||
				choosedLines[1].isDiagonal() && choosedLines[0].isHorizontal()) {

				// aumentamos la probabilidad de las lineas que necesitan
				// una horizontal y diagonal a cierta distancia

				if ( abs(choosedLines[0].yPos1 - choosedLines[0].yPos2) < 300  ) {
					probabilityDistribution[7];
				}

			}
			else if ( choosedLines[0].isDiagonal() && choosedLines[1].isVertical() ||
				choosedLines[1].isDiagonal() && choosedLines[0].isVertical()) {

				// aumentamos la probabilidad de las lineas que necesitan
				// una vertical y diagonal a cierta distancia

				if ( abs(choosedLines[0].xPos1 - choosedLines[0].xPos2) < 300  ) {
					probabilityDistribution[1]++;
				}
			}
		}
	}

	void adjustPDByLinesDirection() {

		/* 
			Aumenta valores en el arreglo de puntos por numero tomando en
			cuenta la direccion de las lineas

			Complejidad: O(c) siendo c igual a DEFAULTDISTANCECALCULUSAMOUNT
		*/

		for (Line line: lines) {
			if ( line.isDiagonal() && line.type == BOTTOM_TO_RIGHT ) {				
				// aumentamos la probabilidad de los numeros que tienen diagonales
				probabilityDistribution[7]++;
				probabilityDistribution[1]++;
			} 
			else if ( line.isVertical() ) {
				// aumentamos la probabilidad de los numeros que tienen verticales
				for (int i=0; i<NUMBERSAMOUNT; i++)
					if (i != 7) // unico numero que no tiene verticales
						probabilityDistribution[i]++;

			} else if ( line.isHorizontal() ) {
				// aumentamos la probabilidad de los numeros que tienen horizontales
				for (int i=0; i<NUMBERSAMOUNT; i++)
					if (i != 1) // unico numero que no tiene verticales
						probabilityDistribution[i]++;
			}
		}
	}

	void lookForNumbers(int attemptsNumber = DEFAULTATTEMPTSNUMBER) {

		/* 
			Aproxima la cantidad de numeros encontrados en las lineas 
			basandose en un random que usa la distribucion de probabilidad 

			Complejidad: O(c) siendo c igual a attemptsNumber
		*/
		
		std::cout << "Repeating process: " << attemptsNumber << " times" << std::endl;	
		std::unordered_map<int, std::unordered_set<std::string>> lineRegistry;

		while (attemptsNumber--) {

			// 1. Elegimos un numero candidato a reconocer
			int candidateToRecognize = chooseNumber( randomFloat() );

			// 2. Elegimos un sample o muestra para probar
			std::vector<Line> randomSelectedLines;
			std::vector<int> linesIndexes;

			int selectCounter = 0;

			while (selectCounter++ != NEEDEDLINES[candidateToRecognize]) {
	
				int lineSelectedIndex = rand() % lines.size();
				randomSelectedLines.push_back( lines[ lineSelectedIndex ] );	
				linesIndexes.push_back(lineSelectedIndex);

			}

			// 3. Checamos que cumpla con las condicion de forma del numero en 2D
			bool recognized = thinker.perceiveNumber(candidateToRecognize, randomSelectedLines);

			// 4. Si, se reconoce como un numero se aumentan las apariciones, en el caso de usar 
			// al menos una linea diferente
			std::string lineKey = getKey(candidateToRecognize, linesIndexes); 

			if (recognized && lineRegistry[ candidateToRecognize ].count( lineKey ) == 0 ) {
				
				approximateNumbersAmount[ candidateToRecognize ]++;
				lineRegistry[ candidateToRecognize ].insert( lineKey );
			}
		}
	}

	int chooseNumber(float randomNumber) {

		/* 
			Tomando en cuenta el valor random generado, toma en cuenta un valor acumulado 
			de la distribucion de probabilidad para saber cual sera el numero a probar

			Complejidad: O(c) siendo c igual a NUMBERSAMOUNT
		*/

		float accrued = 0;

		for (int counter = 0; counter < NUMBERSAMOUNT; counter++) {

			float currentProbability = getPossibility(counter);
			
			if ( accrued + currentProbability > randomNumber) 
				return counter;
			else 
				accrued += currentProbability;
			
		}

		return -1;
	}

	std::string getKey(int n, std::vector<int> linesIndexes) {

		/* 
			#Util: para registrar la cantidad de numeros generados, toma en cuenta 
			los indices de las lineas generadas para que de forma aproximada sepa distinguir
			si un set de lineas ya fue tomado en cuenta para un numero

			Complejidad: O(c) siendo c igual a NEEDEDLINES *ver constante arriba*
		*/

		std::string key = "";

		for (int counter = 0; counter < NEEDEDLINES[n]; counter++) 
			key += linesIndexes[counter];
		
		return key;
	}

	float getPossibility(int n) {
		/*
			Retorna el porcentaje correspondiente segun el valor n dado, usando la distribucion de
			probabilidad

			Complejidad: O(c)	
		*/

		return (float) probabilityDistribution[n] / (float) totalPoints;
	}

	void displayResults() {

		/* 
			#Util: desplega los resultados de cantidades aproximadas despues de haber
			ejecutado *lookForNumbers*

			Complejidad: O(c) siendo c igual a NEEDEDLINES *ver constante arriba*
		*/

		std::cout << "Approximated Amount finded " << std::endl;
		for (int counter = 0; counter < NUMBERSAMOUNT; counter++)
			printf("(%1.3f%) -> %d : %d appearances approximately \n", getPossibility(counter), counter, approximateNumbersAmount[counter]);
	}
	
};