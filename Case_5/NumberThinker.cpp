class NumberThinker {
public:
	NumberThinker() {}

	bool perceiveNumber(int number, std::vector<Line> candidateLines) {

		int diagonalIndex = -1, verticalIndex = -1, horizontalIndex = -1;
		int verticalCounter = -1, horizontalCounter = -1;

		bool vertical = false, horizontal =  false, diagonal = false;
		switch(number){

			case 0:

			break;
			case 1:
				/*
				  /|
					|
					|
				*/

			for (int counter = 0; counter < CandidateLinesAmount; counter++) {
				int direction = -1;
				if ( candidateLines[counter].isDiagonal(direction) )
					if (direction == DIAGONAL_BOTTOM_TO_RIGHT)
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


				for (int counter = 0; counter < CandidateLinesAmount; counter++) {
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

			for (int counter = 0; counter < CandidateLinesAmount; counter++) {
				if ( candidateLines[counter].isVertical()  )
					verticalCounter++;
				else if ( candidateLines[counter].isHorizontal() ) 
					horizontalCounter++;
			}

			return verticalCounter == 1 && horizontalCounter == 3;

			break;
			case 4:	
			/*  
				 /|   
				/_|_   	
				  |	
			*/

			for (int counter = 0; counter < CandidateLinesAmount; counter++) {
				int direction = -1;
				if ( candidateLines[counter].isVertical() )
					vertical   = true;
				else if ( candidateLines[counter].isHorizontal() )
					horizontal = true;
				else if ( candidateLines[counter].isDiagonal(direction) )
					if (direction == DIAGONAL_BOTTOM_TO_RIGHT)
						diagonal   = true;
			}

			return vertical && diagonal && horizontal;

			break;
			case 5:
			/*	 __
				|__
				 __|
			*/

			for (int counter = 0; counter < CandidateLinesAmount; counter++) {
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

			for (int counter = 0; counter < CandidateLinesAmount; counter++) {
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

			for (int counter = 0; counter < CandidateLinesAmount; counter++) {
				int direction = -1;
				if ( candidateLines[counter].isDiagonal(direction) )
					if (direction == DIAGONAL_BOTTOM_TO_RIGHT)
						diagonalIndex = counter;
				else if ( candidateLines[counter].isHorizontal() )
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

			for (int counter = 0; counter < CandidateLinesAmount; counter++) {
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

			for (int counter = 0; counter < CandidateLinesAmount; counter++) {
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