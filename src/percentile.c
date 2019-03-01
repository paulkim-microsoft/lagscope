#include "percentile.h"

static Node *new_node(unsigned long lat)
{
    Node *lat_node = (struct Node *)malloc(sizeof(Node));
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
    if(percentile == 100)
        index = arr_size - 1;
    else
    {
         of_total = (((percentile) * (n_pings + 1)) / 100) - 1;
         while(freq_counter <= of_total)
         {
            //printf("Index: %d | Freq: %lu | Freq Total: %lu\n", i, lat_array[i], freq_counter);
            freq_counter += lat_array[index];
            index++;
         }
         index--;
    }
    return index;
}

void show_percentile(List *latency_list, unsigned long lat_array_size, unsigned long n_pings)
{
    unsigned long *lat_array = NULL;
    unsigned int i = 0;
    double percentile_array[] = {50, 75, 90, 99.9, 99.99, 99.999};
    size_t percentile_array_size = sizeof(percentile_array) / sizeof(percentile_array[0]);
    int percentile_idx = 0;

	lat_array = (unsigned long *)malloc(sizeof(unsigned long) * lat_array_size + 1);
    memset(lat_array, 0, lat_array_size + 1 * sizeof(unsigned long));

    count_sort(latency_list, lat_array_size, lat_array);

	if(!lat_array){
		printf("cannot allocate meory for calculating percentile, unable to show result\n");
			return;
	}

/*
    for(unsigned long i = 0; i <= lat_array_size; i++)
    {
        if(lat_array[i] == 0)
            continue;
        printf("Latency is: %lu  |  Freq is: %lu\n", i, lat_array[i]);
    }
*/

    /* Get percentiles at these specified points */
    printf("\n\tPercentile\t   Latency(us)\n");
    for(i = 0; i < percentile_array_size; i++)
    {
        percentile_idx = get_percentile_index(lat_array, percentile_array[i], lat_array_size, n_pings);
        printf("\t%g%%\t\t    %d\n", percentile_array[i], percentile_idx);
    }
}

void store_latency(List *latency_list, unsigned long lat)
{
    Node *to_store = new_node(lat);
    //Node* temp = NULL;
    if(latency_list->head == NULL)
        latency_list->head = latency_list->tail = to_store;
    else
    {   
        latency_list->tail->next = to_store;
        latency_list->tail = latency_list->tail->next;
        /*
        temp = node;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        // store new node;
        temp->next = to_store;
        */
    }
}

void count_sort(List *latency_list, unsigned long count_size, unsigned long *lat_array)
{
    //unsigned int *count_array = NULL;
    //count_array = (unsigned int *)malloc(sizeof(unsigned int) * count_size);
    //if(!lat_array)
        //return;
    //printf("head is: %lu\n", node->lat);
    Node * temp;

    if(latency_list->head == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    temp = latency_list->head;
    int counter = 0;
    while(temp != NULL)
    {
        //printf("In count sort loop %lu \n", temp->lat);
        lat_array[temp->lat]++;
        temp = temp->next;
        counter++;
    }
    //printf("last element: %lu\n", lat_array[count_size]);
    //printf("Counter %d \n", counter);
    //printf("test 2\n");
}

void delete_list(List *latency_list)
{
    Node *to_delete, *temp;
    to_delete = latency_list->head;
    while(to_delete != NULL)
    {
        temp = to_delete->next;
        free(to_delete);
        to_delete = temp;
    }
}