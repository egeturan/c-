

#include "TreeNode.h"
#include <stddef.h>
/**
* Title : Binary Search Trees
* Author : EGE TURAN
* ID: 21502441
* Section : 2
* Assignment : 2
* Description : PbBSTNode class
*/

TreeNode::TreeNode(){
    item = -999999;
    leftChildPtr = NULL;
    rightChildPtr = NULL;
}

TreeNode::TreeNode(const int& nodeItem,
        TreeNode *left, TreeNode *right){
    item = nodeItem;
    leftChildPtr = left;
    rightChildPtr = right;
}

TreeNode::~TreeNode(){

}
