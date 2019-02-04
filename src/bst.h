#include <stdlib.h>
#include <stdio.h>

struct Node
{
    double lat;
    int count;
    struct Node *left;
    struct Node *right;
};

struct Node *new_node(double lat);
struct Node *insert(struct Node* node, double lat);
void inorder(struct Node *root, int idx, double *buf);
void deallocate(struct Node *root);