#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Node
{
    unsigned long lat;
    struct Node *next;
};
typedef struct Node Node;

typedef struct
{
    Node *head;
    Node *tail;
}List;

void create_list(List *);
void show_percentile(List *, unsigned long, unsigned long);
void store_latency(List *, unsigned long);
void delete_list(List *);
void count_sort(List *, unsigned long, unsigned long*);