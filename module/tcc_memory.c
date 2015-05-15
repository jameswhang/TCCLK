/* tcc_memory.c 
 * Includes the kernel memory allocator for TCC kernel module
 * Author: James Whang
 * Last Updated: 5/12/2015
 */

#include "tcc_memory.h"
#include "tcc_page.h"

// global variable to keep track of the map
tcc_page_t * g_map = NULL;
ptr_size_pair_t * g_dict = NULL;

void * tcc_kmalloc(size_t size)
{
    if ((size + sizeof(tcc_page_t*)) > PAGESIZE) {
        return NULL;
    }

    if (size < sizeof(tcc_page_t)) {
        size = sizeof(tcc_page_t);
    }

    if (g_map == NULL) {
        g_map = get_page();
        new_page(g_map);
    }

    void * ret = find_space(size);
    page_info_t * basepage = BASEADDR(ret);
    basepage->buffer_count++;
    return ret;
}

void * tcc_krealloc(void *p, size_t n)
{
    return krealloc(p, n, GFP_ATOMIC);
}

void tcc_free(void *p)
{
    size_t n = find_size_pair(p); // jwhang: TODO, implement this.
    add_pair(p, n); // new pair of free memory
    coalesce(p, n); // coalesce the memory space
}

void new_page(tcc_page_t* page)
{
    *((tcc_page_t **)page->ptr) = page;
    page_info_t * pageinfo = (page_info_t*)(page->ptr);
    pageinfo->page_count = 0;
    pageinfo->buffer_count = 0;
    pageinfo->entry = (pair_t*)((long int)pageinfo + sizeof(page_info_t));
    pageinfo->page = page;
    add_pair((void*)(pageinfo->entry), (PAGESIZE-sizeof(page_info_t)));
}

// find_size_pair
// currently there is no way of keeping track of how much memory is allocated in each pointer. Need this in order to free them later.
// May need an extra struct to keep track of this pair
size_t find_size_pair(void *p)
{
    // TODO
    
}

// Takes in a pointer to base of block and size, and adds a node to the linked list of a pair
void add_pair(void * base, size_t size) 
{
  page_info_t * pageinfo = (page_info_t*)(g_rmap->ptr);
  void * entry = (pair_t*)(pageinfo->entry);
  
  ((pair_t*)base)->size = size;
  ((pair_t*)base)->prevblock = NULL;
  
  if(base < entry) // CASE WHERE THE NEW BLOCK IS LESS THAN THE ENTRY TO LIST 
  {
    ((pair_t*)entry)->prevblock = base; // Update the prev of what used to be first node
    ((pair_t*)base)->nextblock = entry; // Update the next of new first node
    pageinfo->entry = (pair_t*)base; // Update the linked list entry pointer in g_rmap
  } else if (base == entry) // CASE WHERE PAGE IS COMPLETELY EMPTY (PROBABLY NEW PAGE)
  {
    ((pair_t*)base)->nextblock = NULL; 
  } else  // ALL THE OTHER CASES
  {
    // Find where to put it in the linked list 
    while(((pair_t*)entry)->nextblock != NULL && entry < base) // Loop till right address is found
    {
      entry = ((pair_t*)entry)->nextblock; 
    }
    void * entry_next = ((pair_t*)entry)->nextblock;
    if(entry_next != NULL) // if the next block isn't null, set its prevblock as base
    { 
      ((pair_t*)entry_next)->prevblock = base; 
    }
    ((pair_t*)entry)->nextblock = base; // add the base into the linked list
    ((pair_t*)base)->prevblock = entry;
    ((pair_t*)base)->nextblock = entry_next;
  }
}


// takes a pointer to the base that needs to be freed and removes its pair from the linked list
void remove_pair(void * base) 
{
    void * ptr = (pair_t*)base;
    void * ptr_prev = ((pair_t*)ptr)->prevblock;
    void * ptr_next = ((pair_t*)ptr)->nextblock;

    if (ptr_prev != NULL && ptr_next != NULL) {
        ptr_prev->nextblock = ptr_next;
        ptr_next->prevblock = ptr_prev;
        return;
    } else if (ptr_prev == NULL) {
        ptr_next->prevblock = NULL;
        page_info_t * pageinfo = (page_info_t*)(g_map->ptr);
        pageinfo->entry = ptr_next;
        return;
    } else if (ptr_next == NULL) {
        ptr_prev->next = NULL;
    } else {
        page_info_t * pageinfo = (page_info_t*)(g_map->ptr);
        pageinfo->entry = NULL;
        g_map = NULL;
        return;
    }
}

// finds appropriate space and returns the pointer to the space
void * find_space(size_t size)
{
    page_info_t * pageinfo = (page_info_t*)(g_map->ptr);
    pair_t * npair = (pair_t*)(pageinfo->entry);
    while (npair != NULL) {
        if (pair->size < size) {
            npair = (pair_t*)(npair->nextblock);
            continue;
        } else if (npair->size == size || npair->size - size < sizeof(pair_t)) {
            delete_pair(npair);
            return ((void*)npair);
        } else {
            add_pair((void*)((long int)npair + size), (npair->size - size));
            delete_pair(npair);
            return ((void*)npair);
        }
    }
    // no more space left. allocate new page and try again.
    tcc_page_t * newpage = get_page();
    new_page(newpage);
    pageinfo->page_count++;
    return find_space(size);
}

// coalesce the memory space and free pages that don't need to be there
void coalesce(void * ptr)
{
    page_info_t * basepage = BASEADDR(ptr);
    basepage->buffer_count--;

    page_info_t * firstpage = (page_info_t*)(g_map->ptr);
    page_info_t * lastpage;

    int end = firstpage->page_count;
    int iteratve = 1

    while (iterate) {
        lastpage = ((page_info_t*)((long int)firstpage + end * PAGESIZE));
        iterate = 0;
        if (lastpage->buffer_count == 0) {
            iterate = 1;
            pair_t * temp;
            for (temp = firstpage->entry; temp != NULL; temp = temp->nextblock) {
                if (BASEADDR(temp) == lastpage) delete_pair(temp);
            }
            iterate = 1;
            if (lastpage == firstpage) {
                iterate = 0;
                g_map = NULL;
            }
            free_page((tcc_page_t*)(lastpage->page));
            if (g_map != NULL) {
                firstpage->page_count--;
            }
        }
        end--;
    }
}
