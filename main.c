#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "userdata.h"
#include "options.h"

//#define NO_FOOD_TYPE 3
#define NO_FOOD_SUBTYPE 4
#define NO_DRINKS 4
#define FOOD_LENGTH 20
#define LOAD_DATA "Please load the data\n"
#define STRING_LENGTH 250
#define INPUT_ERROR_MSG "Invalid input, please try again."

int main() {
    int noOfFoodTypes, noOfDrinks;

    char *inputString;
    char** foodTypes;
    char*** foodSubtypes;
    int* noFoodSubtypes;


    //reading data
    printf(LOAD_DATA);
    scanf("%d\n", &noOfFoodTypes);

    foodTypes = (char**) malloc(noOfFoodTypes* sizeof(char*));
    inputString = (char*) malloc(STRING_LENGTH* sizeof(char));
    foodSubtypes = (char***) malloc(noOfFoodTypes* sizeof(char**));
    noFoodSubtypes = (int*) malloc(noOfFoodTypes * sizeof(int));

    for (int currentFoodType = 0; currentFoodType < noOfFoodTypes; currentFoodType++) {
        gets(inputString);
        printf("Yo so i got this string here: %s\n", inputString);

        //format string
        unsigned int currentCharPosition = 0; int confirmFoodType = 0;
        while (inputString[currentCharPosition] != ':' && currentCharPosition < strlen(inputString)) {
            foodTypes[currentFoodType][currentCharPosition] = inputString[currentCharPosition];
            printf("I copied character %c. foodTypes[%d] = %c.\n", inputString[currentCharPosition], currentCharPosition, foodTypes[currentFoodType][currentCharPosition]);
            currentCharPosition++;
        }
        foodTypes[currentFoodType][currentCharPosition] = '\0';
        printf("Your food type is %s\n", foodTypes[currentFoodType]);
        printf("current character is at position %d, the input string is %s, character %c\n", currentCharPosition, inputString, inputString[currentCharPosition]);
        if (inputString[currentCharPosition] != ':' || currentCharPosition >= strlen(inputString)) {printf(INPUT_ERROR_MSG); currentFoodType--;}
        else {
            noFoodSubtypes[currentFoodType] = 0;
            for (unsigned int k=currentCharPosition; k < strlen(inputString); k++) {
                //counting items
                if (inputString[k] == '(') noFoodSubtypes[currentFoodType]++;
            }
            foodSubtypes[currentFoodType] = (char**) malloc(noFoodSubtypes[currentFoodType] * sizeof(char*));
            for (int currentSubtype = 0; currentSubtype < noFoodSubtypes[currentFoodType]; currentSubtype++) {
                foodSubtypes[currentFoodType][currentSubtype] = (char*)malloc(FOOD_LENGTH* sizeof(char));
                while (inputString[currentCharPosition] != '(') currentCharPosition++;
                while (inputString[currentCharPosition] != ')') {
                    int subtypePosition = 0;
                    if (isalpha(inputString[currentCharPosition]) || inputString[currentCharPosition] == ' ')
                        foodSubtypes[currentFoodType][currentSubtype][subtypePosition] = inputString[currentCharPosition];
                    currentCharPosition++;
                    if (inputString[currentCharPosition] == ')')
                        foodSubtypes[currentFoodType][currentSubtype][currentCharPosition] = '\0';
                }

                printf(" (I read a word! It's %s)\n", foodSubtypes[currentFoodType][currentSubtype]);
            }
        }
    }

    for (int l = 0; l < noOfFoodTypes; l++) {
        printf("%s: ", foodTypes[l]);
        for (int i = 0; i < noFoodSubtypes[l]; i++) {
            printf("(%s)", foodSubtypes[l][i]);
        }
        printf("\n");
    }

    //dealloc memory

    free(noFoodSubtypes);
    for (int i = 0; i < noOfFoodTypes; i++) {
        for (int j = 0; j < noFoodSubtypes[i]; j++) {
            free(foodSubtypes[i][j]);
        }
        free(foodSubtypes[i]);
    }
    free(foodSubtypes);
    free(inputString);
    for (int j = 0; j < noOfFoodTypes; j++) {
        free(foodTypes[j]);
    }
    free(foodTypes);


    char *username = (char*)malloc(FOOD_LENGTH * sizeof(char));
    char *password = (char*)malloc(FOOD_LENGTH * sizeof(char));
    //char foodTypes[NO_FOOD_TYPE][FOOD_LENGTH] = {"Pizza", "Pasta", "Salad"};
   /* int foodTypeChoice = -1;
    int foodSubtypeChoice = -1;
    int drinkChoice = -2;
   */ int cutleryChoice = -1;
    int choice; /*
    int foodSubtypePrices[NO_FOOD_TYPE][NO_FOOD_SUBTYPE] = {
        {21, 23, 19},
        {23, 21},
        {23, 22, 19, 21} };
    int noFoodSubtypes[NO_FOOD_TYPE] = {3, 2, 4};
    char foodSubtypes[NO_FOOD_TYPE][NO_FOOD_SUBTYPE][FOOD_LENGTH] = {
        {"Pizza con Pollo", "Pizza Diavola", "Pizza Margherita"},
        {"Chicken alfredo", "Mac&cheese"},
        {"Tuna Salad", "Chicken Salad", "Greek Salad", "Cobb"} };
    char drinkOptions[NO_DRINKS][FOOD_LENGTH] = {"Coca-Cola", "Fanta", "Lipton", "Water"};
    int drinkOptionPrices[NO_DRINKS] = {5, 5, 5, 4};*/

    /*
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
                printMenu(NO_FOOD_TYPE, FOOD_LENGTH, foodTypes);
                foodTypeChoice = makeChoice(&state, NO_FOOD_TYPE, 1); break;
            case 2: //food subtype selection
                printf("Please choose your favourite %s:\n", foodTypes[foodTypeChoice]);
                printMenuWithPrices(0, noFoodSubtypes[foodTypeChoice], FOOD_LENGTH, foodSubtypes[foodTypeChoice], foodSubtypePrices[foodTypeChoice]);
                foodSubtypeChoice = makeChoice(&state, noFoodSubtypes[foodTypeChoice], 1); break;
            case 3: //drink selection
                printf("Please choose a drink to go with your %s:\n", foodTypes[foodTypeChoice]);
                printMenuWithPrices(1, NO_DRINKS, FOOD_LENGTH, drinkOptions, drinkOptionPrices);
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

        */
    return 0;}
