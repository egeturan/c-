#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h> 

typedef struct graph Graph;
typedef struct node Node;
typedef struct heap Heap;

struct node
{
    Node *next;
    int index;
    int partition;
    int fixed;
    int cost;
};

//Structs to represent Graph and 
struct graph {
    Node entries[10000000];
    int nodeCount;
};

struct heap{
    Node entries[10000000];
    int heapSize;
};

//HEAP FUNCTIONS START ***********************************************************

void heapify(Heap* heap, int j, int n){
    int largest = j;
    if (((2 * j) <= n) && (heap->entries[2 * j].cost > heap->entries[j].cost)){
        largest = 2 * j;
    }
    if (((2*j + 1) <= n) && (heap->entries[2 * j + 1].cost > heap->entries[largest].cost)){
        largest = 2 * j + 1;
    }
    if (largest != j){
        //exhange
        int temp_index = heap->entries[j].index;
        int temp_cost = heap->entries[j].cost;

        heap->entries[j].index = heap->entries[largest].index;
        heap->entries[j].cost = heap->entries[largest].cost;

        heap->entries[largest].index = temp_index;
        heap->entries[largest].cost = temp_cost;
        heapify(heap, largest, n);
    }
}

void build_heap(Heap* heap){
    int heapSize = heap->heapSize;
    int start = heapSize / 2;
    for(int i = start; i >= 1; i--){
        heapify(heap, i, heapSize);
    }
}


void extract_max(Heap *heap, Node *newHeapNode){
    newHeapNode->index = heap->entries[1].index;
    newHeapNode->cost = heap->entries[1].cost;
    newHeapNode->fixed = heap->entries[1].fixed;
    int heapSize = heap->heapSize;
    heap->entries[1].index = heap->entries[heap->heapSize].index;
    heap->entries[1].cost = heap->entries[heap->heapSize].cost;
    heap->entries[1].fixed = heap->entries[heap->heapSize].fixed;
    heap->heapSize = heapSize - 1;
    heapify(heap, 1, heap->heapSize);
}

void printHeap(Heap * heap){
    int heapSize = heap->heapSize;
    printf("%d", heap->heapSize);
    for(int i = 1; i < heapSize; i++){
        printf("Heap index %d, node cost %d\n", heap->entries[i].index, heap->entries[i].cost);
    }
}



//HEAP FUNCTIONS END ***********************************************************

//GRAPH FUNCTIONS START ***********************************************************

// A utility function to print the adjacency list  
// representation of graph 

void printGraph(Graph *graph) 
{ 
    int totalNode = 0;
    for (int i = 0; i < graph->nodeCount; i++) 
    {
        int edge_count = 0;
        int partitionACount = 0;
        int partitionBCount = 0;
        Node *temp = &graph->entries[i];
        //printf("\n Adjacency list of vertex %d\n head ", i); 
        while (temp != NULL) 
        { 
            if(temp->partition == 0 && edge_count != 0){
                partitionACount++;
            }
            else if(temp->partition == 1 && edge_count != 0)
            {
                partitionBCount++;
            }
            printf("-> %d [%d]", temp->index, temp->partition); 
            temp = temp->next; 
            totalNode = totalNode + 1;
            edge_count++;
        } 
        printf("\n");
        printf("Edge Count: %d, Partition A count: %d, Partition B count: %d\n", edge_count - 1,partitionACount, partitionBCount); 
    } 
    printf("Total #of nodes in graph: %d\n", totalNode);
} 



void removeGraph(Graph* graph) 
{ 
    int removedNodeCount = 0;
    for (int i = 0; i < graph->nodeCount; i++) 
    { 
        Node* temp = &graph->entries[i];
        temp = temp->next; 
        //printf("\n Adjacency list of vertex %d\n head ", i); 
        while (temp != NULL) 
        { 
            Node* del = temp;
            temp = temp->next; 
            removedNodeCount++;
            free(del);
        }
        //printf("\n"); 
    }
    //printf("Removed number of nodes are: %d\n", removedNodeCount + (graph->nodeCount));
    free(graph); 
} 



