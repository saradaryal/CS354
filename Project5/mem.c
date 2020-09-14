/******************************************************************************
 * FILENAME: mem.c
 * AUTHOR:   sarad@cs.wisc.edu <Sarad Aryals>
 * DATE:     08 Aug 2020
 * PROVIDES: Contains a set of library functions for memory allocation
 * *****************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include "mem.h"

int fit;

/* this structure serves as the header for each block */
typedef struct block_hd{
  /* The blocks are maintained as a linked list */
  /* The blocks are ordered in the increasing order of addresses */
  struct block_hd* next;

  /* size of the block is always a multiple of 4 */
  /* ie, last two bits are always zero - can be used to store other information*/
  /* LSB = 0 => free block */
  /* LSB = 1 => allocated/busy block */

  /* So for a free block, the value stored in size_status will be the same as the block size*/
  /* And for an allocated block, the value stored in size_status will be one more than the block size*/

  /* The value stored here does not include the space required to store the header */

  /* Example: */
  /* For a block with a payload of 24 bytes (ie, 24 bytes data + an additional 8 bytes for header) */
  /* If the block is allocated, size_status should be set to 25, not 24!, not 23! not 32! not 33!, not 31! */
  /* If the block is free, size_status should be set to 24, not 25!, not 23! not 32! not 33!, not 31! */
  int size_status;

}block_header;

/* Global variable - This will always point to the first block */
/* ie, the block with the lowest address */
block_header* list_head = NULL;


/* Function used to Initialize the memory allocator */
/* Not intended to be called more than once by a program */
/* Argument - sizeOfRegion: Specifies the size of the chunk which needs to be allocated 
   	      policy: indicates the policy to use eg: best fit is 0*/
/* Returns 0 on success and -1 on failure */
int Mem_Init(int sizeOfRegion,  int policy)
{
  int pagesize;
  int padsize;
  int fd;
  int alloc_size;
  void* space_ptr;
  static int allocated_once = 0;
  
  if(0 != allocated_once)
  {
    fprintf(stderr,"Error:mem.c: Mem_Init has allocated space during a previous call\n");
    return -1;
  }
  if(sizeOfRegion <= 0)
  {
    fprintf(stderr,"Error:mem.c: Requested block size is not positive\n");
    return -1;
  }

  /* Get the pagesize */
  pagesize = getpagesize();

  /* Calculate padsize as the padding required*/ 
  /*to round up sizeOfRegion to a multiple of pagesize */
  padsize = sizeOfRegion % pagesize;
  padsize = (pagesize - padsize) % pagesize;

  alloc_size = sizeOfRegion + padsize;

  /* Using mmap to allocate memory */
  fd = open("/dev/zero", O_RDWR);
  if(-1 == fd)
  {
    fprintf(stderr,"Error:mem.c: Cannot open /dev/zero\n");
    return -1;
  }
  space_ptr = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  if (MAP_FAILED == space_ptr)
  {
    fprintf(stderr,"Error:mem.c: mmap cannot allocate space\n");
    allocated_once = 0;
    return -1;
  }
  
  allocated_once = 1;
  
  /* To begin with, there is only one big, free block */
  list_head = (block_header*)space_ptr;
  list_head->next = NULL;
  /* Remember that the 'size' stored in block size excludes the space for the header */
  list_head->size_status = alloc_size - (int)sizeof(block_header);
  fit = policy;
  return 0;
}


/* Function for allocating 'size' bytes. */
/* Returns address of allocated block on success */
/* Returns NULL on failure */
/* Here is what this function should accomplish */
/* - Check for sanity of size - Return NULL when appropriate */
/* - Round up size to a multiple of 4 */
/* - Traverse the list of blocks and allocate the best free block which can accommodate the requested size */
/* -- Also, when allocating a block - split it into two blocks when possible */
/* Tips: Be careful with pointer arithmetic */

