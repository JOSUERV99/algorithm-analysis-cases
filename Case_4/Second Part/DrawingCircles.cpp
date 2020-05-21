/*
	Dado el siguiente video 'luces.mp4' que está en el Dropbox, asumiendo
	que son dos colores únicamente, y que se quieren pintar K círculos. 
	Cómo podría usted generar una salida que le permita a un UI
	pintar de la forma más rápida posible dichos puntos o círculos de 
	colores de tal forma que se genera la misma animación del video en un
	ciclo infinito.

	Complejidad esperada: O(n) siendo n la cantidad de puntos
*/

#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<vector>
#include<unordered_map>
#include<utility>

using namespace std;

#define COS_PERIOD 		2*M_PI
#define POINT 				pair<float, float>
#define CIRCLE_STRUCT 	vector<POINT>
#define COLOR 				vector<tuple<int, int, int>>

void show(vector<CIRCLE_STRUCT>);

class CircleGenerator {
private:
	int pointsPerCircle, radius, framesAmount = 0, kCirclesPerGroup, circlesGroups;
	POINT initialPos;
	COLOR colors;
	float distanceRate;
	
public:

	vector<vector< vector<CIRCLE_STRUCT> >> frames;

	CircleGenerator(
		int pointsPerCircle, 
		int radius, 
		int kCirclesPerGroup,
		POINT initialPos,
		COLOR colors,
		float distanceRate
	): 
		pointsPerCircle(pointsPerCircle), 
		radius(radius),
		kCirclesPerGroup(kCirclesPerGroup),
		initialPos(initialPos),
		colors(colors),
		distanceRate(distanceRate),
		circlesGroups(2)
		{}
	
	// funcion principal
	void loadFrames();

	// funciones auxiliares
	CIRCLE_STRUCT moveCircle(CIRCLE_STRUCT lastCircle, float xDistance, float yDistance);
	CIRCLE_STRUCT createCircle( POINT initialPos, int radius);
	vector<CIRCLE_STRUCT> getReescaledCircles( POINT initialPos, int radius);
	void showMeta();

};

void  CircleGenerator::showMeta() {
	/*
		Objetivo: brindar informacion acerca de la salida del programa
	*/

	// data shape
	cout << "Circles Group : " << circlesGroups << endl;
	cout << "Circles amount for group: " << kCirclesPerGroup << endl;
	cout << "Points for every circle : " << pointsPerCircle << endl;
	cout << "Distance Rate : " << distanceRate << endl;
	cout << "Minimus Radius : " << radius << endl;
	cout << "initial Position : " << "(" << initialPos.first << "," << initialPos.second << ")" << endl;
	cout << "Frames amount : " << framesAmount << endl;
	cout << "Data Shape : [ " << frames.size() << ", " << frames[0].size() << ", " << frames[0][0].size() << "]";
}

void CircleGenerator::loadFrames() {

	vector<vector<vector<CIRCLE_STRUCT>>> frames;

	// para simular la posicion inicial de los circulos del video
	/*							|
								o		
								|
	_____________________|____________________________
								|
								|
								o
								|
	*/

	// calculamos la cantidad de frames en base al angulo de corrimiento entre cada 
	// par de puntos entre frame y frame (entre menos distancia, mas cantidad de cuadros)
	framesAmount = M_PI / distanceRate;

	float angle = 0.0f; // determina la nueva posicion de los circulos
	int frameCounter = 0;
	while (frameCounter < framesAmount ) {

		// primer grupo de circulos
		float xmov1 =  abs( cos(angle) ) * radius;
	  	float ymov1 =  sin(   angle    ) * radius;

	  	vector<CIRCLE_STRUCT> movedCircle_FirstGroup = getReescaledCircles( {xmov1, ymov1}, radius );

		// segundo grupo de circulos
	  	float xmov2 = - abs( cos(angle) ) * radius;
	  	float ymov2 = - sin(   angle    ) * radius;

		vector<CIRCLE_STRUCT> movedCircle_SecondGroup = getReescaledCircles( {xmov2, ymov2}, radius );

	  	std::vector<vector<CIRCLE_STRUCT>> newFrame;
	  	newFrame.push_back(movedCircle_FirstGroup );
	  	newFrame.push_back(movedCircle_SecondGroup);

	  	frames.push_back(newFrame);

		angle += distanceRate;
		frameCounter++;
	}	

	this->frames = frames;
}

CIRCLE_STRUCT CircleGenerator::moveCircle(CIRCLE_STRUCT lastCircle, float xDistance, float yDistance) {

	CIRCLE_STRUCT movedCircle;

	for (POINT point : lastCircle) {
		float nextX = point.first + xDistance;
		float nextY = point.second + yDistance;

		movedCircle.push_back( {nextX, nextY} );
	}

	return movedCircle;
}


CIRCLE_STRUCT CircleGenerator::createCircle( POINT initialPos, int radius ) {

	// puntos que conforman el circulo
	CIRCLE_STRUCT circle; 
	
	// para calcular la distancia entre cada punto del circulo 
	float distanceBetweenPoints = COS_PERIOD / pointsPerCircle; 

	// distancia acumulada con limite el periodo de coseno
	float distanceCounter = 0;

	int pointCounter = 0;

	while ( pointCounter++ < pointsPerCircle ) {

		float xPos = cos(distanceCounter) * radius + initialPos.first;
		float yPos = sin(distanceCounter) * radius + initialPos.second;

		circle.push_back( {xPos, yPos} );

		distanceCounter += distanceBetweenPoints;
	}

	return circle;
}

vector<CIRCLE_STRUCT> CircleGenerator::getReescaledCircles( POINT initialPos, int radius) {

	vector<CIRCLE_STRUCT> reescaledCircles;

	int spaceBetweenReescaledCircles = 30;
	int counter = 0;
	while (counter != kCirclesPerGroup ) {
		reescaledCircles.push_back( createCircle(initialPos, radius + (counter)*spaceBetweenReescaledCircles ));
		counter++;
	}

	return reescaledCircles;
}

int main() {	

	int pointsPerCircle = 8;
	int radius = 80;
	int kCirclesPerGroup = 4;
	float distanceRate = 0.1f;
	POINT initialPos = {0,0};
	COLOR colors = { {255, 0, 0}, {10, 230, 10}  }; // (rgb mode)

	CircleGenerator cgen(pointsPerCircle, radius, kCirclesPerGroup, initialPos, colors, distanceRate);
	cgen.loadFrames(); 

	cgen.showMeta();

	return EXIT_SUCCESS;
}


void show(vector< vector<CIRCLE_STRUCT> > frames) {

		for (vector<CIRCLE_STRUCT> circles: frames) {
			cout << "####################################################" << endl;
			for (CIRCLE_STRUCT circle: circles) {
				cout << "[ ";
				for (POINT p : circle)
					cout << "(" << p.first << ", " << p.second << "),";
				cout << "]" << endl;
			}
			cout << "####################################################" << endl;
		}
	
}
