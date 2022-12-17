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

int isVisible(int **treeField, int x, int y, int width, int height) {
    int visibleRight = 1;
    int visibleLeft = 1;
    int visibleUp = 1;
    int visibleDown = 1;

    // printf("\n---COMPARATION---\n");

    for(int i=x-1; i>=0; --i) { // going left from tree
        // printf("comparing to left: %d\n", treeField[i][y]);
        if(treeField[i][y] >= treeField[x][y]) {
            visibleLeft = 0;
            break;
        }
    }

    for(int i=x+1; i<width; ++i) { // going right from tree
        // printf("comparing to right: %d\n", treeField[i][y]);
        if(treeField[i][y] >= treeField[x][y]) {
            visibleRight = 0;
            break;
        }
    }

    for(int i=y-1; i>=0; --i) { // going up from tree
        // printf("comparing to up: %d\n", treeField[x][i]);
        if(treeField[x][i] >= treeField[x][y]) {
            visibleUp = 0;
            break;
        }
    }

    for(int i=y+1; i<height; ++i) { // going down from tree
        // printf("comparing to down: %d\n", treeField[x][i]);
        if(treeField[x][i] >= treeField[x][y]) {
            visibleDown = 0;
            break;
        }
    }
    // printf("\n%d(%d,%d) is visible from left: %d\n", treeField[x][y], x, y, visibleLeft);
    // printf("\n%d(%d,%d) is visible from right: %d\n", treeField[x][y], x, y, visibleRight);
    // printf("\n%d(%d,%d) is visible from up: %d\n", treeField[x][y], x, y, visibleUp);
    // printf("\n%d(%d,%d) is visible from down: %d\n", treeField[x][y], x, y, visibleDown);
    // printf("\n%d(%d,%d) is visible: %d\n", treeField[x][y], x, y, visibleLeft || visibleRight || visibleDown || visibleUp);
    return (visibleLeft || visibleRight || visibleDown || visibleUp);
    
}

int getVisibleTrees(int **treeField, int width, int height) {
    int total = ((width+height)*2)-4;   // starts with all border trees; -4 for duplicates at corners
    for (int i=1; i<width-1; i++) {
        for (int j=1; j<height-1; j++) {
            total += isVisible(treeField, j, i, width, height);
            
        }
    }
    return total;
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

    // show(field, width, height);

    printf("%d\n", getVisibleTrees(field, width, height));

    // free the memory
    for(int i=0; i<height; ++i) {
        free(field[i]);
    }
    free(field);
    
    return 0;
}