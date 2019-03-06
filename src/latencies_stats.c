#include "util.h"

/* datastructure to hold latencies. */
typedef struct node
{
    unsigned long lat;
    struct node *next;
}node_t;

static node_t *head = NULL;
static node_t *tail = NULL;

static unsigned long *freq_table = NULL;

/* Private Functions */
static node_t *new_node(unsigned long lat)
{
    node_t *lat_node = (node_t *)malloc(sizeof(node_t));
    lat_node->lat = lat;
    lat_node->next = NULL;
    return lat_node;
}

/* Gets index of specified percentile in sorted array */
static int get_percentile_index(double percentile, unsigned long arr_size, unsigned long n_pings)
{
    unsigned int index = 0;
    unsigned long of_total_pings = 0;
    unsigned long freq_counter = 0;
    if(percentile == 100)
        index = arr_size - 1;
    else
    {
         of_total_pings = (((percentile) * (n_pings + 1)) / 100) - 1;
         while(freq_counter <= of_total_pings)
         {
            freq_counter += freq_table[index];
            index++;
         }
         index--;
    }
    return index;
}

/* Creates frequency table from list of nodes */
static int process_latencies(unsigned long max_latency)
{
    node_t * temp = NULL;

    freq_table = (unsigned long*) malloc(sizeof(unsigned long) * max_latency + 1);

	if(!freq_table)
	{
		return ERROR_MEMORY_ALLOC;
	}

	memset(freq_table, 0, (max_latency + 1) * sizeof(unsigned long));

    if(head == NULL)
    {
        return 0;
    }

    temp = head;
    while(temp != NULL)
    {
        freq_table[temp->lat]++;
        temp = temp->next;
    }

    return 1;
}

/* Public Functions */
int show_percentile(unsigned long max_latency, unsigned long n_pings)
{
    int err_check = 0;
    if(!freq_table)
    {
        err_check = process_latencies(max_latency);
        if(err_check == ERROR_MEMORY_ALLOC)
            return ERROR_MEMORY_ALLOC;
        else if(err_check == 0)
            return 0;
    }

    unsigned int i = 0;
    double percentile_array[] = {50, 75, 90, 99.9, 99.99, 99.999};
    size_t percentile_array_size = sizeof(percentile_array) / sizeof(percentile_array[0]);
    int percentile_idx = 0;

    /* Get percentiles at these specified points */
    printf("\n\tPercentile\t   Latency(us)\n");
    for(i = 0; i < percentile_array_size; i++)
    {
        percentile_idx = get_percentile_index(percentile_array[i], max_latency, n_pings);
        printf("\t%g%%\t\t    %d\n", percentile_array[i], percentile_idx);
    }

    return 1;
}

/* Prints histogram with user specified inputs */
int show_histogram(int start, int len, int count, unsigned long max_latency)
{
    int err_check = 0;
    if(!freq_table)
    {
        err_check = process_latencies(max_latency);
        if(err_check == ERROR_MEMORY_ALLOC)
            return ERROR_MEMORY_ALLOC;
        else if(err_check == 0)
            return 0;
    }

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

    return 1;
}

void store_latency(unsigned long lat)
{
    node_t *tmp = new_node(lat);
    if(head == NULL)
        head = tail = tmp;
    else
    {   
        tail->next = tmp;
        tail = tail->next;
    }
}

void latencies_stats_cleanup(void)
{
    node_t *temp = NULL;
    while(head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
    head = NULL;
    free(freq_table);
    return;
}