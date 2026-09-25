#include <heap.h>

static char heap[HEAP_SIZE];
static char *freep = heap;

char *alloc(unsigned int size) {
    // if (freep + size > heap + HEAP_SIZE) {
    //     return handle_error("Not enough memory available in the heap");
    // }
    char *p = freep;
    freep += size;
    

    return p;
}

void free_all() {
    freep = heap;
}
