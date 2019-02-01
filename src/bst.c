#include "bst.h"

struct Node *new_node(double lat)
{
    //printf("Created New Node\n");
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
        //printf("Insert function Check 1\n");
        return new_node(lat);
    }

    if(lat == node->lat)
    {
        printf("Insert function Check 2\n");
        (node->count)++;
        return node;
    }

    if(lat < node->lat)
    {
        printf("Insert function Check 3\n");
        node->left = insert(node->left, lat);
    }
    else
    {
        printf("Insert function Check 4\n");
        node->right = insert(node->right, lat);
    }


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

void deallocate(struct Node *root)
{
    deallocate(root->left);
    deallocate(root->right);

    free(root);
}