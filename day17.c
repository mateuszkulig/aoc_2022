#include "stdio.h"
#include "stdlib.h"

// day 8 code function modified to and use char instead of int and decorate
void show(char **arr2d, int nx, int ny) {
    for(int i=0; i<ny; ++i) {
        for(int j=0; j<nx; ++j) {
            if (j==0) {
                printf("|");
            }
            printf("%c", arr2d[j][i]); // i and j could probably be flipped
            if (j==nx-1) {
                printf("|");
            }
        }
        printf("\n");
    }
    printf("+");
    for(int i=0; i<nx; ++i) {
        printf("-");
    }
    printf("+\n");
}

typedef struct Shape {
    int     width;
    int     height;
    char    **grid;
} Shape;

void setShape(Shape *s, char *artLine, int newW, int newH) {
    int artCounter = 0;

    s->width = newW;
    s->height = newH;

    s->grid = malloc(sizeof(char*)*newW);
    for (int i=0; i<newW; ++i) {
        s->grid[i] = malloc(sizeof(char)*newH);
    }

    for (int i=0; i<newH; ++i) {
        for (int j=0; j<newW; ++j) {
            s->grid[j][i] = artLine[artCounter];
            artCounter++;
        }
    }
}

// freeup memory of shape
void freeShape(Shape *sh) {
    for (int j=0; j<sh->width; ++j) {
        free(sh->grid[j]);
    }
    free(sh->grid);
}

void reallocChamber(Shape *cham, int newHeight) {
    int     oldHeight = cham->height;
    int     heightDiff = newHeight - oldHeight;
    char    **newGrid = malloc(sizeof(char*)*7);

    for (int i=0; i<7; ++i) {
        newGrid[i] = malloc(sizeof(char)*newHeight);
    }

    for (int i=0; i<heightDiff; ++i) {
        for (int j=0; j<7; ++j) {
            newGrid[j][i] = '.';
        }
    }

    if (heightDiff >= 0) {  // new chamber is bigger than existing one
        for (int i=0; i<oldHeight; ++i) {
            for (int j=0; j<7; ++j) {
                newGrid[j][i+heightDiff] = cham->grid[j][i];
            }
        }
    } else {    // new chamber is smaller than existing one
        for (int i=0; i<newHeight; ++i) {
            for (int j=0; j<7; ++j) {
                newGrid[j][i] = cham->grid[j][i-heightDiff];    // heightDiff is negative in this scenario
            }
        }
    }

    

    freeShape(cham);
    cham->grid = newGrid;
    cham->height = newHeight;
}

// adds shape to the top of chamber
void addShape(Shape *chamber, Shape *sh) {
    int k = 0;
    int brkK = 0;
    for (k; k<chamber->height; ++k) {   // find the highest spot
        for (int i=0; i<chamber->width; ++i) {
            if (chamber->grid[i][k] == '#') {
                brkK = 1;
                break;
            }
        }
        if (brkK) {
            break;
        }
    }

    reallocChamber(chamber, chamber->height-k+sh->height+3);    // realloc to fit new shape; +3 for gap

    for (int i=0; i<sh->height; ++i) {  // add shape to chamber grid
        for (int j=0; j<sh->width; ++j) {
            chamber->grid[j+2][i] = sh->grid[j][i];
        }
    }
}

