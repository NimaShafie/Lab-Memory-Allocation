/*
Lab 4 - Memory Allocation
Comp 322/L
Nima Shafie
Date Here

Description:
To simulate memory allocation with hole-fitting algorithms (First-fit, Best-fit)
and implement deallocation anddefragmentation of memory blocks.

• First-fit: Allocate the first hole that is big enough
• Best-fit: Allocate the smallest hole that is big enough; must search entire list, unless ordered by size
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


// global variables above *******************************************/


// option 1
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
	if (block_list == NULL) {
		printf("\nNo memory is allocated.\n\n");
		exit(0);
	}
	printf("\n");
	// initilize linked list with "dummy" block of size 0
	block_list[dummy].id = -1;
	block_list[dummy].start = 0;
	block_list[dummy].end = 0;
	block_list[dummy].link = NULL;

	return;
}


/********************************************************************/
void PrintAllocationTable() {
	// declare local variables
	block_type* table = block_list;

	// print table containing block id, starting address, ending address
	printf("\nID\tStart\tEnd\n");
	printf("-----------------------------\n");
	while (table != NULL) {
		// below if statement is to not print out the head (dummy) of the linked list
		if (table->id >= 0) {
			printf("%d", table->id);
			printf("\t%d", table->start);
			printf("\t%d", table->end);
			printf("\n");
		}
		table = table->link;
	}
	// remove this when done debugging
	printf("\nRemaining: %d\n\n", remaining);
	return;
}


