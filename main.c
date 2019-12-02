#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "userdata.h"
#include "options.h"
//#define NO_FOOD_TYPE 3
#define LOAD_DATA "Please load the data\n"
#define CHAR_LENGTH 20

void cleanExtraChars(char *string, char *chars) {
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
}

int getNrOfTypes(char* input) {
    int number = 0;
    for (unsigned int i = 0; i < strlen(input); ++i) {
        if (!isdigit(input[i])) {
            input[i] = '\0';
            break;
        }
    }
    for (int i = strlen(input)-1; i >= 0 ; i--) {
        number = number*10 + (input[i]- '0');
    }
    return number;
}

int main() {
    printf(LOAD_DATA);
    int noOfFoodTypes = 0, noOfDrinks = 0;
    ///FOODS
    char* userInput = (char*)malloc(8* CHAR_LENGTH* sizeof(char));
    gets(userInput);
    /*for (unsigned int i = 0; i < strlen(userInput); ++i) {
        if (!isdigit(userInput[i])) {
            userInput[i] = '\0';
            break;
        }
    }
    for (int i = strlen(userInput)-1; i >= 0 ; i--) {
        noOfFoodTypes = noOfFoodTypes*10 + (userInput[i]- '0');
    }*/
    noOfFoodTypes = getNrOfTypes(userInput);
    char *username = (char*)malloc(CHAR_LENGTH* sizeof(char));
    char *password = (char*)malloc(CHAR_LENGTH* sizeof(char));;
    char **foodTypes = (char**)malloc(noOfFoodTypes* sizeof(char*));
    int foodTypeChoice = -1;
    int foodSubtypeChoice = -1;
    int drinkChoice = -2;
    int cutleryChoice = -1;
    int choice;
    int *noFoodSubtypes = (int*)malloc(noOfFoodTypes* sizeof(int));
    double **foodSubtypePrices = (double**)malloc(noOfFoodTypes* sizeof(double*));
    char ***foodSubtypes = (char***)malloc(noOfFoodTypes* sizeof(char*));
    for (int currentType = 0; currentType < noOfFoodTypes; ++currentType) {
        gets(userInput);
        noFoodSubtypes[currentType] = 0;
        char* auxString = (char*) malloc(strlen(userInput)* sizeof(char));
        /*///COUNT FOOD SUBTYPES
        for (int j = 0; j < strlen(userInput); ++j) {
            if (userInput[j] == '(') noFoodSubtypes[currentType]++;
        }*/
        ///ASSIGN MEMORY
        foodTypes[currentType] = (char*)malloc(CHAR_LENGTH * sizeof(char));

        strcpy(foodTypes[currentType], strtok(userInput, " "));
        strcpy(auxString, strtok(NULL, ""));
        char* nrChar = (char*)malloc(5* sizeof(char));
        char* pt;
        strcpy(nrChar, strtok(auxString, ":"));
        strcpy(auxString, strtok(NULL, ""));
        noFoodSubtypes[currentType] = strtol(nrChar, &pt, 10);

        foodSubtypePrices[currentType] = (double*)malloc(noFoodSubtypes[currentType] * sizeof(double));
        foodSubtypes[currentType] = (char**) malloc(noFoodSubtypes[currentType] * sizeof(char*));
        for (int j = 0; j < noFoodSubtypes[currentType]; ++j) {
            foodSubtypes[currentType][j] = (char*) malloc(CHAR_LENGTH * sizeof(char));
        }
        ///PARSE INPUT
        for (int currentSubtype = 0; currentSubtype < noFoodSubtypes[currentType]; ++currentSubtype) {
            char* object = (char*) malloc(2* CHAR_LENGTH* sizeof(char));
            strcpy(object, strtok(auxString, ")"));
            cleanExtraChars(object, " ");
            if(currentSubtype != noFoodSubtypes[currentType] - 1) strcpy(auxString, strtok(NULL, ""));
            strcpy(foodSubtypes[currentType][currentSubtype], strtok(object, "()-"));
            cleanExtraChars(foodSubtypes[currentType][currentSubtype], " ");
            strcpy(object, strtok(NULL, ""));
            cleanExtraChars(object, "()- ");
            char* ptr;
            foodSubtypePrices[currentType][currentSubtype] = strtod(object, &ptr);

            free(object);
        }

        free(auxString);
    }
    ///DRINKS    
    gets(userInput);
    noOfDrinks = getNrOfTypes(userInput);
    char **drinkOptions = (char**)malloc(noOfDrinks* sizeof(char*));
    /*drinkOptions[0] = (char*)malloc(CHAR_LENGTH* sizeof(char)); strcpy(drinkOptions[0], "Coca-cola");
    drinkOptions[1] = (char*)malloc(CHAR_LENGTH* sizeof(char)); strcpy(drinkOptions[1], "fanta");
    drinkOptions[2] = (char*)malloc(CHAR_LENGTH* sizeof(char)); strcpy(drinkOptions[2], "lipton");
    drinkOptions[3] = (char*)malloc(CHAR_LENGTH* sizeof(char)); strcpy(drinkOptions[3], "Water");//[NO_DRINKS][CHAR_LENGTH] = {"Coca-Cola", "Fanta", "Lipton", "Water"};*/
    double* drinkOptionPrices = (double*)malloc(noOfDrinks* sizeof(double)); //drinkOptionPrices[0] = 5; drinkOptionPrices[1] = 5; drinkOptionPrices[2] = 5; drinkOptionPrices[3] = 4; //[NO_DRINKS] = {5, 5, 5, 4};
    gets(userInput);
    for(int currentType=0;currentType<noOfDrinks;++currentType) {
        drinkOptions[currentType] = (char*) malloc(CHAR_LENGTH* sizeof(char));

        ///PARSE
        char* object = (char*)malloc(2*CHAR_LENGTH*sizeof(char));

        strcpy(object, strtok(userInput, ")"));
        if (currentType!= noOfDrinks-1) strcpy(userInput, strtok(NULL, ""));
        cleanExtraChars(object, ", ");
        strcpy(drinkOptions[currentType], strtok(object, "()-"));
        strcpy(object, strtok(NULL, ""));
        cleanExtraChars(drinkOptions[currentType], "()- ");
        cleanExtraChars(object, "()- ");
        char *ptr;
        drinkOptionPrices[currentType] = strtod(object, &ptr);

        free(object);
    }

    char **cutleryOptions = (char**)malloc(2* sizeof(char));
    cutleryOptions[0] = (char*)malloc(4* sizeof(char)); strcpy(cutleryOptions[0], "Yes");
    cutleryOptions[1] = (char*)malloc(3* sizeof(char)); strcpy(cutleryOptions[1], "No");//[2][5] = {"Yes", "No"};
    char *additionalInfo = (char *)malloc(100* sizeof(char));//[100];
    int state = 0, isOrderConfirmed = 0;
    while(isOrderConfirmed == 0) {
        switch (state) {
            case 0: //read user data
                signIn(username, password);
                state++; break;
            case 1: //food type selection
                printf("Please choose your meal:\n");
                printMenu(noOfFoodTypes, foodTypes);
                foodTypeChoice = makeChoice(&state, noOfFoodTypes, 1); break;
            case 2: //food subtype selection
                printf("Please choose your favourite %s:\n", foodTypes[foodTypeChoice]);
                printMenuWithPrices(0, noFoodSubtypes[foodTypeChoice], foodSubtypes[foodTypeChoice],
                                    foodSubtypePrices[foodTypeChoice]);
                foodSubtypeChoice = makeChoice(&state, noFoodSubtypes[foodTypeChoice], 1); break;
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
    return 0;
}
