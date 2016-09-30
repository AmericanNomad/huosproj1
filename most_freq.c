/* #####################################################################
FIle: most_freq.c
Author: Hassan.Karim@bison.howard.edu
Purpose: Functions implementations for Pt 2 of Proj 1 - CSCI 401 Operating Systems 
Update History:
09/02/2016: HSK: File Created & Wrote initial driver/main()
09/03/2016: HSK: Flshed out printStringList
09/05/2016: HSK: Fleshed out freeStringList
09/10/2016: HSK: Fleshed out remaining functions based on lessons learned from queue
09/10/2016: HSK: Got most functions coded
09/11/2016: HSK: Added flesh to getMostFreq
09/13/2016: HSK: Debugged and got readLine to work
09/16/2016: HSK: after days of fighting, got readStringList to work
09/17/2016: HSK: revised readStringList because it passed an empty head!
##################################################################### */
#include <stdio.h>
#include <stdlib.h>	/* required for atoi - handles command line input */
#include <string.h>
#include "most_freq.h"	

int readLine(FILE *ptrINF, char *line_buffer){
  /*
   * ###########################################################
This function reads one line at a time from the file and stores the contents of
the line into the line_buffer string. The line_buffer string is dynamically
allocated outside of the readLine function. If the function succeeds in reading
a line, it should return 0, otherwise it should return some non-zero error code.
   * ##########################################################
   */
	int DEBUG=0;
	int sxsLineRead=NULL;

	if(ptrINF==NULL){ // Be sure that we actually opend the file
		printf("ERROR: most_freq unable to open input file for reading. Barf!! \n");
		return FILEREADERROR; // FILEREADERROR was defined in the header
	}
	/* ####### FILE ASSUMED TO BE OPEN ######### */
	if(fscanf(ptrINF, "%s", line_buffer) != EOF) {
		sxsLineRead=0;
		if(DEBUG==1){
			printf("DEBUGLineRead: sxsLineRead = %d\n", sxsLineRead);
			/* %s is for type char. %p is for the memory address  */
			printf("DEBUGLineRead: String = %s, Address = %p\n", line_buffer, &line_buffer);
			printf("DEBUGLineRead: printing strings-working!\n");
			printf("DEBUGLineRead: File handles-working!\n");
		}
	} else {
		sxsLineRead=1;
	}
	return(sxsLineRead);
}


struct node *readStringList(FILE *ptrINF){ 
	/*
	 * ###########################################################
	 * a. This function reads strings from the file 
	 * b. puts them into a sorted (alphabetically) word list with 
	 * c. each word node records the frequency of the word
	 * d. Each node & string is dynamically allocated on the heap (using malloc);
	 * e. This function returns a pointer to a node 
	 * e.QUESTION: Which ptr_node should be returned? Head or Tail, 
	 * It should not be the one we just added because maybe we didn't have to add.
	 * f.ASSUMPTION: We have to create the list/queue via this function.
	 * ########################################################## 
	 */
	if(GENDEBUG) printf("DBG ENTERING readStringList()\n ########### \n");
	char 	*tmpLineBuffer=NULL;
	char 	*line_buffer=NULL;
	queue 	*list=NULL;
	struct 	node *nodeCur=NULL;
	struct 	node *nodeTracker=NULL;
	int intCompare=0;

	/* allocating memory with malloc */
	tmpLineBuffer= malloc(sizeof(char) * 255); /* buffer for 255 chars */
	nodeCur = malloc(sizeof(node)); 

	list=create_queue(); // instantiate a que
	list->head=nodeCur; // point the head of the queue to null
	list->tail=nodeCur; // point the tail of the queue to null
	nodeTracker=list->head; //tmp tracking node

	if(GENDEBUG) {
		printf("DBGreadLnStr: ####### 1st Check #########\n");
		printf("DBGreadLnStr: list->head= %p\n", &list->head);
		printf("DBGreadLnStr: list->tail= %p\n", &list->tail);
	}
	
