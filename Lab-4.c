/*
Lab 4 - Memory Allocation
Comp 322/L
Nima Shafie
Date Here

Description:
To simulate memory allocation with hole-fitting algorithms (First-fit, Best-fit) and implement deallocation and defragmentation of memory blocks.
*/

#include <stdio.h>
#include <stdlib.h>

// declare structure to store block information (id, starting address, ending address, link to next block)
struct node {
// the identification of the block
int id;

// the size of the new block
int start;

// the ending address of the block
int end;

// a link to the next allocated block
struct node *link;
} *block_list = NULL;

typedef struct node block_type;

// declare linked list to connect allocation block

// declare global variables
int pm_size = -1;
int remaining;
int hole_algo = -1;

/********************************************************************/
void EnterParameters() {
	// declare local variables (if any)

    // prompt for size of physical memory and choice of hole-fitting algorithm (0=first-fit, 1=best-fit)
    printf("Enter size of physical memory: ");
    scanf("%d", &pm_size);
    while(pm_size <= 0) {
        printf("Size of physical memory must be greater than 0\n");
        printf("Enter size of physical memory: ");
        scanf("%d", &pm_size);
    }
    remaining = pm_size;

    while(hole_algo != 0 && hole_algo != 1) {
    printf("Enter hole-fitting algorithm (0 = First Fit, 1 = Best-Fit): ");
    scanf("%d", &hole_algo);
    }

    // initialize remaining memory 

    
	// initilize linked list with "dummy" block of size 0


	return;
}


/********************************************************************/
void PrintAllocationTable() {
	// declare local variables

	// print table containing block id, starting address, ending address


	return;
}


/********************************************************************/
void AllocteBlockMemory() {
	// declare local variables
    int temp_block;

	// initialize best hole so far to size of physical memory

	// prompt for block id & block size
    printf("Enter block id: ");
    scanf("%d", &temp_block);
    while(temp_block <= 0) {
        // block id entered cannot match another block id in the system
        // block id entered must be >= 0
        printf("Block ID cannot match a previous ID, and must 0 or greater\n");
        printf("Enter block id: ");
        scanf("%d", &temp_block);
    }

	// check if size of block is larger than remaining unallocated space, if so, print message and return	

	// allocate space for new block and set id

	// if only "dummy" block exists, insert block at end of linked list, set fields, return
	// else traverse list until either appropriate hole is found or the end of the list is reached
		// if id already exists, reject request and return
		// set values for start and end of currently found hole
		// if hole is large enough for block
			// if first-fit algorithm
				// set start & end fields of new block & add block into linked list
				// reduce remaining available memory and return
			// else--best-fit algorithm
				// if hole is smaller than best so far
					// set values of best start & best end & best hole size so far
					// update best block & advance next block 
	// set start & end fields of new block & add block into linked list 	  
	// reduce remaining available memory and return
	return;
}


/********************************************************************/
void DeallocteBlockMemory() {
	// declare local variables

	// prompt for block id

	// until end of linked list is reached or block id is found 
		// traverse list

	// if end of linked list reached, print block id not found

	// else remove block and deallocate memory
	return;
}


/********************************************************************/
void DefragmentMemory() {
	// declare local variables 	  

	// until end of list is reached
		// calculate current hole size
		// adjust start & end fields of current block to eliminate hole

	return;
}


/*******************************************************************/
// this needs parameter_type * node as an arg
void FreeMemoryQuitProgram(/*parameter_type *node arg*/) {
	// if node is NULL, return

	// else
		//recursively call procedure on node->link
		// deallocate memory from node

	return;
}


/***************************************************************/
int main() {
    int choice = 0;
	enum { PARAM, ALLOCATE, DEALLOCATE, DEFRAGMENT, QUIT, INVALID } menuChoice;

	while (choice != 5) {
		printf("Memory Allocation\n------------------------------\n");
		printf("1) Enter parameters\n");
		printf("2) Allocate memory for block\n");
		printf("3) Deallocate memory for block\n");
        printf("4) Defragment memory\n");
        printf("5) Quit program\n");
		printf("\nEnter selection: ");
		scanf("%d", &choice);
		if (choice == 1) menuChoice = PARAM;
		else if (choice == 2) menuChoice = ALLOCATE;
        else if (choice == 3) menuChoice = DEALLOCATE;
        else if (choice == 4) menuChoice = DEFRAGMENT;
		else if (choice == 5) menuChoice = QUIT;
		else menuChoice = INVALID;

		switch (menuChoice) {
		case PARAM:
			EnterParameters();
			break;
		case ALLOCATE:
			AllocteBlockMemory();
			break;
        case DEALLOCATE:
			DeallocteBlockMemory();
			break;
        case DEFRAGMENT:
			DefragmentMemory();
			break;
		case QUIT:
			FreeMemoryQuitProgram();
			break;
		case INVALID:
			printf("Invalid selection made, try again.\n\n");
		}
	};
	printf("\nThank you for using the Banker's Algorithm program, have a good day!\n");

	/* declare local vars */
	/* while user has not chosen to quit */
		/* print menu of options */
		/* prompt for menu selection */
		/* call appropriate procedure based on choice--use switch statement or series of if, else if, else statements */
 /* while loop */

return 1; /* indicates success */
} /* end of procedure */