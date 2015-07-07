//#include <unistd.h>
#include "tcc_page.h"
#include <stddef.h>

/*** pair_t *****/
/* Used to keep the pair <base, size> resource map entries. Has a linked list form */
typedef struct tcc_pair
{
    int size;
    void * nextblock;
    void * prevblock;
} tcc_pair_t; 

/*** page_info_t ***/
/* Contains necessary information about the page. Makes life easier when freeing & coalescing pages. */
typedef struct tcc_page_info
{
    int buffer_count;
    int page_count;
    tcc_pair_t * entry;
    void * page;
} tcc_page_info_t;

/*** ptr_size_pair_t **/
/* a type of linked list. contains the mapping pointer to their size */
typedef struct tcc_ptr_size_pair
{
    size_t size;
    void * ptr;
    struct tcc_ptr_size_pair * next;
} tcc_ptr_size_pair_t;

//size_t PAGESIZE = getpagesize();  // kinda a bad thing to define this globally.. should probably figure out a way to do this with MACRO but still adapt to different machines paging settings.

size_t PAGESIZE = 4096;

/*** Function prototypes ***/
void * tcc_kmalloc(size_t n);
void * tcc_krealloc(void *p, size_t n);
void tcc_free(void *p);

void new_page(tcc_page_t *page);
size_t find_size_pair(void *p);
void add_size_pair(void *p, size_t size);
int remove_size_pair(void *p, size_t size);
void add_pair(void * base, size_t size);
void remove_pair(void * base);
void *find_space(size_t size);
void coalesce(void *ptr);
