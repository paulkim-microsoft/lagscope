#include "countsort.h"

#define LAGSCOPE_PERCENTILE_STATUS_OK			0
#define LAGSCOPE_PERCENTILE_MEM_ALLOCATION_FAILED	1
#define LAGSCOPE_PERCENTILE_STATUS_FAILED		2

void show_percentile(unsigned long *lat_array, unsigned long count_size, unsigned long lat_array_size)
{
    int i = 0;
    int offset = 1;
	  int ret_val = LAGSCOPE_PERCENTILE_STATUS_FAILED;

	  ret_val = count_sort(lat_array, count_size, lat_array_size);
	
	  if(ret_val != LAGSCOPE_PERCENTILE_STATUS_OK)
		  return;

	  double percentile_array[] = {50, 75, 90, 99.9, 99.99, 99.999};
    size_t percentile_array_size = sizeof(percentile_array) / sizeof(percentile_array[0]);
    printf("\n\tPercentile\t   Latency(us)\n");
    for(i = 0; i < percentile_array_size; i++)
    {
        int percentile_idx = get_percentile_index(percentile_array[i], lat_array_size);
        printf("\t%f %%\t     %lu\n", (double) i, lat_array[percentile_idx - offset]);
    }

}

int count_sort(unsigned long *lat_array, unsigned long count_size, unsigned long lat_array_size)
{
    unsigned int *count_array = NULL;
    unsigned long j = 0;
    int k = 0;
    
    count_array = (unsigned int *)malloc(sizeof(unsigned int) * count_size);
    
    if (!count_array)
        return LAGSCOPE_PERCENTILE_MEM_ALLOCATION_FAILED;
        
    memset(count_array, 0, count_size * sizeof(unsigned int));

    for(j = 0; j < lat_array_size; j++)
    {
        count_array[lat_array[j]]++;
    }

    for(j = 0; j < count_size; j++)
    {
        while(count_array[j] != 0)
        {
            lat_array[k++] = j;
            count_array[j]--;
        }
    }

    if(count_array)
    {
        free(count_array);
        count_array = NULL;
    }
    
    return LAGSCOPE_PERCENTILE_STATUS_OK;
}

/* gets index of specified percentile in sorted array */
int get_percentile_index(double percentile, unsigned long arr_size)
{
    if(percentile == 100)
    {
        return arr_size - 1;
    }
    int index = (percentile) / 100 * (double) (arr_size + 1);
    return index;
}
