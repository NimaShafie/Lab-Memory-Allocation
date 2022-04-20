/*
Lab 4 - Memory Allocation
Comp 322/L
Nima Shafie
Date Here

Description:
To simulate memory allocation with hole-fitting algorithms (First-fit, Best-fit)
and implement deallocation anddefragmentation of memory blocks.

� First-fit: Allocate the first hole that is big enough
� Best-fit: Allocate the smallest hole that is big enough; must search entire list, unless ordered by size
(Produces the smallest leftover hole)
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

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
	struct node* link;
} *block_list = NULL;

typedef struct node block_type;

// declare linked list to connect allocation block

// declare global variables
int pm_size = -1;
int remaining;
// replace below with enum for better understanding
//int hole_algo = -1;

enum hole_algorithm { def = -1, first_fit = 0, best_fit = 1 } hole_algorithm;

/********************************************************************/
void EnterParameters() {
	// declare local variables (if any)
	int dummy = 0;
	int algorithm_choice = -1;

	// prompt for size of physical memory and choice of hole-fitting algorithm (0=first-fit, 1=best-fit)
	printf("Enter size of physical memory: ");
	scanf("%d", &pm_size);
	while (pm_size <= 0) {
		printf("Size of physical memory must be greater than 0\n");
		printf("Enter size of physical memory: ");
		scanf("%d", &pm_size);
	}
	remaining = pm_size;

	// this line below is being skipped, we need to set up this while loop differently to work with enums
	while (algorithm_choice != 0 && algorithm_choice != 1) {
		printf("Enter hole-fitting algorithm (0 = First Fit, 1 = Best-Fit): ");
		scanf("%d", &algorithm_choice);
	}
	hole_algorithm = algorithm_choice;

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

	printf("\n");
	// initialize remaining memory
	// why is this sizeof(x) different than above??
	/*
	block_list = (block_type*)malloc(remaining * sizeof(block_list));
	if (block_list == NULL) {
		printf("\nNot able to allocate enough memory, terminating program.\n\n");
		exit(0);
	}
	*/

	// initilize linked list with "dummy" block of size 0
	block_list[dummy].id = -1;
	block_list[dummy].parent = -1;
	block_list[dummy].start = 0;
	block_list[dummy].end = 0;
	block_list[dummy].link = NULL;

	return;
}


/********************************************************************/
void PrintAllocationTable() {
	// declare local variables
	int index = 0;
	block_type* table = block_list;

	// print table containing block id, starting address, ending address
	printf("\nID\tStart\tEnd\n");
	printf("-----------------------------\n");
	while (table != NULL) {
		if (table[index].id >= 0) {
			printf("%d", table[index].id);
			printf("\t%d", table[index].start);
			printf("\t%d", table[index].end);
			printf("\n");
		}
		table = table->link;
	}
	// remove this when done debugging
	printf("\nRemaining: %d\n\n", remaining);
	return;
}