void backup_graph(Graph* graph_src, Graph* graph_dest){
    graph_dest->nodeCount = graph_src->nodeCount;

    for(int i = 0; i < graph_dest->nodeCount; i++){
        graph_dest->entries[i].next = NULL;
        graph_dest->entries[i].index = graph_src->entries[i].index;
        graph_dest->entries[i].fixed = graph_src->entries[i].fixed;
        graph_dest->entries[i].partition = graph_src->entries[i].partition;
        graph_dest->entries[i].cost = graph_src->entries[i].cost;
    }
} 


//GRAPH FUNCTIONS END ***********************************************************

//HANDLER FUNCTIONS START

void swapNodes(Graph* graph, int indexA, int indexB){
    int temp = graph->entries[indexA].partition;
    //printf("index %d A partition: %d\n", indexA, graph->head[indexA].partition);
    //printf("index %d B partition: %d\n", indexB, graph->head[indexB].partition);
    graph->entries[indexA].partition = graph->entries[indexB].partition;
    graph->entries[indexB].partition = temp;
    //printf("index %d A partition: %d\n", indexA, graph->head[indexA].partition);
    //printf("index %d B partition: %d\n", indexB, graph->head[indexB].partition);
    graph->entries[indexA].fixed = 1;
    graph->entries[indexB].fixed = 1;
}

void swapNodes2(Graph* graph, int indexA, int indexB){
    int temp = graph->entries[indexA].partition;
    //printf("index %d A partition: %d\n", indexA, graph->head[indexA].partition);
    //printf("index %d B partition: %d\n", indexB, graph->head[indexB].partition);
    graph->entries[indexA].partition = graph->entries[indexB].partition;
    graph->entries[indexB].partition = temp;
    //printf("index %d A partition: %d\n", indexA, graph->head[indexA].partition);
    //printf("index %d B partition: %d\n", indexB, graph->head[indexB].partition);
    graph->entries[indexA].fixed = 0;
    graph->entries[indexB].fixed = 0;
}

int makeDecision(Graph * graph, Graph * graph_backup, int *swap_src, int * swap_dest, int *gain_for_each_pass, int pass_count, int * gain_max_per_iteration, int * result, int number_of_iterations)
{
    int gmax = 0;
    //Step 4
    int temp = 0;
    int movement_sequence = 1;
    int search_improvement = 1; //boolean to find movement sequence

    for(int i = 1; i <= pass_count; i++)
    {
        temp = gmax;
        gmax = gmax + gain_for_each_pass[i];
        //printf("Gmax is: %d and index is: %d********\n", gmax, i);
        gain_max_per_iteration[i] = gmax;
        if(temp > gmax && search_improvement)
        {
            movement_sequence = i - 1;
            search_improvement = 0;
        }
    }
    int max_index = 1;
    int max_element = gain_max_per_iteration[1];
    for(int j = 1; j <= pass_count; j++){
        if (max_element < gain_max_per_iteration[j]){
            max_element = gain_max_per_iteration[j];
            max_index = j;
        }
    }
    //printf("*************Max Index is: %d, Max Element is: %d**************\n", max_index, max_element);
    //printf("Gmax is: %d\n", gmax);

    result[number_of_iterations - 1] = max_index;

    if(gmax > 0)
    {   
        // if gmax > 0 then find Gmax sequence and execute m swaps
        for(int i = 0; i < graph->nodeCount; i++)
        {
            graph->entries[i].fixed = 0; //can be used again
            //backup partition and make all not fixed
            graph->entries[i].partition = graph_backup->entries[i].partition;
        }
        //old graph acquired now apply movement sequence that maximizes Gmax

        for(int i = 0; i < max_index; i++)
        {
            int indexA = swap_src[i];
            int indexB = swap_dest[i];
            swapNodes2(graph, indexA, indexB);
        }
        return 1;
    }
    else if(gmax <= 0)
    {
        //load last partition
        for(int i = 0; i < graph->nodeCount; i++)
        {
            graph->entries[i].partition = graph_backup->entries[i].partition;
        }   
        return 0;       
    }  
}


