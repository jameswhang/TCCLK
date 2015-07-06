/* tcc_memory.c 
 * Includes the kernel memory allocator for TCC kernel module
 * Author: James Whang
 * Last Updated: 5/12/2015
 */

#include "tcc_memory.h"
#include "tcc_page.h"

// global variable to keep track of the map
tcc_page_t * g_map = NULL;
tcc_ptr_size_pair_t * g_ptr_list = NULL;

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
    tcc_page_info_t * basepage = BASEADDR(ret);
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
    if (n < 0) { 
        printk("TCC: ERROR WHEN FREEING POINTER AT ADDRESS %p\n", p);
        return;
    } else {
        add_pair(p, n); // new pair of free memory
        coalesce(p, n); // coalesce the memory space
    }
}

void new_page(tcc_page_t* page)
{
    *((tcc_page_t **)page->ptr) = page;
    tcc_page_info_t * pageinfo = (tcc_page_info_t*)(page->ptr);
    pageinfo->page_count = 0;
    pageinfo->buffer_count = 0;
    pageinfo->entry = (tcc_pair_t*)((long int)pageinfo + sizeof(tcc_page_info_t));
    pageinfo->page = page;
    add_pair((void*)(pageinfo->entry), (PAGESIZE-sizeof(tcc_page_info_t)));
}

// find_size_pair
// currently there is no way of keeping track of how much memory is allocated in each pointer. Need this in order to free them later.
// May need an extra struct to keep track of this pair
size_t find_size_pair(void *p)
{
    if (g_ptr_list == NULL) {
        return -1; //err
    }
    tcc_ptr_size_pair_t * tmp = g_ptr_list;
    while (tmp->ptr != p) {
        tmp = tmp->next;
    }
    return tmp->size; 
}

// add_size_pair
void add_size_pair(void *p, size_t size)
{
    if (g_ptr_list == NULL) {
        g_ptr_list = malloc(tcc_ptr_size_pair_t);
        g_ptr_list->size = size;
        g_ptr_list->ptr = p;
    } else {
        tcc_ptr_size_pair_t * tmp = g_ptr_list;
        tcc_ptr_size_pair_t * newpair = malloc(tcc_ptr_size_pair_t);
        newpair->size = size;
        newpair->ptr = p;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = newpair;
    }
}

// remove_size_pair
// removes the size pair node from the list 
void remove_size_pair(void *p, size_t size)
{
    if (g_ptr_list != NULL) {
        
    }
}

// Takes in a pointer to base of block and size, and adds a node to the linked list of a pair
void add_pair(void * base, size_t size) 
{
  tcc_page_info_t * pageinfo = (tcc_page_info_t*)(g_rmap->ptr);
  void * entry = (tcc_pair_t*)(pageinfo->entry);
  
  ((tcc_pair_t*)base)->size = size;
  ((tcc_pair_t*)base)->prevblock = NULL;
  
  if (base < entry) // CASE WHERE THE NEW BLOCK IS LESS THAN THE ENTRY TO LIST 
  {
    ((tcc_pair_t*)entry)->prevblock = base; // Update the prev of what used to be first node
    ((tcc_pair_t*)base)->nextblock = entry; // Update the next of new first node
    pageinfo->entry = (tcc_pair_t*)base; // Update the linked list entry pointer in g_rmap
  } else if (base == entry) // CASE WHERE PAGE IS COMPLETELY EMPTY (PROBABLY NEW PAGE)
  {
    ((tcc_pair_t*)base)->nextblock = NULL; 
  } else  // ALL THE OTHER CASES
  {
    // Find where to put it in the linked list 
    while(((tcc_pair_t*)entry)->nextblock != NULL && entry < base) // Loop till right address is found
    {
      entry = ((tcc_pair_t*)entry)->nextblock; 
    }
    void * entry_next = ((tcc_pair_t*)entry)->nextblock;
    if (entry_next != NULL) // if the next block isn't null, set its prevblock as base
    { 
      ((tcc_pair_t*)entry_next)->prevblock = base; 
    }
    ((tcc_pair_t*)entry)->nextblock = base; // add the base into the linked list
    ((tcc_pair_t*)base)->prevblock = entry;
    ((tcc_pair_t*)base)->nextblock = entry_next;
  }
}


// takes a pointer to the base that needs to be freed and removes its pair from the linked list
void remove_pair(void * base) 
{
    void * ptr = (tcc_pair_t*)base;
    void * ptr_prev = ((tcc_pair_t*)ptr)->prevblock;
    void * ptr_next = ((tcc_pair_t*)ptr)->nextblock;

    if (ptr_prev != NULL && ptr_next != NULL) {
        ptr_prev->nextblock = ptr_next;
        ptr_next->prevblock = ptr_prev;
        return;
    } else if (ptr_prev == NULL) {
        ptr_next->prevblock = NULL;
        tcc_page_info_t * pageinfo = (tcc_page_info_t*)(g_map->ptr);
        pageinfo->entry = ptr_next;
        return;
    } else if (ptr_next == NULL) {
        ptr_prev->next = NULL;
    } else {
        tcc_page_info_t * pageinfo = (tcc_page_info_t*)(g_map->ptr);
        pageinfo->entry = NULL;
        g_map = NULL;
        return;
    }
}

// finds appropriate space and returns the pointer to the space
void * find_space(size_t size)
{
    tcc_page_info_t * pageinfo = (tcc_page_info_t*)(g_map->ptr);
    tcc_pair_t * npair = (tcc_pair_t*)(pageinfo->entry);
    while (npair != NULL) {
        if (pair->size < size) {
            npair = (tcc_pair_t*)(npair->nextblock);
            continue;
        } else if (npair->size == size || npair->size - size < sizeof(tcc_pair_t)) {
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
    tcc_page_info_t * basepage = BASEADDR(ptr);
    basepage->buffer_count--;

    tcc_page_info_t * firstpage = (tcc_page_info_t*)(g_map->ptr);
    tcc_page_info_t * lastpage;

    int end = firstpage->page_count;
    int iteratve = 1

    while (iterate) {
        lastpage = ((tcc_page_info_t*)((long int)firstpage + end * PAGESIZE));
        iterate = 0;
        if (lastpage->buffer_count == 0) {
            iterate = 1;
            tcc_pair_t * temp;
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
