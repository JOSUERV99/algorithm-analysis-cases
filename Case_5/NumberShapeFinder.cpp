
#define DEFAULTATTEMPTSNUMBER 10000
#define DIRECTIONMODES 4

// minimo de lineas necesarias para poder
// representar un numero entre 0 y 10 en 2D
const int NEEDEDLINES[] = {
	4, // -> 0
	2, // -> 1
	3, // -> 2
	4, // -> 3
	5, // -> 4
	5, // -> 5
	5, // -> 6
	2, // -> 7
	5, // -> 8
	4, // -> 9
};

const int SHAPE_EXIST = 0, SHAPE_NOT_EXIST =  1;
const int USELESS_LINE_TYPE = 3;

class NumberShapeFinder {
private:

	// atributos
	int approximateNumbersAmount[NUMBERSAMOUNT]; // registra la cantidad de numeros aproximados encontrados
	std::vector<Line> lines; 							// contiene las lineas generadas por LineGenerator 
	int totalPoints, existPoints; 					// cantidad de puntos totales (Distribucion de probabilidad)

	int numbersProbDistribution[NUMBERSAMOUNT];    // registra la cantidad de puntos de posible aparicion 
																  // segun el set de lineas dadas
	int directionProbDistribution[DIRECTIONMODES]; // almacena la distribucion de las lineas

	int numberShapeProbDistribution[2] = {0,0}; // determinar la existencia de un numero

public:
	// constructor
	NumberShapeFinder(std::vector<Line> lines): lines(lines), totalPoints(0) {

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

			Complejidad: O(n) siendo n la cantidad de lineas
		*/

		adjustProbabilityDistribution();
		setTotalPoints();

		Utils::showLines(lines);
	}

	float randomNumber() {
		
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

		existPoints = totalPoints;

	}

	void adjustProbabilityDistribution() {

		/* 
			Aumenta valores en el arreglo de puntos por numero tomando en
			cuenta la direccion de las lineas

			Complejidad: O(c) siendo c igual a DEFAULTDISTANCECALCULUSAMOUNT
		*/

		for (Line line: lines) {

			if ( line.type == BOTTOM_TO_RIGHT || line.type == TOP_TO_LEFT) {

				directionProbDistribution[DIAGONAL]++;

					// aumentamos la probabilidad de los numeros que tienen diagonales
					numbersProbDistribution[7]++;
					numbersProbDistribution[1]++;
					numbersProbDistribution[6]++;
					numbersProbDistribution[4]++;
					numbersProbDistribution[2]++;

					numberShapeProbDistribution[SHAPE_EXIST]++; 
			} 
			else if ( line.isVertical() ) {

				directionProbDistribution[VERTICAL]++;

				// aumentamos la probabilidad de los numeros que tienen verticales
				for (int i=0; i<NUMBERSAMOUNT; i++)
					if (i != 7) // unicos numeros que no tienen verticales
						numbersProbDistribution[i]++;

				numberShapeProbDistribution[SHAPE_EXIST]++;
			
			} else if ( line.isHorizontal() ) {

				directionProbDistribution[HORIZONTAL]++;

				// aumentamos la probabilidad de los numeros que tienen horizontales
				for (int i=0; i<NUMBERSAMOUNT; i++) {
					if (i != 1) // unico numero que no tiene verticales
						numbersProbDistribution[i] += 2;
				}

				numberShapeProbDistribution[SHAPE_EXIST]++;

			} else {

				numberShapeProbDistribution[SHAPE_NOT_EXIST]++;
				
				directionProbDistribution[ USELESS_LINE_TYPE ]++;
			}

		}
	}

