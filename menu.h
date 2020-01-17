//
// Created by diana on 19/12/2019.
//

#ifndef FOOD_ORDERING_V2_MENU_H
#define FOOD_ORDERING_V2_MENU_H

#include "food.h"
#include "drink.h"
#include "food-ordering-macros.h"
#include "food-subtype.h"
#include "user.h"


typedef struct _order {
    foodSubtype chosenFood;
    drink chosenDrink;
    int drinkIsSelected;
    char* cutlery;
    char* additionalInfo;
} order;

enum STATE {SIGN_IN, CHOOSE_FOOD, CHOOSE_SUBTYPE, CHOOSE_DRINK, CHOOSE_CUTLERY, GIVE_ADDITIONAL_INF0, SIGN_ORDER, FINISHED_ORDER};

order createOrder();
food chooseFood(int* state, food* foods, int);
foodSubtype chooseSubtype(int *state, food chosenFood);
drink chooseDrink(int *state, drink *drinks, int nrOfDrinks, int *userWantsDrink);
char* chooseCutlery(int *state);

int printReceipt(order mOrder, user mUser);

#endif //FOOD_ORDERING_V2_MENU_H
