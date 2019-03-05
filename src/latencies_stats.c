#include "util.h"

struct node
{
    unsigned long lat;
    struct node *next;
};
typedef struct node node;

static node *head = NULL;
static node *tail = NULL;

static unsigned long *freq_table = NULL;

static node *new_node(unsigned long lat)
{
    node *lat_node = (struct node *)malloc(sizeof(node));
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

void show_percentile(unsigned long freq_table_size, unsigned long n_pings)
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

void show_histogram(int start, int len, int count, unsigned long max_latency)
{
    int i = 0;
    unsigned long freq_counter = 0;
    unsigned long final_interval = (len * count) + start;
    unsigned long lat_intervals = 0;
    int interval_start = 0;
    unsigned long after_final_interval = 0;
    unsigned long leftover = 0;

    /* Print frequencies between 0 and starting interval */
    printf("\nInterval(usec)\t Frequency\n");
    if (start > 0) 
    {
        for(i = 0; i < start; i++)
        {
            freq_counter += freq_table[i];
        }
        printf("%7d \t %lu\n", 0, freq_counter);
    }

    /*  Prints frequencies between each interval */
    freq_counter = 0;
    for(lat_intervals = start; lat_intervals < final_interval; lat_intervals+=len)
    {
        interval_start = 0;
        if(lat_intervals > max_latency)
        {
            printf("%7lu \t %d\n", lat_intervals, 0);
            if(lat_intervals + len == final_interval)
                printf("%7lu \t %d\n", lat_intervals + len, 0);
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

    /* Print all leftover latencies after the final interval only if final interva < max latency */
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

void store_latency(unsigned long lat)
{
    node *to_store = new_node(lat);
    if(head == NULL)
        head = tail = to_store;
    else
    {   
        tail->next = to_store;
        tail = tail->next;
    }
}

void process_latencies(unsigned long max_latency)
{
    node * temp;

    freq_table = (unsigned long*) malloc(sizeof(unsigned long) * max_latency + 1);

	if(!freq_table)
	{
		PRINT_ERR("cannot allocate memory for percentile and histogram calculation");
		return;
	}

	memset(freq_table, 0, max_latency + 1 * sizeof(unsigned long));

    if(head == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    temp = head;
    int counter = 0;
    while(temp != NULL)
    {
        freq_table[temp->lat]++;
        temp = temp->next;
        counter++;
    }
}

void delete_list(void)
{
    node *to_delete, *temp;
    to_delete = head;
    while(to_delete != NULL)
    {
        temp = to_delete->next;
        free(to_delete);
        to_delete = temp;
    }
}