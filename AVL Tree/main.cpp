#include "AVLTree.h"
#include "TreeNode.h"
#include <stddef.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
using namespace std;

/**
* Title : Binary Search Trees
* Author : Name Surname
* ID: 21000000
* Section : 0
* Assignment : 2
* Description : description of your code
*/
int main(){
    AVLTree t1;
     //  7; 3; 6; 12; 13; 4; 1; 9; 15; 0; 11; 14; 2; 8; 14; 5

    t1.insertKey(13);
    t1.insertKey(10);
    t1.insertKey(15);
    t1.insertKey(5);
    t1.insertKey(4);
 /*   t1.insertKey1(13);
    t1.insertKey1(4);
    t1.insertKey1(1);
    t1.insertKey1(9);
    t1.insertKey1(15);
    t1.insertKey1(0);
    t1.insertKey1(11);
    t1.insertKey1(14);
    t1.insertKey1(2);
    t1.insertKey1(8);
    t1.insertKey1(14);
    t1.insertKey1(5);
*/
    t1.printMe();

   /* t1.deleteKey(7);
    t1.deleteKey(8);

*/
return 0;
}
