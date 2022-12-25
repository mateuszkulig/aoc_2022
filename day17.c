#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

// day 8 code function modified to and use char instead of int64_t and decorate
void show(char **arr2d, int64_t nx, int64_t ny) {
    for(int64_t i=0; i<ny; ++i) {
        for(int64_t j=0; j<nx; ++j) {
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
    for(int64_t i=0; i<nx; ++i) {
        printf("-");
    }
    printf("+\n");
}

typedef struct Shape {
    int64_t     width;
    int64_t     height;
    char    **grid;
} Shape;

void setShape(Shape *s, char *artLine, int64_t newW, int64_t newH) {
    int64_t artCounter = 0;

    s->width = newW;
    s->height = newH;

    s->grid = malloc(sizeof(char*)*newW);
    for (int64_t i=0; i<newW; ++i) {
        s->grid[i] = malloc(sizeof(char)*newH);
    }

    for (int64_t i=0; i<newH; ++i) {
        for (int64_t j=0; j<newW; ++j) {
            s->grid[j][i] = artLine[artCounter];
            artCounter++;
        }
    }
}

// freeup memory of shape
void freeShape(Shape *sh) {
    for (int64_t j=0; j<sh->width; ++j) {
        free(sh->grid[j]);
    }
    free(sh->grid);
}

void reallocChamber(Shape *cham, int64_t newHeight) {
    int64_t     oldHeight = cham->height;
    int64_t     heightDiff = newHeight - oldHeight;
    char    **newGrid = malloc(sizeof(char*)*cham->width);

    for (int64_t i=0; i<cham->width; ++i) {
        newGrid[i] = malloc(sizeof(char)*newHeight);
    }

    for (int64_t i=0; i<heightDiff; ++i) {
        for (int64_t j=0; j<cham->width; ++j) {
            newGrid[j][i] = '.';
        }
    }

    if (heightDiff >= 0) {  // new chamber is bigger than existing one
        for (int64_t i=0; i<oldHeight; ++i) {
            for (int64_t j=0; j<cham->width; ++j) {
                newGrid[j][i+heightDiff] = cham->grid[j][i];
            }
        }
    } else {    // new chamber is smaller than existing one
        for (int64_t i=0; i<newHeight; ++i) {
            for (int64_t j=0; j<cham->width; ++j) {
                newGrid[j][i] = cham->grid[j][i-heightDiff];    // heightDiff is negative in this scenario
            }
        }
    }

    

    freeShape(cham);
    cham->grid = newGrid;
    cham->height = newHeight;
}

// return the highest spot in chamber
int64_t findHighestSpot(Shape *chamber) {
    int64_t k = 0;
    int64_t brkK = 0;
    for (k; k<chamber->height; ++k) {
        for (int64_t i=0; i<chamber->width; ++i) {
            if (chamber->grid[i][k] == '#') {
                brkK = 1;
                break;
            }
        }
        if (brkK) {
            break;
        }
    }

    return chamber->height-k;
}

// adds shape to the top of chamber
void addShape(Shape *chamber, Shape *sh) {
    reallocChamber(chamber, findHighestSpot(chamber)+sh->height+3);    // realloc to fit new shape; +3 for gap

    for (int64_t i=0; i<sh->height; ++i) {  // add shape to chamber grid
        for (int64_t j=0; j<sh->width; ++j) {
            chamber->grid[j+2][i] = sh->grid[j][i];
        }
    }
}

// fall down shape by one block
int64_t move(Shape *chamber, int64_t shapeWidth, char direction) {
    // fall down condition checking; exit function if cannot fall
    for (int64_t i=0; i<chamber->height; ++i) {
        for (int64_t j=0; j<chamber->width; ++j) {
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
            for (int64_t i=chamber->height; i>=0; --i) {    // from bottom to top
                for (int64_t j=0; j<chamber->width; ++j) {
                    if (chamber->grid[j][i] == '@') {   // for each @ (rock element)
                            chamber->grid[j][i+1] = '@';
                            chamber->grid[j][i] = '.';
                    }
                }
            }
            break;
        
        case '>':   // moving to right
            for (int64_t i=0; i<chamber->height; ++i) {
                for (int64_t j=chamber->width-1; j>=0; --j) {  // from right to left
                    if (chamber->grid[j][i] == '@') {   // for each @ (rock element)
                            chamber->grid[j+1][i] = '@';
                            chamber->grid[j][i] = '.';
                    }
                }
            }
            break;
        
        case '<':   // moving to left
            for (int64_t i=0; i<chamber->height; ++i) {
                for (int64_t j=0; j<chamber->width; ++j) {  // from left to right
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
    for (int64_t i=0; i<chamber->height; ++i) {
        for (int64_t j=0; j<chamber->width; ++j) {
            if (chamber->grid[j][i] == '@') {
                chamber->grid[j][i] = '#';
            }
        }
    }
}

// main loop of moving
void mainLoop(Shape *chamber, Shape *rocks, char *jetStream, int64_t jetSize) {
    int64_t alternate;
    int64_t jetCounter = 0;

    for (int64_t i=0; i<1000000000000; ++i) {
        printf("iteration:\t%ld\n", i);
        // show(rocks[i%5].grid, rocks[i%5].width, rocks[i%5].height);

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

    reallocChamber(chamber, findHighestSpot(chamber));  // clear empty space at the top
}

// load jets into array; return array size
// note: does not work with \n at the end of file
int64_t loadJets(char *fileName, char **jetArray) {
    FILE    *inputFile;
    int64_t     arrSize;

    inputFile = fopen(fileName, "r");
    fseek(inputFile, 0L, SEEK_END);
    arrSize = ftell(inputFile) + 1; // looks like it just needs +1; its to late to think why
    fseek(inputFile, 0L, SEEK_SET);

    *jetArray = malloc(sizeof(char)*arrSize);
    fgets(*jetArray, arrSize, inputFile);

    fclose(inputFile);

    return arrSize;
}

int64_t main(int64_t argc, char **argv) {
    Shape   chamber;
    Shape   rocks[5];

    char    *jets;
    int64_t     jetSize;

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
    printf("%ld\n", chamber.height);

    // memory freeup
    for (int64_t i=0; i<5; ++i) {
        freeShape(&rocks[i]);
    }
    freeShape(&chamber);
    free(jets);

    return 0;
}