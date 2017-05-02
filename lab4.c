#include <stdio.h>
#include <stdlib.h>	/* for rand() and srand() */
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>
#include "drunkstagger.h"


void errorChecking(int argc );
void runStagger(int nRow, int nCol, int numExper);

int main(int argc, char* argv[])
{

	int nRow, nCol, numExper ;	/* variable declarations here */
	

	errorChecking(argc);		/* code for testing command line arguments here */
	
	nRow = atoi(argv[1]);		/* Load commandline arguments into variables */
	nCol = atoi(argv[2]);
	numExper = atoi(argv[3]);
	
	runStagger(nRow, nCol, numExper);/* Run the drunkenstagger process */
	
	return 0;
}

void errorChecking(int argc)	/* Check your commandline for errors */
{
	if(argc!= 4){
		printf(" An error occured in your command line. \n");
		printf(" Please make sure your input is in the following format: \n");
		printf(" #Rows #Columns #Experiments \n");
		exit(1);
	}
	return;
}
void runStagger(int nRow, int nCol, int numExper)	/* Function for running the randomStagger process */
{
	int i, seed, numSteps;
	float totalSteps;

	numSteps = 0;
	totalSteps = 0.0;
	
	printf("Floor has %i rows and %i columns, and there are %i experiments.\n", nRow, nCol, numExper);

	for(i=0; i < numExper; i++)			/* For each experiment */ 
	{
		/* use i to help seed the random generator */
		seed = i*10;
		numSteps = randomStagger(nRow,nCol, seed);
		printf("Sailor takes %i steps \n", numSteps);
		totalSteps = totalSteps + numSteps;
	}	
	
	/* more interesting code here */
	printf("Average number of steps %.6f\n", ( ((double)totalSteps) /  ((double)numExper)) );


}

