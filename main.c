#include <stdio.h>
#include "userdata.h"
#include "options.h"

#define NO_FOOD_TYPE 3
#define NO_FOOD_SUBTYPE 4
#define NO_DRINKS 4
#define CHAR_LENGTH 20



int main() {

    char username[CHAR_LENGTH], password[CHAR_LENGTH];
    char foodTypes[NO_FOOD_TYPE][CHAR_LENGTH] = {"Pizza", "Pasta", "Salad"};
    int foodTypeChoice = -1;
    int foodSubtypePrices[NO_FOOD_TYPE][NO_FOOD_SUBTYPE] = {
            {21, 23, 19},
            {23, 21},
            {23, 22, 19, 21}
    };
    int noFoodSubtypes[NO_FOOD_TYPE] = {3, 2, 4};
    char foodSubtypes[NO_FOOD_TYPE][NO_FOOD_SUBTYPE][CHAR_LENGTH] = {
            {"Pizza con Pollo", "Pizza Diavola", "Pizza Margherita"},
            {"Chicken alfredo", "Mac&cheese"},
            {"Tuna Salad", "Chicken Salad", "Greek Salad", "Cobb"}
    };
    int foodSubtypeChoice = -1;
    char drinkOptions[NO_DRINKS][CHAR_LENGTH] = {"Coca-Cola", "Fanta", "Lipton", "Water"};
    int drinkOptionPrices[NO_DRINKS] = {5, 5, 5, 4};
    int drinkChoice = -2;
    int cutleryChoice = -1;
    char additionalInfo[100];
    char choice;
    int state = 0;
    int isOrderConfirmed = 0;

    while(isOrderConfirmed == 0) {
        switch (state) {
            //log in
            case 0: {
                signIn(username, password);
                state++;
                break;
            }
            //choose food
            case 1: {
                printf("Please choose your meal:\n");
                printMenu(NO_FOOD_TYPE, CHAR_LENGTH, foodTypes);
                foodTypeChoice = makeChoice(&state, NO_FOOD_TYPE);
                break;
            }
            //choose food subtype
            case 2: {
                printf("Please choose your meal:\n");
                printMenuWithPrices(0, noFoodSubtypes[foodTypeChoice], CHAR_LENGTH, foodSubtypes[foodTypeChoice], foodSubtypePrices[foodTypeChoice]);
                choice = getchar();
                getchar();
                if (choice - 'a'==noFoodSubtypes[foodTypeChoice]) {
                    state--;
                    break;
                }
                if ((choice-'a'<0) || (choice-'a' >noFoodSubtypes[foodTypeChoice])) {
                    printf("Invalid answer, please select again.\n");
                    break;
                }
                foodSubtypeChoice = choice - 'a';
                state++;
                break;
            }
            //choosing drink
            case 3: {
                printf("Please choose a drink to go with your %s:\n", foodTypes[foodTypeChoice]);
                printMenuWithPrices(1, NO_DRINKS, CHAR_LENGTH, drinkOptions, drinkOptionPrices);
                choice= getchar();
                getchar();
                if(choice - 'a' == NO_DRINKS+1) {
                    state--;
                    break;
                }
                if ((choice-'a'<0) || (choice-'a' >NO_DRINKS+1)) {
                    printf("Invalid answer, please select again.\n");
                    break;
                }
                drinkChoice = choice - 'a';
                state++;
                break;
            }
            //cutlery
            case 4: {
                printf("Do you want cutlery?\n");
                printf("a) Yes\n");
                printf("b) No\n");
                printf("c) Go back\n");
                choice = getchar();
                getchar();
                int choiceInt;
                choiceInt = choice - 'a';
                switch (choiceInt) {
                    case 0: {
                        cutleryChoice = 1;
                        state++;
                        break;
                    }
                    case 1: {
                        cutleryChoice = 0;
                        state++;
                        break;
                    }
                    case 2: {
                        state--;
                        break;
                    }
                    default: {
                        printf("Invalid answer, please select again.\n");
                        break;
                    }
                }
                break;
            }
            //additional info
            case 5: {
                printf("Any additional information?\n");
                gets(additionalInfo);
                state++;
                break;
            }
            //confirmation
            case 6: {
                printf("-----------------\n"
                       "This is your order:\n"
                       "Name: %s\n"
                       "Food items:\n"
                       "--%s: %d\n", username, foodSubtypes[foodTypeChoice][foodSubtypeChoice], foodSubtypePrices[foodTypeChoice][foodSubtypeChoice]);
                if (drinkChoice != NO_DRINKS) {
                    printf("--%s: %d\n", drinkOptions[drinkChoice], drinkOptionPrices[drinkChoice]);
                }
                printf("Cutlery: ");
                if (cutleryChoice == 0) printf("no\n");
                else printf("yes\n");
                printf("Additional information: %s\n", additionalInfo);
                if (drinkChoice != NO_DRINKS)
                    printf("Payment amount: %d\n", foodSubtypePrices[foodTypeChoice][foodSubtypeChoice] + drinkOptionPrices[drinkChoice]);
                else
                    printf("Payment amount: %d\n", foodSubtypePrices[foodTypeChoice][foodSubtypeChoice]);
                printf("-----------------\n");
                printf("a) Confirm order\n"
                       "b) Go back\n");
                choice = getchar();
                getchar();
                int choiceInt;
                choiceInt = choice - 'a';
                switch (choiceInt) {
                    case 0: {
                        printf("Order confirmed! Thank you for buying from us, %s!", username);
                        isOrderConfirmed = 1;
                        break;
                    }
                    case 1: {
                        state-=2;
                        break;
                    }
                    default: {
                        printf("Invalid answer, please select again.\n");
                        break;
                    }
                }
                break;
            }
        }
    }

    return 0;
}