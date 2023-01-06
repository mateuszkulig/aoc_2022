#include "stdio.h"

// find what char appears in both compartments
char findSharingItem(char *buffer);

// get the length of characters in 128char buffer
int getBufferLength(char *buffer);

int main(int argc, char **argv) {
    FILE *inputFile;
    char buffer[128];
    
    
    inputFile = fopen("input3.txt", "r");
    
    while (fgets(buffer, 128, inputFile) != 0) {
        findSharingItem(buffer);
    }

    fclose(inputFile);

    return 0;
}

char findSharingItem(char *buffer) {
    char    repeating;
    char    firstHalf[64];
    char    secondHalf[64];
    int     bufferLength = getBufferLength(buffer);
    


    return repeating;
}

int getBufferLength(char *buffer) {
    for (int i=0; i<128; ++i) {
        if (buffer[i] == '\n') {
            return i;
        }
    }
}