	void lookForNumbers(int attemptsNumber = DEFAULTATTEMPTSNUMBER) {

		/*
			Objetivo: aproximar la cantidad de numeros formados en la visualizacion 2d de las lineas dadas

			Puntos a tomar en cuenta:

			1. Ya que cada numero debe tener al menos dos lineas(segun la forma que he elegido) debe existir
			como maximo, siendo n la cantidad de lineas, podrian existir n/2 formas de numeros, tomando en cuenta 
			el caso donde se formarian solo numeros que necesitan la menor cantidad de lineas (en mi caso 1 y 7)

			2. Se ha de llevar un registro para poder aproximar la cantidad para posteriormente
			ajustar el margen de error, y brindar una respuesta mas acertada

			3. He tomado en cuenta dos distribucion de probabilidad:
				- Dist. con respecto a que tipo de lineas fueron generadas
				- Existencia o no de la forma de un numero 
		*/

		// registro para posteriormente obtener la media de los resultados
		std::unordered_map< int, std::vector<int> > appearancesMap;

		// Calculamos la cantidad maxima de numeros que se podrian formar
		int maxShapeAmount = lines.size() / 2; // ver punto 1, arriba

		int attemptCounter = 0;
		while ( attemptCounter++ < attemptsNumber) {

			int counter = 0;
			while (counter < maxShapeAmount) {

				// 1. Mediante un random se decide si hay o no la forma de un numero
				int rNumber = chooseBetweenDistribution( randomNumber() , numberShapeProbDistribution, lines.size(), 2);
				std::cout << rNumber << std::endl;

				bool numberShapeExists = rNumber == 0;

				// 2. Mediante un random guiado por la distr. de cuales numeros se podrian formar
				// segun la direccion de las lineas
				if ( numberShapeExists ) {

					int numberChoosed = 
						chooseBetweenDistribution( randomNumber(), numbersProbDistribution, totalPoints, NUMBERSAMOUNT);

					// restamos la cantidad de lineas usadas por el numero elegido
					maxShapeAmount -= NEEDEDLINES[ numberChoosed ];
					
					// contamos la aparicion
					approximateNumbersAmount[ numberChoosed ]++;

				}

				counter++;
			}

			// registramos la cantidad de lineas encontradas para luego mejorar la aproximacion del resultado
			for (int counter = 0; counter < NUMBERSAMOUNT; counter++) {

				if (approximateNumbersAmount[counter] != 0) {
					appearancesMap[ counter ].push_back( approximateNumbersAmount[ counter ]  );
					approximateNumbersAmount[ counter ] = 0;
				}
			}

		}

		// encontramos la media de los valores encontrados
		findFinalResult( appearancesMap );

	}

	void findFinalResult(std::unordered_map< int, std::vector<int> > appearancesMap) {

 		/*
			Objetivo: en base a la cantidad de numeros generadas tomar la media de los resultados
			para reducir el margen de error

 		*/

		int counter = 0;

		for ( auto iterator = appearancesMap.begin(); iterator != appearancesMap.end(); iterator++ ) {

			std::vector<int> numbersQuantity = (*iterator).second;

			int median = 0;

			if (numbersQuantity.size() != 0 ) {

				std::sort(  
					numbersQuantity.begin(), 
					numbersQuantity.end()
				);

				if (numbersQuantity.size() % 2 == 0 && numbersQuantity.size() > 2) {
					median = 
						( numbersQuantity[ numbersQuantity.size() / 2 ] + 
							numbersQuantity[ numbersQuantity.size() / 2 + 1] ) / 2;
				} 
				else if ( numbersQuantity.size() % 2 != 0 && numbersQuantity.size() > 2 ){
					median = numbersQuantity[ numbersQuantity.size()/2 ];
				} 
				else {
					median = numbersQuantity[0];
				}
			}

			approximateNumbersAmount[ counter ] = median;
			counter++; 
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

		return limit - 1;
	}

	void displayResults() {

		/* 
			#Util: desplega los resultados de cantidades aproximadas despues de haber
			ejecutado *lookForNumbers*

			Complejidad: O(c) siendo c igual a NEEDEDLINES *ver constante arriba*
		*/

		std::cout << "\nApproximated Amount finded " << std::endl;

		for (int counter = 0; counter < NUMBERSAMOUNT; counter++)
			printf("(%1.3f%) -> %d : %d appearances approximately \n", 
				numbersProbDistribution[ counter ] / (float) totalPoints, 
				counter, 
				approximateNumbersAmount[ counter ]
			);
	}
	

		void showDistribution() {

		/* 
			#Util : mostrar la distribucion de probabilidad generada

			Complejidad: O(c) siendo c igual a NUMBERSAMOUNT
		*/

		std::cout << std::endl;
		float sum = 0;
		for (int counter = 0; counter < DIRECTIONMODES; counter++) {

			float currentProbability = (float) directionProbDistribution[ counter ] / (float) lines.size();
			std::cout << "Direccion: [ " << counter << " ] : " << currentProbability << std::endl; 
			sum += currentProbability;
		}

		std::cout << "P(" << sum <<")" << std::endl;
		sum = 0;
		std::cout << std::endl;

		for (int counter = 0; counter < NUMBERSAMOUNT; counter++) {

			float currentProbability = (float) numbersProbDistribution[ counter ] / (float) totalPoints;
			std::cout << "Number: [ " << counter << " ] : " << currentProbability << std::endl; 
			sum += currentProbability;
		}

		std::cout << "P(" << sum <<")" << std::endl;

		sum = 0;
		std::cout << std::endl;

		for (int counter = 0; counter < 2; counter++) {

			float currentProbability = (float) numberShapeProbDistribution[ counter ] / (float) lines.size();
			std::cout << "Shape : [ " << (counter == 0 ? "EXISTS" : "NOT EXIST") << " ] : " << currentProbability << std::endl; 
			sum += currentProbability;
		}

		std::cout << "P(" << sum <<")" << std::endl;
		sum = 0;
		std::cout << std::endl;

	}

};