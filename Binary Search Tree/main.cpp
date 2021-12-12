#include "PbBST.h"
#include "PbBSTNode.h"
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
    PbBST t1;
     //  7; 3; 6; 12; 13; 4; 1; 9; 15; 0; 11; 14; 2; 8; 14; 5

   /* t1.insertKey(10);
    t1.insertKey(9);
    t1.insertKey(12);
    t1.insertKey(13);
    t1.insertKey(4);
    t1.insertKey(5);
    t1.insertKey(1);*/

    t1.insertKey(7);
    t1.insertKey(3);
    t1.insertKey(6);
    t1.insertKey(12);
    t1.insertKey(13);
    t1.insertKey(4);
    t1.insertKey(1);
    t1.insertKey(9);
    t1.insertKey(15);
    t1.insertKey(0);
    t1.insertKey(11);
    t1.insertKey(14);
    t1.insertKey(2);
    t1.insertKey(8);
    t1.insertKey(14);
    t1.insertKey(5);


    t1.findNodesRequired();

    t1.inorde();

    t1.deleteKey(7);
    t1.deleteKey(8);

    t1.inorde();

    //t1.mirrorTree();
    t1.inorde();

return 0;
}
