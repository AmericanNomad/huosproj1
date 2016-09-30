#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
/* 
 * ################################################################ 
 * File: queue.c
 * Author: Hassan.Karim@bison.howard.edu
 * Purpose: Queue functions. Part 1 of Proj 1 - CSCI 401 Operating Systems 
 * Update History:
 * 08/28/2016: HSK: File Created
 * 09/03/2016: HSK: File template copied from queue.h
 * 09/09/2016: HSK: Added flesh to each function
 * 09/09/2016:	HSK: Got all functions to work
 * ####################################################################
 * 
 */

 
/* #####################################################################
* Put any struct definitions, typedefs and the above function prototypes in a 
* header file “queue.h” 
* Put function bodies (implementations) in a source file “queue.c”. 
* Make a test file “queue_test.c” that tests your queue implementation. 
* Your test file should try various tests of your create_queue, enqueue, 
* dequeue, flush_queue, print_queue, and free_queue functions. 
* Write a Makefile that compiles queue.c and queue_test.c to create a binary 
* executable named queue_test. 
##################################################################### */



/* ######################################################################## 
	 ############ 	Overall Instructions 			###########
Create a C-string queue (FIFO) data structure for storing character strings 
using a header file (queue.h) and separate source file (queue.c) for all 
functions. You need to implement the following functions, as well as define the 
struct(s) necessary for your queue to work correctly. 
########################################################################### */


/* #####################################################################
##################################################################### */

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


void enqueue(queue *ptrKew, char *item){
	/* ##############
	 * Adds item to end of the queue. This function allocates a new 
	 * buffer and copies the string from item (use malloc, strlen, 
	 * and strncpy; or try  strdup) 
	 * ACKNOWLEDGEMENTS: Got help from http://www.learn-c.org/en/Linked_lists
	 * ##############
	 */ 
	int DEBUG=1;
	if(DEBUG==1)printf("\nDEBUG-ENQUEUE: ITEM PASSED = %s\n", item);
	node *nodeEle = NULL; /* declare & initialize a pointer new node to add*/
	nodeEle = malloc(sizeof(node)); /* Allocate memory for the node itself */
	int sizeOfWord = strlen(item);
	if(DEBUG==1)printf("\nDEBUG-ENQUEUE: Initial SizeOfItem = %d\n", sizeOfWord);
	if(sizeOfWord>255){
	/* README_NOTE: I truncate the item if its too big. 
	 * I do this rather than crash later when enough mem has not been allocated
	 */
		sizeOfWord=255;
	}
	if(DEBUG==1){
		printf("DEBUG-ENQUEUE: ITEM SIZE = %d\n", sizeOfWord);
	}

	/* 
	 * Give me some memory for the word string. Im asking for just enough 
	 * space for character types x amt of characters sent to us.
	 */
	nodeEle->word = (char *) malloc(sizeof(char)*(sizeOfWord));
	if(nodeEle->word==NULL){
		printf("ERROR: Not enough memory to add anymore nodes\n");
	} else {
		/* put the item passed to us into the word section of node */
		strncpy(nodeEle->word, item, sizeOfWord); 
		int szNodeEle =strlen(nodeEle->word);
		if(DEBUG==1){
			printf("DEBUG-ENQUEUE: nodeEle->word SIZE = %d\n", szNodeEle);
			printf("DEBUG-ENQUEUE: nodeEle->word = %s\n", nodeEle->word);
		}

		/* Now, where do we put this node */
		if (ptrKew->head==NULL){ 
	  		/*
	   	 	 * if head is still pointing to NULL, it must be empty
	   	 	 * so change it to this new node
	   	 	 */
			ptrKew->head=nodeEle; 
			ptrKew->tail=nodeEle;
	
		} else {
	  		/*
	   		* Not empty. Never Change Head. just keep moving tail
	   		* From discussions with Portia Herndon, I learned that I need to:
	   		* a) use the q->tail->next as a connector to the new node
	   		* b) rename the new node as the last element
	   		*/
		
	  		ptrKew->tail->next=nodeEle; /* a connector to the new node */
	  		ptrKew->tail=nodeEle; /* last thing in the queue is nodeEle */
		}
	}	
}

 
char *dequeue(queue *ptrKew){
	/* ##############
	 * Pops and returns the string from the front of the queue. The calling 
	 * function is expected to free the string returned when finished with it.
	 * ##############
	 */ 
	char *nodeWord = NULL;
	node *tempNode;
	tempNode=NULL;
	int DEBUG=0;
	if (ptrKew->head==NULL){ 
		ptrKew->tail=NULL;
		nodeWord=NULL;
		if(DEBUG==1){
			printf("DEBUG-DEQUEUE: Word to be popped off is NULL\n");
		}
	} else {
	  nodeWord= ptrKew->head->word; /* Secure the word to return before any queue movement */
	  if(DEBUG==1){
		printf("DEBUG-DEQUEUE: Word to be popped:\t%s\n", nodeWord);
	  }
	  /* From discussions with Portia Herndon, I learned that I need to:
	   * a) keep track of the queue with a temp node before chopping off the head
	   */
	  if(ptrKew->head->next != NULL){
		tempNode=ptrKew->head->next; /* 1. grab the ref to the next node */
	  	free(ptrKew->head);	     /* 2. let go of this node */
	  	ptrKew->head=tempNode;	     /* 3. make the next node the current head */
		/* head could now be null, because we just freed a head which could have 
		 * been the last head to get popped.
		 */
		if(ptrKew->head == NULL){
	  		if(DEBUG==1){
				printf("DEBUG-DEQUEUE: Head has just been nulled out\n");
				printf("DEBUG-DEQUEUE: DONT COME BACK!\n");
	  		}
		} else {
	  		if(DEBUG==1){
	  			if(ptrKew->head->word!=NULL){
					printf("DEBUG-DEQUEUE: New Head->Word: %s\n", ptrKew->head->word);
					printf("DEBUG-DEQUEUE: Come back soon!\n");
				}
	  		}
		}
	  } else {
		if(ptrKew->head == NULL){
	  		nodeWord=NULL;
			ptrKew->tail=NULL;
	  		if(DEBUG==1){
				printf("DEBUG-DEQUEUE: Queue is now empty. No New Head->Word\n");
				printf("DEBUG-DEQUEUE: ********* ****************** ***************\n");
				printf("DEBUG-DEQUEUE: DONT COME BACK!\n");
	  		}
		}else{ /* Apparently Something is still in the kew... what is it!? */
	  		if(DEBUG==1){
				printf("DBUG-DQ-LastTest: ********* ****************** ***************\n");
				printf("DBUG-DQ-LastTest: *\tGENTLY release the last node \n");
				printf("DBUG-DQ-LastTest: ********* ****************** ***************\n");
	  			printf("DBUG-DQ-LastTest:\t\tnodeword:\t%s\n", nodeWord);
				printf("DBUG-DQ-LastTest:\t\tptrKew->head->word:\t%s\n", ptrKew->head->word);
				if(ptrKew->tail != NULL){
					printf("DEBUG-DQ-LastTest: ");
					printf("ptrKew->tail->word:\t%s\n", ptrKew->tail->word);
				}else {
					printf("DEBUG-DQ-LastTest: ptrKew->tail IS_NULL\n");
				}
				printf("DBUG-DQ-LastTest: deleting: \tptrKew->head->word");
			}
			ptrKew->head->word=NULL;
			ptrKew->head=NULL;
	  		if(DEBUG==1){
				printf(" @()O0o... DONE!\n");
				printf("ptrKew->tail->word:\t%s\n", ptrKew->tail->word);
			}
			ptrKew->tail->word=NULL;
			ptrKew->tail=NULL;
	  		if(DEBUG==1){
				printf(" @()O0o... DONE!\n");
				printf("DEBUG-DQ-LastTest: ********* ****************** ***************\n");
				printf("DEBUG-DQ-LastTest: DONT COME BACK!\n");
			}	
		}
	  }
	}

	return(nodeWord);
}

