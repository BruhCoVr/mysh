/**
 * @file myheap.h
 * @brief Custom heap memory management functions
 */

#ifndef MY_HEAP_H
#define MY_HEAP_H

#include <constants.h>

/**
 * @brief Allocates a block of memory of the specified size from the custom heap.
 * 
 * @param size The size of the memory block to allocate in bytes.
 * @return A pointer to the allocated memory block, or NULL if allocation fails.
 */
char *alloc(unsigned int size);

/**
 * @brief Frees all allocated memory in the custom heap.
 */
void free_all();

#endif
