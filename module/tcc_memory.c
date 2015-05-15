/* tcc_memory.c 
 * Includes the kernel memory allocator for TCC kernel module
 * Author: James Whang
 * Last Updated: 5/12/2015
 */

#include "tcc_memory.h"

typedef struct {
    void * nextblock;
} buffer_t;

typedef struct {
    buffer_t * header;
} buffer_list_t;

typedef struct page_node_struct {
    tcc_page_t* page;
    struct page_node_struct * next;
} page_node_t;

typedef struct 
void * tcc_kmalloc(size_t n)
{
    return __vmalloc(n, GFP_ATOMIC, PAGE_KERNEL_EXEC);
}

void * tcc_krealloc(void *p, size_t n)
{
    return krealloc(p, n, GFP_ATOMIC);
}

void * tcc_free(void *p)
{
    // TODO
}
