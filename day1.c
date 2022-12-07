#include "stdio.h"
#include "stdlib.h"

// find highest number in array
int findBest(int *, int);

int main(int argc, char **argv) {

    int elves[1024];
    int counter = 0;
    char callorie[64];
    int currentRead;
    FILE *inputFile;

    for(int i=0; i<1024; ++i) {
        elves[i] = 0;
    }

    inputFile = fopen("input1.txt", "r");
    while (fgets(callorie, 64, inputFile) != NULL) {
        currentRead = atoi(callorie);
        if (currentRead) {
            elves[counter] += currentRead;
        } else {
            counter++;
        }
    }

    printf("%d\n", findBest(elves, counter));

    return 0;
}

int findBest(int *arr, int size) {
    int best = 0;
    for (int i=0; i<size; ++i) {
        if (arr[i] > best) {
            best = arr[i];
        }
    }
    return best;
}