void* Mem_Alloc(int size)
{
   /**
     * check if the size is less than 0, if it is 
     * return NULL
    */
    if (size <= 0) {
        return NULL;
    }
    int new_size;
    
    /*  round up the size to the multiple of 4 */
    if (size % 4 == 0) {
       new_size = size;
    } else {
       new_size = size + 4 - (size % 4);
    }
    
    block_header* curr_node = list_head;
    block_header* best_block = NULL;
    int curr_NodeSize;
    
    /**
     *  set maxBlockSize to longest int value.
     */
    int max_BlockSize = 2147483647;
    
    while (curr_node != NULL) {
        curr_NodeSize = curr_node->size_status;
        if ((!(curr_NodeSize & 1)) && (curr_NodeSize >=
                                  (int)(sizeof(block_header)) + new_size)) {
            /**
             *  If the criteria matches,  for the best fit candidate 
             *  The best fit candidate is updated to the current block
             */
            if (max_BlockSize > curr_NodeSize) {
                best_block = curr_node;
                max_BlockSize = curr_NodeSize;
            }
        }
        curr_node = curr_node->next;
    }
    /**
     *  Return null if none of the blocks could fit.l
     */
    if (best_block == NULL) {
        return NULL;
    } else {
        /**
         *  If possible, split the block into smaller blocks
         */
        if (max_BlockSize - new_size > ((int)sizeof(block_header))) {
            block_header* new = (block_header*)((int)(best_block) + new_size
                                                + (int)(sizeof(block_header)));
            new->size_status = max_BlockSize - (int)(sizeof(block_header))
                                                                + new_size;
            best_block->size_status = new_size + 1;
            new->next = best_block->next;
            best_block->next = new;
            return (block_header*)((int)(best_block)
                                   + (int)(sizeof(block_header)));
        } else {
            best_block->size_status++;
            return (block_header*)((int)(best_block)
                                  + (int)(sizeof(block_header)));
        }
    }
}
/* Function for freeing up a previously allocated block */
/* Argument - ptr: Address of the block to be freed up */
/* Returns 0 on success */
/* Returns -1 on failure */
/* Here is what this function should accomplish */
/* - Return -1 if ptr is NULL */
/* - Return -1 if ptr is not pointing to the first byte of a busy block */
/* - Mark the block as free */
/* - Coalesce if one or both of the immediate neighbours are free */
int Mem_Free(void *ptr)
{
    /*- If ptr is NULL returns -1 */
    if (ptr == NULL) {
        return -1;
    }
    /**
     *  Returns -1 if the pointer is two small. 
     */
    if (ptr < (void*)(sizeof(block_header))) {
        return -1;
    }

    block_header* currNode = list_head;
    block_header* prevsBlock = NULL;

    while (currNode != NULL) {

        if (currNode > (block_header*)(ptr - (int)(sizeof(block_header)))) {
            return -1;
        }
        if (currNode < (block_header*)(ptr - (int)(sizeof(block_header)))) {
            prevsBlock = currNode;
            currNode = currNode->next;
        } else {
            /**
             *  Delete the block if the block is busy. 
             */
            if (currNode->size_status & 1) {
                currNode->size_status--;
                /**
                 *  Coalesceing with the right neighbours.
                 */
                if (currNode->next != NULL) {
                    if (!(currNode->next->size_status & 1)) {
                        currNode->size_status += (int)(sizeof(block_header))
                            + currNode->next->size_status;

                        currNode->next = currNode->next->next;
                    }
                }
                /**
                 *  Coalesceing with the left neighbours.
                 */
                if (prevsBlock != NULL) {
                    if (!(prevsBlock->size_status & 1)) {
                        prevsBlock->size_status += (int)(sizeof(block_header)) +
                                    currNode->size_status;

                        prevsBlock->next = currNode->next;
                        currNode = prevsBlock;
                    }
                }
                /**
                 *  Retrns 0 if freeing was successful.
                 */
                return 0;
            }
        }
    }
    /**
     *  If there is any other issues, return -1.
     */
    return -1;

}

/* Function to be used for debug */
/* Prints out a list of all the blocks along with the following information for each block */
/* No.      : Serial number of the block */
/* Status   : free/busy */
/* Begin    : Address of the first useful byte in the block */
/* End      : Address of the last byte in the block */
/* Size     : Size of the block (excluding the header) */
/* t_Size   : Size of the block (including the header) */
/* t_Begin  : Address of the first byte in the block (this is where the header starts) */
void Mem_Dump()
{
  int counter;
  block_header* current = NULL;
  char* t_Begin = NULL;
  char* Begin = NULL;
  int Size;
  int t_Size;
  char* End = NULL;
  int free_size;
  int busy_size;
  int total_size;
  char status[5];

  free_size = 0;
  busy_size = 0;
  total_size = 0;
  current = list_head;
  counter = 1;
  fprintf(stdout,"************************************Block list***********************************\n");
  fprintf(stdout,"No.\tStatus\tBegin\t\tEnd\t\tSize\tt_Size\tt_Begin\n");
  fprintf(stdout,"---------------------------------------------------------------------------------\n");
  while(NULL != current)
  {
    t_Begin = (char*)current;
    Begin = t_Begin + (int)sizeof(block_header);
    Size = current->size_status;
    strcpy(status,"Free");
    if(Size & 1) /*LSB = 1 => busy block*/
    {
      strcpy(status,"Busy");
      Size = Size - 1; /*Minus one for ignoring status in busy block*/
      t_Size = Size + (int)sizeof(block_header);
      busy_size = busy_size + t_Size;
    }
    else
    {
      t_Size = Size + (int)sizeof(block_header);
      free_size = free_size + t_Size;
    }
    End = Begin + Size;
    fprintf(stdout,"%d\t%s\t0x%08lx\t0x%08lx\t%d\t%d\t0x%08lx\n",counter,status,(unsigned long int)Begin,
           (unsigned long int)End,Size,t_Size,(unsigned long int)t_Begin);
    total_size = total_size + t_Size;
    current = current->next;
    counter = counter + 1;
  }
  fprintf(stdout,"---------------------------------------------------------------------------------\n");
  fprintf(stdout,"*********************************************************************************\n");

  fprintf(stdout,"Total busy size = %d\n",busy_size);
  fprintf(stdout,"Total free size = %d\n",free_size);
  fprintf(stdout,"Total size = %d\n",busy_size+free_size);
  fprintf(stdout,"*********************************************************************************\n");
  fflush(stdout);
  return;
}