void print_queue(queue *ptrKew){ 
	/* ##############
	 * Prints every string in the queue, with a new line character at the end of 
	 * each string 
	 * ##############
	 */ 
	node *queFront;
	int DEBUG=1;
	queFront=ptrKew->head; /* can't use it later if its not 1st initialized */

	while(queFront != NULL){
		printf("%s\n",  queFront->word);
		queFront=queFront->next; // cycle through with this
	}
	if(DEBUG==1) printf("DEBUG-PrintQueue: Finished printing the queue\n");
}

 
void flush_queue(queue *ptrKew){ 
	/* ##############
	 * Flushes (clears) the entire queue and re-initializes the queue. 
	 * The passed pointer  ptrKew should still point to a valid queue when 
	 * this function returns. 
	 * 
	 * Any memory allocated to store items in the queue should be freed. 
	 * ##############
	 */ 
	int DEBUG=0;
	char *popWord;

	while(ptrKew->head!=NULL){
		popWord=dequeue(ptrKew);
		if(popWord != NULL){
			if(DEBUG==1){
				printf("DEBUG-FlushQueue: Flushing this %s\n", popWord);
			}
		} else {
			if(DEBUG==1){
				printf("DEBUG-FlushQueue: All flushed\n");
			}
			ptrKew->head=NULL;
			ptrKew->tail=NULL;
			return;
		}
	}

}

void free_queue(queue *ptrKew){ 
	/* De-allocates all data for the queue. Note: this function ensures 
	 * all memory allocated for this queue is freed. 
	 */ 
	int DEBUG=0;
	flush_queue(ptrKew);
	if(DEBUG==1) printf("DEBUG-FreeQueue: Fly away free queue\n");
	free(ptrKew);
}

