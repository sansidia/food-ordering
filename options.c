//
// Created by diana on 05/11/2019.
//

#include "options.h"
#include <stdio.h>

int isChoiceValid(int choice, int nrOfTypes);
int modifyState(int state, int choice, int nrOfTypes, int stateModifier);

void printMenu(int nrOfTypes, char **types) {
    int i;
    for (i = 0; i < nrOfTypes; i++) {
        putchar('a'+i); printf(") %s\n", types[i]);
    }
    i = nrOfTypes;
    putchar('a'+i); printf(") Go back\n");
}

void printMenuWithPrices(int id, int nrOfTypes, char **types, double *prices) {
    int i;
    for (i = 0; i < nrOfTypes; i++) {
        putchar('a'+i); printf(") %s (%.2f)\n", types[i], prices[i]);
    }
    if (id == 1) {
        putchar('a'+i); printf(") No, thanks!\n");
        i++;
    }
    putchar('a'+i); printf(") Go back\n");
}

int makeChoice(int *state, int nrOfTypes, int stateModifier) {
    char input = getchar();
    getchar();
    int choice = input - 'a';
    if (isChoiceValid(choice, nrOfTypes)) {
        *state = modifyState(*state, choice, nrOfTypes, stateModifier);
    }
    return choice;
}

int isChoiceValid(int choice, int nrOfTypes) {
    if ((choice < 0) || (choice > nrOfTypes)) {
        printf(INVALID_INPUT);
        return 0;
    }
    return 1;
}

int modifyState(int state, int choice, int nrOfTypes, int stateModifier) {
    if (choice == nrOfTypes)
        state-= stateModifier;
    else
        state++;
    return state;
}

void getAdditionalInfo(int *state, char additionalInfo[]) {
    printf("Any additional information?\n");
    gets(additionalInfo);
    *state= *state+1;
}