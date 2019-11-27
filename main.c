#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse-string.h"
#include "userdata.h"
#include "options.h"
#include <ctype.h>
#define NO_FOOD_TYPE 3
#define NO_FOOD_SUBTYPE 4
#define NO_DRINKS 4
#define MAX_ITEM_LENGTH 20
#define MAX_INPUT 100
#define UNINITIALIZED_VALUE -1
#define PREV_IS_TEXT 0
#define PREV_IS_NR 1
#define ERROR_MSG "Invalid input, please try again."
int main() {

    //TODO DONE: effective user inout management
    //TODO DONE: implement string parsing

    int noOfFoodTypes;
    scanf("%d", &noOfFoodTypes); getchar();
    printf("nr of food types is %d\n", noOfFoodTypes);

    char** foodTypes = (char**) malloc(noOfFoodTypes* sizeof(char*));
    char*** foodSubtypes = (char***) malloc(noOfFoodTypes* sizeof(char**));
    int* noOfFoodSubtypes = (int*) malloc(noOfFoodTypes* sizeof(int));
    double** foodSubtypePrices = (double**) malloc(noOfFoodTypes* sizeof(double*));

    char *userInput = (char*) malloc(MAX_INPUT * sizeof(char));
    for (int currentItem = 0; currentItem < noOfFoodTypes; ++currentItem) {
        gets(userInput);
        printf("Input is \"%s\"\n", userInput);
        //COUNT SUBTYPES
        noOfFoodSubtypes[currentItem] = 0;
        for (unsigned int i = 0; i < strlen(userInput); ++i) {
            if (userInput[i] == '(') noOfFoodSubtypes[currentItem]++;
        }
        foodSubtypes[currentItem] = (char**) malloc(noOfFoodSubtypes[currentItem] * sizeof(char*));
        foodSubtypePrices[currentItem] = (double*) malloc(noOfFoodSubtypes[currentItem]* sizeof(double));
        //PARSE INPUT
        char* separator;
        char separatorString[] = ",() :;-";
        separator = strtok(userInput, separatorString);
        printf("separator is %s\n", separator);
        foodTypes[currentItem] = ( char * ) malloc(MAX_ITEM_LENGTH * sizeof(char));
        strcpy(foodTypes[currentItem], separator);
        printf("foodtype is %s\n", foodTypes[currentItem]);
        int currentSubtype = UNINITIALIZED_VALUE;
        int previousStringType = UNINITIALIZED_VALUE;
        while ((separator = strtok(NULL, separatorString))) {
            printf("sep is %s\n", separator);
            if (isalpha(separator[0])) {
                if (previousStringType == UNINITIALIZED_VALUE) {
                    currentSubtype ++;
                    previousStringType = PREV_IS_TEXT;
                    foodSubtypes[currentItem][currentSubtype] = ( char * ) malloc(MAX_ITEM_LENGTH * sizeof(char));
                    strcpy(foodSubtypes[currentItem][currentSubtype], separator);
                    printf("%s type %d is %s\n", foodTypes[currentItem], currentSubtype,
                           foodSubtypes[currentItem][currentSubtype]);
                } else if (previousStringType == PREV_IS_TEXT) {
                    strcat(foodSubtypes[currentItem][currentSubtype], " ");
                    strcat(foodSubtypes[currentItem][currentSubtype], separator);
                    printf("%s type %d is %s\n", foodTypes[currentItem], currentSubtype,
                           foodSubtypes[currentItem][currentSubtype]);
                    previousStringType = PREV_IS_TEXT;
                } else if (previousStringType == PREV_IS_NR) {
                    currentSubtype ++;
                    previousStringType = PREV_IS_TEXT;
                    foodSubtypes[currentItem][currentSubtype] = ( char * ) malloc(MAX_ITEM_LENGTH * sizeof(char));
                    strcpy(foodSubtypes[currentItem][currentSubtype], separator);
                    printf("%s type %d is %s\n", foodTypes[currentItem], currentSubtype,
                           foodSubtypes[currentItem][currentSubtype]);
                }
            } else if (isdigit(separator[0])) {
                if (previousStringType == UNINITIALIZED_VALUE) {
                    printf(ERROR_MSG);
                } else if (previousStringType == PREV_IS_TEXT) {
                    previousStringType = PREV_IS_NR;
                    char **pVoid = NULL;
                    foodSubtypePrices[currentItem][currentSubtype] = strtod(separator, pVoid);
                    printf("%s type %d is %s and costs %.2f\n", foodTypes[currentItem], currentSubtype,
                           foodSubtypes[currentItem][currentSubtype], foodSubtypePrices[currentItem][currentSubtype]);
                } else if (previousStringType == PREV_IS_NR) {
                    printf(ERROR_MSG);
                }
            }
        }
    }

    int noOfDrinks;
    scanf("%d", &noOfDrinks); getchar();

    char **drinkOptions = (char**) malloc(noOfDrinks* sizeof(char*));
    double *drinkOptionPrices = (double*) malloc(noOfDrinks* sizeof(double));

    gets(userInput);
    printf("Input is \"%s\"\n", userInput);

    int currentItem = UNINITIALIZED_VALUE;
    char* separator;
    char separatorString[] = ",() :;-";
    separator = strtok(userInput, separatorString);
    printf("separator is %s\n", separator);
    drinkOptions[currentItem] = ( char * ) malloc(MAX_ITEM_LENGTH * sizeof(char));
    int previousStringType = UNINITIALIZED_VALUE;
    if(isalpha(separator[0])) {
        currentItem++;
        strcpy(drinkOptions[currentItem], separator);
        //int currentSubtype = UNINITIALIZED_VALUE;
        previousStringType = PREV_IS_TEXT;
    } else {
        printf(ERROR_MSG);
    }
    while ((separator = strtok(NULL, separatorString))) {
        printf("sep is %s\n", separator);
        if (isalpha(separator[0])) {
            if (previousStringType == UNINITIALIZED_VALUE) {
                printf(ERROR_MSG);
            } else if (previousStringType == PREV_IS_TEXT) {
                strcat(drinkOptions[currentItem], " ");
                strcat(drinkOptions[currentItem], separator);
                printf("Drink type %d is %s\n", currentItem, drinkOptions[currentItem]);
                previousStringType = PREV_IS_TEXT;
            } else if (previousStringType == PREV_IS_NR) {
                currentItem++; printf("I'm here!\n");
                previousStringType = PREV_IS_TEXT;
                drinkOptions[currentItem] = (char *) malloc(MAX_ITEM_LENGTH * sizeof(char));
                strcpy(drinkOptions[currentItem], separator);
                printf("Drink type %d is %s\n", currentItem, drinkOptions[currentItem]);
            }
        } else if (isdigit(separator[0])) {
            if (previousStringType == UNINITIALIZED_VALUE) {
                printf(ERROR_MSG);
            } else if (previousStringType == PREV_IS_TEXT) {
                previousStringType = PREV_IS_NR;
                char **pVoid = NULL;
                drinkOptionPrices[currentItem] = strtod(separator, pVoid);
                printf("Drink type %d is %s and costs %.2f\n", currentItem, drinkOptions[currentItem], drinkOptionPrices[currentItem]);
            } else if (previousStringType == PREV_IS_NR) {
                printf(ERROR_MSG);
            }
        }
    }

    //TODO DONE: count how many subtypes there are

    //TODO: break apart into functions
    //TODO: variable redeclaration according to assignment requirements
    //TODO: dynamic memory allocation

    char username[MAX_ITEM_LENGTH];
    char password[MAX_ITEM_LENGTH];
    //char foodTypes[NO_FOOD_TYPE][MAX_ITEM_LENGTH] = {"Pizza", "Pasta", "Salad"};
    int foodTypeChoice = -1;
    int foodSubtypeChoice = -1;
    int drinkChoice = -2;
    int cutleryChoice = -1;
    int choice;
    /*int foodSubtypePrices[NO_FOOD_TYPE][NO_FOOD_SUBTYPE] = {  //TODO: modify foodSubtypePrices sizes so that it it refers to the strict nr of subtypes
        {21, 23, 19},
        {23, 21},
        {23, 22, 19, 21} };*/
    //int noOfFoodSubtypes[NO_FOOD_TYPE] = {3, 2, 4};
    /*char foodSubtypes[NO_FOOD_TYPE][NO_FOOD_SUBTYPE][MAX_ITEM_LENGTH] = {
        {"Pizza con Pollo", "Pizza Diavola", "Pizza Margherita"},
        {"Chicken alfredo", "Mac&cheese"},
        {"Tuna Salad", "Chicken Salad", "Greek Salad", "Cobb"} };*/
    //char drinkOptions[NO_DRINKS][MAX_ITEM_LENGTH] = {"Coca-Cola", "Fanta", "Lipton", "Water"};
    //int drinkOptionPrices[NO_DRINKS] = {5, 5, 5, 4};
    char **cutleryOptions = NULL; strcpy(cutleryOptions[0], "Yes"); strcpy(cutleryOptions[1], "No");
    char additionalInfo[100];
    int state = 0, isOrderConfirmed = 0;
    while(isOrderConfirmed == 0) {
        switch (state) {
            case 0: //read user data
                signIn(username, password);
                state++; break;
            case 1: //food type selection
                printf("Please choose your meal:\n");
                printMenu(NO_FOOD_TYPE, foodTypes);
                foodTypeChoice = makeChoice(&state, NO_FOOD_TYPE, 1); break;
            case 2: //food subtype selection
                printf("Please choose your favourite %s:\n", foodTypes[foodTypeChoice]);
                printMenuWithPrices(0, noOfFoodSubtypes[foodTypeChoice], foodSubtypes[foodTypeChoice], foodSubtypePrices[foodTypeChoice]);
                foodSubtypeChoice = makeChoice(&state, noOfFoodSubtypes[foodTypeChoice], 1); break;
            case 3: //drink selection
                printf("Please choose a drink to go with your %s:\n", foodTypes[foodTypeChoice]);
                printMenuWithPrices(1, NO_DRINKS, drinkOptions, drinkOptionPrices);
                drinkChoice = makeChoice(&state, NO_DRINKS + 1, 1); break;
            case 4: //cutlery selection
                printf("Do you want cutlery?\n");
                printMenu(2, cutleryOptions);
                cutleryChoice = makeChoice(&state, 2, 1); break;
            case 5: //additional info
                getAdditionalInfo(&state, additionalInfo); break;
            case 6: //confirmation
                printForm(username, foodSubtypes[foodTypeChoice][foodSubtypeChoice], foodSubtypePrices[foodTypeChoice][foodSubtypeChoice], drinkOptions[drinkChoice],drinkOptionPrices[drinkChoice], drinkChoice, NO_DRINKS, cutleryChoice, additionalInfo);
                printf("a) Confirm order\n" "b) Go back\n");
                choice = makeChoice(&state, 1, 2);
                if (choice == 0) printf("Order confirmed! Thank you for buying from us, %s!", username); break; //TODO: check grading from previous assignment
        }
    }


    //MEMORY DEALLOCATION
    for (int k = 0; k < noOfDrinks; ++k) {
        free(drinkOptions[k]);
    }
    free(drinkOptions);
    free(drinkOptionPrices);
    for (int i = 0; i < noOfFoodTypes; ++i) {
        free(foodTypes[i]);
        free(foodSubtypePrices[i]);
        for (int j = 0; j < noOfFoodSubtypes[i]; ++j) {
            free(foodSubtypes[i][j]);
        }
        free(foodSubtypes[i]);
    }
    free(foodSubtypePrices);
    free(foodSubtypes);
    free(noOfFoodSubtypes);
    free(foodSubtypes);
    free(userInput);
    return 0;
}