Graph* obtainGraphFromInputs(int * data, int vertexsize, int edgesize){
    Graph* graph = malloc(sizeof(Graph));
    graph->nodeCount = vertexsize;
    int partitionA = 0;
    int partitionB = 0;

    for(int i = 0; i < graph->nodeCount; i++){
        graph->entries[i].next = NULL;
        graph->entries[i].index = i + 1;
        graph->entries[i].fixed = 0;
        graph->entries[i].cost = 0;
        if (i % 2 == 1){
            graph->entries[i].partition = 0; //0 represents partition A
            partitionA++;
        }else{
            graph->entries[i].partition = 1; //1 represents partition B
            partitionB++;
        }
    }

    printf("Partition A is: %d", partitionA);
    printf("Partition B is: %d", partitionB);

    //READ THE INPUTS AND CREATE GRAPH

    int totalInputSize = (edgesize * 2) + 3;
    int i = 3;
    int total_nodes = 0;
    while(i < totalInputSize){
        //first index edge src
        int src_index = data[i] - 1;
        //second index edge dest
        int dest_index = data[i + 1] - 1;
        total_nodes = total_nodes + 1;

        //create newnode to add to graph as an edge
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->next = NULL;
        newNode->index = dest_index;

        if(newNode->index % 2 == 1){
            newNode->partition = 0;
        }else{
            newNode->partition = 1;
        }
        //take the source node
        Node * temp = &graph->entries[src_index];
        //printf("Temp is: %p\n", temp);


        if(temp == NULL){
            printf("Head is Null\n");
        }

        //move until next is NULL
        while(temp->next != NULL){
            temp = temp->next;
        }

        //add newnode
        temp->next = newNode;

        //create newnode to add to graph as an edge
        Node* newNode2 = (Node*)malloc(sizeof(Node));

        newNode2->next = NULL;
        newNode2->index = src_index;
        if(newNode2->index % 2 == 1){
            newNode2->partition = 0;
        }else{
            newNode2->partition = 1;
        }
        temp = &graph->entries[dest_index];
        if(temp == NULL){
            printf("Head is Null\n");
        }
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode2;   
        i = i + 2;
    } 
    //printGraph(graph);
    printf("Total number of (V, E): %d\n", total_nodes);
    return graph;
}

//HANDLER FUNCTIONS END


void printPartitions(Graph* graph){
    printf("Partition A: \n");
    for(int i = 0; i < graph->nodeCount; i++){
        if(graph->entries[i].partition == 0){
            printf("%d ", graph->entries[i].index);
        }
    }
    printf("Partition B: \n");
    for(int i = 0; i < graph->nodeCount; i++){
        if(graph->entries[i].partition == 1){
            printf("%d ", graph->entries[i].index);
        }
    }     
}