/********************************************************************/
void AllocteBlockMemory() {
	// declare local variables
	int dummy = 0;
	int index = 1;
	int temp_block;
	int temp_block_size;
	bool duplicate_id = false;
	bool hole_found = false;
	block_type* table = block_list;
	block_type* temp = block_list;

	PrintAllocationTable();
	printf("\n");
	 
	// initialize best hole so far to size of physical memory

	// prompt for block id & block size
	printf("Enter block id: ");
	scanf("%d", &temp_block);
	// scan through list of current block ID's to ensure no duplicates exist
	while (temp_block < 0 || duplicate_id) {
		// block id entered cannot match another block id in the system
		for (block_list[0].link->link; block_list->link != NULL, block_list = block_list->link;) {
			if (temp_block == block_list->id) {
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
	while (temp_block_size > remaining) {
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

	struct node* new_block = (block_type*)malloc(sizeof(block_type));
	new_block->id = temp_block;
	new_block->link = NULL;
	new_block->start = 0;
	new_block->end = 0;
	new_block->parent = 0;
	// block_list = (block_type*)malloc(pm_size * sizeof(block_type));
	//block_list = (block_type*)malloc(remaining * sizeof(block_list));
	// struct node *link = (struct node*) malloc(sizeof(struct node));

	// if we got here, we're going to create something
	if (block_list->link == NULL) {
		printf("\nEXPER, this is the first block, adding it now.\n");
		block_list->link = new_block;
		new_block->parent = block_list->id;
		new_block->start = block_list->end;
		new_block->end = temp_block_size + block_list->end;
	}

	PrintAllocationTable();
	printf("\n");


	// if only "dummy" block exists, insert block at end of linked list, set fields, return
	// this applies for either algorithm we're working with
	if (block_list[dummy].link == NULL) {
		block_list[dummy].link = &block_list[index];
		block_list[index].id = temp_block;
		block_list[index].parent = block_list[dummy].id;
		block_list[index].start = 0;
		block_list[index].end = temp_block_size;
		block_list[index].link = NULL;

		// back up of above in array implementation
		/*
		if (block_list[dummy].link == NULL) {
		block_list[dummy].link = &block_list[index];
		block_list[index].id = temp_block;
		block_list[index].parent = block_list[dummy].id;
		block_list[index].start = 0;
		block_list[index].end = temp_block_size;
		block_list[index].link = NULL;
		*/

		printf("\nWe should only be here if the block_list is NULL\n");
		
		/*
		printf("\nID : %d \nParent : %d \nStart : %d \nEnd : %d \nLink : %p",
			block_list[index].id, block_list[index].parent,
			block_list[index].start, block_list[index].end, block_list[index].link);
		*/
	}
	// else traverse list until either appropriate hole is found or the end of the list is reached
	else {
		// based on which algorithm we're using... 0 = first-fit, else = best-fit
		// First-fit: Allocate the first hole that is big enough
		// if (hole_algo == 0) {
		if (hole_algorithm == first_fit) {
			// iterate through linked list, as soon as you find an opening, test it
			// to confirm opening, see if the end block of previous block is equal to start block of next block
			// start = 50, end = 100, temp_block_size = 50, we've found our target
			// in other words, (end - start) >= temp_block_size, insert that ID right after the
			while (!hole_found) {
				// we only continue here if we have at least two elements in the list
				if (table->link->link != NULL) {
					printf("\nDetermined we have at least two elements in the list.\n");
					// we can fit the block in a hole iff
					// next elements ending size - current elements starting size >= element to be added size
					if ((table->link->end - table->start) >= (temp_block_size)) {
						printf("\nblock can fit between two blocks! adding it now\n");
						// create add node function here

						block_list[index].link = &block_list[temp_block];
						block_list[temp_block].id = temp_block;
						block_list[temp_block].start = block_list[index].end;
						block_list[temp_block].end = block_list[temp_block].start + temp_block_size;
						block_list[temp_block].link = NULL;
						hole_found = true;
					}
				}

				// no other links left, so we will insert the block after this current one
				if (table->link == NULL) {
					printf("\nWe've determined no other blocks fit the requirements/exist, we're going to insert"
						"the block at the end of the linked list now.\n");
					printf("\nDisabled this for now\n");
					/*
					block_list->link = &block_list;
					block_list->id = temp_block;
					block_list->start = block_list[index].end;
					block_list[temp_block].end = block_list[temp_block].start + temp_block_size;
					block_list[temp_block].link = NULL;
					hole_found = true;
					*/
				}

				// backup of working array method using linked list
				/*
				// no other links left, so we will insert the block after this current one
				if (table->link == NULL) {
					printf("\nWe've determined no other blocks fit the requirements/exist, we're going to insert"
						"the block at the end of the linked list now.\n");
					block_list[index].link = &block_list[temp_block];
					block_list[temp_block].id = temp_block;
					block_list[temp_block].start = block_list[index].end;
					block_list[temp_block].end = block_list[temp_block].start + temp_block_size;
					block_list[temp_block].link = NULL;
					hole_found = true;
				}
				*/

				// iterate here
				// should probably test this sometime to see if its behaving correctly
				table = table->link;
			}
		}

		// best-fit (must search entire list, unless ordered by size, produces the smallest leftover hole)
		// Best-fit: Allocate the smallest hole that is big enough
		else {

		}


		printf("\nAttempting to add another block_list but this code hasn't been written yet\n");
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
	PrintAllocationTable();

	return;
}

// find table head function - probably need to erase this after working
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
	int temp_block;
	int found_index = 0;
	bool found_block = false;
	bool last_block = false;
	block_type* table = block_list;

	// prompt for block id
	printf("Enter Block ID: ");
	scanf("%d", &temp_block);
	while (temp_block < 0) {
		printf("Invalid ID, Block ID must be non-negative.\n");
		printf("Enter block ID: ");
		scanf("%d", &temp_block);
	}


	// THE PROBLEM IS
	/*
	table[0].id == -1
	table[1].id == 3
	we need a counter to determine how many times we iterate through the table, then we use
	table[count] and remove that one
	*/

	// until end of linked list is reached or block id is found 
	while (table != NULL && !found_block) {
		// if found the block id
		if (table->id == temp_block) {
			found_block = true;
			//printf("\nTest to show im not insane: table[0].id = %d\n\n", table[0].id);
			//printf("\nTest to show im not insane: block_list[dummy].id = %d\n\n", block_list[0].id);
			// for debugging
			printf("\nThe ID we're going to remove is = %d\n", block_list[found_index].id);
			printf("\nFound ID : %d\n", found_index);
			// --
			if (table->link == NULL) last_block = true;
		}
		if (!found_block) {
			found_index++;
			table = table->link;
		}
	}

	// if end of linked list reached, print block id not found
	if (!found_block) {
		printf("\nBlock ID not found\n");
	}
	// else remove block and deallocate memory
	else {
		// base case, if the block to remove is the last one, we don't alter the next block
		if (last_block) {		// fatal null error
			remaining = (block_list[found_index].end - block_list[found_index].start);
			// ID of -2 represents an empty block
			block_list[found_index].id = -2;
			block_list[found_index].link = NULL;
			block_list[found_index].parent = 0;
			block_list[found_index].end = 0;
		}
	}

	// problem is we're just nulling out and 0'ing out the values, but the element itself into null
	// so it still appears on the print table function

	printf("\nWhat is table on right now?: %d", table->id);

	printf("\n");
	PrintAllocationTable();
	printf("\n");
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