#include "countsort.h"

void count_sort(unsigned long *lat_array, unsigned long count_size, unsigned long array_size)
{
    unsigned int *count_array;
    count_array = (unsigned int *)malloc(sizeof(unsigned int) * count_size);
    memset(count_array, 0, count_size * sizeof(unsigned int));

    for(unsigned long j = 0; j < array_size; j++)
    {
        count_array[lat_array[j]]++;
    }

    int k = 0;
    for(unsigned long j = 0; j < count_size; j++)
    {
        while(count_array[j] != 0)
        {
            lat_array[k++] = j;
            count_array[j]--;
        }
    }
    
    free(count_array);
}