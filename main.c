#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse-string.h"
#include "userdata.h"
#include "options.h"
#include <ctype.h>
#include "macros.h"

void tokenize (char* string, char* tokens, char* returnString) {
    int stringDelimited = 0;
    while (stringDelimited == 0) {
        char *p = strpbrk(string, tokens);
        if (p - string != 0) {
            strcpy(returnString, string);
            returnString[p-string] = '\0';
            strcpy(string, p);
            stringDelimited = 1;
        } else {
            strcpy(string, string+1);
        }
    }
}

void separate(char* source, char* destination1, char* destination2) {
    char* ptr = (char*) malloc(MAX_ITEM_LENGTH* sizeof(char));
    tokenize(source, "-", destination1);
    strcpy(destination1, strtok(source, "-"));
    strcpy(destination2, strtok(NULL, "-"));
}

void cleanUp(char* string) {
    int extraSpaces = 0;
    for (unsigned int i = 0; i < strlen(string); ++i) {
        if (string[i] == ' ') {
            extraSpaces++;
            if (isalpha(string[i+1]) || isdigit(string[i+1]))
                break;
        } else break;
    }
    strcpy(string, string+extraSpaces);
    extraSpaces = 0;
    for (unsigned int i = strlen(string)-1; i >= 0; --i) {
        if (string[i] == ' ') {
            extraSpaces++;
            if (isalpha(string[i-1]) || isdigit(string[i-1]))
                break;
        } else break;
    }
    string[strlen(string)-extraSpaces] = '\0';
}

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
        foodTypes[currentItem] = (char*) malloc(MAX_ITEM_LENGTH* sizeof(char));
        foodSubtypes[currentItem] = (char **) malloc(noOfFoodSubtypes[currentItem] * sizeof(char *));
        foodSubtypePrices[currentItem] = (double *) malloc(noOfFoodSubtypes[currentItem] * sizeof(double));
        //PARSE INPUT
        char *separator;
        char separatorString[] = ",() :;-";
        separator = strtok(userInput, separatorString);
        strcpy(foodTypes[currentItem], separator);
        for (int currentSubItem = 0; currentSubItem < noOfFoodSubtypes[currentItem]; ++currentSubItem) {
            separator = strtok(NULL, "()");
            if(strcmp(separator, " ") == 0) {
                currentSubItem--;
            } else {
                char *charPrice = (char *) malloc(MAX_ITEM_LENGTH * sizeof(char));
                foodSubtypes[currentItem][currentSubItem] = (char *) malloc(MAX_ITEM_LENGTH * sizeof(char));
                separate(separator, foodSubtypes[currentItem][currentSubItem], charPrice);
                cleanUp(foodSubtypes[currentItem][currentSubItem]);
                cleanUp(charPrice);
                char *voidPtr;
                foodSubtypePrices[currentItem][currentSubItem] = strtod(charPrice, &voidPtr);
            }
        }
    }

    int noOfDrinks = 0;
    scanf("%d", &noOfDrinks); getchar();
    printf("noofdrinks is %d\n", noOfDrinks);

    char** drinkOptions = (char**) malloc(noOfDrinks* sizeof(char*));
    double* drinkOptionPrices = (double*) malloc(noOfDrinks* sizeof(double));

    gets(userInput);
    char* separator = strtok(userInput, "()");
    drinkOptions[0] = (char*) malloc(MAX_ITEM_LENGTH* sizeof(char));
    char* charPrice =(char*) malloc(MAX_ITEM_LENGTH* sizeof(char));
    char * voidPtr;

    separate(separator, drinkOptions[0], charPrice);
    cleanUp(drinkOptions[0]);
    cleanUp(charPrice);
    drinkOptionPrices[0] = strtod(charPrice, &voidPtr);
    for (int currentDrink = 1; currentDrink < noOfDrinks; ++currentDrink) {
        separator = strtok(NULL, "()");
        separate(separator, drinkOptions[currentDrink], charPrice);
        cleanUp(drinkOptions[currentDrink]);
        cleanUp(charPrice);
        drinkOptionPrices[currentDrink] = strtod(charPrice, &voidPtr);
    }

    for (int l = 0; l < noOfFoodTypes; ++l) {
        printf("%s:", foodTypes[l]);
        for (int i = 0; i < noOfFoodSubtypes[l]; ++i) {
            printf("%s - %.1f\n", foodSubtypes[l][i], foodSubtypePrices[l][i]);
        }
    }
    for (int l = 0; l < noOfDrinks; ++l) {
        printf("%s: %.1f; ", foodTypes[l]);
        for (int i = 0; i < noOfFoodSubtypes[l]; ++i) {
            printf("%s - %.1f\n", foodSubtypes[l][i], foodSubtypePrices[l][i]);
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
    //char drinkOptions[noOfDrinks][MAX_ITEM_LENGTH] = {"Coca-Cola", "Fanta", "Lipton", "Water"};
    //int drinkOptionPrices[noOfDrinks] = {5, 5, 5, 4};
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
                printMenuWithPrices(1, noOfDrinks, drinkOptions, drinkOptionPrices);
                drinkChoice = makeChoice(&state, noOfDrinks + 1, 1); break;
            case 4: //cutlery selection
                printf("Do you want cutlery?\n");
                printMenu(2, cutleryOptions);
                cutleryChoice = makeChoice(&state, 2, 1); break;
            case 5: //additional info
                getAdditionalInfo(&state, additionalInfo); break;
            case 6: //confirmation
                printForm(username, foodSubtypes[foodTypeChoice][foodSubtypeChoice], foodSubtypePrices[foodTypeChoice][foodSubtypeChoice], drinkOptions[drinkChoice],drinkOptionPrices[drinkChoice], drinkChoice, noOfDrinks, cutleryChoice, additionalInfo);
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
