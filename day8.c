#include "stdio.h"
#include "stdlib.h"

int main(int argc, char **argv) {
    int     width = 0;
    int     height = 0;
    char    buffer[128];
    FILE    *inputFile;
    int     currentW = 0;
    int     currentH = 0;
    char    **field;

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
    field = malloc(sizeof(char*)*width);
    for(int i=0; i<height; ++i) {
        field[i] = malloc(sizeof(char)*height);
    }

    // fill the rows and columns
    inputFile = fopen("input8.txt", "r");

    int k=0;
    while(fgets(buffer, 128, inputFile) != NULL) {
        printf("%s", buffer);
        for(int i=0; i<width; ++i) {
            field[i][k]=buffer[i];
        }
        ++k;
    }
    fclose(inputFile);

    printf("\n%c", field[0][2]);

    // printf("%d\t%d\n", width, height);
    return 0;
}