void simpler_kl(Graph* graph, int edgeCount, int max_number_of_iterations){
    //Step 0:
    //create initial arbitrary partitioning
    int sizeA = graph->nodeCount / 2;
    int sizeB = graph->nodeCount - sizeA;
    //printf("Size A: %d\n", sizeA);
    //printf("Size B: %d\n", sizeB);
    clock_t t; 
    t = clock(); 

    int fixed_count = 0;

    //Initialize Heaps
    //Create Heap for partition A
    Heap* heapA = (Heap*) malloc(sizeof(Heap));
    heapA->heapSize = sizeA + 1;
    for(int i = 1; i < heapA->heapSize + 1; i++){
        heapA->entries[i].index = i;
        heapA->entries[i].partition = 0;
        heapA->entries[i].next = NULL;
        heapA->entries[i].fixed = 0;
        heapA->entries[i].cost = 0;
    }

    //Create Heap for partition B
    Heap* heapB = (Heap*) malloc(sizeof(Heap));
    heapB->heapSize = sizeB + 1;
    for(int i = 1; i < heapB->heapSize + 1; i++){
        heapB->entries[i].index = i + sizeA;
        heapB->entries[i].partition = 1;
        heapB->entries[i].next = NULL;
        heapA->entries[i].fixed = 0;
        heapB->entries[i].cost = 0;
    }

    printf("Pass\n");

    //number of passes
    int pass_count = 1;

    //improving
    int improving = 1;
    int numberofiterations = 0;

    //Keep Gain values
    int *gain_for_each_pass = (int *) malloc(100000000 * sizeof(int));
    int * gain_max_per_iteration = (int *) malloc(100000000 * sizeof(int));
    int *swap_src = (int *) malloc(100000000 * sizeof(int));
    int *swap_dest = (int *) malloc(100000000 * sizeof(int));
    int *result = (int *) malloc(100 * sizeof(int));
    int swapCount = 0;

    Graph* graph_backup = (Graph*) malloc(sizeof(Graph));
    Node* targetNodePartitionA = (Node*)malloc(sizeof(Node));
    Node* targetNodePartitionB = (Node*)malloc(sizeof(Node));
    

  
    while(improving == 1)
    { // ******* (1)
        
        //partition backup
        backup_graph(graph, graph_backup);
        swapCount = 0;
        numberofiterations++;
        fixed_count = 0;
        pass_count = 1;
        //boolean for all fixed
        int all_fixed = 0;

        while(all_fixed == 0)
        {  // ******* (2)
                    
            //printf("Pass is: %d\n", pass_count);

            //Step 1:
            //Compute D(v) for all nodes v in V.

            heapA->heapSize = 1;
            heapB->heapSize = 1;
            
            int heapAIndex = 1;
            int heapBIndex = 1;
            int not_fixed_count = 0;

            for(int i = 0; i < graph->nodeCount; i++)
            {
                if(graph->entries[i].fixed == 0) //calculate cost for each not fixed
                {
                    int partitionASize = 0;
                    int partitionBSize = 0;
                    int src_node = graph->entries[i].index;
                    int externalCount = 0;
                    int internalCount = 0;
                    int edge_count = 0;

                    Node * targetNode = &graph->entries[src_node - 1];

                    //Search its edges from the graph
                    Node * edgeNodes = &graph->entries[src_node - 1];
                    edgeNodes = edgeNodes->next;
   
                    while(edgeNodes != NULL)
                    {
                        if(targetNode->partition == 0)
                        { //node in partition A
                            //Calculate Costs for the partition A
                            partitionASize++;
                            if(graph->entries[edgeNodes->index -1].partition == 0)
                            {
                                internalCount++;
                            }else
                            {
                                externalCount++;
                            }
                        }
                        else if(targetNode->partition == 1)
                        {
                            //Calculate Costs for the partition B
                            partitionBSize++;
                            if(graph->entries[edgeNodes->index -1].partition == 1)
                            {
                                internalCount++;
                            }else{
                                externalCount++;
                            }
                        }
                        else
                        {
                            printf("Error**********\n");
                        }
                        edge_count++;
                        edgeNodes = edgeNodes->next;
                    }

                    /*
                    if(pass_count > 15 && pass_count < 20){
                        printf("Iteration: %d Node number: %d edge count: %d\n", numberofiterations ,src_node, edge_count);
                        printf("Internal Cost is: %d\n", internalCount);
                        printf("External Cost is: %d\n", externalCount);     
                    }       
                    */         

                    //CALCULATE COST

                    int cost_for_node = externalCount - internalCount;
                    //put it into heap
                    if(targetNode->partition == 0)// it is in partition A
                    {
                        //printf("Partition A, Src Node is: %d\n", src_node);
                        //FILL THE HEAP
                        heapA->entries[heapAIndex].index = src_node; 
                        heapA->entries[heapAIndex].cost = cost_for_node; 
                        //printf("Heap Node index: %d, its index value %d, cost is: %d\n", src_node, heapA->head[src_node].index, heapA->head[src_node].cost);
                        heapAIndex++;
                        heapA->heapSize = heapA->heapSize + 1;
                    }
                    else if(targetNode->partition == 1)// it is in partition B
                    {
                        //printf("Partition B, Src Node is: %d\n", src_node);
                        //FILL THE HEAP
                        int targetIndex = src_node - sizeA;
                        //printf("Target index is: %d\n", heapBIndex);
                        heapB->entries[heapBIndex].index = src_node;
                        heapB->entries[heapBIndex].cost = cost_for_node; 
                        //printf("Heap Node index: %d, its index value %d, cost is: %d\n", targetIndex, heapB->head[heapBIndex].index, heapB->head[heapBIndex].cost);
                        heapBIndex++;
                        heapB->heapSize = heapB->heapSize + 1;
                    }
                    //printf("Graph Node count is: %d:, Pass count is: %d\n", i ,pass_count);
                    not_fixed_count++;
                }
            }

            /*
            printf("Graph Node Count is: %d\n", graph->nodeCount);
            printf("Not fixed count is: %d\n", not_fixed_count);
            printf("Heap A Size is: %d\n", heapA->heapSize);
            printf("Heap B Size is: %d\n", heapB->heapSize);
            */


            //Step 2:
            //Choose ai and bi such that change in gain of a and b is maximized
            //Swap and fix ai and bi

            //Call Build Heap
            build_heap(heapA);
            build_heap(heapB);
            
            extract_max(heapA, targetNodePartitionA);
            extract_max(heapB, targetNodePartitionB);

            int indexA = targetNodePartitionA->index - 1;
            int indexB = targetNodePartitionB->index - 1;
            int g = targetNodePartitionA->cost + targetNodePartitionB->cost;
            gain_for_each_pass[pass_count] = g;

            swapNodes(graph, indexA, indexB);

            swap_src[swapCount]= indexA;
            swap_dest[swapCount] = indexB;
            swapCount++;

            /*
            printf("Target Node 1 index is: %d, cost is: %d\n", targetNodePartitionA->index, targetNodePartitionA->cost);
            printf("Target Node 2 index is: %d, cost is: %d\n", targetNodePartitionB->index, targetNodePartitionB->cost);
            printf("Heap A size: %d\n", heapA->heapSize);
            printf("Heap B size: %d\n", heapB->heapSize);
            */

            heapAIndex = 1;
            heapBIndex = 1;

            fixed_count = fixed_count + 2;
            //printf("Fixed Count is: %d\n", fixed_count);
            //Step 3:
            //if all nodes are fixed then go to Step 4:
            //Otherwise compute and update D values for all nodes that are connected to ai and bi and are not fixed.
            if(fixed_count >= graph->nodeCount) //all fixed for that iteration
            {
                //printPartitions(graph);
                //printf("ITERATION %d is completed.\n", numberofiterations);
                all_fixed = 1;
                improving = makeDecision(graph, graph_backup, swap_src, swap_dest, gain_for_each_pass, pass_count, gain_max_per_iteration, result, numberofiterations);  
                pass_count = 1;
            }
            else
            {
                pass_count++;
            }

            if(numberofiterations == max_number_of_iterations){
                all_fixed = 1;
                improving = 0;
            }
        }  // ******* (2)
        //improving = 0;
    } // ******* (1)

    printf("KL Bisection completed\n");
    printf("FINAL OUTPUT: \n");

    //Calculate Time spent
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 

    //FINAL OUTPUT
    printf("Initial Cut Size: %d, Final Cut Size: %d Time Taken: %f\n", result[0], result[numberofiterations - 2], time_taken);

    //Free the memory 
    free(result);
    free(gain_max_per_iteration);
    free(targetNodePartitionA);
    free(targetNodePartitionB);
    free(gain_for_each_pass);
    free(swap_src);
    free(swap_dest);
    free(graph_backup);
    free(heapA); 
    free(heapB);
}



