#include "stdio.h"


int getRoundResult(char myP, char opP);

int get2ndPartResult(char myP, char opP);

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
                fgetc(inputFile);   // ignore \n
                // score += getRoundResult(myPick, opponentPick);   // first part
                score += get2ndPartResult(myPick, opponentPick);

            default:
                break;
            }
        bufferCounter++;
    }

    printf("%d\n", score);
    return 0;
}

// get result of 2nd part; just select proper pick and add win/lose/draw
// this could be also done with lopping over array because every next pick beats previous
int get2ndPartResult(char myP, char opP) {
    switch (opP) {
        case 'A':
            if (myP == 'X') {
                return 3 + 0;   // scissors + lose
            } else if (myP == 'Y') {
                return 1 + 3;   // rock + draw
            } else {
                return 2 + 6;   // paper + win
            }
            
        case 'B':
            if (myP == 'X') {
                return 1 + 0;   // rock + lose
            } else if (myP == 'Y') {
                return 2 + 3;   // paper + draw
            } else {
                return 3 + 6;   // scissors + win
            }
        
        case 'C':
            if (myP == 'X') {
                return 2 + 0;   // paper + lose
            } else if (myP == 'Y') {
                return 3 + 3;   // scissors + draw
            } else {
                return 1 + 6;   // rock + win
            }
        
        default:
            return 0;
    }
}

// get the result score of the round
int getRoundResult(char myP, char opP) {
    int score;

    switch (myP) {  // starting score
        case 'X':
            score = 1;
            if (opP == 'A') {
                score += 3;
            } else if (opP == 'C') {
                score += 6;
            }
            break;
    
        case 'Y':
            score = 2;
            if (opP == 'B') {
                score += 3;
            } else if (opP == 'A') {
                score += 6;
            }
            break;
        
        case 'Z':
            score = 3;
            if (opP == 'C') {
                score += 3;
            } else if (opP == 'B') {
                score += 6;
            }
            break;
        
        default:
            break;
    }

    return score;
}