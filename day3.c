#include "stdio.h"
#include "string.h"

// find what char appears in both compartments
char findSharingItem(char *buffer);

// find what char appears in 3-rucksack group
char findGroupSharingItem(char *buffer1, char *buffer2, char *buffer3);

// get the length of characters in 128char buffer
int getBufferLength(char *buffer);

int main(int argc, char **argv) {
    FILE    *inputFile;
    char    buffer[128];
    char    rucksacks[3][128];
    char    repeating;
    int     total = 0;
    int     counter = 0;

    inputFile = fopen("input3.txt", "r");
    
    while (fgets(buffer, 128, inputFile) != 0) {
        strcpy(rucksacks[counter%3], buffer);
        if (!((counter+1)%3)) {
            repeating = findGroupSharingItem(rucksacks[0], rucksacks[1], rucksacks[2]); // could probably pass an whole array and divide in func
            if (repeating < 97) {   // upper letter
                total += repeating - 65 + 27;   // A ascii code is 65, upper letter priorities start with 27
            } else {
                total += repeating - 97 + 1;    // a ascii code is 97, lower letter priorities start with 1
            }
        }
        counter++;

        // first part
        // repeating = findSharingItem(buffer);
        // if (repeating < 97) {   // upper letter
        //     total += repeating - 65 + 27;   // A ascii code is 65, upper letter priorities start with 27
        // } else {
        //     total += repeating - 97 + 1;    // a ascii code is 97, lower letter priorities start with 1
        // }
    }

    printf("%d\n", total);
    fclose(inputFile);

    return 0;
}

char findGroupSharingItem(char *buffer1, char *buffer2, char *buffer3) {
    for (int i=0; i<getBufferLength(buffer1); ++i) {
        for (int j=0; j<getBufferLength(buffer2); ++j) {
            for (int k=0; k<getBufferLength(buffer3); ++k) {
                if (buffer1[i] == buffer2[j] && buffer1[i] == buffer3[k] && buffer2[j] == buffer3[k]) {
                    return buffer1[i];
                }
            }
        }
    }
}

char findSharingItem(char *buffer) {
    char    firstHalf[64];
    char    secondHalf[64];
    int     bufferLength = getBufferLength(buffer);
    int     halfBufferLength = bufferLength / 2;

    // divide buffer into halfs
    for (int i=0; i<halfBufferLength; ++i) {
        firstHalf[i] = buffer[i];
        secondHalf[i] = buffer[i+halfBufferLength];
    }
    firstHalf[halfBufferLength] = '\0';
    secondHalf[halfBufferLength] = '\0';
    // printf("first:\t%s\t\tsecond:\t%s\n", firstHalf, secondHalf);

    for (int i=0; i<halfBufferLength; ++i) {
        for (int j=0; j<halfBufferLength; ++j) {
            if (firstHalf[i] == secondHalf[j]) {
                return firstHalf[i];
            }
        }
    }
}

int getBufferLength(char *buffer) {
    for (int i=0; i<128; ++i) {
        if (buffer[i] == '\n') {
            return i;
        }
    }
}
