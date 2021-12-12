#include <iostream>
#include "PbBST.h"
#include "PbBSTNode.h"
#include <cmath>
#include <stdio.h>
#include <stddef.h>
#include <cstdlib>
#include <ctime>




using namespace std;
/**
* Title : Binary Search Trees PbBST is the binary search tree class
* Author : EGE TURAN
* ID: 21502441
* Section : 2
* Assignment : 2
* Description : Binary Search Trees PbBST is the binary search tree class
*/


PbBST::PbBST(){
    root = NULL;
}

PbBST::PbBST(const int& rootItem){
    root->item = rootItem;
}

// Copy constructor
PbBST::PbBST(const PbBST& tree) {
		copyTree(tree.root, root);
}

// Uses preorder traversal for the copy operation
// (Visits first the node and then the left and right children)
void PbBST::copyTree(PbBSTNode *treePtr, PbBSTNode *& newTreePtr) const {

		if (treePtr != NULL) {		// copy node
			newTreePtr = new PbBSTNode(treePtr->item, NULL, NULL);
			copyTree(treePtr->leftChildPtr, newTreePtr->leftChildPtr);
			copyTree(treePtr->rightChildPtr, newTreePtr->rightChildPtr);
		}
		else
			newTreePtr = NULL;	// copy empty tree
}


PbBST::~PbBST(){
    destroyTree(root);
}

// Uses postorder traversal for the destroy operation
// (Visits first the left and right children and then the node)
void PbBST::destroyTree(PbBSTNode *& treePtr) {

		if (treePtr != NULL){
			destroyTree(treePtr->leftChildPtr);
			destroyTree(treePtr->rightChildPtr);
			delete treePtr;
			treePtr = NULL;
		}
}



PbBST::PbBST(const int& rootItem,
				 PbBST& leftTree, PbBST& rightTree) {
		root = new PbBSTNode(rootItem, NULL, NULL);
		attachLeftSubtree(leftTree);
		attachRightSubtree(rightTree);
}

void PbBST::attachLeftSubtree(PbBST& leftTree) {
		// Assertion: nonempty tree; no left child
		if (!isEmpty() && (root->leftChildPtr == NULL)) {
			root->leftChildPtr = leftTree.root;
			leftTree.root = NULL;
		}
}

void PbBST::attachRightSubtree(PbBST& rightTree) {
		// Assertion: nonempty tree; no left child
		if (!isEmpty() && (root->rightChildPtr == NULL)) {
			root->rightChildPtr = rightTree.root;
			rightTree.root = NULL;
		}
}

bool PbBST::isEmpty(){
    if(root->leftChildPtr == NULL && root->rightChildPtr == NULL){
        return true;
    }else{
        return false;
    }
}


void PbBST::searchTreeRetrieve(int searchKey,
				int& treeItem){
		retrieveItem(root, searchKey, treeItem);
}


void PbBST::retrieveItem(PbBSTNode *treePtr, int searchKey,
				int& treeItem)  {

		if (treePtr == NULL)
			cout << "Tree is not found" << endl;
		else if (searchKey == treePtr->item)
			treeItem = treePtr->item;
		else if (searchKey < treePtr->item)
			retrieveItem(treePtr->leftChildPtr, searchKey, treeItem);
		else
			retrieveItem(treePtr->rightChildPtr, searchKey, treeItem);
}

//Insert an Item
void PbBST::insertKey(int key){
        insertKeyHelper(root, key);
}


void PbBST::insertKeyHelper(PbBSTNode *& treePtr, int & newItem){
    if (treePtr == NULL) {
			treePtr = new PbBSTNode(newItem, NULL, NULL);
			if (treePtr == NULL){
				cout << "Insert is failed"  << endl;
			}
        }
		// Else search for the insertion position
		else if (newItem < treePtr->item)
			insertKeyHelper(treePtr->leftChildPtr, newItem);
		else
			insertKeyHelper(treePtr->rightChildPtr, newItem);
}

//Insert an Item endsss

// Delete an Item
 void PbBST::deleteKey(int key){
    deleteItem(root, key);
 }

void PbBST::deleteItem(PbBSTNode * &treePtr, int searchKey){
		if (treePtr == NULL) // Empty tree
                cout << "Delete Failed " << endl;

		// Position of deletion found
		else if (searchKey == treePtr->item)
			deleteNodeItem(treePtr);

		// Else search for the deletion position
		else if (searchKey < treePtr->item)
			deleteItem(treePtr->leftChildPtr, searchKey);
		else
			deleteItem(treePtr->rightChildPtr, searchKey);
}


void PbBST::deleteNodeItem(PbBSTNode * &nodePtr) {
		PbBSTNode *delPtr;
		int replacementItem;


		// (1)  Test for a leaf
		if ( (nodePtr->leftChildPtr == NULL) && (nodePtr->rightChildPtr == NULL) ) {
			delete nodePtr;
			nodePtr = NULL;
		}


		// (2)  Test for no left child
		else if (nodePtr->leftChildPtr == NULL){
			delPtr = nodePtr;
			nodePtr = nodePtr->rightChildPtr;
			delPtr->rightChildPtr = NULL;
			delete delPtr;
		}

    // (3)  Test for no right child
		else if (nodePtr->rightChildPtr == NULL) {
                delPtr = nodePtr;
                nodePtr = nodePtr->leftChildPtr;
                delPtr->leftChildPtr =NULL;
                delete delPtr;
		}


		// (4)  There are two children:
		//      Retrieve and delete the inorder successor
		else {
			processLeftmost(nodePtr->rightChildPtr, replacementItem);
			nodePtr->item = replacementItem;
		}

}

