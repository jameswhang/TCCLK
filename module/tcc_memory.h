#include <unistd.h>

/*** pair_t *****/
/* Used to keep the pair <base, size> resource map entries. Has a linked list form */
typedef struct
{
    int size;
    void * nextblock;
    void * prevblock;
} pair_t; 

/*** page_info_t ***/
/* Contains necessary information about the page. Makes life easier when freeing & coalescing pages. */
typedef struct
{
    int buffer_count;
    int page_count;
    pair_t * entry;
    void * page;
} page_info_t;

/*** ptr_size_pair_t **/
/* a type of linked list. contains the mapping pointer to their size */
typedef struct ptr_size_pair
{
    size_t size;
    void * ptr;
    ptr_size_pair * next;
} ptr_size_pair_t;

size_t PAGESIZE = getpagesize();  // kinda a bad thing to define this globally.. should probably figure out a way to do this with MACRO but still adapt to different machines paging settings.

/*** Function prototypes ***/
void * tcc_kmalloc(size_t n);
void * tcc_krealloc(void *p, size_t n);
void tcc_free(void *p)
