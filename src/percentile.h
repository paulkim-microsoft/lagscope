#define _GNU_SOURCE

#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>

int get_percentile_index(double percentile, unsigned long arr_size);