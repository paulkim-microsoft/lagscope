#include "bst.h"

void show_percentile( struct Node *root, double *lat_array, unsigned long lat_array_size)
{
    unsigned int i = 0;
    int offset = 1;
    int inorder_idx = 0;

	inorder(root, inorder_idx, lat_array);

	double percentile_array[] = {50, 75, 90, 99.9, 99.99, 99.999};
    size_t percentile_array_size = sizeof(percentile_array) / sizeof(percentile_array[0]);
    printf("\n\tPercentile\t   Latency(us)\n");
    for(i = 0; i < percentile_array_size; i++)
    {
        int percentile_idx = get_percentile_index(percentile_array[i], lat_array_size);
        printf("\t%f %%\t    %f\n", (double) percentile_array[i], lat_array[percentile_idx - offset]);
    }

}

struct Node *new_node(double lat)
{
    struct Node *lat_node = (struct Node *)malloc(sizeof(struct Node));
    lat_node->lat = lat;
    lat_node->left = NULL;
    lat_node->right = NULL;
    lat_node->count = 1;
    return lat_node;
}

struct Node *insert(struct Node *node, double lat)
{
    if(node == NULL)
    {
        return new_node(lat);
    }

    if(lat == node->lat)
    {
        (node->count)++;
        return node;
    }

    if(lat < node->lat)
    {
        node->left = insert(node->left, lat);
    }
    else
    {
        node->right = insert(node->right, lat);
    }

    return node;
}

int inorder(struct Node *root, int idx, double *lat_array)
{
    if(root != NULL)
    {
        idx = inorder(root->left, idx, lat_array);
        while(root->count != 0)
        {
            lat_array[idx] = root->lat;
            idx++;
            (root->count)--;
        }
        idx = inorder(root->right, idx, lat_array);
    }
    return idx;
}

void deallocate(struct Node *node)
{
    if(node == NULL) return;

    deallocate(node->left);
    deallocate(node->right);

    free(node);
}

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
