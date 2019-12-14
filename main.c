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
#define FILE_PATH "data.txt"

int main() {
    //region variable definition
    char *userInput;
    char *username;
    char *password;
    char **foodTypes;
    int foodTypeChoice;
    int foodSubtypeChoice;
    int drinkChoice;
    int cutleryChoice;
    int choice;
    int *noFoodSubtypes;
    double **foodSubtypePrices;
    char ***foodSubtypes;
    char **drinkOptions;
    double *drinkOptionPrices;
    char **cutleryOptions;
    char *additionalInfo;
    int state = 0, isOrderConfirmed = 0;
    int noOfFoodTypes, noOfDrinks;
    //endregion

    FILE *foodDataFile = fopen(FILE_PATH, "r");
    if (foodDataFile == NULL) {
        perror("File could not be opened");

        //region LOADING DATA
        printf(LOAD_DATA);

        //region FOODS

        //region Define & alloc: userInput
        userInput = (char *) malloc(8 * CHAR_LENGTH * sizeof(char));
        //endregion

        scanf("%d", &noOfFoodTypes);
        getchar();

        //region Define & alloc: username, password, foodTypes, foodTypeChoice, foodSubtypeChoice, drinkChoice, cutleryChoice, choice, noFoodSubtypes, foodSubtypePrices, foodSubtypes

        username = (char *) malloc(CHAR_LENGTH * sizeof(char));
        password = (char *) malloc(CHAR_LENGTH * sizeof(char));;
        foodTypes = (char **) malloc(noOfFoodTypes * sizeof(char *));
        foodTypeChoice = UNINITIALIZED_VALUE;
        foodSubtypeChoice = UNINITIALIZED_VALUE;
        drinkChoice = UNINITIALIZED_VALUE;
        cutleryChoice = UNINITIALIZED_VALUE;
        noFoodSubtypes = (int *) malloc(noOfFoodTypes * sizeof(int));
        foodSubtypePrices = (double **) malloc(noOfFoodTypes * sizeof(double *));
        foodSubtypes = (char ***) malloc(noOfFoodTypes * sizeof(char *));
        //endregion

        for (int currentType = 0; currentType < noOfFoodTypes; ++currentType) {
            gets(userInput);

            //region Define & alloc: foodTypes[currentType]
            foodTypes[currentType] = (char *) malloc(CHAR_LENGTH * sizeof(char));
            //endregion

            parseTypeName(userInput, foodTypes[currentType]);
            noFoodSubtypes[currentType] = atoi(userInput);

            gets(userInput);

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

        scanf("%d", &noOfDrinks);
        getchar();

        //region Define & alloc: drinkOptions, drinkOptionsPrices
        drinkOptions = (char **) malloc(noOfDrinks * sizeof(char *));
        drinkOptionPrices = (double *) malloc(noOfDrinks *
                                              sizeof(double)); //drinkOptionPrices[0] = 5; drinkOptionPrices[1] = 5; drinkOptionPrices[2] = 5; drinkOptionPrices[3] = 4; //[NO_DRINKS] = {5, 5, 5, 4};
        //endregion

        gets(userInput);
        for (int currentType = 0; currentType < noOfDrinks; ++currentType) {
            //region Define & alloc: drinkOptions[currentType]
            drinkOptions[currentType] = (char *) malloc(CHAR_LENGTH * sizeof(char));
            //endregion

            parseObject(userInput, drinkOptions[currentType], &drinkOptionPrices[currentType], currentType,
                        noOfDrinks - 1);
        }
        //endregion

        //region Define & alloc: cutleryOptions, cutleryOptions[1/0], additionalInfo, state, isOrderConfirmed
        cutleryOptions = (char **) malloc(2 * sizeof(char));
        cutleryOptions[0] = (char *) malloc(4 * sizeof(char));
        strcpy(cutleryOptions[0], "Yes");
        cutleryOptions[1] = (char *) malloc(3 * sizeof(char));
        strcpy(cutleryOptions[1], "No");
        additionalInfo = (char *) malloc(LONG_INPUT * sizeof(char));
        //endregion

        //endregion

        //region WRITING DATA TO FILE

        FILE *outputFile = fopen(FILE_PATH, "w");

        fprintf(outputFile, "%d\n", noOfFoodTypes);
        for (int currentFoodType = 0; currentFoodType < noOfFoodTypes; ++currentFoodType) {
            fprintf(outputFile, "%s:%d\n", foodTypes[currentFoodType], noFoodSubtypes[currentFoodType]);
            for (int currentSubType = 0; currentSubType < noFoodSubtypes[currentFoodType]; ++currentSubType) {
                fprintf(outputFile, "(%s-%.2f) ", foodSubtypes[currentFoodType][currentSubType],
                        foodSubtypePrices[currentFoodType][currentSubType]);
            }
            fprintf(outputFile, "\n");
        }
        fprintf(outputFile, "%d\n", noOfDrinks);
        for (int currentDrink = 0; currentDrink < noOfDrinks; ++currentDrink) {
            fprintf(outputFile, "(%s-%.2f) ", drinkOptions[currentDrink], drinkOptionPrices[currentDrink]);
        }

        fclose(outputFile);
        //endregion
    } else {
        //region LOADING DATA
        //printf(LOAD_DATA);

        //region FOODS

        //region Define & alloc: userInput
        userInput = (char *) malloc(8 * CHAR_LENGTH * sizeof(char));
        //endregion

        fscanf(foodDataFile, "%d", &noOfFoodTypes);
        fgetc(foodDataFile);
        //region Define & alloc: username, password, foodTypes, foodTypeChoice, foodSubtypeChoice, drinkChoice, cutleryChoice, choice, noFoodSubtypes, foodSubtypePrices, foodSubtypes
        username = (char *) malloc(CHAR_LENGTH * sizeof(char));
        password = (char *) malloc(CHAR_LENGTH * sizeof(char));;
        foodTypes = (char **) malloc(noOfFoodTypes * sizeof(char *));
        foodTypeChoice = UNINITIALIZED_VALUE;
        foodSubtypeChoice = UNINITIALIZED_VALUE;
        drinkChoice = UNINITIALIZED_VALUE;
        cutleryChoice = UNINITIALIZED_VALUE;
        noFoodSubtypes = (int *) malloc(noOfFoodTypes * sizeof(int));
        foodSubtypePrices = (double **) malloc(noOfFoodTypes * sizeof(double *));
        foodSubtypes = (char ***) malloc(noOfFoodTypes * sizeof(char *));
        //endregion

        for (int currentType = 0; currentType < noOfFoodTypes; ++currentType) {
            fgets(userInput, LONG_INPUT, foodDataFile);
            userInput[strlen(userInput)-1] = '\0';

            //region Define & alloc: foodTypes[currentType]
            foodTypes[currentType] = (char *) malloc(CHAR_LENGTH * sizeof(char));
            //endregion

            parseTypeName(userInput, foodTypes[currentType]);
            noFoodSubtypes[currentType] = atoi(userInput);

            //region Define & alloc: foodSubtypePrices[currentType], foodSubtypes[currentType], foodSubtypes[currentType][j]
            foodSubtypePrices[currentType] = (double *) malloc(noFoodSubtypes[currentType] * sizeof(double));
            foodSubtypes[currentType] = (char **) malloc(noFoodSubtypes[currentType] * sizeof(char *));
            for (int j = 0; j < noFoodSubtypes[currentType]; ++j) {
                foodSubtypes[currentType][j] = (char *) malloc(CHAR_LENGTH * sizeof(char));
            }
            //endregion

            fgets(userInput, LONG_INPUT, foodDataFile);
            userInput[strlen(userInput)-1] = '\0';

            for (int currentSubtype = 0; currentSubtype < noFoodSubtypes[currentType]; ++currentSubtype)
                parseObject(userInput, foodSubtypes[currentType][currentSubtype],
                            &foodSubtypePrices[currentType][currentSubtype], currentSubtype,
                            noFoodSubtypes[currentType] - 1);
        }
        //endregion

        //region DRINKS

        fgets(userInput, LONG_INPUT, foodDataFile);
        userInput[strlen(userInput)-1] = '\0';

        noOfDrinks = atoi(userInput);

        //region Define & alloc: drinkOptions, drinkOptionsPrices
        drinkOptions = (char **) malloc(noOfDrinks * sizeof(char *));
        drinkOptionPrices = (double *) malloc(noOfDrinks *
                                              sizeof(double)); //drinkOptionPrices[0] = 5; drinkOptionPrices[1] = 5; drinkOptionPrices[2] = 5; drinkOptionPrices[3] = 4; //[NO_DRINKS] = {5, 5, 5, 4};
        //endregion

        fgets(userInput, LONG_INPUT, foodDataFile);
        userInput[strlen(userInput)-1] = '\0';
        for (int currentType = 0; currentType < noOfDrinks; ++currentType) {
            //region Define & alloc: drinkOptions[currentType]
            drinkOptions[currentType] = (char *) malloc(CHAR_LENGTH * sizeof(char));
            //endregion

            parseObject(userInput, drinkOptions[currentType], &drinkOptionPrices[currentType], currentType,
                        noOfDrinks - 1);
        }
        //endregion

        //region Define & alloc: cutleryOptions, cutleryOptions[1/0], additionalInfo, state, isOrderConfirmed
        cutleryOptions = (char **) malloc(2 * sizeof(char));
        cutleryOptions[0] = (char *) malloc(4 * sizeof(char));
        strcpy(cutleryOptions[0], "Yes");
        cutleryOptions[1] = (char *) malloc(3 * sizeof(char));
        strcpy(cutleryOptions[1], "No");
        additionalInfo = (char *) malloc(LONG_INPUT * sizeof(char));
        //endregion

        //endregion
    }
    //region ORDERING INTERACTION
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