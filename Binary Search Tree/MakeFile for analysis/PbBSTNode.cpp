#include "PbBSTNode.h"
#include <stddef.h>
/**
* Title : Binary Search Trees
* Author : EGE TURAN
* ID: 21502441
* Section : 2
* Assignment : 2
* Description : PbBSTNode class
*/
PbBSTNode::PbBSTNode(){
    item = -999999;
    leftChildPtr = NULL;
    rightChildPtr = NULL;
}

PbBSTNode::PbBSTNode(const int& nodeItem,
        PbBSTNode *left, PbBSTNode *right){
    item = nodeItem;
    leftChildPtr = left;
    rightChildPtr = right;
}

PbBSTNode::~PbBSTNode(){

}

