/*
Lab 4 - Memory Allocation
Comp 322/L
Nima Shafie
Date Here

Description:
To simulate memory allocation with hole-fitting algorithms (First-fit, Best-fit) and implement deallocation and defragmentation of memory blocks.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

/*
struct vectorType {
	int resource;
	int available;
} *vector = NULL, * resourceVector = NULL, * availableVector = NULL;
typedef struct vectorType type_vector;
*/

// declare structure to store block information (id, starting address, ending address, link to next block)
struct node {
// the identification of the block
int id;
// the parent of this block
int parent;
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
    int dummy = 0;

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

<<<<<<< HEAD
    // initialize remaining memory
	block_list = (block_type*)malloc(pm_size * sizeof(block_type)); // Memory is allocated for 'n' elements
    /*
    for(int i = 0; i < pm_size; i++) {
        block_list[i].start = NULL;
        block_list[i].end = NULL;
        block_list[i].id = NULL;
        block_list[i].parent = NULL;
        block_list[i].link = NULL;
    }
    */
	if (block_list == NULL) {
		printf("\nNo memory is allocated.\n\n");
		exit(0);
	}

	// initilize linked list with "dummy" block of size 0
    block_list[dummy].id = -1;
    block_list[dummy].parent = -1;
    block_list[dummy].start = 0;
    block_list[dummy].end = 0;
    block_list[dummy].link = NULL;

    printf("\n");
=======
    // initialize remaining memory 
	block_list = (block_type*)malloc(remaining * sizeof(block_list));
	if (block_list == NULL) {
		printf("\nNot able to allocate enough memory, terminating program.\n\n");
		exit(0);
	}
    
	// initilize linked list with "dummy" block of size 0
	block_list[0].id = 0;
	block_list[0].start = 0;
	block_list[0].end = 0;
	block_list[0].link = NULL;

>>>>>>> a0b2ef93bddae3f292ae2263fce44fa16ac40f81
	return;
}


/********************************************************************/
void PrintAllocationTable() {
	// declare local variables
<<<<<<< HEAD
    int index = 0;
    bool end_of_list = false;

	// print table containing block id, starting address, ending address
    printf("\nID\tStart\tEnd\n");
	printf("-----------------------------\n");
	while(!end_of_list) {
        // check if any entries exist in the allocation table
    if (pm_size == remaining) end_of_list = true;
    else {
		printf("%d",   block_list[index].id);
		printf("\t%d", block_list[index].start);
        printf("\t%d", block_list[index].end);
		printf("\n");
        if (block_list[index].link == NULL) {
            printf("\nEnd of list!\n");
            end_of_list = true;
        }
        else if(block_list[index].link != NULL) {
            block_list = block_list->link;
            printf("What is index? (before) : %d", index);
            index = block_list->id;
            printf("\t(after) : %d\n", index);
        }
	}
    }
=======
	int allocation_index = 0;
	block_type* next = NULL;

	// print table containing block id, starting address, ending address
	printf("\nID\tStart\tEnd\n");
	printf("-----------------------------\n");
	// while there are still available children 
	while (block_list[allocation_index].link != NULL) {
		printf("\n%d\t%d\t%d",
			block_list[allocation_index].id, block_list[allocation_index].start, block_list[allocation_index].end);
	}
	/*
	for (int i = 0; i <= MAX_RESOURCES; i++) {
		printf("r%d", i);
		printf("\t%d\t%d", resourceVector[i].resource, availableVector[i].available);
		printf("\n");
	}
	*/

>>>>>>> a0b2ef93bddae3f292ae2263fce44fa16ac40f81
	return;
}


/********************************************************************/
void AllocteBlockMemory() {
	// declare local variables
    int dummy = 0;
    int head = 0;
    int index = 1;
    int temp_block;
    int temp_block_size;
    bool duplicate_id = false;
    bool empty_list = false;

    PrintAllocationTable();
    printf("\n");

	// initialize best hole so far to size of physical memory

	// prompt for block id & block size
    printf("Enter block id: ");
    scanf("%d", &temp_block);
    // scan through list of current block ID's to ensure no duplicates exist
    while(temp_block < 0 || duplicate_id) {
        // block id entered cannot match another block id in the system
        for(block_list[0].link->link; block_list->link != NULL, block_list = block_list->link;) {
        if(temp_block == block_list->id) {
        printf("\nDuplicate ID detected!\n");
        duplicate_id = true;
        }
        }
        block_list = block_list->link;

        // block id entered must be >= 0
        printf("Block ID cannot match a previous ID, and must be greater than or equal to 0\n");
        printf("Enter block id: ");
        scanf("%d", &temp_block);
    }

    // check if size of block is larger than remaining unallocated space, if so, print message and return
    printf("Enter block size: ");
    scanf("%d", &temp_block_size);
    while(temp_block_size > remaining) {
        printf("Cannot initialize more memory than current existing memory.\n");
        printf("Current Existing = %d \t Asking for = %d\n", remaining, temp_block_size);
        printf("\nEnter block size: ");
        scanf("%d", &temp_block_size);
    }

    /*
    // check if this is the first block entry (if so start == 0)
    if (pm_size == remaining) empty_list = true;

	// allocate space for new block and set id
    block_list[temp_block].id = &temp_block;
    // if no entries in the list, we set the first entry as the child of the dummy
    if(empty_list) {
        //block_list[temp_block].start = 0;
        block_list[head].link = &block_list[temp_block];

        //block_list
        empty_list = false;
    }
    // if entries exist in the list, we start at the most recent end size entry
    else {
        for(; 
        block_list->link != NULL;
        block_list = block_list[index].link) {
            printf("\nCurrently on index = %d :  block_list[%d]", index, block_list[index].id);
        }
        // doubly linked list can work, new link can point to previous links end
        // block_list[temp_block].start = block_list[temp_block].
    }
    */

    // if only "dummy" block exists, insert block at end of linked list, set fields, return
    if (block_list[dummy].link == NULL) {
        block_list[dummy].link = &block_list[index];
        block_list[index].id = temp_block;
        block_list[index].parent = block_list[dummy].id;
        block_list[index].start = 0;
        block_list[index].end = temp_block_size;
        printf("\nID : %d \nParent : %d \nStart : %d \nEnd : %d \nLink : %d" , 
        block_list[index].id, block_list[index].parent, block_list[index].start, block_list[index].end, block_list[index].link);
    }
    // else traverse list until either appropriate hole is found or the end of the list is reached
    else {
        // need to fill this in 
    }

	// reduce remaining available memory and return
    remaining -= temp_block_size;



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
<<<<<<< HEAD
    PrintAllocationTable();

=======

	PrintAllocationTable();
>>>>>>> a0b2ef93bddae3f292ae2263fce44fa16ac40f81
	return;
}

/*
int FindTableHead() {
    int i;
    int head = NULL;

    for(i = 0; i < pm_size; i++) {
        // if the block is initalized
        if(block_list[i].id != NULL) {
            if(block_list[i].parent != NULL) {
                printf("\nFound head of blocks");
                return block_list[i].id;
            }
        }
    }
    return head;
}
*/

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