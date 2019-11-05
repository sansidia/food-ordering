//
// Created by diana on 05/11/2019.
//

#include "options.h"
#include <stdio.h>

int isChoiceValid(int choice, int maxValue);
int modifyState(int state, int choice, int maxValue);

void printMenu(int nrOfTypes, int stringSize, char types[nrOfTypes][stringSize]) {
    int i;
    for (i = 0; i < nrOfTypes; i++) {
        putchar('a'+i); printf(") %s\n", types[i]);
    }
    i = nrOfTypes;
    putchar('a'+i); printf(") Go back\n");
}

void printMenuWithPrices(int id, int nrOfTypes, int stringSize, char types[nrOfTypes][stringSize], int prices[]) {
    int i;
    for (i = 0; i < nrOfTypes; i++) {
        putchar('a'+i); printf(") %s (%d)\n", types[i], prices[i]);
    }
    if (id == 1) {
        putchar('a'+i); printf(") No, thanks!\n");
    }
    i = nrOfTypes + 1;
    putchar('a'+i); printf(") Go back\n");
}

int makeChoice(int *state, int maxValue) {
    char input = getchar();
    getchar();
    int choice = input - 'a';
    if (isChoiceValid(choice, maxValue)) {
        *state = modifyState(*state, choice,maxValue);
    }
    return choice;


    /*
    if (choice == NO_FOOD_TYPE) {
        *state--;
        break;
    }
    if ((choice<0) || (choice > NO_FOOD_TYPE)) {
        printf("Invalid answer, please select again.\n");
        break;
    }*/
}

int isChoiceValid(int choice, int maxValue) {
    if ((choice < 0) || (choice > maxValue)) {
        printf("Invalid answer, please select again.\n");
        return 0;
    }
    return 1;
}

int modifyState(int state, int choice, int maxValue) {
    if (choice == maxValue)
        state--;
    else
        state++;
    return state;
}