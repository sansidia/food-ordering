#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse-string.h"
#include "userdata.h"
#include "options.h"
#define NO_FOOD_TYPE 3
#define NO_FOOD_SUBTYPE 4
#define NO_DRINKS 4
#define CHAR_LENGTH 20
#define MAX_INPUT 100
int main() {

    //TODO: effective user inout management
    //TODO: implement string parsing

    int noOfFoodTypes;
    scanf("%d", &noOfFoodTypes); getchar();
    printf("nr of food types is %d\n", noOfFoodTypes);
    char *userInput = (char*) malloc(MAX_INPUT * sizeof(char));
    for (int currentItem = 0; currentItem < noOfFoodTypes; ++currentItem) {
        gets(userInput);
        printf("Input is \"%s\"\n", userInput);
    }

    //MEMORY DEALLOCATION
    free(userInput);

    /*char userInput[100];
    gets(userInput);
    //TODO: count how many subtypes there are
    int noOfSubtypes = 0;
    for (unsigned int i = 0; i < strlen(userInput); i++) {
        if (userInput[i] == '(') noOfSubtypes++;
    }*/


/*Please load the data
>3:
>Pizza: (Pizza Carbonara - 21.00) (Pizza Diavola - 23.00) (Pizza Margherita - 19.00)
>Pasta: (Chicken alfredo - 23.00) (Mac&cheese - 21.00)
>Salad: (Tuna Salad - 23.00) (Chicken Salad - 22.00) (Greek Salad - 19.00) (Cobb - 21.00)
>4:
>(Coca-cola - 5), (Fanta -5), (Lipton - 5), (Water - 4)*/
    /*char separatorString[] = " (),-:;";
    char* splitter = strtok(userInput, separatorString);
    char food[25], subtype[3][25];
    char priceString[3][25]; double prices[3];


    strcpy(food, splitter);
    for (int k = 0; k < noOfSubtypes; k++) {
        parse(NULL, subtype, priceString);
        printf("subtype[%d] is %s and priceString[%d] is %s\n", k, subtype[k], k, priceString[k]);
        char **pVoid = NULL;
        prices[k] = strtod(priceString[k], pVoid);
    }*/

    /*int i= -1;
    while (splitter!= NULL) {
        splitter = strtok(NULL, separatorString);
        if (splitter != NULL) {
            i++;
            strcpy(subtype[i], splitter);
        }
    }*/

    /*printf("%s: ", food);
    for (int j = 0; j < noOfSubtypes; j++) {
        printf("%s - %.2f, ",subtype[j], prices[j]);
    }*/

    //TODO: break apart into functions
    //TODO: variable redeclaration according to assignment requirements
    //TODO: dynamic memory allocation


/*
    char username[CHAR_LENGTH];
    char password[CHAR_LENGTH];
    char foodTypes[NO_FOOD_TYPE][CHAR_LENGTH] = {"Pizza", "Pasta", "Salad"};
    int foodTypeChoice = -1;
    int foodSubtypeChoice = -1;
    int drinkChoice = -2;
    int cutleryChoice = -1;
    int choice;
    int foodSubtypePrices[NO_FOOD_TYPE][NO_FOOD_SUBTYPE] = {  //TODO: modify foodSubtypePrices sizes so that it it refers to the strict nr of subtypes
        {21, 23, 19},
        {23, 21},
        {23, 22, 19, 21} };
    int noOfFoodSubtypes[NO_FOOD_TYPE] = {3, 2, 4};
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
                printMenuWithPrices(0, noOfFoodSubtypes[foodTypeChoice], CHAR_LENGTH, foodSubtypes[foodTypeChoice], foodSubtypePrices[foodTypeChoice]);
                foodSubtypeChoice = makeChoice(&state, noOfFoodSubtypes[foodTypeChoice], 1); break;
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
                if (choice == 0) printf("Order confirmed! Thank you for buying from us, %s!", username); break; //TODO: check grading from previous assignment
        }}

        */
    return 0;}