// option 2
/********************************************************************/
void AllocteBlockMemory() {
	// declare local variables
	int temp_block;
	int temp_block_size;
	int temp_smallest_hole_size = pm_size;
	bool duplicate_id = false;
	bool invalid_id = false;
	bool hole_found = false;
	bool smallest_hole = false;
	block_type* tmp_scan = block_list;
	block_type* current = block_list;
	block_type* previous = current;

	// prompt for block id & block size
	printf("Enter block id: ");
	scanf("%d", &temp_block);
	do {
		invalid_id = false;
		duplicate_id = false;
		if (temp_block < 0) invalid_id = true;
		// scan through list of current block ID's to ensure no duplicates exist
		while (tmp_scan != NULL && !invalid_id) {
			// below if statement is to not print out the head (dummy) of the linked list
			if (tmp_scan->id == temp_block) duplicate_id = true;
			tmp_scan = tmp_scan->link;
		}

		// block id must not be a duplicate
		if (duplicate_id) {
			printf("\nBlock ID cannot match an existing id.\n\n");
			printf("Enter block id: ");
			scanf("%d", &temp_block);
		}
		// block id entered must be >= 0
		else if (invalid_id) {
			printf("\nBlock ID must be non-negative.\n\n");
			printf("Enter block id: ");
			scanf("%d", &temp_block);
		}
		tmp_scan = block_list;
	} while (duplicate_id || invalid_id);
	
	// block size must be greater than 0
	printf("Enter block size: ");
	scanf("%d", &temp_block_size);
	while (temp_block_size <= 0) {
		printf("\nBlock size must be greater than 0\n");
		printf("Enter block size: ");
		scanf("%d", &temp_block_size);
	}

	// check if size of block is larger than remaining unallocated space, if so, print message and return
	if (temp_block_size <= remaining) {
		// allocation of a new block into the linked list
		struct node* new_block = (block_type*)malloc(sizeof(block_type));
		new_block->id = temp_block;
		new_block->link = NULL;
		new_block->start = 0;
		new_block->end = 0;

		// if only "dummy" block (head) exists, insert block at end of linked list, set fields, return
		// this applies for either algorithm we're working with
		if (current->link == NULL) {
			//printf("\nThis is the first block, adding it now.\n");
			current->link = new_block;
			new_block->start = current->end;
			new_block->end = temp_block_size + current->end;
		}

		// else traverse list until either appropriate hole is found or the end of the list is reached
		else {
			// based on which algorithm we're using first-fit, or best-fit

			// First-fit: Allocate the first hole that is big enough
			if (hole_algorithm == first_fit) {
				// iterate through linked list, as soon as you find an opening, test it
				// to confirm opening, see if the end block of previous block is equal to start block of next block
				// start = 50, end = 100, temp_block_size = 50, we've found our target
				// in other words, (end - start) >= temp_block_size, insert that ID right after the
				while (!hole_found) {
					// only one block left over
					if (current->link == NULL) {
						current->link = new_block;
						new_block->start = current->end;
						new_block->end = temp_block_size + current->end;
						hole_found = true;
					}

					if (!hole_found) current = current->link;

					// comparing previous to start to figure out if we need to insert the new block between the two
					// compare head with next child
					if (previous->end != current->start) {
						if ((current->start - previous->end) >= (temp_block_size)) {
							previous->link = new_block;
							new_block->link = current;
							new_block->start = previous->end;
							new_block->end = new_block->start + temp_block_size;
							hole_found = true;
						}
					}
					if (!hole_found) {
						previous = current;
					}
				}
			}
			// best-fit (must search entire list, unless ordered by size, produces the smallest leftover hole)
			// Best-fit: Allocate the smallest hole that is big enough
			else {
				while (!hole_found) {
					// only one block left over
					if (current->link == NULL) {
						current->link = new_block;
						new_block->start = current->end;
						new_block->end = temp_block_size + current->end;
						hole_found = true;
					}

					if (!hole_found) current = current->link;

					// comparing previous to start to figure out if we need to insert the new block between the two
					// compare head with next child
					if (previous->end != current->start) {
						if ((current->start - previous->end) >= (temp_block_size)) {
							previous->link = new_block;
							new_block->link = current;
							new_block->start = previous->end;
							new_block->end = new_block->start + temp_block_size;
							hole_found = true;
						}
					}
					if (!hole_found) {
						previous = current;
					}
				}
			}
		}
		// reduce remaining available memory and return
		remaining -= temp_block_size;
	}

	else {
		printf("Cannot initialize more memory than current existing memory.\n");
		printf("Current Existing = %d \t Asking for = %d\n", remaining, temp_block_size);
	}

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


// option 3
/********************************************************************/
void DeallocteBlockMemory() {
	// declare local variables
	int temp_block;
	bool found_block = false;
	bool last_block = false;
	block_type* current = block_list;
	block_type* previous = NULL;

	// prompt for block id
	printf("Enter Block ID: ");
	scanf("%d", &temp_block);
	while (temp_block < 0) {
		printf("Invalid ID, Block ID must be non-negative.\n");
		printf("Enter block ID: ");
		scanf("%d", &temp_block);
	}

	while (current != NULL && !found_block) {
		// below if statement is to not print out the head (dummy) of the linked list
		if (current->id == temp_block) {
			printf("\nFound ID to remove : %d\n", current->id);
			found_block = true;
			if (current->link == NULL) last_block = true;
		}
		if (!found_block) {
			previous = current;
			current = current->link;
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
			remaining += (current->end - current->start);		// fatal null error
		}
		// the target block is not the last one, so we connect the previous element to this one now
		else {
			remaining += (current->end - current->start);
			previous->link = current->link;
		}
	}
	// free memory from node out of linked list
	free(current);
	printf("\n");
	PrintAllocationTable();
	printf("\n");
	return;
}


// option 4
/********************************************************************/
void DefragmentMemory() {
	// declare local variables
	bool last_block = false;
	block_type* current = block_list;
	block_type* previous = current;
	int block_size = 0;

	// until end of list is reached
	// calculate current hole size
	// adjust start & end fields of current block to eliminate hole
	while (current != NULL && !last_block) {
		if (current->link == NULL) last_block = true;
		current = current->link;
		// hole in memory found, we will defrag this now
		if (!last_block) {
			if (previous->end != current->start) {
				block_size = (current->end - current->start);
				current->start = previous->end;
				current->end = current->start + block_size;
			}
			previous = current;
		}
	}
	printf("\n");
	PrintAllocationTable();
	return;
}


// option 5
/*******************************************************************/
void FreeMemoryQuitProgram(struct node* head) {
	// if node is NULL, return
	if (head == NULL) return;
	// else
		// recursively call procedure on node->link
		// deallocate memory from node
	else {
		FreeMemoryQuitProgram(head->link);
		free(head);
	}
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
			FreeMemoryQuitProgram(block_list);
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