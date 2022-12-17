#include "stdio.h"
#include "stdlib.h"

// print the contents of 2d array
void show(int **arr2d, int nx, int ny) {
    for(int i=0; i<ny; ++i) {
        for(int j=0; j<nx; ++j) {
            printf("%d ", arr2d[j][i]); // i and j could probably be flipped
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    int     width = 0;
    int     height = 0;
    char    buffer[128];
    FILE    *inputFile;
    int     currentW = 0;
    int     currentH = 0;
    int     **field;
    char    atoiBuffer[2] = {'\0', '\0'};
    int     k = 0;

    // get the dimentions of field
    inputFile = fopen("input8.txt", "r");
    while(fgets(buffer, 128, inputFile) != NULL) {
        for(int i=0; i<128; ++i) {  // this really needs to run only once but runs in loop
            if (buffer[i] != '\0' && buffer[i] != '\n') {
                currentW++;
            } else {
                width = currentW;
                currentW = 0;
                break;
            }
        }
        height++;
    }
    fclose(inputFile);

    // allocate memory for field
    field = malloc(sizeof(int*)*width);
    for(int i=0; i<width; ++i) {
        field[i] = malloc(sizeof(int)*height);
    }

    // fill the rows and columns
    inputFile = fopen("input8.txt", "r");
    while(fgets(buffer, 128, inputFile) != NULL) {
        for(int i=0; i<width; ++i) {
            atoiBuffer[0] = buffer[i];
            field[i][k]=atoi(atoiBuffer);
        }
        ++k;
    }
    fclose(inputFile);

    show(field, width, height);

    // free the memory
    for(int i=0; i<height; ++i) {
        free(field[i]);
    }
    free(field);
    
    return 0;
}