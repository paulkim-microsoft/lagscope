#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#define LAGSCOPE_PERCENTILE_STATUS_OK			    0
#define LAGSCOPE_PERCENTILE_MEM_ALLOCATION_FAILED	1
#define LAGSCOPE_PERCENTILE_STATUS_FAILED		    2

void show_percentile(unsigned long *lat_array, unsigned long count_size, unsigned long lat_array_size);
int count_sort(unsigned long *lat_array, unsigned long count_size, unsigned long lat_array_size);
int get_percentile_index(double percentile, unsigned long arr_size);