void PbBST::processLeftmost(PbBSTNode *&nodePtr,
						  int& treeItem){

		if (nodePtr->leftChildPtr == NULL) {
			treeItem = nodePtr->item;
			PbBSTNode *delPtr = nodePtr;
			nodePtr = nodePtr->rightChildPtr;
			delPtr->rightChildPtr = NULL; // defense
			delete delPtr;
		}
		else
			processLeftmost(nodePtr->leftChildPtr, treeItem);
}


//Delete an Item endsss

////Node coutn
int PbBST::getNodeCount(){
        return helperGetCount(root);
    }

 int PbBST::helperGetCount(PbBSTNode *treePtr){
        if(treePtr == NULL)
            return 0;

        return helperGetCount(treePtr->leftChildPtr) + helperGetCount(treePtr->rightChildPtr) + 1;
    }

////// Node count ENDSSSS


/////HEIGHT OF THE TREEE
    int PbBST::getHeight(){
        return getHeightHelper(root);
    }

    int PbBST::getHeightHelper(PbBSTNode *subTreePtr){
        if (subTreePtr == NULL )
            return 0;
        else
            return 1 + max(getHeightHelper(subTreePtr->leftChildPtr), getHeightHelper(subTreePtr->rightChildPtr));
    }// end getHeightHelper

/////HEIGHT OF THE TREEE ENDSSS

//Find number of nodes required for tree
 int PbBST::findNodesRequired(){
        int heigth1 = getHeight();
        int nodeCounter = getNodeCount();
        int sumOfRequiredNodes = 1;
        for(int i = 0; i < heigth1; i++){
            sumOfRequiredNodes = sumOfRequiredNodes * 2;
        }
        sumOfRequiredNodes--;

        cout << "Number of required nodes are: "  <<  sumOfRequiredNodes - nodeCounter << " " << endl;
        return sumOfRequiredNodes - nodeCounter;
 }

 int PbBST::findFullBTLevel(){
    int noOfLevels = this->getHeight();
    if(noOfLevels == 0)
        return 0;
    for(int l = 1; l <= noOfLevels; l++)
        if(!this->isLevelFull(l))
            return l - 1;
    return noOfLevels;
 }


int PbBST::isLevelFull(int l){
        int nodesInLevel = 0;
        isLevelFull(root, l, nodesInLevel);
        return nodesInLevel = pow(2, l - 1);
}


void PbBST::levelTest(PbBSTNode * pNode, int l, int &nodesInLevel, int &a){
    if (pNode == NULL){
        return;
    }
    if(l == 1){
             for(int i = 0; i < a * 2; i++){
                    cout << "   ";
             }
            if(pNode->leftChildPtr !=NULL){
                cout << "------- ";
            }
                cout << pNode->item;

            if(pNode->rightChildPtr !=NULL){
                cout << " ------- ";
            }

        nodesInLevel++;
        }
    else{
        this->levelTest(pNode->leftChildPtr, l - 1 , nodesInLevel, a);
        this->levelTest(pNode->rightChildPtr, l - 1, nodesInLevel, a);
    }
}



void PbBST::isLevelFull(PbBSTNode * pNode, int l, int &nodesInLevel){
    if (pNode == NULL) return;
    if(l == 1){
        nodesInLevel++;
    }
    else{
        this->isLevelFull(pNode->leftChildPtr, l - 1 , nodesInLevel);
        this->isLevelFull(pNode->rightChildPtr, l - 1, nodesInLevel);
    }
}

void PbBST::printTree(){
        int length = getHeight();
        if (root != NULL){

        }
        preorder(root, length);
}


void PbBST::preorder(PbBSTNode *treePtr, int & length) {
		int noOfLevels = this->getHeight();
		int totalNodes = getNodeCount();
        int a = 5;
        if(noOfLevels == 0){
            cout << "Empty Tree "  << endl;
        }
        for(int l = 1; l <= noOfLevels; l++)
            {
                if(l == noOfLevels){
                    cout << "           " ;
                }
                if(!this->printLevel(l, totalNodes, a)){
                    break;
                    }
                    a--;
             cout << "\n" << endl;
            //I have 4 different entry here
        }
}

bool PbBST::printLevel(int l, int & totalNodes, int &a){
        int nodesInLevel = 0;

        levelTest(root, l, nodesInLevel, a);
        totalNodes = totalNodes - nodesInLevel;
        if(totalNodes == 0){
            return false;
        }else{
            return true;
        }
}

void PbBST::inorde() {
		inorder(root);
}


void PbBST::inorder(PbBSTNode *treePtr) {
		if (treePtr != NULL) {
			inorder(treePtr->leftChildPtr);
			cout << treePtr->item << endl;
			inorder(treePtr->rightChildPtr);
		}
}


void PbBST::mirrorTree(){
    mirrorTreeHelper(root);
}

void PbBST::mirrorTreeHelper(PbBSTNode *treePtr){
        PbBSTNode *carry;
        if (treePtr == NULL){
            return;
        }
        else{
            mirrorTreeHelper(treePtr ->leftChildPtr);
            mirrorTreeHelper(treePtr -> rightChildPtr);

            carry = treePtr ->leftChildPtr;
            treePtr->leftChildPtr = treePtr-> leftChildPtr;
            treePtr->leftChildPtr = carry;
        }
}
