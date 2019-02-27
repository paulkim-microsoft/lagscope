#include <stdlib.h>
#include <stdio.h>

struct Node
{
    unsigned long lat;
    //int count;
    struct Node *next;
};

void show_percentile(struct Node *root, unsigned long lat_array_size);
struct Node *store_latency(struct Node* node, double lat);
void deallocate(struct Node *root);