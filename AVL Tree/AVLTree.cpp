#include <iostream>
#include "AVLTree.h"
#include "TreeNode.h"
#include <cmath>
#include <stdio.h>
#include <stddef.h>
#include <cstdlib>
#include <ctime>
using namespace std;


/**
* Title : Heaps and AVL Trees
* Author : Name Surname
* ID: 21000000
* Section : 0
* Assignment : 3
* Description : description of your code
*/

AVLTree::AVLTree(){
    root = NULL;
    nodeCount = 0;
}

AVLTree::AVLTree(const int& rootItem){
    root->item = rootItem;
}

// Copy constructor
AVLTree::AVLTree(const AVLTree& tree) {
		copyTree(tree.root, root);
}

// Uses preorder traversal for the copy operation
// (Visits first the node and then the left and right children)
void AVLTree::copyTree(TreeNode *treePtr, TreeNode *& newTreePtr) const {

		if (treePtr != NULL) {		// copy node
			newTreePtr = new TreeNode(treePtr->item, NULL, NULL);
			copyTree(treePtr->leftChildPtr, newTreePtr->leftChildPtr);
			copyTree(treePtr->rightChildPtr, newTreePtr->rightChildPtr);
		}
		else
			newTreePtr = NULL;	// copy empty tree
}


AVLTree::~AVLTree(){
    destroyTree(root);
}

// Uses postorder traversal for the destroy operation
// (Visits first the left and right children and then the node)
void AVLTree::destroyTree(TreeNode *& treePtr) {

		if (treePtr != NULL){
			destroyTree(treePtr->leftChildPtr);
			destroyTree(treePtr->rightChildPtr);
			delete treePtr;
			treePtr = NULL;
		}
}



AVLTree::AVLTree(const int& rootItem,
				 AVLTree& leftTree, AVLTree& rightTree) {
		root = new TreeNode(rootItem, NULL, NULL);
		attachLeftSubtree(leftTree);
		attachRightSubtree(rightTree);
}

void AVLTree::attachLeftSubtree(AVLTree& leftTree) {
		// Assertion: nonempty tree; no left child
		if (!isEmpty() && (root->leftChildPtr == NULL)) {
			root->leftChildPtr = leftTree.root;
			leftTree.root = NULL;
		}
}

void AVLTree::attachRightSubtree(AVLTree& rightTree) {
		// Assertion: nonempty tree; no left child
		if (!isEmpty() && (root->rightChildPtr == NULL)) {
			root->rightChildPtr = rightTree.root;
			rightTree.root = NULL;
		}
}

bool AVLTree::isEmpty(){
    if(root->leftChildPtr == NULL && root->rightChildPtr == NULL){
        return true;
    }else{
        return false;
    }
}


void AVLTree::searchTreeRetrieve(int searchKey,
				int& treeItem){
		retrieveItem(root, searchKey, treeItem);
}