	/* Read from the file until there's no more lines to read from */
	while(readLine(ptrINF, tmpLineBuffer) == 0 ){
		/* Take steps now to constrain input to 255 characters */
		int inputLength = strlen(tmpLineBuffer);
		if(inputLength>=255){
			inputLength=255;
		} 
		line_buffer = (char *) malloc(sizeof(char)*inputLength+1); 
		strncpy(line_buffer, tmpLineBuffer, inputLength); 

		if(GENDEBUG)printf("DBG nodeCur: Build a new node\n");
		nodeCur->word=line_buffer;
		if(GENDEBUG)printf("DBG nodeCur: just assigned word=line_buffer\n");
		nodeCur->next=NULL;
		nodeCur->prev=NULL;
		if(GENDEBUG){
			printf("DBG.nodeCur: ### Here is the new node ###\n");
			printf("DBG.nodeCur: Struct Node NodeNew {\n");
			//printf("DBG.nodeCur:   nodeCur->freq = %d\n",nodeCur->freq);
			printf("DBG.nodeCur:   nodeCur->freq = _NOTSET_YET_\n");
			printf("DBG.nodeCur:   nodeCur->word = %s\n",nodeCur->word);
			printf("DBG.nodeCur:   nodeCur->prev = %p\n",nodeCur->prev);
			printf("DBG.nodeCur:   nodeCur->next = %p\n",nodeCur->next);
			printf("DBG.nodeCur: }\n");
		}
		/* Where to put this node ???? */
		
		if(nodeTracker->word==NULL){
			// make this node the head
			if(GENDEBUG)printf("DBG List->head: list->head was NULL\n");
			nodeCur->freq=1;
			list->head=nodeCur; // point the head of the queue to our Current Node
			list->tail=nodeCur; // point the tail of the queue to our Current Node
			if(GENDEBUG){
				printf("DBG.listHead: ### list-> head points to this ###\n");
				printf("DBG.listHead: list-head { \n");
				printf("DBG.listHead:\tlist->head->freq = %d\n",list->head->freq);
				printf("DBG.listHead:\tlist->head->word = %s\n",list->head->word);
				printf("DBG.listHead:\tlist->head->prev = %p\n",list->head->prev);
				printf("DBG.listHead:\tlist->head->next = %p\n",list->head->next);
				printf("DBG.listHead: }\n");
			}
		} else {
			// find where to put this node
			if(GENDEBUG){
				printf("DBGreadLnStr: If here, then list->head != NULL\n");
				printf("DBGreadLnStr: list->head->word = %s  Freq: %d\n",list->head->word, list->head->freq);
				printf("DBGreadLnStr: ####### Check Point       #########\n");
				printf("DBGreadLnStr: list->head= %p\n", &list->head);
				printf("DBGreadLnStr: list->tail= %p\n", &list->tail);
			}
			// Where do we put this node?
			while((nodeTracker!= NULL)&&(nodeCur->word != NULL)){
		/* Compare line_buffer to current->word 
		 *
		 * I used strcmp() vs strncmp() because I want to compare the whole string
		 * At this point I am not concerned about string length because I already 
		 * ensure that I have enough space.
		 * FROM man 3 strcmp
       		 * int strcmp(const char *s1, const char *s2);
		 * The  strcmp() function compares the two strings s1 and s2. It returns
		 * an integer less than, equalto, or greater than zero if s1 is found, 
		 * respectively, to be less than, to match,  or  be  greater than s2. 
		 * i.e. 
		 * int < 0 ... s1 is higher in the alpha order than s2 (closer to a)
		 * int == 0 .. s1 is the same word as s2
		 * int > 0 ... s1 is lower in the alpha order than s2 (closer to z)
		 */
				if(GENDEBUG){
					printf("DBGreadString: compare line buffer to current node's word\n");
					printf("DBGreadString: nodeCur->word = %s  Freq: %d\n",nodeCur->word, nodeCur->freq);
					printf("DBGreadString: lined_buffer = %s  \n",line_buffer);
					printf("DBGreadString: ####### MAIN COMPARE Check #########\n");
					printf("DBGreadString: # Before comparison.      #\n");
					printf("DBGreadString: list->head= %p\n", &list->head);
					printf("DBGreadString: list->tail= %p\n", &list->tail);
					printf("DBGreadString: compare nodeCur (%s) to line_buffer (%s) aka the new word\n", nodeCur->word, line_buffer);
				}
				intCompare = strcmp(nodeCur->word, line_buffer);
				if(GENDEBUG)printf("ListDBG: intCompare = %d\n", intCompare);
				if( intCompare==0 ){
					/*
	 	 			* 2.a	CASE_1: line_buffer same as head->word, 
	 	 			* 2.a.1	increment head->freq. 
	 	 			* 2.a.2	discard line_buffer
		 			*/
					if(GENDEBUG)printf("ListDBG: Since these words were the same ");
					if(GENDEBUG)printf("i.e. intCompare == 0, we increment Freq\n");
	
					nodeCur->freq++;
				  if(GENDEBUG){
						printf("ListDBG: nodeCur->word = %s  ", nodeCur->word);
						printf("Freq: %d\n", nodeCur->freq);
						printf("DBGreadString: ####### 4th Check #########\n");
						printf("DBGreadString: ####### Compare == 0 ######\n");
						printf("DBGreadString: ## Head or tail doesnt move ##\n");
						printf("DBGreadString: list->head= %p\n", &list->head);
						printf("DBGreadString: list->tail= %p\n", &list->tail);
				  }
        } else if (intCompare <0) {
	 	 			//2.b	CASE_2: line_buffer should be first
	 	 			/* 2.b.1	create_node */
					if(GENDEBUG){
			printf("DBGreadStrLn.Cmp<0: ####### 5th Check #########\n");
			printf("DBGreadStrLn.Cmp<0: ####### Compare < 0 #######\n");
			printf("DBGreadStrLn.Cmp<0: list->head= %p\n", &list->head);
			printf("DBGreadStrLn.Cmp<0: list->tail= %p\n", &list->tail);
						printf("ListDBG: Apparently My word comes 1st!");
						printf(" because %s comes before %s in alpha order\n",
						line_buffer, nodeCur->word);
					}
					struct node *nodeNew=NULL; // instantiate a new node
					
	 	 			/* if a node is being created, it must be the new #1 */
	 	 			nodeNew->freq=1;
	 	 			nodeNew->word=line_buffer;
					/* Hook on to the current Node's previous link */
	 	 			nodeNew->prev=nodeCur->prev;
					/* Attach one end of new to the current Node */
	 	 			nodeNew->next=nodeCur;
					/* Now make the currentNode treat me as previous */
					nodeCur->prev=nodeNew;
					list->tail=nodeCur;
					if(GENDEBUG){
						printf("ListDBG: Struct Node NodeNew {\n");
						printf("ListDBG: nodeNew->freq = %d\n",nodeNew->freq);
						printf("ListDBG: nodeNew->word = %s\n",nodeNew->word);
						printf("ListDBG: }\n");
						printf("DBGreadString: ####### 6th Check #########\n");
						printf("DBGreadString: ####### Compare < 0 #######\n");
						printf("DBGreadString: ##   head should change  ##\n");
						printf("DBGreadString: list->head= %p\n", &list->head);
						printf("DBGreadString: list->tail= %p\n", &list->tail);
					}
					nodeTracker=NULL; //effectively break
			} else { /* case >0 */ 
					if(GENDEBUG){
						printf("ListDBG: check the new word against next \n");
						printf("DBGreadString: ####### 7th Check #########\n");
			  		printf("DBGreadString: ####### Compare > 0 #######\n");
			  		printf("DBGreadString: list->head= %p\n", &list->head);
			  		printf("DBGreadString: list->tail= %p\n", &list->tail);
					}

						nodeCur = nodeCur->next;
				} //END_COMPARE
				if(GENDEBUG){ printf("DBG.readStrLn: Compare is finished\n");
						printf("DBGreadString: ####### #######\n");
			  		printf("DBGreadString: ####### #######\n");
			  		printf("DBGreadString: list->head= %p\n", &list->head);
			  		printf("DBGreadString: list->tail= %p\n", &list->tail);
				}

			 } 
				/* END_WHILE_CURRENT_NODE */
		} /* END_head_NULL_TEST */
	} /* No more words to read in */
	
