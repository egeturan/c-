
#include "TreeNode.h"
#include <stddef.h>
#ifndef _AVLTree_H_
#define _AVLTree_H_
/**
* Title : AVL Search Tree
* Author : EGE TURAN
* ID: 21502441
* Section : 2
* Assignment : 3
* Description : header of the AVL
*/
class AVLTree
{
private:
    int item; // Data portion
    int nodeCount;

    AVLTree * leftChildPtr; // Pointer to left child
    AVLTree * rightChildPtr;
public:
    AVLTree();
    TreeNode * root;
    AVLTree(const int& rootItem);
    AVLTree(const int& rootItem,
			   AVLTree& leftTree, AVLTree& rightTree);

	AVLTree(const AVLTree& tree);
	void copyTree(TreeNode *treePtr, TreeNode* & newTreePtr) const;
    void insertKey1(int key);

    ~AVLTree();
    void destroyTree(TreeNode *&treePtr);


    void attachRightSubtree(AVLTree& rightTree);
    void attachLeftSubtree(AVLTree& rightTree);
    bool isEmpty();
    AVLTree& operator=(const AVLTree& rhs);

    void insertKey(int key);
    TreeNode* insertKeyHelper(TreeNode *& treePtr, int & newItem);


    //DELETE key
    void deleteKey(int key);
    void deleteItem(TreeNode * &treePtr, int searchKey);
    void deleteNodeItem(TreeNode * &nodePtr);
    void processLeftmost(TreeNode *&nodePtr,
						  int& treeItem);



    //addings
    TreeNode* retrieveItem1(TreeNode *treePtr, int searchKey);
    TreeNode* singleRotateToTheLeft(TreeNode *root);
    TreeNode* singleRotateToTheRight(TreeNode *root);
    int controlTheBalance(TreeNode *root);

    //For node count
    int getNodeCount();
    int helperGetCount(TreeNode *treePtr);

    //For height of the Tree
    int getHeight();
    int getHeight1(TreeNode *subTreePtr);
    int getHeightHelper(TreeNode *subTreePtr);

    int diff(TreeNode *temp);

    void printMe();
    void printMe2(TreeNode *nodePtr);

    //Print the tree
     void printTree(); // 10 points
     int floorForTree(int &length);

     void inorder(TreeNode *treePtr);
     int floorForTree1(int &length);
     void inorde();

     bool printLevel(int l, int & totalNodes, int &a);
     void preorder(TreeNode *treePtr, int & length);

    protected:
        //Retrieve a item
    void retrieveItem(TreeNode *treePtr, int searchKey,
						int& item);
    void searchTreeRetrieve(int searchKey, int& item);


    bool isBST(TreeNode * ptr);
    bool isAVL(TreeNode * ptr, int min1, int max1);
};

#endif // _AVLTree_H_


void analysis();