void AVLTree::retrieveItem(TreeNode *treePtr, int searchKey,
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
void AVLTree::insertKey(int key){
        insertKeyHelper(root, key);

        bool returned = isBST(root); //?????
}

bool AVLTree::isBST(TreeNode * ptr){

    return isAVL(ptr, INT_MIN , INT_MAX);
}


bool AVLTree::isAVL(TreeNode * ptr, int min1, int max1  ){

    if(ptr == NULL)
        return true;

    if((ptr->item < min1) || (ptr->item > max1)){
     cout << "ENTERED" << endl;
        return false;
    }

    bool lCheck = isAVL(ptr->leftChildPtr, min1, ptr->item - 1);
    bool rCheck = isAVL(ptr->rightChildPtr, ptr->item + 1, max1);

    if(lCheck && rCheck){
        int lh = getHeightHelper(ptr->leftChildPtr);
        int rh = getHeightHelper(ptr->rightChildPtr);
        int res = lh - rh;

        cout << "*********** "<< res << endl;

         // Left Left Case
    if (res > 1 &&  (diff(ptr->leftChildPtr) > 0 )){
            cout << "1111111" << endl;
         singleRotateToTheLeft(ptr);
    }

    // Right Right Case
    if (res < -1 && (diff(ptr->rightChildPtr) < 0 )){
               cout << "222222" << endl;
        singleRotateToTheRight(ptr);
    }

    // Left Right Case
    if (res > 1 &&  (diff(ptr->leftChildPtr) < 0 ))
    {
        cout << "333333" << endl;
        ptr->leftChildPtr = singleRotateToTheLeft(ptr->leftChildPtr);
        singleRotateToTheRight(ptr);
    }

    // Right Left Case
    if (res < -1 && (diff(ptr->rightChildPtr) > 0 ))
    {
        cout << "44444" << endl;
        ptr->rightChildPtr = singleRotateToTheRight(ptr->rightChildPtr);
         singleRotateToTheLeft(ptr);
    }
    cout <<     "dsdfsdfsfsdf " <<  endl;
        return true;
    }

    return false;

}


int AVLTree::diff(TreeNode *temp)
{
    int l_height = getHeightHelper(temp->leftChildPtr);
    int r_height = getHeightHelper(temp->rightChildPtr);
    int b_factor= l_height - r_height;
    return b_factor;
}



TreeNode* AVLTree::insertKeyHelper(TreeNode *& treePtr, int & newItem){
    if (treePtr == NULL) {

			treePtr = new TreeNode(newItem, NULL, NULL);
			return treePtr;
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
 void AVLTree::deleteKey(int key){
    deleteItem(root, key);
 }

void AVLTree::deleteItem(TreeNode * &treePtr, int searchKey){
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


void AVLTree::deleteNodeItem(TreeNode * &nodePtr) {
		TreeNode *delPtr;
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

 void AVLTree::processLeftmost(TreeNode *&nodePtr,
						  int& treeItem){

		if (nodePtr->leftChildPtr == NULL) {
			treeItem = nodePtr->item;
			TreeNode *delPtr = nodePtr;
			nodePtr = nodePtr->rightChildPtr;
			delPtr->rightChildPtr = NULL; // defense
			delete delPtr;
		}
		else
			processLeftmost(nodePtr->leftChildPtr, treeItem);
}




////Node coutn
int AVLTree::getNodeCount(){
        return helperGetCount(root);
    }



int AVLTree::helperGetCount(TreeNode *treePtr){
        if(treePtr == NULL)
            return 0;

        return helperGetCount(treePtr->leftChildPtr) + helperGetCount(treePtr->rightChildPtr) + 1;
    }



    ////// Node count ENDSSSS


/////HEIGHT OF THE TREEE
    int AVLTree::getHeight(){
        return getHeightHelper(root);
    }

        int AVLTree::getHeight1(TreeNode *subTreePtr){
        return getHeightHelper(subTreePtr);
    }

    int AVLTree::getHeightHelper(TreeNode *subTreePtr){
        if (subTreePtr == NULL )
            return 0;
        else
            return 1 + max(getHeightHelper(subTreePtr->leftChildPtr), getHeightHelper(subTreePtr->rightChildPtr));
    }

    TreeNode* AVLTree::singleRotateToTheRight(TreeNode *sub1){
      /*  TreeNode *temp = root;
        TreeNode *temp2 = root -> leftChildPtr;
        root->leftChildPtr = NULL;
        root->leftChildPtr = temp2->rightChildPtr;
        temp2->rightChildPtr = NULL;
        temp2->rightChildPtr = temp;
        root = temp2;
*/

        cout <<     "EGe " <<  endl;
    TreeNode *temp;
    temp = sub1->leftChildPtr;
    sub1->leftChildPtr = temp->rightChildPtr;
    temp->rightChildPtr = sub1;

        return root;
    }


    TreeNode* AVLTree::singleRotateToTheLeft(TreeNode *sub1){
      /*    TreeNode *temp = root;
        TreeNode *temp2 = root -> rightChildPtr;
        root->rightChildPtr = NULL;
        root->rightChildPtr = temp2->leftChildPtr;
        temp2->leftChildPtr = NULL;
        temp2->leftChildPtr = temp;
        root = temp2;
*/
    TreeNode *temp;
    temp = sub1->leftChildPtr;
    sub1->leftChildPtr = temp->rightChildPtr;
    temp->rightChildPtr = sub1;

        cout <<     "aqqq " <<  endl;

        return sub1;


    }

    void AVLTree::printMe(){
        printMe2(root);
    }

    void AVLTree::printMe2(TreeNode *root){
        if(root != NULL){
            cout << " "  << root->item;
            printMe2(root->leftChildPtr);
            printMe2(root->rightChildPtr);
        }
    }


    int AVLTree::controlTheBalance(TreeNode *root){
        if(root != NULL){
            int left = getHeight1(root->leftChildPtr);
            int right = getHeight1(root->rightChildPtr);
            return left - right;
        }else
            return 0;
    }

