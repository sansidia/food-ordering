//
// Created by diana on 05/11/2019.
//

#ifndef FOOD_ORDERING_OPTIONS_H
#define FOOD_ORDERING_OPTIONS_H

void printMenu(int nrOfTypes, int stringSize, char types[nrOfTypes][stringSize]);
void printMenuWithPrices(int id, int nrOfTypes, int stringSize, char types[nrOfTypes][stringSize], int prices[]);
int makeChoice(int *state, int nrOfTypes, int stateModifier);
void getAdditionalInfo(int *state, char additionalInfo[]);


#endif //FOOD_ORDERING_OPTIONS_H
