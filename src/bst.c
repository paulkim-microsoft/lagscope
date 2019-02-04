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

int inorder(struct Node *root, int idx, double *buf)
{
    if(root != NULL)
    {
        idx = inorder(root->left, idx, buf);
        while(root->count != 0)
        {
            printf("Lat: %f | Count: (%d) | Index: %d \n", root->lat, root->count, idx);
            buf[idx] = root->lat;
            idx++;
            (root->count)--;
        }
        idx = inorder(root->right, idx, buf);
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