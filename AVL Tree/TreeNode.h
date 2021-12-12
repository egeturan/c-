#include <stddef.h>

#ifndef _TreeNode_H_
#define _TreeNode_H_

class TreeNode{

public:
    TreeNode();
    TreeNode(const int& nodeItem,
        TreeNode *left = NULL,
        TreeNode *right = NULL);

     ~TreeNode();

    void destroyTree(TreeNode * &treePtr);

    int item;       // data portion
    TreeNode *leftChildPtr;  // pointer to left child
    TreeNode *rightChildPtr; // pointer to right child
private:
};

#endif // _AVLTree_H_

