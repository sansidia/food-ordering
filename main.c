#include <stdio.h>
#include "user.h"
#include "food.h"
#include "food-subtype.h"
#include "drink.h"
#include "load-data.h"
#include "food-ordering-macros.h"
#include "menu.h"
#include "sign_in.h"

int main() {
    int nrOfFoods, nrOfDrinks, state=SIGN_IN;
    food* foods, chosenFood;;
    drink* drinks;
    user* users, currentUser;
    order myOrder;

    users = (user*)malloc(NR_OF_USERS* sizeof(user));

    for (int i = 0; i < NR_OF_USERS; ++i) users[i] = createUser();
    defineDefaultUser(&users[0]);

    FILE* inputFile = fopen(FILE_PATH, "r");
    if (inputFile != NULL)
        loadDataFromFile(inputFile, &nrOfFoods, &foods, &nrOfDrinks, &drinks);
    else
        loadDataFromConsole(&nrOfFoods, &foods, &nrOfDrinks, &drinks);
	fclose(inputFile);

    myOrder = createOrder();

    while(state != FINISHED_ORDER) {
        switch (state) {
            case SIGN_IN: {
                currentUser = createUser();
                signInOrUp(&currentUser, users);
                state = CHOOSE_FOOD;
                break;
            }
            case CHOOSE_FOOD: {
                chosenFood = chooseFood(&state, foods, nrOfFoods);
                break;
            }
            case CHOOSE_SUBTYPE: {
                myOrder.chosenFood = chooseSubtype(&state, chosenFood);
                break;
            }
            case CHOOSE_DRINK: {
                myOrder.chosenDrink = chooseDrink(&state, drinks, nrOfDrinks);
                break;
            }
            case CHOOSE_CUTLERY: {
                myOrder.cutlery = chooseCutlery(&state);
                break;
            }
            case GIVE_ADDITIONAL_INF0: {
                printf("Any additional info?\n");
                gets(myOrder.additionalInfo);
                state = SIGN_ORDER;
                break;
            }
            case SIGN_ORDER: {
                state = printReceipt(myOrder, currentUser);
                break;
            }
            default: {
                state = SIGN_IN;
                break;
            }
        }
    }
    printf("Order confirmed! Thank you for buying from us, %s!", currentUser.username);


    for (int j = 0; j < nrOfDrinks; ++j) free(drinks[j].name);
    free(drinks);
    for (int k = 0; k < nrOfFoods; ++k)  {
        free(foods[k].name);
        for (int i = 0; i < foods[k].nrOfSubtypes; ++i) free(foods[k].subtypes[i].name);
        free(foods[k].subtypes);
    }
    free(foods);
    for (int l = 0; l < NR_OF_USERS; ++l) {
        free(users[l].username);
        free(users[l].password);
    }
    free(users);
    free(currentUser.password); free(currentUser.username);
    free(myOrder.chosenFood.name); free(myOrder.chosenDrink.name); free(myOrder.additionalInfo);
    free(myOrder.cutlery);
    free(chosenFood.name);
    for (int m = 0; m < chosenFood.nrOfSubtypes; ++m) {
        free(chosenFood.subtypes[m].name);
    }
    free(chosenFood.subtypes);
    return 0;
}