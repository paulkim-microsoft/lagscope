#include "percentile.h"

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
