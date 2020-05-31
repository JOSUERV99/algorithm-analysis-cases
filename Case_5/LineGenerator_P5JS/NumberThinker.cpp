class NumberThinker {
public:
	NumberThinker() {}

	bool perceiveNumber(int number, Line[CANDIDATELINESAMOUNT] candidateLines) {

		switch(number){

			case 0:

			break;
			case 1:
				/*
				  /|
					|
					|
				*/
			int diagonalIndex = 0, verticalIndex = 0;

			for (int counter = 0; counter < CANDIDATELINESAMOUNT; counter++) {
				if ( candidateLines[counter].isDiagonal() )
					diagonalIndex = counter;
				else if ( candidateLines[counter].isVertical() )
					verticalIndex = counter;
			}

			return diagonalIndex != verticalIndex && 
					candidateLines[diagonalIndex].hasIntersection(candidateLines[verticalIndex]);
	
			break;
			case 2:
				/*
				  __
				  __|
				 |__	 
				*/

				int verticalCounter = 0, horizontalCounter = 0;

				for (int counter = 0; counter < CANDIDATELINESAMOUNT; counter++) {
					if ( candidateLines[counter].isVertical()  )
						verticalCounter++;
					else if ( candidateLines[counter].isHorizontal() ) 
						horizontalCounter++;
				}

				return verticalCounter == 2 && horizontalCounter == 3;

			break;	
			case 3:
			/*
				 __
				 __|
				 __|
				
			*/
			bool vertical = false; 
			int horizontalCounter = 0;

			for (int counter = 0; counter < CANDIDATELINESAMOUNT; counter++) {
				if ( candidateLines[counter].isVertical()  )
					verticalCounter = true;
				else if ( candidateLines[counter].isHorizontal() ) 
					horizontalCounter++;
			}

			return verticalCounter && horizontalCounter == 3;

			break;
			case 4:	
			/*  
				 /|   
				/_|_   	
				  |	
			*/

			bool vertical = false, diagonal = false, horizontal = false;

			for (int counter = 0; counter < CANDIDATELINESAMOUNT; counter++) {
				if ( candidateLines[counter].isVertical() )
					vertical   = true;
				else if ( candidateLines[counter].isHorizontal() )
					horizontal = true;
				else if ( candidateLines[counter].isDiagonal() )
					diagonal   = true;
			}

			return vertical && diagonal && horizontal;

			break;
			case 5:
			/*	 __
				|__
				 __|
			*/
			int verticalCounter = 0, horizontalCounter = 0;

			for (int counter = 0; counter < CANDIDATELINESAMOUNT; counter++) {
				if ( candidateLines[counter].isVertical()  )
					verticalCounter++;
				else if ( candidateLines[counter].isHorizontal() ) 
					horizontalCounter++;
			}

			return verticalCounter == 2 && horizontalCounter == 3;

			break;
			case 6:
			/* ___
				|___     
 				|__|     
			*/

			int verticalCounter = 0, horizontalCounter = 0;

			for (int counter = 0; counter < CANDIDATELINESAMOUNT; counter++) {
				if ( candidateLines[counter].isVertical()  )
					verticalCounter++;
				else if ( candidateLines[counter].isHorizontal() ) 
					horizontalCounter++;
			}

			return verticalCounter == 2 && horizontalCounter == 3;

			break;
			case 7:
			/* ___
				  /    
				 / 
			*/

			int diagonalIndex = 0, horizontalIndex = 0;

			for (int counter = 0; counter < CANDIDATELINESAMOUNT; counter++) {
				if ( candidateLines[counter].isDiagonal() )
					diagonalIndex = counter;
				else if ( candidateLines[counter].isParallel() )
					horizontalIndex = counter;
			}

			return diagonalIndex != horizontalIndex && 
					candidateLines[diagonalIndex].hasIntersection(candidateLines[horizontalIndex]);

			break;
			case 8:
			/*	 ___
     			|___|
            |___|
			*/

			int verticalCounter = 0, horizontalCounter = 0;

			for (int counter = 0; counter < CANDIDATELINESAMOUNT; counter++) {
				if ( candidateLines[counter].isVertical()  )
					verticalCounter++;
				else if ( candidateLines[counter].isHorizontal() ) 
					horizontalCounter++;
			}

			return verticalCounter == 2 && horizontalCounter == 3;

			break;
			case 9:
			/*  ___
			   |___|
                |
			*/

			int verticalCounter = 0, horizontalCounter = 0;

			for (int counter = 0; counter < CANDIDATELINESAMOUNT; counter++) {
				if ( candidateLines[counter].isVertical()  )
					verticalCounter++;
				else if ( candidateLines[counter].isHorizontal() ) 
					horizontalCounter++;
			}

			return verticalCounter == 2 && horizontalCounter == 2;


			break;
			default:
				std::cout << "?" << std::endl;
			break;
		}

		return false;
	}

};