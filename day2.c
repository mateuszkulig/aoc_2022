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
    char    rock1 = 'A';
    char    paper1 = 'B';
    char    scissors1 = 'C';
    char    rock2 = 'X';
    char    paper2 = 'Y';
    char    scissors2 = 'Z';
}