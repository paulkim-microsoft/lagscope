#include "percentile.h"

static struct Node *new_node(double lat)
{
    struct Node *lat_node = (struct Node *)malloc(sizeof(struct Node));
    lat_node->lat = lat;
    lat_node->left = NULL;
    lat_node->right = NULL;
    lat_node->count = 1;
    return lat_node;
}

/* puts bst data into an array in order */
static int inorder(struct Node *root, int idx, double *lat_array)
{
    if(root != NULL)
    {
        idx = inorder(root->left, idx, lat_array);
        while(root->count != 0)
        {
            lat_array[idx] = root->lat;
            idx++;
            root->count--;
        }
        idx = inorder(root->right, idx, lat_array);
    }
    return idx;
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
    double *lat_array = NULL;
    unsigned int i = 0;
    int inorder_idx = 0;
    double percentile_array[] = {50, 75, 90, 99.9, 99.99, 99.999};
    size_t percentile_array_size = sizeof(percentile_array) / sizeof(percentile_array[0]);
    int percentile_idx = 0;

	lat_array = (double *)malloc(sizeof(double) * lat_array_size);
	if(!lat_array){
		printf("cannot allocate meory for calculating percentile, unable to show result\n");
			return;
	}

    inorder(root, inorder_idx, lat_array);

    /* Get percentiles at these specified points */
    printf("\n\tPercentile\t   Latency(us)\n");
    for(i = 0; i < percentile_array_size; i++)
    {
        percentile_idx = get_percentile_index(percentile_array[i], lat_array_size);
        printf("\t%g%%\t\t    %.3f\n", percentile_array[i], lat_array[percentile_idx]);
    }
}

struct Node *store_latency(struct Node *node, double lat)
{
    if(node == NULL)
        return new_node(lat);

    if(lat == node->lat)
    {
        node->count++;
        return node;
    }

    if(lat < node->lat)
        node->left = store_latency(node->left, lat);
    else
        node->right = store_latency(node->right, lat);

    return node;
}

void deallocate(struct Node *node)
{
    if(node == NULL) return;

    deallocate(node->left);
    deallocate(node->right);

    free(node);
}