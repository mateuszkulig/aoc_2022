#include "stdio.h"
#include "stdlib.h"

// find highest number in array
int findBest(int *, int);

// sort int array descending via bubble sort;
void bubbleSortDescending(int *, int);

// count and return first n elements in int array
int countFirstElements(int *, int);

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

    bubbleSortDescending(elves, counter);

    printf("%d", countFirstElements(elves, 3));

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

void bubbleSortDescending(int *arr, int size) {
    int temp;
    int switched = 1;
    while (switched) {
        switched = 0;
        for (int i=0; i<size; ++i) {
            if (arr[i+1] > arr[i]) {
                switched = 1;
                temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
            }
        }
    }
}

int countFirstElements(int *arr, int n) {
    int total = 0;
    for(int i=0; i<n; ++i) {
        total += arr[i];
    }

    return total;
}

