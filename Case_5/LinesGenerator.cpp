#define DefaultAmount 30

#define WIDTH  1080
#define HEIGHT 920
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
	      line.push_back( {0, randomY} );
	      line.push_back( {WIDTH, randomY} );
	    break;

	    case HORIZONTAL: 
	      line.push_back( {randomX, 0} );
	      line.push_back( {randomX, HEIGHT} );
	    break;

	    case DIAGONAL_FROM_TOP: 
	      line.push_back( {randomX, 0} );
	      if (diagonalSideCoin) 
	        line.push_back( {WIDTH, randomY} ); 
	      else 
	        line.push_back( {0, randomY} ); 
	           
	    break;

	    case DIAGONAL_FROM_LEFT:
	      line.push_back( {0, randomY} );
	      if (diagonalSideCoin) 
	        line.push_back( {randomX, HEIGHT} ); 
	      else 
	        line.push_back( {randomX, 0} ); 
	      
	    break;
	    default:
	    	// nothing to do
	    	break;
	  }

		return line;
	}

};