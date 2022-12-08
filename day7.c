#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct systemFile
{
    int size;
    char name[32];
} systemFile;

typedef struct systemDir systemDir;

struct systemDir
{
    char name[32];
    systemFile *files;
    systemDir *dirs;
    int fileCounter;
    int dirCounter;
    systemDir *parent;
};

typedef struct systemCommand
{
    char arg1[16];
    char arg2[16];
    int isOutput;
} systemCommand;


void fillCommand(systemCommand *newCommand, char *arg1, char *arg2, int isOutput) {
    int i;
    i = 0;
    while (arg1[i] != '\0') {
        newCommand->arg1[i] = arg1[i];
        ++i;
    }
    newCommand->arg1[i] = '\0';
    i = 0;
    while (arg2[i] != '\0') {
        newCommand->arg2[i] = arg2[i];
        ++i;
    }
    newCommand->arg2[i] = '\0';
    newCommand->isOutput = isOutput;
}

void setDir(systemDir *dir, char *name, systemDir *parent) {
    int i=0;
    while(name[i] != '\0') {
        dir->name[i] = name[i];
        ++i;
    }
    dir->name[i] = '\0';
    dir->dirCounter = 0;
    dir->fileCounter = 0;
    dir->files = malloc(sizeof(systemFile) * 16);
    dir->dirs = malloc(sizeof(systemDir) * 16);
    dir->parent = parent;
}

void setFile(systemFile *sFile, char *name, char *size) {
    int i=0;
    while(name[i] != '\0') {
        sFile->name[i] = name[i];
        ++i;
    }
    sFile->name[i] = '\0';
    sFile->size = atoi(size);
}

systemCommand *parse(char *cmd) {
    int command = 0;
    int second = 0;
    int i;
    char cmd1[16], cmd2[16];
    if (cmd[0] == '$') {
        command = 1;
    }

    if (command) {
        i = 2;
    } else {
        i = 0;
    }
    int j = 0;

    while (cmd[i] != '\0' && cmd[i] != '\n') {
        if (cmd[i] == ' ') {
            cmd1[j] = '\0';
            second = 1;
            j = 0;
        } else if (second) {
            cmd2[j] = cmd[i];
            j++;
        } else {
            cmd1[j] = cmd[i];
            j++;
        }
        ++i;
    }

    // ls case
    if (!second) {  
        cmd1[j] = '\0';
        cmd2[0] = '\0';
    }

    // last char breaks from the loop so it needs to be readded 
    cmd2[j] = '\0';
    
    systemCommand *parsedCommand = malloc(sizeof(systemCommand));
    fillCommand(parsedCommand, cmd1, cmd2, !command);

    return parsedCommand;
}

void interpret(systemDir *currentDir, systemCommand* currentCommand) {
    switch (currentCommand->isOutput) {
        case 1:
            if (currentCommand->arg1[0] == 'd') {
                setDir(&currentDir->dirs[currentDir->dirCounter], currentCommand->arg2, currentDir);
                currentDir->dirCounter++;
            } else {
                setFile(&currentDir->files[currentDir->fileCounter], currentCommand->arg2, currentCommand->arg1);
                currentDir->fileCounter++;
            }
            break;
        case 0:
            if (currentCommand->arg1[0] == 'l') {}  // command is ls
            // command is cd ..
            else if (currentCommand->arg1[0] == 'c' && currentCommand->arg1[3] == '.') {
                currentDir = currentDir->parent;
            // command is cd {arg}
            } else {
                for(int i=0; i<currentDir->dirCounter; ++i) {
                    // printf("%s ?= %s: %d\n", currentDir->dirs[i].name, currentCommand->arg2, strcmp(currentDir->dirs[i].name, currentCommand->arg2) == 0);
                    if (strcmp(currentDir->dirs[i].name, currentCommand->arg2) == 0){
                        currentDir = &currentDir->dirs[i];
                    }
                }
            }
            break;
    }
}

int getDirSize(systemDir *dir) {
    int total = 0;
    
    // printf("%d", dir->fileCounter);
    for (int i=0; i<dir->fileCounter; ++i) {
        // printf("%s\t%d\n", dir->files[i].name, dir->files[i].size);
        total += dir->files[i].size;
    }
    for (int i=0; i<dir->dirCounter; ++i) {
        total += getDirSize(&dir->dirs[i]);
    }

    return total;
}

int main(int argc, char **argv) {
    FILE *inputFile;
    systemDir *currentDir;
    systemCommand *currentCommand;
    char cmd[64];

    systemDir root;
    setDir(&root, "/\0", &root);
    currentDir = &root;

    inputFile = fopen("input7.txt", "r");

    while (fgets(cmd, 64, inputFile) != NULL) {
        currentCommand = parse(cmd);
        interpret(currentDir, currentCommand);
    }
    
    currentDir = &root;
    printf("%s\t%d\t%d\n", currentDir->name, currentDir->dirCounter, getDirSize(currentDir));
    // for(int i=0; i<currentDir->dirCounter; i++) {
    //     printf("%s\t%d\t%d\n", currentDir->dirs[i].name, currentDir->dirs[i].dirCounter, getDirSize(&currentDir->dirs[i]));
    // }
    
    return 0;
}