void simpler_kl_a(Graph* graph, int edgeCount, int max_number_of_iterations){
    //Step 0:
    //create initial arbitrary partitioning
    int sizeA = graph->nodeCount / 2;
    int sizeB = graph->nodeCount - sizeA;
    //printf("Size A: %d\n", sizeA);
    //printf("Size B: %d\n", sizeB);
    clock_t t; 
    t = clock(); 

    int fixed_count = 0;

    //Initialize Heaps
    //Create Heap for partition A
    Heap* heapA = (Heap*) malloc(sizeof(Heap));
    heapA->heapSize = sizeA + 1;
    for(int i = 1; i < heapA->heapSize + 1; i++){
        heapA->entries[i].index = i;
        heapA->entries[i].partition = 0;
        heapA->entries[i].next = NULL;
        heapA->entries[i].fixed = 0;
        heapA->entries[i].cost = 0;
    }

    //Create Heap for partition B
    Heap* heapB = (Heap*) malloc(sizeof(Heap));
    heapB->heapSize = sizeB + 1;
    for(int i = 1; i < heapB->heapSize + 1; i++){
        heapB->entries[i].index = i + sizeA;
        heapB->entries[i].partition = 1;
        heapB->entries[i].next = NULL;
        heapA->entries[i].fixed = 0;
        heapB->entries[i].cost = 0;
    }

    printf("Pass\n");

    //number of passes
    int pass_count = 1;

    //improving
    int improving = 1;
    int numberofiterations = 0;

    //Keep Gain values
    int *gain_for_each_pass = (int *) malloc(100000000 * sizeof(int));
    int * gain_max_per_iteration = (int *) malloc(100000000 * sizeof(int));
    int *swap_src = (int *) malloc(100000000 * sizeof(int));
    int *swap_dest = (int *) malloc(100000000 * sizeof(int));
    int *result = (int *) malloc(100 * sizeof(int));
    int swapCount = 0;

    Graph* graph_backup = (Graph*) malloc(sizeof(Graph));
    Node* targetNodePartitionA = (Node*)malloc(sizeof(Node));
    Node* targetNodePartitionB = (Node*)malloc(sizeof(Node));
    

    while(improving == 1)
    { // ******* (1)
        
        //partition backup
        backup_graph(graph, graph_backup);
        swapCount = 0;
        numberofiterations++;
        fixed_count = 0;
        pass_count = 1;
        //boolean for all fixed
        int all_fixed = 0;

        while(all_fixed == 0)
        {  // ******* (2)
                    
            //printf("Pass is: %d\n", pass_count);

            //Step 1:
            //Compute D(v) for all nodes v in V.

            heapA->heapSize = 1;
            heapB->heapSize = 1;
            
            int heapAIndex = 1;
            int heapBIndex = 1;
            int not_fixed_count = 0;

            for(int i = 0; i < graph->nodeCount; i++)
            {
                if(graph->entries[i].fixed == 0) //calculate cost for each not fixed
                {
                    int partitionASize = 0;
                    int partitionBSize = 0;
                    int src_node = graph->entries[i].index;
                    int externalCount = 0;
                    int internalCount = 0;
                    int edge_count = 0;

                    Node * targetNode = &graph->entries[src_node - 1];

                    //Search its edges from the graph
                    Node * edgeNodes = &graph->entries[src_node - 1];
                    edgeNodes = edgeNodes->next;
   
                    while(edgeNodes != NULL)
                    {
                        if(targetNode->partition == 0)
                        { //node in partition A
                            //Calculate Costs for the partition A
                            partitionASize++;
                            if(graph->entries[edgeNodes->index -1].partition == 0)
                            {
                                internalCount++;
                            }else
                            {
                                externalCount++;
                            }
                        }
                        else if(targetNode->partition == 1)
                        {
                            //Calculate Costs for the partition B
                            partitionBSize++;
                            if(graph->entries[edgeNodes->index -1].partition == 1)
                            {
                                internalCount++;
                            }else{
                                externalCount++;
                            }
                        }
                        else
                        {
                            printf("Error**********\n");
                        }
                        edge_count++;
                        edgeNodes = edgeNodes->next;
                    }

                    /*
                    if(pass_count > 15 && pass_count < 20){
                        printf("Iteration: %d Node number: %d edge count: %d\n", numberofiterations ,src_node, edge_count);
                        printf("Internal Cost is: %d\n", internalCount);
                        printf("External Cost is: %d\n", externalCount);     
                    }       
                    */         

                    //CALCULATE COST

                    int cost_for_node = externalCount - internalCount;
                    //put it into heap
                    if(targetNode->partition == 0)// it is in partition A
                    {
                        //printf("Partition A, Src Node is: %d\n", src_node);
                        //FILL THE HEAP
                        heapA->entries[heapAIndex].index = src_node; 
                        heapA->entries[heapAIndex].cost = cost_for_node; 
                        //printf("Heap Node index: %d, its index value %d, cost is: %d\n", src_node, heapA->head[src_node].index, heapA->head[src_node].cost);
                        heapAIndex++;
                        heapA->heapSize = heapA->heapSize + 1;
                    }
                    else if(targetNode->partition == 1)// it is in partition B
                    {
                        //printf("Partition B, Src Node is: %d\n", src_node);
                        //FILL THE HEAP
                        int targetIndex = src_node - sizeA;
                        //printf("Target index is: %d\n", heapBIndex);
                        heapB->entries[heapBIndex].index = src_node;
                        heapB->entries[heapBIndex].cost = cost_for_node; 
                        //printf("Heap Node index: %d, its index value %d, cost is: %d\n", targetIndex, heapB->head[heapBIndex].index, heapB->head[heapBIndex].cost);
                        heapBIndex++;
                        heapB->heapSize = heapB->heapSize + 1;
                    }
                    //printf("Graph Node count is: %d:, Pass count is: %d\n", i ,pass_count);
                    not_fixed_count++;
                }
            }

            /*
            printf("Graph Node Count is: %d\n", graph->nodeCount);
            printf("Not fixed count is: %d\n", not_fixed_count);
            printf("Heap A Size is: %d\n", heapA->heapSize);
            printf("Heap B Size is: %d\n", heapB->heapSize);
            */


            //Step 2:
            //Choose ai and bi such that change in gain of a and b is maximized
            //Swap and fix ai and bi

            //Call Build Heap
            build_heap(heapA);
            build_heap(heapB);
            
            extract_max(heapA, targetNodePartitionA);
            extract_max(heapB, targetNodePartitionB);

            int indexA = targetNodePartitionA->index - 1;
            int indexB = targetNodePartitionB->index - 1;
            int g = targetNodePartitionA->cost + targetNodePartitionB->cost;
            gain_for_each_pass[pass_count] = g;

            swapNodes(graph, indexA, indexB);

            swap_src[swapCount]= indexA;
            swap_dest[swapCount] = indexB;
            swapCount++;

            /*
            printf("Target Node 1 index is: %d, cost is: %d\n", targetNodePartitionA->index, targetNodePartitionA->cost);
            printf("Target Node 2 index is: %d, cost is: %d\n", targetNodePartitionB->index, targetNodePartitionB->cost);
            printf("Heap A size: %d\n", heapA->heapSize);
            printf("Heap B size: %d\n", heapB->heapSize);
            */

            heapAIndex = 1;
            heapBIndex = 1;

            fixed_count = fixed_count + 2;
            //printf("Fixed Count is: %d\n", fixed_count);
            //Step 3:
            //if all nodes are fixed then go to Step 4:
            //Otherwise compute and update D values for all nodes that are connected to ai and bi and are not fixed.
            if(fixed_count >= graph->nodeCount) //all fixed for that iteration
            {
                //printPartitions(graph);
                //printf("ITERATION %d is completed.\n", numberofiterations);
                all_fixed = 1;
                improving = makeDecision(graph, graph_backup, swap_src, swap_dest, gain_for_each_pass, pass_count, gain_max_per_iteration, result, numberofiterations);  
                pass_count = 1;
            }
            else
            {
                pass_count++;
            }

            if(numberofiterations == max_number_of_iterations){
                all_fixed = 1;
                improving = 0;
            }
        }  // ******* (2)
        //improving = 0;
    } // ******* (1)

    printf("KL Bisection completed\n");
    printf("FINAL OUTPUT: \n");

    //Calculate Time spent
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 

    //FINAL OUTPUT
    printf("Initial Cut Size: %d, Final Cut Size: %d Time Taken: %f\n", result[0], result[numberofiterations - 2], time_taken);

    //Free the memory 
    free(result);
    free(gain_max_per_iteration);
    free(targetNodePartitionA);
    free(targetNodePartitionB);
    free(gain_for_each_pass);
    free(swap_src);
    free(swap_dest);
    free(graph_backup);
    free(heapA); 
    free(heapB);
}


