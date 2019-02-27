#include "percentile.h"

static struct Node *new_node(unsigned long lat)
{
    struct Node *lat_node = (struct Node *)malloc(sizeof(struct Node));
    lat_node->lat = lat;
    lat_node->next = NULL;
    return lat_node;
}

/* gets index of specified percentile in sorted array */
static int get_percentile_index(unsigned long *lat_array, double percentile, unsigned long arr_size, unsigned long n_pings)
{
    unsigned int index = 0;
    unsigned long of_total = 0;
    unsigned long freq_counter = 0;
    unsigned int i = 0;
    if(percentile == 100)
        index = arr_size;
    else
    {
         of_total = (((percentile) * (n_pings + 1)) / 100);
         while(freq_counter <= of_total)
         {
            if(lat_array[i] ==  0)
                continue;
            freq_counter += lat_array[i];
            i++;
         }
         index = i;
    }
    return index;
}

void show_percentile( struct Node *root, unsigned long lat_array_size, unsigned long n_pings)
{
    unsigned long *lat_array = NULL;
    unsigned int i = 0;
    double percentile_array[] = {50, 75, 90, 99.9, 99.99, 99.999};
    size_t percentile_array_size = sizeof(percentile_array) / sizeof(percentile_array[0]);
    int percentile_idx = 0;

	lat_array = (unsigned long *)malloc(sizeof(unsigned long) * lat_array_size + 1);
    memset(lat_array, 0, lat_array_size + 1 * sizeof(unsigned long));

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
        printf("\t%g%%\t\t    %.3lu\n", percentile_array[i], lat_array[percentile_idx]);
    }
}

struct Node* store_latency(struct Node *node, unsigned long lat)
{
    struct Node* to_store = new_node(lat);
    struct Node* temp = NULL;
    if(node == NULL)
    {
        node = to_store;
    }
    else
    {
        temp = node;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        // store new node;
        temp->next = to_store;
    }
    return node;
}

void count_sort(struct Node *node, unsigned long count_size, unsigned long *lat_array)
{
    //unsigned int *count_array = NULL;
    //count_array = (unsigned int *)malloc(sizeof(unsigned int) * count_size);
    //if(!lat_array)
        //return;
    //printf("head is: %lu\n", node->lat);
    int counter = 0;
    while(node != NULL)
    {
        //printf("In count sort loop %lu \n", node->lat);
        lat_array[node->lat]++;
        if(node->next == NULL)
        {
            break;
        }
        node = node->next;
        counter++;
    }
    //printf("last element: %lu\n", lat_array[count_size]);
    //printf("Counter %d \n", counter);
    //printf("test 2\n");
}

void deallocate(struct Node *node)
{
    if(node == NULL) return;
}