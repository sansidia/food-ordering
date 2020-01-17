//
// Created by diana on 18/12/2019.
//

#ifndef FOOD_ORDERING_V2_LOAD_DATA_H
#define FOOD_ORDERING_V2_LOAD_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include "food.h"
#include "food-subtype.h"
#include "drink.h"
#include "food-ordering-macros.h"

#define INPUT_DATA_MSG "Please load the data\n"


void loadDataFromFile(FILE *inputFile, int *nrOfFoodsAddr, food **foodsAddr, int *nrOfDrinksAddr, drink **drinksAddr);

void loadDataFromConsole(int *nrOfFoods, food **foods, int *nrOfDrinks, drink **drinks);

#endif //FOOD_ORDERING_V2_LOAD_DATA_H
