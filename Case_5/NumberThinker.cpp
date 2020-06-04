
class NumberThinker {
public:
	NumberThinker() {}

	bool perceiveNumber(int number, std::vector<Line> candidateLines) {

		/*
			Busca en base a una forma absoluta de un numero, trata de reconocerlo usando
			el set de lineas que obtiene por parametro

			Complejidad: O(c)
		*/

		int firstDistance = 0, secondDistance = 0, thirdDistance = 0;

		switch(number){

			case 0:
			/*  ___
				|	 |
				|___|
			*/

			firstDistance = abs(candidateLines[0].xPos1  - candidateLines[2].xPos1);
			secondDistance = abs(candidateLines[1].yPos1 - candidateLines[3].xPos1);

			return 
				candidateLines[0].type == VERTICAL   && candidateLines[2].type == VERTICAL &&
				candidateLines[1].type == HORIZONTAL && candidateLines[3].type == HORIZONTAL &&
				firstDistance < secondDistance;

			break;
			case 1:
				/*
				  /|
					|
					|
				*/

			firstDistance = abs(candidateLines[1].xPos2 - candidateLines[1].xPos1);

			return 
				  candidateLines[0].type == VERTICAL && candidateLines[1].type == BOTTOM_TO_RIGHT &&
				  firstDistance < 150;
		
			break;
			case 2:
				/*
				  __
				  __|
				 |__	 
				*/

			firstDistance  = abs(candidateLines[0].xPos1 - candidateLines[1].xPos1); // VERTICAL DISTANCE
			secondDistance = abs(candidateLines[2].yPos1 - candidateLines[3].yPos1); // HORIZONTAL DISTANCE (CENTER, TOP)
			thirdDistance  = abs(candidateLines[2].yPos1 - candidateLines[4].yPos1); // HORIZONTAL DISTANCE (CENTER, BOTTOM)

			return candidateLines[0].type == VERTICAL && candidateLines[1].type == VERTICAL &&
					 candidateLines[2].type == HORIZONTAL &&  candidateLines[3].type == HORIZONTAL &&
					 candidateLines[4].type == HORIZONTAL && abs(firstDistance - secondDistance) < 300 &&
					 abs(secondDistance -  thirdDistance) < 300;

			break;	
			case 3:
			/*
				 __
				 __|
				 __|
				
			*/

			firstDistance   = abs(candidateLines[2].yPos1 - candidateLines[3].yPos1); // HORIZONTAL DISTANCE (CENTER, TOP)
			secondDistance  = abs(candidateLines[2].yPos1 - candidateLines[4].yPos1); // HORIZONTAL DISTANCE (CENTER, BOTTOM)

			return candidateLines[0].type == VERTICAL && candidateLines[1].type == VERTICAL &&
					 candidateLines[2].type == HORIZONTAL &&  candidateLines[3].type == HORIZONTAL &&
					 candidateLines[4].type == HORIZONTAL && abs(firstDistance - secondDistance) < 300;

			break;
			case 4:	
			/*  
				 /|   
				/_|_   	
				  |	
			*/

			firstDistance = candidateLines[1].xPos2 - candidateLines[1].xPos1;

			return candidateLines[0].type == VERTICAL && candidateLines[1].type == BOTTOM_TO_RIGHT &&
					 candidateLines[2].type == HORIZONTAL && firstDistance < 150 && firstDistance >= 0 &&
					 firstDistance < 250;

			break;
			case 5:
			/*	 __
				|__
				 __|
			*/

			firstDistance  = abs(candidateLines[0].xPos1 - candidateLines[1].xPos1); // VERTICAL DISTANCE
			secondDistance = abs(candidateLines[2].yPos1 - candidateLines[3].yPos1); // HORIZONTAL DISTANCE (CENTER, TOP)
			thirdDistance  = abs(candidateLines[2].yPos1 - candidateLines[4].yPos1); // HORIZONTAL DISTANCE (CENTER, BOTTOM)

			return candidateLines[0].type == VERTICAL && candidateLines[1].type == VERTICAL &&
					 candidateLines[2].type == HORIZONTAL &&  candidateLines[3].type == HORIZONTAL &&
					 candidateLines[4].type == HORIZONTAL && abs(firstDistance - secondDistance) < 300 &&
					 abs(secondDistance -  thirdDistance) < 300;

			break;
			case 6:
			/* ___
				|___     
 				|__|     
			*/

			firstDistance  = abs(candidateLines[0].xPos1 - candidateLines[1].xPos1); // VERTICAL DISTANCE
			secondDistance = abs(candidateLines[2].yPos1 - candidateLines[3].yPos1); // HORIZONTAL DISTANCE (CENTER, TOP)
			thirdDistance  = abs(candidateLines[2].yPos1 - candidateLines[4].yPos1); // HORIZONTAL DISTANCE (CENTER, BOTTOM)

			return candidateLines[0].type == VERTICAL && candidateLines[1].type == VERTICAL &&
					 candidateLines[2].type == HORIZONTAL &&  candidateLines[3].type == HORIZONTAL &&
					 candidateLines[4].type == HORIZONTAL && abs(firstDistance - secondDistance) < 300 &&
					 abs(secondDistance -  thirdDistance) < 300;

			break;
			case 7:
			/* ___
				  /    
				 / 
			*/

			firstDistance = abs(candidateLines[1].xPos2 - candidateLines[1].xPos1);

			return 
				  candidateLines[0].type == HORIZONTAL && candidateLines[1].type == BOTTOM_TO_RIGHT
				  && firstDistance < 600;
			break;
			case 8:
			/*	 ___
     			|___|
            |___|
			*/

			firstDistance  = abs(candidateLines[0].xPos1 - candidateLines[2].xPos1);  // VERTICALES
			secondDistance = abs(candidateLines[1].yPos1 - candidateLines[3].xPos1);  // HORIZONTALES
			thirdDistance  = abs(candidateLines[4].yPos1 - candidateLines[3].yPos2);  // LINEA DEL CENTRO

			return 
				candidateLines[0].type == VERTICAL   && candidateLines[2].type == VERTICAL &&
				candidateLines[1].type == HORIZONTAL && candidateLines[3].type == HORIZONTAL &&
				candidateLines[4].type == HORIZONTAL && firstDistance < secondDistance &&
				thirdDistance < 200;

			break;
			case 9:
			/*  ___
			   |___|
                |
			*/

			firstDistance  = abs(candidateLines[0].xPos1 - candidateLines[2].xPos1);  // VERTICALES
			secondDistance = abs(candidateLines[1].yPos1 - candidateLines[3].xPos1);  // HORIZONTALES

			return 
				candidateLines[0].type == VERTICAL   && candidateLines[2].type == VERTICAL &&
				candidateLines[1].type == HORIZONTAL && candidateLines[3].type == HORIZONTAL &&
				abs(firstDistance - secondDistance)  < 250;

			break;
			default:
				// nothing to to
				break;
		}

		return false;
	}

};