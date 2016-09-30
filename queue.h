#include <stdio.h>
#include <string.h>

#ifndef QUEUE_H
#define QUEUE_H
/* 
 * ################################################################ 
 * File: queue.h
 * Author: Hassan.Karim@bison.howard.edu
 * Purpose: Header file for Part 1 of Proj 1 - CSCI 401 Operating Systems 
 * ################################################################ 
 * Update History:
 * 08/28/2016: HSK: File Created
 * 08/30/2016: HSK: 
 * # Inserted ifndef/define/endif to make sure the const variable is scoped
 *   only once.
 * # Added error constant 
 * 09/03/2016: HSK: File template copied from queue.h
 * 09/03/2016: Removed Part 1 defs from this file
 * 09/09/2016: fleshed out most of the functions
 * 09/10/2016: Fixed missing queue type based on http://www.tutorialspoint.com/cprogramming/c_typedef.htm
 */

/* ######################################################################## 
   ############ 	Overall Instructions 			###########
Create a C-string queue (FIFO) data structure for storing character strings 
using a header file (queue.h) and separate source file (queue.c) for all 
functions. You need to implement the following functions, as well as define the 
struct(s) necessary for your queue to work correctly. 
########################################################################### */

#define FILEREADERROR 2
typedef struct node { 
	/*
	 * ###########################################################
	 * # The linked list will be composed of these nodes
	 * ########################################################### 
	 */
	char *word; 
	unsigned int freq; /* used in the freq program. */
	struct node *next; 
} node; 

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


/* #####################################################################
PROVIDED FUNCTION PROTOTYPES 
ACKNOWLEDGEMENT: These prototypes were defined by Dr. G. Bloom.
##################################################################### */

/* Allocates and initializes a new queue */ 
queue* create_queue( ); 

/* Adds item to end of the queue. This function allocates a new buffer and 
copies the string from item (use malloc, strlen, and strncpy; or try strdup) */ 
void enqueue(queue* Q, char* item); 

 
/* Pops and returns the string from the front of the queue. The calling 
function is expected to free the string returned when finished with it. */ 
char* dequeue(queue* Q); 
 

/* Prints every string in the queue, with a new line character at the end of 
each string */ 
void print_queue(queue *Q); 

 

/* Flushes (clears) the entire queue and re-initializes the queue. The passed 
pointer Q should still point to a valid queue when this function returns. Any 
memory allocated to store items in the queue should be freed. */ 
void flush_queue(queue* Q); 

/* De-allocates all data for the queue. Note: this function ensures all 
memory allocated for this queue is freed. */ 
void free_queue(queue *Q); 

 
/* #####################################################################
* Put any struct definitions, typedefs and the above function prototypes in a 
  header file “queue.h” 
* Put function bodies (implementations) in a source file “queue.c”. 
* Make a test file “queue_test.c” that tests your queue implementation. 
* Your test file should try various tests of your create_queue, enqueue, 
  dequeue, flush_queue, print_queue, and free_queue functions. 
* Write a Makefile that compiles queue.c and queue_test.c to create a binary 
  executable named queue_test. 
##################################################################### */



#endif
