//
// Created by diana on 18/12/2019.
//

#ifndef FOOD_ORDERING_V2_DRINK_H
#define FOOD_ORDERING_V2_DRINK_H

typedef struct _drink {
    char* name;
    double price;
} drink;

drink createDrink();
void freeDrink(drink* d);

#endif //FOOD_ORDERING_V2_DRINK_H
