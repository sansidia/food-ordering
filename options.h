//
// Created by diana on 05/11/2019.
//

#ifndef FOOD_ORDERING_OPTIONS_H
#define FOOD_ORDERING_OPTIONS_H

void printMenu(int nrOfTypes, char **types);
void printMenuWithPrices(int id, int nrOfTypes, char **types, int *prices);
int makeChoice(int *state, int nrOfTypes, int stateModifier);
void getAdditionalInfo(int *state, char additionalInfo[]);


#endif //FOOD_ORDERING_OPTIONS_H