int main(int argc, char **argv){
    int fd;
    int vertexCount;
    int edgeCount;

    if(argc == 3){
        char *buffer = (char *) malloc(100000000 * sizeof(char));
        int *values = (int *) malloc(100000000 * sizeof(int));
        int size;
        printf("Arguments are valid\n");
        fd = open(argv[1], O_RDONLY);

        char *c = argv[2];
        printf("Option : %c\n", *c);
        

        if(fd < 0)
        {
            printf("Error while readin the file, Error is: %d\n", fd);
        }
        size = read(fd, buffer, 100000000);
        int valueCount = 0;
        int charOrder = 0;
        char *charCarrier = (char *) malloc(2000 * sizeof(char));
        //Create integer array with these data
        int passTheLine = 0;
        for (int i = 0; i < size; ++i)
        {
            if(buffer[i] == '%')
            {
                passTheLine = 1;
            }
            if(passTheLine == 0)
            {
                if (buffer[i] == '\n' || buffer[i] == ' ')
                {
                    values[valueCount] = atoi(charCarrier);
                    memset(charCarrier, ' ', 10 * sizeof(char)); //make it empty the filled areas of the array
                    valueCount++;
                    charOrder = 0;
                }
                else
                {
                    charCarrier[charOrder] = buffer[i];
                    charOrder++;
                }
            }
            if (passTheLine == 1 && buffer[i] == '\n')
            {
                passTheLine = 0;
            }
        }
        printf("Value Count %d\n", valueCount);
        vertexCount = values[0];
        edgeCount = values[2];
        printf("Vertex Count is: %d\n", vertexCount);
        printf("Edge Count is: %d\n", edgeCount);
        int max_number_of_iterations = 10;
        Graph *graph = obtainGraphFromInputs(values, vertexCount, edgeCount);

        //Part A 
        if (*c == 'a'){
            simpler_kl_a(graph, edgeCount, max_number_of_iterations);
        }
        //Part B
        if (*c == 'b'){
            simpler_kl(graph, edgeCount, max_number_of_iterations);
        }
        //printGraph(graph);

        removeGraph(graph);
        free(charCarrier);
        free(values);
        free(buffer);
    }else{
        printf("Arguments are invalid. Terminated.");
        return 0;
    }
}