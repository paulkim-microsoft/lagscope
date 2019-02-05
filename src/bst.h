#include <stdlib.h>
#include <stdio.h>

struct Node
{
    int lat;
    int count;
    struct Node *left;
    struct Node *right;
};

struct Node *new_node(int lat);
struct Node *insert(struct Node* node, int lat);
int inorder(struct Node *root, int idx, int *buf);
void deallocate(struct Node *root);