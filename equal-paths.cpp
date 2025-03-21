#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int heightTree(Node *root)
{
	if(root == NULL) return 0;
	if(root->left == NULL && root->right == NULL)
	{
		return 0;
	}
    if(root->left != NULL && root->right != NULL)
    {
        int left = heightTree(root->left);
        int right = heightTree(root->right);
        if(left == right)
        {
            return 1 + left;
        }
        else
        {
            return -1;
        }
    }
    else if(root->left != NULL)
    {
        int left = heightTree(root->left);
        return 1 + left;
    }
    else
    {
        int right = heightTree(root->right);
        return 1 + right;
    }
}

bool equalPaths(Node * root)
{
    // Add your code below
    if(root == NULL)
    {
        return true;
    }
    if(heightTree(root->left) == heightTree(root->right))
    {
        return true;
    }
    else
    {
        return false;
    }
}

