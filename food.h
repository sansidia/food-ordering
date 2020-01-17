//
// Created by diana on 18/12/2019.
//

#ifndef FOOD_ORDERING_V2_FOOD_H
#define FOOD_ORDERING_V2_FOOD_H

#include "food-subtype.h"

typedef struct _food {
    char* name;
    int nrOfSubtypes;
    foodSubtype* subtypes;
} food;

food createFood(int);

#endif //FOOD_ORDERING_V2_FOOD_H