// fall down shape by one block
int move(Shape *chamber, int shapeWidth, char direction) {
    // fall down condition checking; exit function if cannot fall
    for (int i=0; i<chamber->height; ++i) {
        for (int j=0; j<chamber->width; ++j) {
            if (chamber->grid[j][i] == '@' && (direction == '|' && (i == chamber->height-1 || chamber->grid[j][i+1] == '#'))) {
                return 0;
            } else if (chamber->grid[j][i] == '@' && (
                (direction == '>' && (j == chamber->width-1 || chamber->grid[j+1][i] == '#')) ||
                (direction == '<' && (j == 0 || chamber->grid[j-1][i] == '#')))
            ) {
                return 1;
            }
        }
    }


    switch (direction) {
        case '|':   // actual falling down
            for (int i=chamber->height; i>=0; --i) {    // from bottom to top
                for (int j=0; j<chamber->width; ++j) {
                    if (chamber->grid[j][i] == '@') {   // for each @ (rock element)
                            chamber->grid[j][i+1] = '@';
                            chamber->grid[j][i] = '.';
                    }
                }
            }
            break;
        
        case '>':   // moving to right
            for (int i=0; i<chamber->height; ++i) {
                for (int j=chamber->width-1; j>=0; --j) {  // from right to left
                    if (chamber->grid[j][i] == '@') {   // for each @ (rock element)
                            chamber->grid[j+1][i] = '@';
                            chamber->grid[j][i] = '.';
                    }
                }
            }
            break;
        
        case '<':   // moving to left
            for (int i=0; i<chamber->height; ++i) {
                for (int j=0; j<chamber->width; ++j) {  // from left to right
                    if (chamber->grid[j][i] == '@') {   // for each @ (rock element)
                            chamber->grid[j-1][i] = '@';
                            chamber->grid[j][i] = '.';
                    }
                }
            }
            break;
        
        default:
            break;
        }
    return 1;
    
}

// replaces '@' to '#'
void solidifyRocks(Shape *chamber) {
    for (int i=0; i<chamber->height; ++i) {
        for (int j=0; j<chamber->width; ++j) {
            if (chamber->grid[j][i] == '@') {
                chamber->grid[j][i] = '#';
            }
        }
    }
}

// main loop of moving
void mainLoop(Shape *chamber, Shape *rocks, char *jetStream, int jetSize) {
    int alternate;
    int jetCounter = 0;

    for (int i=0; i<2022; ++i) {
        printf("iteration:\t%d\nshape:\n", i);
        show(rocks[i%5].grid, rocks[i%5].width, rocks[i%5].height);

        alternate = 1;  // always start from left/right push
        addShape(chamber, &rocks[i%5]);
        while (move(chamber, rocks[i%5].width, alternate ? jetStream[jetCounter%(jetSize-1)] : '|')) {
            if (alternate) {
                jetCounter++;
            }
            alternate = !alternate;
        }
        solidifyRocks(chamber);
        // show(rocks[i%5].grid, rocks[i%5].width, rocks[i%5].height);
        // show(chamber->grid, chamber->width, chamber->height);
    }
}

// load jets into array; return array size
int loadJets(char *fileName, char **jetArray) {
    FILE    *inputFile;
    int     arrSize;

    inputFile = fopen(fileName, "r");
    fseek(inputFile, 0L, SEEK_END);
    arrSize = ftell(inputFile) + 1; // looks like it just needs +1; its to late to think why
    fseek(inputFile, 0L, SEEK_SET);

    *jetArray = malloc(sizeof(char)*arrSize);
    fgets(*jetArray, arrSize, inputFile);

    fclose(inputFile);

    return arrSize;
}

int main(int argc, char **argv) {
    Shape   chamber;
    Shape   rocks[5];

    char    *jets;
    int     jetSize;

    char    artChamber[7*1] = ".......";
    char    artZero[4*1] = "@@@@";
    char    artOne[3*3] = ".@.@@@.@.";
    char    artTwo[3*3] = "..@..@@@@";
    char    artThree[1*4] = "@@@@";
    char    artFour[2*2] = "@@@@";

    setShape(&chamber, artChamber, 7, 1);
    setShape(&rocks[0], artZero, 4, 1);
    setShape(&rocks[1], artOne, 3, 3);
    setShape(&rocks[2], artTwo, 3, 3);
    setShape(&rocks[3], artThree, 1, 4);
    setShape(&rocks[4], artFour, 2, 2);
    
    jetSize = loadJets("input17.txt", &jets);
    mainLoop(&chamber, rocks, jets, jetSize);

    show(chamber.grid, chamber.width, chamber.height);
    printf("%d\n", chamber.height);

    // memory freeup
    for (int i=0; i<5; ++i) {
        freeShape(&rocks[i]);
    }
    freeShape(&chamber);
    free(jets);

    return 0;
}