	fclose(ptrINF); /* Close the input file */

	if(GENDEBUG) printf("DBG LEAVING readStringList()\n ############## \n");
	return(list->head);
}


void printStringList(struct node *head){
	/*
	 * ###########################################################
	 * This function can be used to print out a list (displaying the words and
	 * frequency).
	 * ##########################################################
	 */
	if(GENDEBUG) printf("DBG ENTERING printStringList()\n ########### \n");
  if(head==NULL){
  	printf("Error: most_freq.printStringList: head==NULL\n");
  } else {
		struct node *nodeTmp=NULL; //instantiate a temporary node
		nodeTmp=head;
	  if(GENDEBUG) printf("DBG head->word = %s\n", head->word);
	  if(GENDEBUG) printf("DBG nodeTmp->word = %s\n", nodeTmp->word);
		while(nodeTmp != NULL){
			printf("List->Word:\t%s Freq: %d\n", nodeTmp->word, nodeTmp->freq);
			nodeTmp=nodeTmp->next;
		}
	}
	if(GENDEBUG) printf("DBG LEAVING printStringList()\n ########### \n");
}


int main(int argc, char *argv[]){
	FILE *ptrWordFile;
	//int maxlines = atoi(argv[1]);
	char *filename  = argv[2];
	char *line_buffer = "";
	struct node *headOL=NULL;
	/* 
	 * Make sure we can are passed the right amount of arguments , i.e.
	 *	1. the program name itself is argv[0]
	 *	2. maxlines is argv[1]
	 *	3. the filename is argv[2]
	 */
	if(argc != 3){
		printf("Usage: most_freq # filename\n");
		return 99; /* README Notes: exit code 99 means wrong # arguments */
	}
	/* Make sure we can open the file for reading. */
	ptrWordFile=fopen(filename, "r");
	if(ptrWordFile==NULL){
		printf("ERROR: most_freq Unable to open input file for reading\n");
		return 29; /* README Notes: Define exit 29 as unable to open for read */
	}
	if(TESTREADLINE){
		// Code to test REadline as a standalone function
		line_buffer = malloc(sizeof(char) *255);
		while(readLine(ptrWordFile, line_buffer)!=0){
			printf("Word:\t%s\n", line_buffer);
		}
		printf("No more words in %s\n", filename);
	} // END of TESTREADLINE

	headOL = readStringList(ptrWordFile);
	if(TESTBUILDLIST){
		printf("DBG.main(): After readStringList(), before print...\n");
		printf("DBG.main(): Address of head Node of Ordered List= %p\n", &headOL);
		printf("headOL->word:\t%s Freq: %d\n", headOL->word, headOL->freq);
		printf("headOL->freq:\t%s Freq: %d\n", headOL->word, headOL->freq);
		printStringList(headOL);
		printf("DBG.main(): After printStringList() finished\n");
	} // END of TESTBUILDLIST
	fclose(ptrWordFile);

	//printStringList(listTopX);
	//listTopX = getMostFrequent(headOL->head, maxlines);

	/* Now lets print the top x list */
	//printStringList(listTopX);

	/* Now the list is finished, lets free up the memory*/
	//freeStringList(headOL);

	exit(0);
}
