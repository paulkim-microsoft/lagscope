#include "percentile.h"

static Node *new_node(unsigned long lat)
{
    Node *lat_node = (struct Node *)malloc(sizeof(Node));
    lat_node->lat = lat;
    lat_node->next = NULL;
    return lat_node;
}

/* gets index of specified percentile in sorted array */
static int get_percentile_index(unsigned long *freq_table, double percentile, unsigned long arr_size, unsigned long n_pings)
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
            freq_counter += freq_table[index];
            index++;
         }
         index--;
    }
    return index;
}

void show_percentile(unsigned long *freq_table, unsigned long freq_table_size, unsigned long n_pings)
{
    unsigned int i = 0;
    double percentile_array[] = {50, 75, 90, 99.9, 99.99, 99.999};
    size_t percentile_array_size = sizeof(percentile_array) / sizeof(percentile_array[0]);
    int percentile_idx = 0;

    /* Get percentiles at these specified points */
    printf("\n\tPercentile\t   Latency(us)\n");
    for(i = 0; i < percentile_array_size; i++)
    {
        percentile_idx = get_percentile_index(freq_table, percentile_array[i], freq_table_size, n_pings);
        printf("\t%g%%\t\t    %d\n", percentile_array[i], percentile_idx);
    }
}

void show_histogram(unsigned long *freq_table, int start, int len, int count, unsigned long max_latency)
{
    int i = 0;
    unsigned long freq_counter = 0;
    unsigned long final_interval = (len * count) + start;
    unsigned long lat_intervals = 0;
    int interval_start = 0;
    unsigned long after_final_interval = 0;
    unsigned long leftover = 0;

    printf("\nInterval(usec)\t Frequency\n");
    if (start > 0) 
    {
        for(i = 0; i < start; i++)
        {
            freq_counter += freq_table[i];
        }
        printf("%7d \t %lu\n", 0, freq_counter);
    }

    freq_counter = 0;
    for(lat_intervals = start; lat_intervals < final_interval; lat_intervals+=len)
    {
        interval_start = 0;
        if(lat_intervals > max_latency)
        {
            printf("%7lu \t %d\n", lat_intervals, 0);
            continue;
        }
            
        while(interval_start < len)
        {
            if(lat_intervals + interval_start > max_latency)
                break;
            freq_counter += freq_table[lat_intervals + interval_start];
            interval_start++;
        }
        printf("%7lu \t %lu\n", lat_intervals, freq_counter);
        freq_counter = 0;
    }

    /* Get all leftover latencies after the final interval */
    if(final_interval < max_latency)
    {
        after_final_interval = final_interval;
        for(leftover = after_final_interval; leftover <= max_latency; leftover++)
        {
            freq_counter += freq_table[leftover];   
        }
        printf("%7lu \t %lu\n", after_final_interval, freq_counter);
    }
}

void store_latency(List *latency_list, unsigned long lat)
{
    Node *to_store = new_node(lat);
    if(latency_list->head == NULL)
        latency_list->head = latency_list->tail = to_store;
    else
    {   
        latency_list->tail->next = to_store;
        latency_list->tail = latency_list->tail->next;
    }
}

void count_sort(List *latency_list, unsigned long *freq_table)
{
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
        freq_table[temp->lat]++;
        temp = temp->next;
        counter++;
    }
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