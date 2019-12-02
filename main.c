#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "userdata.h"
#include "options.h"
#include "parse_input.h"

#define LONG_INPUT 100
#define UNINITIALIZED_VALUE -1
#define LOAD_DATA "Please load the data\n"
#define CHAR_LENGTH 20

int main() {
    printf(LOAD_DATA);
    int noOfFoodTypes, noOfDrinks;

    //region FOODS

    //region Define & alloc: userInput
    char *userInput = (char *) malloc(8 * CHAR_LENGTH * sizeof(char));
    //endregion

    gets(userInput);
    noOfFoodTypes = getNrOfTypes(userInput);

    //region Define & alloc: username, password, foodTypes, foodTypeChoice, foodSubtypeChoice, drinkChoice, cutleryChoice, choice, noFoodSubtypes, foodSubtypePrices, foodSubtypes
    char *username = (char *) malloc(CHAR_LENGTH * sizeof(char));
    char *password = (char *) malloc(CHAR_LENGTH * sizeof(char));;
    char **foodTypes = (char **) malloc(noOfFoodTypes * sizeof(char *));
    int foodTypeChoice = UNINITIALIZED_VALUE;
    int foodSubtypeChoice = UNINITIALIZED_VALUE;
    int drinkChoice = UNINITIALIZED_VALUE;
    int cutleryChoice = UNINITIALIZED_VALUE;
    int choice;
    int *noFoodSubtypes = (int *) malloc(noOfFoodTypes * sizeof(int));
    double **foodSubtypePrices = (double **) malloc(noOfFoodTypes * sizeof(double *));
    char ***foodSubtypes = (char ***) malloc(noOfFoodTypes * sizeof(char *));
    //endregion

    for (int currentType = 0; currentType < noOfFoodTypes; ++currentType) {
        gets(userInput);

        //region Define & alloc: foodTypes[currentType]
        foodTypes[currentType] = (char *) malloc(CHAR_LENGTH * sizeof(char));
        //endregion

        parseTypeName(userInput, foodTypes[currentType]);
        noFoodSubtypes[currentType] = parseNrOfTypes(userInput);

        //region Define & alloc: foodSubtypePrices[currentType], foodSubtypes[currentType], foodSubtypes[currentType][j]
        foodSubtypePrices[currentType] = (double *) malloc(noFoodSubtypes[currentType] * sizeof(double));
        foodSubtypes[currentType] = (char **) malloc(noFoodSubtypes[currentType] * sizeof(char *));
        for (int j = 0; j < noFoodSubtypes[currentType]; ++j) {
            foodSubtypes[currentType][j] = (char *) malloc(CHAR_LENGTH * sizeof(char));
        }
        //endregion

        for (int currentSubtype = 0; currentSubtype < noFoodSubtypes[currentType]; ++currentSubtype)
            parseObject(userInput, foodSubtypes[currentType][currentSubtype],
                        &foodSubtypePrices[currentType][currentSubtype], currentSubtype,
                        noFoodSubtypes[currentType] - 1);
    }
    //endregion

    //region DRINKS

    gets(userInput);
    noOfDrinks = getNrOfTypes(userInput);

    //region Define & alloc: drinkOptions, drinkOptionsPrices
    char **drinkOptions = (char **) malloc(noOfDrinks * sizeof(char *));
    double *drinkOptionPrices = (double *) malloc(noOfDrinks *
                                                  sizeof(double)); //drinkOptionPrices[0] = 5; drinkOptionPrices[1] = 5; drinkOptionPrices[2] = 5; drinkOptionPrices[3] = 4; //[NO_DRINKS] = {5, 5, 5, 4};
    //endregion

    gets(userInput);
    for (int currentType = 0; currentType < noOfDrinks; ++currentType) {
        //region Define & alloc: drinkOptions[currentType]
        drinkOptions[currentType] = (char *) malloc(CHAR_LENGTH * sizeof(char));
        //endregion

        parseObject(userInput, drinkOptions[currentType], &drinkOptionPrices[currentType], currentType, noOfDrinks - 1);
    }
    //endregion

    //region Define & alloc: cutleryOptions, cutleryOptions[1/0], additionalInfo, state, isOrderConfirmed
    char **cutleryOptions = (char **) malloc(2 * sizeof(char));
    cutleryOptions[0] = (char *) malloc(4 * sizeof(char));
    strcpy(cutleryOptions[0], "Yes");
    cutleryOptions[1] = (char *) malloc(3 * sizeof(char));
    strcpy(cutleryOptions[1], "No");
    char *additionalInfo = (char *) malloc(LONG_INPUT * sizeof(char));
    int state = 0, isOrderConfirmed = 0;
    //endregion

    //region Ordering Interaction
    while (isOrderConfirmed == 0) {
        switch (state) {
            case 0: //read user data
                signIn(username, password);
                state++;
                break;
            case 1: //food type selection
                printf("Please choose your meal:\n");
                printMenu(noOfFoodTypes, foodTypes);
                foodTypeChoice = makeChoice(&state, noOfFoodTypes, 1);
                break;
            case 2: //food subtype selection
                printf("Please choose your favourite %s:\n", foodTypes[foodTypeChoice]);
                printMenuWithPrices(0, noFoodSubtypes[foodTypeChoice], foodSubtypes[foodTypeChoice],
                                    foodSubtypePrices[foodTypeChoice]);
                foodSubtypeChoice = makeChoice(&state, noFoodSubtypes[foodTypeChoice], 1);
                break;
            case 3: //drink selection
                printf("Please choose a drink to go with your %s:\n", foodTypes[foodTypeChoice]);
                printMenuWithPrices(1, noOfDrinks, drinkOptions, drinkOptionPrices);
                drinkChoice = makeChoice(&state, noOfDrinks + 1, 1);
                break;
            case 4: //cutlery selection
                printf("Do you want cutlery?\n");
                printMenu(2, cutleryOptions);
                cutleryChoice = makeChoice(&state, 2, 1);
                break;
            case 5: //additional info
                getAdditionalInfo(&state, additionalInfo);
                break;
            case 6: //confirmation
                printForm(username, foodSubtypes[foodTypeChoice][foodSubtypeChoice],
                          foodSubtypePrices[foodTypeChoice][foodSubtypeChoice], drinkOptions[drinkChoice],
                          drinkOptionPrices[drinkChoice], drinkChoice, noOfDrinks, cutleryChoice, additionalInfo);
                printf("a) Confirm order\n" "b) Go back\n");
                choice = makeChoice(&state, 1, 2);
                if (choice == 0) {
                    printf("Order confirmed! Thank you for buying from us, %s!", username);
                    isOrderConfirmed = 1;
                }
                break;
            default:
                break;
        }
    }
    //endregion

    //region MEMORY CLEAN-UP
    free(additionalInfo);
    for (int i = 0; i < 2; ++i) free(cutleryOptions[i]);
    free(cutleryOptions);
    free(drinkOptionPrices);
    for (int i = 0; i < noOfDrinks; ++i) free(drinkOptions[i]);
    free(drinkOptions);
    for (int i = 0; i < noOfFoodTypes; ++i) {
        for (int j = 0; j < noFoodSubtypes[i]; ++j) free(foodSubtypes[i][j]);
        free(foodSubtypes[i]);
    }
    free(foodSubtypes);
    for (int i = 0; i < noOfFoodTypes; ++i) free(foodSubtypePrices);
    free(foodSubtypePrices);
    free(noFoodSubtypes);
    for (int i = 0; i < noOfFoodTypes; ++i) free(foodTypes[i]);
    free(foodTypes);
    free(password);
    free(username);
    free(userInput);
    //endregion
    return 0;
}
