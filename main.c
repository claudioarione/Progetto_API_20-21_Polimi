#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NIL -1

typedef struct heap{
    int heapSize;
    int maxHeapSize;
    struct graphType *arrayOfElements;
}heap;

typedef struct graphType{
    int distance;
    int graphNumber;
}graphType;

int dijkstraAlgo(int *graph, int numNodes);

int strToInt(char *input);

int findMin(int *listOfDistances, int *listOfPrevious, int nodes);

heap insertInHeap(heap heap, int graphNumber, int value);

void swap(graphType *firstGraphPointer, graphType *secondGraphPointer);

heap deleteMaxFromHeap(heap inputHeap);

heap maxHeapifyFromMaxElem(heap inputHeap, int position);

int main()
{
    int num_nodes, topK, graphNumber = 0, insertedGraphCount = 0;
    char inputText[20];
    char *trash;
    heap topKHeap;

    if(!scanf("%d %d \n", &num_nodes, &topK))
        return 1;

    topKHeap.maxHeapSize = topK;
    topKHeap.heapSize = 0;
    topKHeap.arrayOfElements = malloc(topK*sizeof(graphType));

    while(fgets(inputText, sizeof(inputText), stdin) != NULL){
        char firstChar = inputText[0];
        if(firstChar == 'A'){
            int *graphMatrix = malloc(num_nodes*num_nodes*sizeof(int));
            for (int i = 0; i < num_nodes; ++i) {
                int maxLineSize = num_nodes*10;
                char line[maxLineSize];
                trash = fgets(line, maxLineSize, stdin);
                *(trash) = 'a';
                int elementInRow = 0;
                for (int j = 0; line[j] != '\n' ; j++) {
                    char numberInString[11];
                    int index = 0;
                    while (line[j] != ',' && line[j] != '\n'){
                        numberInString[index] = line[j];
                        index++;
                        j++;
                    }
                    numberInString[index] = '\0';
                    int number = strToInt(numberInString);

                    *(graphMatrix + num_nodes*i + elementInRow) = number;
                    elementInRow++;

                    if(line[j] == '\n')
                        break;
                }
            }
            // Calculate Dijkstra for the given graph
            int result = dijkstraAlgo(graphMatrix, num_nodes);

            if(insertedGraphCount < topK){
                // Search in the heap the node n with max distance
                // if (n.key > result) then delete n and insert result in the Tree
                topKHeap = insertInHeap(topKHeap, graphNumber, result);
                insertedGraphCount++;
            }
            else{
                int maxWeight = (*(topKHeap.arrayOfElements)).distance;
                if(result < maxWeight){
                    topKHeap = deleteMaxFromHeap(topKHeap);
                    topKHeap = insertInHeap(topKHeap, graphNumber, result);
                }
            }

            graphNumber++;

            free(graphMatrix);
        }
        else if(firstChar == 'T'){
            // Print TopK graphs
            graphType *graphsWeightList = topKHeap.arrayOfElements;
            if(topKHeap.heapSize <= 0){
                printf("\n");
            }
            else{
                for (int i = 0; i < (insertedGraphCount-1); i++) {
                    printf("%d ", (graphsWeightList+i)->graphNumber);
                }
                printf("%d\n", (graphsWeightList+insertedGraphCount-1)->graphNumber);
            }
        }
    }

    free(topKHeap.arrayOfElements);

    return 0;
}

int strToInt(char *input) {
    int result = 0;
    for (int i = 0; *(input+i) != '\0'; i++) {
        result = (result*10 + *(input+i)) - '0';
    }
    return result;
}

