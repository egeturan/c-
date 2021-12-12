#include "PbBST.h"
#include "PbBSTNode.h"
#include <cmath>
#include <stdio.h>
#include <stddef.h>
#include <cstdlib>
#include <iostream>
#include <ctime>

/**
* Title : Binary Search Trees
* Author : Name Surname
* ID: 21502441
* Section : 2
* Assignment : 2
* Description : this class uses ctime to calculate time complety of insert and delete
*/

using namespace std;

int main(){
    analysis();


    return 0;
}

void analysis(){

    PbBST t1;
    //Store the starting time
    double duration;
    clock_t startTime;
     //Times
    double d1, d2, d3, d4, d5, d6, d7, d8, d9, d10;
    double da1, da2, da3, da4, da5, da6, da7, da8, da9, da10;

    //1500
    int array1[15000];


     for(int i = 0; i < 1500; i++){
         //Store the starting time
        array1[i] = rand();
    }

    startTime= clock();

    for(int i = 0; i < 1500; i++){
         //Store the starting time
         t1.insertKey(array1[i]);
    }

    //Compute the number of seconds that passed since the starting time
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;

     d1 = duration;

    startTime= clock();

    for(int i = 0; i < 1500; i++){
         //Store the starting time
         t1.deleteKey(array1[i]);
    }

    //Compute the number of seconds that passed since the starting time
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;

    da1 = duration;





    //////////////// 3000


    for(int i = 0; i < 3000; i++){
         //Store the starting time
        array1[i] = rand();
    }

    startTime = clock();
    for(int i = 0; i < 3000; i++){
         //Store the starting time
         t1.insertKey(array1[i]);
    }

    //Compute the number of seconds that passed since the starting time
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    d2 = duration;

    startTime = clock();
    for(int i = 0; i < 3000; i++){
         //Store the starting time
         t1.deleteKey(array1[i]);
    }

    //Compute the number of seconds that passed since the starting time
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    da2 = duration;



    // 4500


    for(int i = 0; i < 4500; i++){
         //Store the starting time
        array1[i] = rand();
    }

    startTime = clock();
    for(int i = 0; i < 4500; i++){
         //Store the starting time
         t1.insertKey(array1[i]);
    }

    //Compute the number of seconds that passed since the starting time
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    d3 = duration;

    startTime = clock();
    for(int i = 0; i < 4500; i++){
         //Store the starting time
         t1.deleteKey(array1[i]);
    }

    //Compute the number of seconds that passed since the starting time
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    da3 = duration;

     // 6000

    for(int i = 0; i < 6000; i++){
         //Store the starting time
        array1[i] = rand();
    }

    startTime = clock();
    for(int i = 0; i < 6000; i++){
         //Store the starting time
         t1.insertKey(array1[i]);
    }

    //Compute the number of seconds that passed since the starting time
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    d4 = duration;


    startTime = clock();
    for(int i = 0; i < 6000; i++){
         //Store the starting time
         t1.deleteKey(array1[i]);
    }

    //Compute the number of seconds that passed since the starting time
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    da4 = duration;

//////////////////////////////////////////////////////////
     // 7500
    for(int i = 0; i < 7500; i++){
         //Store the starting time
        array1[i] = rand();
    }
        startTime = clock();
    for(int i = 0; i < 7500; i++){
         //Store the starting time
         t1.insertKey(array1[i]);
    }

    //Compute the number of seconds that passed since the starting time
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    d5 = duration;

    startTime = clock();
    for(int i = 0; i < 7500; i++){
         //Store the starting time
         t1.deleteKey(array1[i]);
    }

    //Compute the number of seconds that passed since the starting time
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    da5 = duration;

     // 9000


    for(int i = 0; i < 9000; i++){
         //Store the starting time
        array1[i] = rand();
    }
    startTime = clock();
    for(int i = 0; i < 9000; i++){
         //Store the starting time
         t1.insertKey(array1[i]);
    }

    //Compute the number of seconds that passed since the starting time
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    d6 = duration;

        startTime = clock();
    for(int i = 0; i < 9000; i++){
         //Store the starting time
         t1.deleteKey(array1[i]);
    }

    //Compute the number of seconds that passed since the starting time
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    da6 = duration;

     // 10500


    for(int i = 0; i < 10500; i++){
         //Store the starting time
        array1[i] = rand();
    }
        startTime = clock();
    for(int i = 0; i < 10500; i++){
         //Store the starting time
         t1.insertKey(array1[i]);
    }

    //Compute the number of seconds that passed since the starting time
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    d7 = duration;


    startTime = clock();
    for(int i = 0; i < 10500; i++){
         //Store the starting time
         t1.deleteKey(array1[i]);
    }

    //Compute the number of seconds that passed since the starting time
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    da7 = duration;

     // 12000


    for(int i = 0; i < 12000; i++){
         //Store the starting time
        array1[i] = rand();
    }

        startTime = clock();
    for(int i = 0; i < 12000; i++){
         //Store the starting time
         t1.insertKey(array1[i]);
    }

    //Compute the number of seconds that passed since the starting time
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    d8 = duration;


    startTime = clock();
    for(int i = 0; i < 12000; i++){
         //Store the starting time
         t1.deleteKey(array1[i]);
    }

    //Compute the number of seconds that passed since the starting time
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    da8 = duration;


     // 13500


    for(int i = 0; i < 13500; i++){
         //Store the starting time
        array1[i] = rand();
    }

     startTime = clock();
    for(int i = 0; i < 13500; i++){
         //Store the starting time
         t1.insertKey(array1[i]);
    }

    //Compute the number of seconds that passed since the starting time
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    d9 = duration;


    startTime = clock();
    for(int i = 0; i < 13500; i++){
         //Store the starting time
         t1.deleteKey(array1[i]);
    }

    //Compute the number of seconds that passed since the starting time
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    da9 = duration;

     // 15000


    for(int i = 0; i < 15000; i++){
         //Store the starting time
        array1[i] = rand();
    }

     startTime = clock();
    for(int i = 0; i < 15000; i++){
         //Store the starting time
         t1.insertKey(array1[i]);
    }

    //Compute the number of seconds that passed since the starting time
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    d10 = duration;


    startTime = clock();
    for(int i = 0; i < 15000; i++){
         //Store the starting time
         t1.deleteKey(array1[i]);
    }

    //Compute the number of seconds that passed since the starting time
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    da10 = duration;


        cout <<    " Part e - Time analysis of Binary Search Tree - part 1   "  << endl;
        cout <<    " ------------------------------------------------------ "   << endl;
        cout <<    " Tree Size Time Elapsed                                 "   << endl;
        cout <<    " ------------------------------------------------------ "   << endl;
        cout <<    " 1500        "     <<         d1                              << endl;
        cout <<    " 3000        "     <<          d2                             << endl;
        cout <<    " 4500        "     <<          d3                             << endl;
        cout <<    " 6000        "     <<          d4                             << endl;
        cout <<    " 7500        "     <<           d5                            << endl;
        cout <<    " 9000        "     <<           d6                            << endl;
        cout <<    " 10500       "     <<            d7                           << endl;
        cout <<    " 12000       "     <<             d8                          << endl;
        cout <<    " 13500       "     <<             d9                          << endl;
        cout <<    " 15000       "     <<              d10                         << endl;
        cout <<    " ------------------------------------------------------ "   << endl;


         cout <<    " Part e - Time analysis of Binary Search Tree - part 2   "  << endl;
        cout <<    " ------------------------------------------------------ "   << endl;
        cout <<    " Tree Size Time Elapsed                                 "   << endl;
        cout <<    " ------------------------------------------------------ "   << endl;
        cout <<    " 1500        "     <<         da1                              << endl;
        cout <<    " 3000        "     <<          da2                             << endl;
        cout <<    " 4500        "     <<          da3                             << endl;
        cout <<    " 6000        "     <<          da4                             << endl;
        cout <<    " 7500        "     <<           da5                            << endl;
        cout <<    " 9000        "     <<           da6                            << endl;
        cout <<    " 10500       "     <<            da7                           << endl;
        cout <<    " 12000       "     <<             da8                          << endl;
        cout <<    " 13500       "     <<             da9                          << endl;
        cout <<    " 15000       "     <<              da10                         << endl;
        cout <<    " ------------------------------------------------------ "   << endl;

}
