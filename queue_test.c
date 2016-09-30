#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "queue.c"
/* #####################################################################
 * File:queue_test.c
 * Author: Hassan.Karim@bison.howard.edu
 * Purpose: test driver for Proj 1 - CSCI 401 Operating Systems 
 * Update History:
 * 08/28/2016: HSK: File Created
 * #####################################################################
 */

/* ###################### Project 1 Instructions #####################
* Put any struct definitions, typedefs and the above function prototypes in a 
* header file “queue.h” 
* Put function bodies (implementations) in a source file “queue.c”. 
* Make a test file “queue_test.c” that tests your queue implementation. 
* Your test file should try various tests of your create_queue, enqueue, 
* dequeue, flush_queue, print_queue, and free_queue functions. 
* Write a Makefile that compiles queue.c and queue_test.c to create a binary 
* executable named queue_test. 
##################################################################### */

int main(){
	printf("Welcome to queue_test - (c) 2016 Hassan Karim\n");

	int DEBUG=1;
	queue *ptrNewQue; /* Declare variable of type queue * */

	/*  #### OPEN INPUT FILE #### */
	FILE *ptrINF; // File pointer
	ptrINF=fopen("inputfile.txt", "r"); // open the file read only

	if(ptrINF==NULL){ // Be sure that we actually opend the file
		printf("Unable to open input file for reading. Barf!! \n");
		exit (FILEREADERROR); // FILEREADERROR was defined in the header
	}
	/* ####### FILE ASSUMED TO BE OPEN ######### */

	ptrNewQue = create_queue(); /* instantiate the queue from queue.c */
	if(ptrNewQue == NULL){
		printf("ERROR! Out of Memory. Couldn't make a new queue. Sorry!\n");
	} else {
		if(DEBUG==1) {
			printf("Queue created\n");
		}
	}
	/* ####### QUEUE NOW EXISTS ######### */

	/* ####### TEST ENQUEUE ######### */
	char *inString;
	char *ptrString;
	int enqDEBUG=0;
	/* Initialize strings by allocating memory with malloc */
	inString = (char *) malloc(sizeof(char) * 255); /* buffer for 255 chars */
	while (fscanf(ptrINF, "%s", inString) != EOF) {
		if(enqDEBUG==1) {
			/* My Test string +1 for null character ?? */
			ptrString = (char *) malloc(sizeof(char) * 22); 
			strcpy(ptrString, "Op Sys with Dr. Bloom");
			/* %s is for type char. %p is for the memory address  */
			printf("DEBUG: String = %s,  Address = %p\n", ptrString, &ptrString);
			printf("DEBUG: malloc-working! \n");
			printf("DEBUG: printing strings-working!\n");
			free(ptrString);
		}
		enqueue(ptrNewQue, inString);
	}
	fclose(ptrINF); /* Close the input file */
	printf("####### QUEUE is now full #########\n");
	printf(" ####### DISPLAY QUEUE CONTENTS ######### \n");
	print_queue(ptrNewQue);

	printf(" ####### LETS TEST DEQUEUE ######### \n");
	if(ptrNewQue != NULL){
		ptrString = (char *) malloc(sizeof(char)); 
		ptrString = dequeue(ptrNewQue);
		printf("QUETEST-TestingDequeue: Just popped this from the queue:  %s\n", ptrString);
		free(ptrString);
	}

	printf(" ####### FLUSH_QUEUE uses dequeue to flush the whole queue ######### \n");
	flush_queue(ptrNewQue);
	printf(" ####### FLUSH_QUEUE FLUSHED! ######### \n");

	printf(" ####### GET RID OF THE QUE! WHAT! No more Omegas! :p ######### \n");
	free_queue(ptrNewQue);

	printf("Thanks for using queue_test - (c) 2016 Hassan Karim\n");
	return 0;
}
