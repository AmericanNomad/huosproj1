/* #####################################################################
File: most_freq.h
Author: Hassan.Karim@bison.howard.edu
Purpose: header file for Pt 2 of Proj 1 - CSCI 401 Operating Systems 
##################################################################### */
#include <stdio.h>
#include <stdlib.h>	/* required for atoi - handles command line input */
#include <string.h>
/* These definitions were to save on debug time */
#define FILEREADERROR 99
#define GENDEBUG 0
#define TESTREADLINE 0
#define TESTBUILDLIST 0

/*
 * ################### Functions to recode ##########################
 * char *dequeue(queue *ptrKew);
 * unsigned int num_to_select); 
 * void freeStringList(struct node *head) ;
 * ################################################################## 
 */

int readLine(FILE *ptrINF, char *line_buffer);
  /*
   * ###########################################################
This function reads one line at a time from the file and stores the contents of
the line into the line_buffer string. The line_buffer string is dynamically
allocated outside of the readLine function. If the function succeeds in reading
a line, it should return 0, otherwise it should return some non-zero error code.
   * ##########################################################
   */

typedef struct queue { 
/* HSK Implementation Notes: 
 * My queue is a double link list. Head lets me keep track of the
 * front of the queue. Tail lets me keep track of the tail of the queue
 *   struct node *head=NULL; // initiailize the front of the queue
 *   struct node *tail=NULL; // initiailize the end of the queue
 */
	struct node *head; // Every queue will have a head pointer
	struct node *tail; // And we keep track of the end with a tail pointer
} queue; 

queue *create_queue(){
	/* Allocates and initializes a new queue 
	 * Every queue has at least one node. 
	 * The front and tail and point to the 
	 * same node.
	 */
	queue *newKew;
	newKew = malloc(sizeof(queue)); // Get a memory address.
	newKew->head=NULL;// initiailize the front of the queue
	newKew->tail=NULL;// initiailize the end of the queue

	return(newKew);
}

typedef struct node {
	/*
	 * ###########################################################
	 * # The linked list will be composed of these nodes
	 * # Freq node needed to be double linked to keep track of
	 * # order... since the requirements said to be alphabetical...
	 * # And because its easier to count frequency when they are in order
	 * ###########################################################
	 */
	char *word;
	unsigned int freq; /* used in the freq program. */
	struct node *next;
	struct node *prev; 
} node;

struct node *readStringList(FILE *ptrINF); 

void printStringList(struct node *head);
	/*
	 * This function can be used to print out a list (displaying the words and
	 * frequency).
	 * ##########################################################
	 */


