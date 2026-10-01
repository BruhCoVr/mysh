#include <heap.h>

static char heap[HEAP_SIZE];
static char *freep = heap;

char *alloc(unsigned int size) {
    if (freep + size > heap + HEAP_SIZE) {
        exit(1);  // Not enough space in the heap, exit the program
    }
    
    char *p = freep;
    freep += size;
    

    return p;
}

void free_all() {
    freep = heap;
}
