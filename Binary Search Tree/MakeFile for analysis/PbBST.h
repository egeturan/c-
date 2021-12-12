#include "PbBSTNode.h"
#include <stddef.h>
#ifndef _PbBST_H_
#define _PbBST_H_
/**
* Title : Binary Search Trees
* Author : EGE TURAN
* ID: 21502441
* Section : 2
* Assignment : 2
* Description : header of the binary search tree
*/
class PbBST
{
private:
    int item; // Data portion


    PbBST * leftChildPtr; // Pointer to left child
    PbBST * rightChildPtr;
public:
    PbBST();
    PbBSTNode * root;
    PbBST(const int& rootItem);
    PbBST(const int& rootItem,
			   PbBST& leftTree, PbBST& rightTree);

	PbBST(const PbBST& tree);
	void copyTree(PbBSTNode *treePtr, PbBSTNode* & newTreePtr) const;


    ~PbBST();
    void destroyTree(PbBSTNode *&treePtr);


    void attachRightSubtree(PbBST& rightTree);
    void attachLeftSubtree(PbBST& rightTree);
    bool isEmpty();
    PbBST& operator=(const PbBST& rhs);

    //void PbBST::insertKey(int key); // 5 points
    void insertKey(int key);
    void insertKeyHelper(PbBSTNode *& treePtr, int & newItem);


    //DELETE key
    void deleteKey(int key);
    void deleteItem(PbBSTNode * &treePtr, int searchKey);
    void deleteNodeItem(PbBSTNode * &nodePtr);
    void processLeftmost(PbBSTNode *&nodePtr,
						  int& treeItem);


    //For node count
    int getNodeCount();
    int helperGetCount(PbBSTNode *treePtr);

    //For height of the Tree
    int getHeight();
    int getHeightHelper(PbBSTNode *subTreePtr);

    //For necesssary amount of nodes to create full binary tree
     int findNodesRequired();

     int findFullBTLevel();
     int isLevelFull(int l);
     void levelTest(PbBSTNode *pNode, int l, int &nodesLevelInLevel, int &a);
     void isLevelFull(PbBSTNode *pNode, int l, int &nodesLevelInLevel);
    //Print the tree
     void printTree(); // 10 points
     int floorForTree(int &length);



     void inorder(PbBSTNode *treePtr);
     int floorForTree1(int &length);
     void inorde();

     bool printLevel(int l, int & totalNodes, int &a);
     void preorder(PbBSTNode *treePtr, int & length);

    //Miror Tree
     void mirrorTree();
     void mirrorTreeHelper(PbBSTNode *treePtr);
     //
    // void PbBST::mirrorTree(); // 10 points
    //void PbBST::printTree(); // 10 points
    //Find length that full binary tree
   // int PbBST::findFullBTLevel();

    protected:
        //Retrieve a item
    void retrieveItem(PbBSTNode *treePtr, int searchKey,
						int& item);
    void searchTreeRetrieve(int searchKey, int& item);

};

#endif // _PbBST_H_


void analysis();
