//
// Created by diana on 05/11/2019.
//

#ifndef FOOD_ORDERING_OPTIONS_H
#define FOOD_ORDERING_OPTIONS_H

//TODO: break apart file (unclear grouping of functions in the options.h file)

void printMenu(int nrOfTypes, char **types);
void printMenuWithPrices(int id, int stringSize, char **types, double *prices);
int makeChoice(int *state, int nrOfTypes, int stateModifier);
void getAdditionalInfo(int *state, char* additionalInfo);


#endif //FOOD_ORDERING_OPTIONS_H