int dijkstraAlgo(int *graph, int numNodes) {

    int sum = 0;

    int *listOfDistances = malloc(numNodes*sizeof(int));
    int *listOfPrevious = malloc(numNodes*sizeof(int));

    *(listOfDistances) = 0;
    *(listOfPrevious) = NIL;

    for (int i = 1; i < numNodes; i++) {
        *(listOfDistances+i) = INT_MAX;
        // Every node in the list of previous is identified by his index
        *(listOfPrevious+i) = NIL;
    }
    for(int v = 0; v< numNodes; v++){
        int elementWithLessDist = findMin(listOfDistances, listOfPrevious, numNodes);
         *(listOfPrevious+elementWithLessDist) = 1;
        int distanceOfTheElementWithLessDist = *(listOfDistances + elementWithLessDist);
        // The considered line k starts after k*numNodes elements and ends in (k+1)*numNodes
        for (int i = 0; i < numNodes; i++) {
            int weightOfLinkToI = *(graph + elementWithLessDist*numNodes + i);
            if(weightOfLinkToI != 0 && i != elementWithLessDist && *(listOfPrevious+i) != 1){
                // Node i is adjacent to node k, it's not node k and hasn't already been checked (the research is not "going back")
                int distance = weightOfLinkToI + distanceOfTheElementWithLessDist;
                int distanceOfI = *(listOfDistances+i);
                if(distanceOfI > distance){
                    *(listOfDistances+i) = distance;
                }
            }
        }
    }

    free(listOfPrevious);

    for (int i = 0; i < numNodes; i++) {
        int val = *(listOfDistances+i);
        if(val >= INT_MAX)
            val = 0;
        sum += val;
    }

    free(listOfDistances);

    return sum;
}

int findMin(int *listOfDistances, int *listOfPrevious, int nodes) {
    int min = INT_MAX, minIndex = 0;
    for (int i = 0; i < nodes; i++) {
        int curValue = *(listOfDistances+i);
        if(curValue < min && *(listOfPrevious+i) != 1){
            min = curValue;
            minIndex = i;
        }
    }
    return minIndex;
}

heap insertInHeap(heap inputHeap, int graphNumber, int value) {
    inputHeap.heapSize++;
    int index = inputHeap.heapSize - 1;
    graphType *heapToModify = inputHeap.arrayOfElements;
    (*(heapToModify+index)).graphNumber = graphNumber;
    (*(heapToModify+index)).distance = value;

    while(index != 0 && (*(heapToModify+((index-1)/2))).distance <= (*(heapToModify+index)).distance){

        if((*(heapToModify+((index-1)/2))).distance != (*(heapToModify+index)).distance)
            swap(heapToModify+index, heapToModify+(index-1)/2);
        index = (index-1)/2;
    }

    return inputHeap;
}

void swap(graphType *firstGraphPointer, graphType *secondGraphPointer) {
    graphType tmp;
    tmp = *firstGraphPointer;
    (*firstGraphPointer).distance = (*secondGraphPointer).distance;
    (*firstGraphPointer).graphNumber = (*secondGraphPointer).graphNumber;
    (*secondGraphPointer).distance = tmp.distance;
    (*secondGraphPointer).graphNumber = tmp.graphNumber;
}

heap deleteMaxFromHeap(heap inputHeap) {
    if(inputHeap.heapSize < 1){
        inputHeap.arrayOfElements->distance = INT_MAX;
        return inputHeap;
    }
    (*(inputHeap.arrayOfElements)) = (*(inputHeap.arrayOfElements + inputHeap.heapSize -1));
    inputHeap.heapSize --;
    inputHeap = maxHeapifyFromMaxElem(inputHeap, 0);
    return inputHeap;
}

heap maxHeapifyFromMaxElem(heap inputHeap, int position) {
    int leftSon = 2*position + 1, rightSon = 2*position + 2;
    int posMax;
    if(leftSon < inputHeap.heapSize && (*(inputHeap.arrayOfElements + leftSon)).distance > (*(inputHeap.arrayOfElements + position)).distance)
        posMax = leftSon;
    else
        posMax = position;
    if(rightSon < inputHeap.heapSize && (*(inputHeap.arrayOfElements + rightSon)).distance > (*(inputHeap.arrayOfElements + posMax)).distance)
        posMax = rightSon;
    if(posMax != position){
        swap(inputHeap.arrayOfElements + position, inputHeap.arrayOfElements + posMax);
        maxHeapifyFromMaxElem(inputHeap, posMax);
    }
    return inputHeap;
}
