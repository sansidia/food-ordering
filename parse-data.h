//
// Created by diana on 18/12/2019.
//

#ifndef FOOD_ORDERING_V2_PARSE_DATA_H
#define FOOD_ORDERING_V2_PARSE_DATA_H

#include "food.h"
#include "food-ordering-macros.h"
#include "food-subtype.h"
#include "drink.h"
#include <string.h>

void parseFoodName(char* string, food* f);

void parseSubtypes(char* string, food *foodItem);

void parseDrinks(char *string, drink *d, int nrOfDrinks);

char* getInputFromFile(FILE* file);
char* getInputFromConsole();




#endif //FOOD_ORDERING_V2_PARSE_DATA_H
