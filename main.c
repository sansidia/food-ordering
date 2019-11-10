#include <stdio.h>
#include "userdata.h"
#include "options.h"
#define NO_FOOD_TYPE 3
#define NO_FOOD_SUBTYPE 4
#define NO_DRINKS 4
#define CHAR_LENGTH 20
int main() {
    char username[CHAR_LENGTH];
    char password[CHAR_LENGTH];
    char foodTypes[NO_FOOD_TYPE][CHAR_LENGTH] = {"Pizza", "Pasta", "Salad"};
    int foodTypeChoice = -1;
    int foodSubtypeChoice = -1;
    int drinkChoice = -2;
    int cutleryChoice = -1;
    int choice;
    int foodSubtypePrices[NO_FOOD_TYPE][NO_FOOD_SUBTYPE] = {
        {21, 23, 19},
        {23, 21},
        {23, 22, 19, 21} };
    int noFoodSubtypes[NO_FOOD_TYPE] = {3, 2, 4};
    char foodSubtypes[NO_FOOD_TYPE][NO_FOOD_SUBTYPE][CHAR_LENGTH] = {
        {"Pizza con Pollo", "Pizza Diavola", "Pizza Margherita"},
        {"Chicken alfredo", "Mac&cheese"},
        {"Tuna Salad", "Chicken Salad", "Greek Salad", "Cobb"} };
    char drinkOptions[NO_DRINKS][CHAR_LENGTH] = {"Coca-Cola", "Fanta", "Lipton", "Water"};
    int drinkOptionPrices[NO_DRINKS] = {5, 5, 5, 4};
    char cutleryOptions[2][5] = {"Yes", "No"};
    char additionalInfo[100];
    int state = 0, isOrderConfirmed = 0;
    while(isOrderConfirmed == 0) {
        switch (state) {
            case 0: //read user data
                signIn(username, password);
                state++; break;
            case 1: //food type selection
                printf("Please choose your meal:\n");
                printMenu(NO_FOOD_TYPE, CHAR_LENGTH, foodTypes);
                foodTypeChoice = makeChoice(&state, NO_FOOD_TYPE, 1); break;
            case 2: //food subtype selection
                printf("Please choose your favourite %s:\n", foodTypes[foodTypeChoice]);
                printMenuWithPrices(0, noFoodSubtypes[foodTypeChoice], CHAR_LENGTH, foodSubtypes[foodTypeChoice], foodSubtypePrices[foodTypeChoice]);
                foodSubtypeChoice = makeChoice(&state, noFoodSubtypes[foodTypeChoice], 1); break;
            case 3: //drink selection
                printf("Please choose a drink to go with your %s:\n", foodTypes[foodTypeChoice]);
                printMenuWithPrices(1, NO_DRINKS, CHAR_LENGTH, drinkOptions, drinkOptionPrices);
                drinkChoice = makeChoice(&state, NO_DRINKS + 1, 1); break;
            case 4: //cutlery selection
                printf("Do you want cutlery?\n");
                printMenu(2, 5, cutleryOptions);
                cutleryChoice = makeChoice(&state, 2, 1); break;
            case 5: //additional info
                getAdditionalInfo(&state, additionalInfo); break;
            case 6: //confirmation
                printForm(username, foodSubtypes[foodTypeChoice][foodSubtypeChoice], foodSubtypePrices[foodTypeChoice][foodSubtypeChoice], drinkOptions[drinkChoice],drinkOptionPrices[drinkChoice], drinkChoice, NO_DRINKS, cutleryChoice, additionalInfo);
                printf("a) Confirm order\n" "b) Go back\n");
                choice = makeChoice(&state, 1, 2);
                if (choice == 0) printf("Order confirmed! Thank you for buying from us, %s!", username); break;
        }}
    return 0;}
