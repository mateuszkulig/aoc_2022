#include "stdio.h"
#include "stdlib.h"

int main(int argc, char **argv) {
    int     width = 0;
    int     height = 0;
    char    buffer[128];
    FILE    *inputFile;
    int     currentW = 0;
    int     currentH = 0;
    char    **rows;
    char    **columns;

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

    printf("%d\t%d\n", width, height);
    return 0;
}