#include <stdio.h>
#include <stdlib.h>	/* for rand() and srand() */
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include "drunkstagger.h"


void errorChecking(int argc );
void runParallelStagger(int nRow, int nCol, int numExper);

int main(int argc, char* argv[])
{

	int nRow, nCol, numExper ;	/* variable declarations here */
	errorChecking(argc);		/* code for testing command line arguments here */
	
	nRow = atoi(argv[1]);		/* Load commandline arguments into variables */
	nCol = atoi(argv[2]);
	numExper = atoi(argv[3]);
	
	runParallelStagger(nRow, nCol, numExper);/* Run the drunkenstagger process */
	
	return 0;
}


/* Error checking function */
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

/* Function to run the randomStagger function and fork for parallelization */
void runParallelStagger(int nRow, int nCol, int numExper)	/* Function for running the randomStagger process */
{
	int k, seed, numSteps, status;	/* Declarations */
	
	float totalSteps;	/* To track total steps made by a drunken sailor */
	pid_t pid;		/* Process ID */
	int pipeFD[2] ;		/* PIPE: 0 for reading, 1 for writing */
	
	numSteps = 0;		/* Initialize steps to 0 (You haven't moved yet!) */
	totalSteps = 0.0;
	
	if(pipe(pipeFD) == 1){	/* Check pipe */
		fprintf(stderr,"Pipe error:%s\n",strerror(errno));
		exit(1);
	}
	/*memset(pipeFD,'\0',2);*/
	
	printf("Floor has %i rows and %i columns, and there are %i experiments.\n", nRow, nCol, numExper);
	
	for(k=0; k< numExper;k++){	/* Loop through number of experiments */ 

		pid = fork();		/* Declare fork() */
		
		if(pid < 0){		/* error check fork */
			fprintf(stderr,"Fork()error:%s", strerror(errno));
			exit(1);
		}
		
	
		if (pid == 0) {			/* if child, call randStagger */
			close(pipeFD[0]);	/* Close read side of pipe */
			
			seed = k*10; 		/*use k to help seed the random generator */ 
			numSteps = randomStagger(nRow,nCol, seed);	/* Call randomStagger to get */
			write(pipeFD[1], &numSteps,sizeof(int));	/* Write to the pipe */
			numSteps = 0;					/* Re-set numSteps */
			exit(k);					/* Get out of there! */
			
		}else{
			/*printf("I'm the parent with id#%i >:) \n",getppid());	*/
		}
	}
			


	while((pid  = wait (&status)) != -1){	/* WAIT!!!.....Find exit status */
		if(WIFEXITED(status)){		/* If child exits */
			printf("Child pid %i exited with status %d \n",pid, WEXITSTATUS(status));
			read(pipeFD[0],&numSteps,sizeof(int));		/* PIPE: Read your steps in here  */
			
			printf("Sailor takes %i steps \n", numSteps);
			totalSteps = totalSteps + numSteps ;
			
		}else{
			fprintf(stderr,"Fork error: %s \n", strerror(errno));
			exit(1);
		}
		fflush(stdout);		/* flush???? FULP: yes */
	}
	printf("Average number of steps %.6f\n", ( ((double)totalSteps) /  ((double)numExper)) );
}
