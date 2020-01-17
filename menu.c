//
// Created by diana on 19/12/2019.
//

#include "menu.h"
#include "food-ordering-macros.h"
#include "user.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define GO_BACK -1
#define ERROR -2

#define DASHED_LINE "-----------------------\n"

void printFoodOptions(food *foods, int nrOfFoods);

int makeSelection(int nrOfTypes);

void printSubtypeOptions(food foodType);

void printDrinkOptions(drink *pDrink, int drinks);

double calculateSum(order order);

order createOrder() {
    order o;
    o.chosenFood = createSubtype();
    o.chosenDrink = createDrink();
    o.cutlery = (char*) malloc(YES_NO_LENGTH* sizeof(char));
    o.additionalInfo = (char*) malloc(LONG_INPUT_LENGTH* sizeof(char));
    return o;
}

food chooseFood(int *state, food *foods, int nrOfFoods) {
    food chosenFood;
    printFoodOptions(foods, nrOfFoods);
    int choice = makeSelection(nrOfFoods);
    if (choice>=0) {
        chosenFood = createFood(foods[choice].nrOfSubtypes);
        chosenFood = foods[choice];
        *state=CHOOSE_SUBTYPE;
    } else if (choice==GO_BACK) {
        *state=SIGN_IN;
        chosenFood = createFood(1);
    } else {
        chosenFood = createFood(1);
    }
    return chosenFood;
}

foodSubtype chooseSubtype(int *state, food chosenFood) {
    foodSubtype chosenSubType;
    printSubtypeOptions(chosenFood);
    int choice = makeSelection(chosenFood.nrOfSubtypes);
    if (choice>=0) {
        chosenSubType = createSubtype();
        chosenSubType = chosenFood.subtypes[choice];
        *state=CHOOSE_DRINK;
    } else if (choice==GO_BACK) {
        *state=CHOOSE_FOOD;
        chosenSubType = createSubtype();
    } else {
        chosenSubType = createSubtype();
    }
    return chosenSubType;
}

drink chooseDrink(int *state, drink *drinks, int nrOfDrinks, int *userWantsDrink) {
    drink chosenDrink;
    printDrinkOptions(drinks, nrOfDrinks);
    int choice = makeSelection(nrOfDrinks+1);
    if (choice == nrOfDrinks) {
        *userWantsDrink = 0;
        chosenDrink = createDrink();
        *state = CHOOSE_CUTLERY;
    } else if (choice>=0) {
        *userWantsDrink = 1;
        chosenDrink = createDrink();
        chosenDrink = drinks[choice];
        *state=CHOOSE_CUTLERY;
    } else if (choice==GO_BACK) {
        *state=CHOOSE_SUBTYPE;
        chosenDrink = createDrink();
    } else {
        chosenDrink = createDrink();
    }
    return chosenDrink;
}

char *chooseCutlery(int *state) {
    char* chosenCutlery = (char*)malloc(YES_NO_LENGTH* sizeof(char));
    printf("Do you want cutlery?\n");
    printf("a) Yes\n");
    printf("b) No\n");
    printf("c) Go back\n");
    int choice = makeSelection(2);
    if (choice>=0) {
        switch (choice) {
            case 0: {
                strcpy(chosenCutlery, "Yes");
                break;
            }
            default: {
                strcpy(chosenCutlery, "No");
                break;
            }
        }
        *state=GIVE_ADDITIONAL_INF0;
    } else if (choice==GO_BACK) {
        *state=CHOOSE_DRINK;
        chosenCutlery = NULL;
    } else {
        chosenCutlery = NULL;
    }
    return chosenCutlery;
}

int printReceipt(order mOrder, user mUser) {
    printf(DASHED_LINE);
    printf("Name: %s\n", mUser.username);
    printf("Food items:\n");
    printf("---%s- %.2f\n", mOrder.chosenFood.name, mOrder.chosenFood.price);
    if (mOrder.drinkIsSelected == 1) printf("---%s- %.2f\n", mOrder.chosenDrink.name, mOrder.chosenDrink.price);
    printf("Cutlery: %s\n", mOrder.cutlery);
    printf("Additional info: %s\n", mOrder.additionalInfo);
    printf("Payment amount: %.2f\n", calculateSum(mOrder));
    printf(DASHED_LINE);
    printf("a) Confirm order\n"
           "b) Go back\n");
    int choice = makeSelection(1);
    if (choice>=0) {
        return FINISHED_ORDER;
    } else if (choice==GO_BACK) {
        return CHOOSE_CUTLERY;
    } else {
        return SIGN_ORDER;
    }
}

double calculateSum(order order) {
    return order.chosenDrink.price+ order.chosenFood.price;
}

void printDrinkOptions(drink *pDrink, int drinks) {
    printf("Please choose the type of drink:\n");
    int i=0;
    for (i; i < drinks; ++i) {
        putchar('a'+i);
        printf(") %s - %.2f\n", pDrink[i].name, pDrink[i].price);
    }
    putchar('a'+i); i++;
    printf(") No, thanks\n");
    putchar('a'+i);
    printf(") %s\n", GO_BACK_MSG);
}

void printSubtypeOptions(food foodType) {
    printf("Please choose the type of %s:\n", foodType.name);
    int i=0;
    for (i; i < foodType.nrOfSubtypes; ++i) {
        putchar('a'+i);
        printf(") %s - %.2f\n", foodType.subtypes[i].name, foodType.subtypes[i].price);
    }
    putchar('a'+i);
    printf(") %s\n", GO_BACK_MSG);
}

int makeSelection(int nrOfTypes) {
    int c;
    c = getchar();
    getchar();
    c = c-'a';
    if (c< nrOfTypes && c>=0) return c;
    else if (c == nrOfTypes) return GO_BACK;
    else return ERROR;
}

void printFoodOptions(food *foods, int nrOfFoods) {
    printf(SELECT_FOOD_MSG);
    int i = 0;
    for (i; i < nrOfFoods; ++i) {
        putchar('a'+i);
        printf(") %s\n", foods[i].name);
    }
    putchar('a'+i);
    printf(") %s\n", GO_BACK_MSG);
}

