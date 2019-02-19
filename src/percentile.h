#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdbool.h>

struct Node
{
    double lat;
    int count;
    struct Node *left;
    struct Node *right;
};

void show_percentile(struct Node *root, double *lat_array, unsigned long lat_array_size);
struct Node *new_node(double lat);
struct Node *insert(struct Node* node, double lat);
int inorder(struct Node *root, int idx, double *lat_array);
void deallocate(struct Node *root);
int get_percentile_index(double percentile, unsigned long arr_size);