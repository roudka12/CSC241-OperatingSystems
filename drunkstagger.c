#include "drunkstagger.h"  
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* this should be in a source file.... */
int randomStagger(int nRow, int nCol, int seed)
{
	/* local variable declarations here */
	int currRow, currCol, numSteps, randRow, randCol, possRandRow, possRandCol;

	
	currRow = nRow/2;	/* Find center */
	currCol = nCol/2;
	
	numSteps = 0;		/* Keep track of number of steps */
		
	randRow = 0;		/* Random step value (-1, 0, 1) to be added to current */
	randCol = 0;	
	
	
	/* seed the random number generator */
	srand(seed);
	
	/* simulate the stagger here */
	while(1){		/* While I've not fallen off the board */
	
		possRandRow = 0;	/* Set POSSIBLE randRow and randCol variables to 0 */
		possRandCol = 0;
		
		while(possRandRow == 0 && possRandCol == 0 ){	/* While the possible rand values both = 0 (Illegal move), Find legal move */
		
			
			possRandRow = rand() % 3;		/* Compute a possible rand value */
			possRandCol = rand() % 3;
		
			switch(possRandRow){			/* Switch cases */
				case 0:				
					randRow = 0 ;		/* If possible is 0, then randRow is 0*/
					break;
				case 1:
					randRow = -1;		/* If possible is 1, then randRow is -1*/
					break;
				case 2:	
					randRow = 1;		/* If possible is 2, then randRow is 1*/
					break;
			}
			switch(possRandCol){
				case 0:
					randCol = 0 ;		/* If possible is 0, then randCol is 0*/
					break;
				case 1:
					randCol = -1;		/* If possible is 1, then randRow is -1*/
					break;
				case 2:	
					randCol = 1;		/* If possible is 2, then randRow is 1*/
					break;
			}
		}
		
		/*-------------If you get here, you have a legal move. (Row && Col != 0 )----------------------------- */
		
		currRow = currRow + randRow;			/* add thes random steps to the current place */
		currCol = currCol + randCol;
		
		
		
		numSteps++;					/* You made a step! Count it! */
		
		if(currRow < 0 || currCol < 0){			/* break if you go too far and fall */
			break;
		}
		if(currRow > nRow || currCol > nCol){
			break;
		}
		
	}
	return numSteps;
}
