#ifndef _PbBSTNode1_H_
#define _PbBSTNode1_H_
#include <stddef.h>
/**
* Title : Binary Search Trees
* Author : EGE TURAN
* ID: 21502441
* Section : 2
* Assignment : 2
* Description : header of the PbBSTNode
*/
class PbBSTNode{

public:
    PbBSTNode();
    PbBSTNode(const int& nodeItem,
        PbBSTNode *left = NULL,
        PbBSTNode *right = NULL);

     ~PbBSTNode();

    void destroyTree(PbBSTNode * &treePtr);

    int item;       // data portion
    PbBSTNode *leftChildPtr;  // pointer to left child
    PbBSTNode *rightChildPtr; // pointer to right child
private:
};
#endif
