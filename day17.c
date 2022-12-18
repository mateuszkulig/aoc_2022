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

    for (int i=0; i<oldHeight; ++i) {
        for (int j=0; j<7; ++j) {
            newGrid[j][i+heightDiff] = cham->grid[j][i];
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
    printf("\nk:\t%d, sh height:\t%d, ch height:\t%d\n", k, sh->height, chamber->height);

    reallocChamber(chamber, chamber->height-k+sh->height+3);    // realloc to fit new shape; +3 for gap

    for (int i=0; i<sh->height; ++i) {  // add shape to chamber grid
        for (int j=0; j<sh->width; ++j) {
            chamber->grid[j+2][i] = sh->grid[j][i];
        }
    }
}

// main loop of moving
void mainLoop(Shape *chamber, Shape *rocks) {
    for (int i=0; i<8; ++i) {
        addShape(chamber, &rocks[i%5]);
        show(chamber->grid, chamber->width, chamber->height);
    }
}


int main(int argc, char **argv) {
    Shape   chamber;
    Shape   rocks[5];

    char    artChamber[7*1] = ".......";
    char    artZero[4*1] = "####";
    char    artOne[3*3] = ".#.###.#.";
    char    artTwo[3*3] = "..#..####";
    char    artThree[1*4] = "####";
    char    artFour[2*2] = "####";

    setShape(&chamber, artChamber, 7, 1);
    setShape(&rocks[0], artZero, 4, 1);
    setShape(&rocks[1], artOne, 3, 3);
    setShape(&rocks[2], artTwo, 3, 3);
    setShape(&rocks[3], artThree, 1, 4);
    setShape(&rocks[4], artFour, 2, 2);

    // show(chamber.grid, 7, 1);
    // addShape(&chamber, &rocks[1]);
    // printf("\n");
    
    mainLoop(&chamber, rocks);

    // memory freeup
    for (int i=0; i<5; ++i) {
        freeShape(&rocks[i]);
    }
    freeShape(&chamber);

    return 0;
}