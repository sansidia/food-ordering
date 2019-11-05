//
// Created by diana on 05/11/2019.
//

#include "options.h"
#include <stdio.h>

void printMenu(int nrOfTypes, int stringSize, char types[nrOfTypes][stringSize]) {
    int i;
    for (i = 0; i < nrOfTypes; i++) {
        putchar('a'+i); printf(") %s\n", types[i]);
    }
    i = nrOfTypes;
    putchar('a'+i); printf(") Go back\n");
}

void printMenuWithPrices(int nrOfTypes, int stringSize, char types[nrOfTypes][stringSize], int prices[]) {
    int i;
    for (i = 0; i < nrOfTypes; i++) {
        putchar('a'+i); printf(") %s (%d)\n", types[i], prices[i]);
    }
    i = nrOfTypes;
    putchar('a'+i); printf(") Go back\n");
}