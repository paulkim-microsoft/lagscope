#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Node
{
    unsigned long lat;
    struct Node *next;
};

void show_percentile(struct Node*, unsigned long, unsigned long);
struct Node* store_latency(struct Node*, unsigned long);
void deallocate(struct Node*);
void count_sort(struct Node*, unsigned long, unsigned long*);