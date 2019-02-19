#include <stdlib.h>
#include <stdio.h>

struct Node
{
    double lat;
    int count;
    struct Node *left;
    struct Node *right;
};

void show_percentile(struct Node *root, unsigned long lat_array_size);
struct Node *store_latency(struct Node* node, double lat);
void deallocate(struct Node *root);