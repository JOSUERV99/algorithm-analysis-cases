#define DefaultAmount 30
#define DIRECTIONAMOUNT 4

// possible directions mode
const int VERTICAL = 0;
const int HORIZONTAL = 1;
const int DIAGONAL_FROM_TOP = 2;
const int DIAGONAL_FROM_LEFT = 3;

class LinesGenerator {
public:

	std::vector<Line> giveMeLines(int linesAmount = DefaultAmount) {

		std::vector<Line> generatedLines;
		
		for (int _ = 0; _ < linesAmount; _++)
			generatedLines.push_back( getRandomLine() );

		return generatedLines;
	}

	Line getRandomLine() {

		Line line;

		int direction = rand() % DIRECTIONAMOUNT ; // choose direction

		int randomX = rand() % WIDTH;
		int randomY = rand() % HEIGHT;

		// to choose the side for diagonals
		bool diagonalSideCoin = (rand() % 2) == 0;
		  
	  switch(direction) {
	  
	    case VERTICAL: 
	      line.setFirstPoint( {0, randomY} );
	      line.setSecondPoint( {WIDTH, randomY} );
	    break;

	    case HORIZONTAL: 
	      line.setFirstPoint( {randomX, 0} );
	      line.setSecondPoint( {randomX, HEIGHT} );
	    break;

	    case DIAGONAL_FROM_TOP: 
	      line.setFirstPoint( {randomX, HEIGHT} );
	      if (diagonalSideCoin) 
	        line.setSecondPoint( {WIDTH, randomY} ); 
	      else 
	        line.setSecondPoint( {0, randomY} ); 
	    break;

	    case DIAGONAL_FROM_LEFT:
	      line.setFirstPoint( {0, randomY} );
	      if (diagonalSideCoin) 
	        line.setSecondPoint( {randomX, HEIGHT} ); 
	      else 
	        line.setSecondPoint( {randomX, 0} ); 
	      
	    break;
	    default:
	    	// nothing to do
	    	break;
	  }

		return line;
	}

};