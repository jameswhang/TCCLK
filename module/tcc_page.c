/* tcc_page.c
 * Logic for allocation of pages
 */

#include "tcc_page.h"

static tcc_page_stat_t tcc_page_stats = { 0, 0, 0, PAGESIZE };

tcc_page_t * get_page() {
    static int id = 0;
    tcc_page_t * res;

    tcc_page_stats.num_requested++;
    tcc_page_stats.num_in_use++;
    
    res = (tcc_page_t *) malloc(sizeof(tcc_page_t));
    res->id = id++;
    res->size = tcc_page_stats.page_size;
    res->ptr = allocate_exec_page();

    assert(res->ptr != NULL);

    return res;
}

void free_page(tcc_page_t* ptr)
{
  assert(ptr != NULL);
  assert(ptr->ptr != NULL);
  assert(kma_page_stats.num_in_use > 0);
  // jwhang TODO: check if the address is a page addresss
  //
  tcc_page_stats.num_freed++;
  tcc_page_stats.num_in_use--;
  
  freePage(ptr->ptr);
  free(ptr);
}

tcc_page_stat * page_stats()
{
  static kma_page_stat_t stats;
  
  return memcpy(&stats, &kma_page_stats, sizeof(kma_page_stat_t));
}

