#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "userdata.h"
#include "options.h"
#include "macros.h"
#include "input_data.h"



/*void cleanExtraChars(char *string, char *chars) {
    int extraChars = 0;
    for (unsigned int i = 0; i < strlen(string); ++i) {
        if (strchr(chars, string[i])) {
            extraChars++;
            if (isalpha(string[i+1]) || isdigit(string[i+1]))
                break;
        } else break;
    }
    strcpy(string, string + extraChars);
    extraChars = 0;
    for (unsigned int i = strlen(string)-1; i >= 0; --i) {
        if (strchr(chars, string[i])) {
            extraChars++;
            if (isalpha(string[i-1]) || isdigit(string[i-1]))
                break;
        } else break;
    }
    string[strlen(string) - extraChars] = '\0';
}*/

int main() {
    int nrOfFoodTypes = 0, noOfDrinks = 0;
    ///FOODS
    nrOfFoodTypes = readNrOfTypes();
    char *username = (char*)malloc(ITEM_LENGTH * sizeof(char));
    char *password = (char*)malloc(ITEM_LENGTH * sizeof(char));;
    char **foodTypes = (char**)malloc(nrOfFoodTypes * sizeof(char*));
    int foodTypeChoice = -1;
    int foodSubtypeChoice = -1;
    int drinkChoice = -2;
    int cutleryChoice = -1;
    int choice;
    int *nrOfFoodSubtypes = (int*)malloc(nrOfFoodTypes * sizeof(int));
    double **foodSubtypePrices = (double**)malloc(nrOfFoodTypes * sizeof(double*));
    char ***foodSubtypes = (char***)malloc(nrOfFoodTypes * sizeof(char*));
    char * userInput = (char*)malloc(LONG_INPUT_LENGTH* sizeof(char));

    readData(DATA_TYPE_FOOD, nrOfFoodTypes, &foodTypes, &nrOfFoodSubtypes, &foodSubtypes, &foodSubtypePrices);

    /*for (int currentType = 0; currentType < nrOfFoodTypes; ++currentType) {
        gets(userInput);
        nrOfFoodSubtypes[currentType] = 0;
        ///COUNT FOOD SUBTYPES
        for (int j = 0; j < strlen(userInput); ++j) {
            if (userInput[j] == '(') nrOfFoodSubtypes[currentType]++;
        }
        ///ASSIGN MEMORY
        foodTypes[currentType] = (char*)malloc(ITEM_LENGTH * sizeof(char));
        foodSubtypePrices[currentType] = (double*)malloc(nrOfFoodSubtypes[currentType] * sizeof(double));
        foodSubtypes[currentType] = (char**) malloc(nrOfFoodSubtypes[currentType] * sizeof(char*));
        for (int j = 0; j < nrOfFoodSubtypes[currentType]; ++j) {
            foodSubtypes[currentType][j] = (char*) malloc(ITEM_LENGTH * sizeof(char));
        }
        ///PARSE INPUT
        char* auxString = (char*) malloc(strlen(userInput)* sizeof(char));

        strcpy(foodTypes[currentType], strtok(userInput, ": "));
        strcpy(auxString, strtok(NULL, ""));
        for (int currentSubtype = 0; currentSubtype < nrOfFoodSubtypes[currentType]; ++currentSubtype) {
            char* object = (char*) malloc(2 * ITEM_LENGTH * sizeof(char));
            strcpy(object, strtok(auxString, ")"));
            cleanExtraChars(object, " ");
            if(currentSubtype != nrOfFoodSubtypes[currentType] - 1) strcpy(auxString, strtok(NULL, ""));
            strcpy(foodSubtypes[currentType][currentSubtype], strtok(object, "()-"));
            cleanExtraChars(foodSubtypes[currentType][currentSubtype], " ");
            strcpy(object, strtok(NULL, ""));
            cleanExtraChars(object, "()- ");
            char* ptr;
            foodSubtypePrices[currentType][currentSubtype] = strtod(object, &ptr);

            free(object);
        }

        free(auxString);
    }*/
    ///DRINKS    
    gets(userInput);
    for (unsigned int i = 0; i < strlen(userInput); ++i) {
        if (!isdigit(userInput[i])) {
            userInput[i] = '\0';
            break;
        }
    }
    for (int i = strlen(userInput)-1; i >= 0 ; i--) {
        noOfDrinks = noOfDrinks*10 + (userInput[i]- '0');
    }
    char **drinkOptions = (char**)malloc(noOfDrinks* sizeof(char*));
    drinkOptions[0] = (char*)malloc(ITEM_LENGTH * sizeof(char)); strcpy(drinkOptions[0], "Coca-cola");
    drinkOptions[1] = (char*)malloc(ITEM_LENGTH * sizeof(char)); strcpy(drinkOptions[1], "fanta");
    drinkOptions[2] = (char*)malloc(ITEM_LENGTH * sizeof(char)); strcpy(drinkOptions[2], "lipton");
    drinkOptions[3] = (char*)malloc(ITEM_LENGTH * sizeof(char)); strcpy(drinkOptions[3], "Water");//[NO_DRINKS][ITEM_LENGTH] = {"Coca-Cola", "Fanta", "Lipton", "Water"};
    double* drinkOptionPrices = (double*)malloc(noOfDrinks* sizeof(double)); drinkOptionPrices[0] = 5; drinkOptionPrices[1] = 5; drinkOptionPrices[2] = 5; drinkOptionPrices[3] = 4; //[NO_DRINKS] = {5, 5, 5, 4};
    char **cutleryOptions = (char**)malloc(2* sizeof(char));
    cutleryOptions[0] = (char*)malloc(4* sizeof(char)); strcpy(cutleryOptions[0], "Yes");
    cutleryOptions[1] = (char*)malloc(3* sizeof(char)); strcpy(cutleryOptions[1], "No");//[2][5] = {"Yes", "No"};
    char *additionalInfo = (char *)malloc(LONG_INPUT_LENGTH* sizeof(char));//[100];
    int state = 0, isOrderConfirmed = 0;
    while(isOrderConfirmed == 0) {
        switch (state) {
            case 0: //read user data
                signIn(username, password);
                state++; break;
            case 1: //food type selection
                printf("Please choose your meal:\n");
                printMenu(nrOfFoodTypes, foodTypes);
                foodTypeChoice = makeChoice(&state, nrOfFoodTypes, 1); break;
            case 2: //food subtype selection
                printf("Please choose your favourite %s:\n", foodTypes[foodTypeChoice]);
                printMenuWithPrices(0, nrOfFoodSubtypes[foodTypeChoice], foodSubtypes[foodTypeChoice],
                                    foodSubtypePrices[foodTypeChoice]);
                foodSubtypeChoice = makeChoice(&state, nrOfFoodSubtypes[foodTypeChoice], 1); break;
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
                if (choice == 0) { printf("Order confirmed! Thank you for buying from us, %s!", username); isOrderConfirmed = 1;}
                break;
        }}
    ///MEMORY CLEAN-UP
    free(additionalInfo);
    for (int i = 0; i < 2; ++i) free(cutleryOptions[i]);
    free(cutleryOptions);
    free(drinkOptionPrices);
    for (int i = 0; i < noOfDrinks; ++i) free(drinkOptions[i]);
    free(drinkOptions);
    for (int i = 0; i < nrOfFoodTypes; ++i) {
        for (int j = 0; j < nrOfFoodSubtypes[i]; ++j) free(foodSubtypes[i][j]);
        free(foodSubtypes[i]);
    }
    free(foodSubtypes);
    for (int i = 0; i < nrOfFoodTypes; ++i) free(foodSubtypePrices);
    free(foodSubtypePrices);
    free(nrOfFoodSubtypes);
    for (int i = 0; i < nrOfFoodTypes; ++i) free(foodTypes[i]);
    free(foodTypes);
    free(password);
    free(username);
    free(userInput);
    return 0;
}
