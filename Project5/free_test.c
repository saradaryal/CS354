

/******************************************************************************
 * FILENAME: free_test.c
 * AUTHOR:   sarad@cs.wisc.edu <Sarad Aryal>
 * DATE:     08 Aug 2020
 * PROVIDES: Contains a main function to test Mem_free in  mem.c
 * *****************************************************************************/


#include <assert.h>
#include <stdlib.h>
#include "mem.h"

int main() {
   	void* ptr = Mem_Alloc(12);
	assert(ptr != NULL);
	assert(Mem_Free(ptr) == 0);
    assert(Mem_Free(NULL)== -1);
  	exit(0);
}
