#include "stdio.h"


int getRoundResult(char myP, char opP);


int main(int argc, char **argv) {
    int     score = 0;
    int     bufferCounter = 0;

    char    myPick;
    char    opponentPick;

    FILE    *inputFile;

    inputFile = fopen("input2.txt", "r");

    while (!feof(inputFile)) {
        switch (bufferCounter % 4) {
            case 0:
                opponentPick = fgetc(inputFile);
                break;

            case 1:
                fgetc(inputFile);   // ignore space
                break;

            case 2:
                myPick = fgetc(inputFile);
                break;

            case 3: // \n; start round
                score += getRoundResult(myPick, opponentPick);

            default:
                break;
            }
        bufferCounter++;
    }

    return 0;
}

int getRoundResult(char myP, char opP) {
    int score;

    switch (myP) {  // starting score
        case 'X':
            score = 1;
            if (opP == 'A') {
                score += 3;
            } else if (opP == 'Y') {
                score += 6;
            }
            break;
    
        case 'Y':
            score = 2;
            break;
        
        case 'Z':
            score = 3;
            break;
        
        default:
            break;
    }


    return score;
}