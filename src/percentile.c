#include "percentile.h"

static struct Node *new_node(unsigned long lat)
{
    struct Node *lat_node = (struct Node *)malloc(sizeof(struct Node));
    lat_node->lat = lat;
    lat_node->next = NULL;
    return lat_node;
}

/* gets index of specified percentile in sorted array */
static int get_percentile_index(double percentile, unsigned long arr_size)
{
    int index = 0;
    if(percentile == 100)
        index = arr_size - 1;
    else
        index = (((percentile) * (arr_size + 1)) / 100) - 1;
    return index;
}

void show_percentile( struct Node *root, unsigned long lat_array_size)
{
    unsigned long *lat_array = NULL;
    unsigned int i = 0;
    int inorder_idx = 0;
    double percentile_array[] = {50, 75, 90, 99.9, 99.99, 99.999};
    size_t percentile_array_size = sizeof(percentile_array) / sizeof(percentile_array[0]);
    int percentile_idx = 0;

	lat_array = (double *)malloc(sizeof(double) * lat_array_size);
    memset(lat_array, 0, lat_array_size * sizeof(unsigned long));

    count_sort(root, lat_array_size, lat_array);

	if(!lat_array){
		printf("cannot allocate meory for calculating percentile, unable to show result\n");
			return;
	}

    /* Get percentiles at these specified points */
    printf("\n\tPercentile\t   Latency(us)\n");
    for(i = 0; i < percentile_array_size; i++)
    {
        percentile_idx = get_percentile_index(percentile_array[i], lat_array_size);
        printf("\t%g%%\t\t    %.3f\n", percentile_array[i], lat_array[percentile_idx]);
    }
}

void *store_latency(struct Node *node, double lat)
{
    struct Node* to_store = new_node(lat);
    if(node == NULL)
        node = to_store;
    else
    {
        while(node->next != NULL)
        {
            node = node->next;
        }

        // store new node;
        node->next = to_store;
    }
}

void count_sort(struct Node *node, unsigned long count_size, unsigned long *lat_array)
{
    //unsigned int *count_array = NULL;
    unsigned long i = 0;

    //count_array = (unsigned int *)malloc(sizeof(unsigned int) * count_size);

    if(!count_array)
        return;
    
    while(node->next != NULL)
    {
        lat_array[node->lat]++;
        node = node->next;
    }

}

void deallocate(struct Node *node)
{
    if(node == NULL) return;
}