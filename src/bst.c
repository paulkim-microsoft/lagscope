#include "bst.h"

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
        return new_node(lat);

    if(lat == node->lat)
    {
        (node->count)++;
        return node;
    }

    if(lat < node->lat)
        node->left = insert(node->left, lat);
    else
        node->right = insert(node->right, lat);

    return node;
}

void inorder(struct Node *root)
{
    if(root != NULL)
    {
        inorder(root->left);
        printf("%f (%d) \n", root->lat, root->count);
        inorder(root->right);
    }
}