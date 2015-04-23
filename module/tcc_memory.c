#include "tcc_memory.h"

/* tcc_memory.c 
 * Includes the kernel memory allocator for TCC kernel module
 * Author: James Whang
 * Last Updated: 4/23/2015
 */

void * tcc_kmalloc(size_t n)
{
    return __vmalloc(n, GFP_ATOMIC, PAGE_KERNEL_EXEC);
}

void * tcc_krealloc(void *p, size_t n)
{
    return krealloc(p, n, GFP_ATOMIC);
}
