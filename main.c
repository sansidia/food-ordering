#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "userdata.h"
#include "options.h"
//#define NO_FOOD_TYPE 3
//#define NO_DRINKS 4
#define CHAR_LENGTH 20

void cleanUp(char* string) {
    int extraSpaces = 0;
    for (unsigned int i = 0; i < strlen(string); ++i) {
        if (strchr(" ()", string[i])) {
            extraSpaces++;
            if (isalpha(string[i+1]) || isdigit(string[i+1]))
                break;
        } else break;
    }
    strcpy(string, string+extraSpaces);
    extraSpaces = 0;
    for (unsigned int i = strlen(string)-1; i >= 0; --i) {
        if (strchr(" ()", string[i])) {
            extraSpaces++;
            if (isalpha(string[i-1]) || isdigit(string[i-1]))
                break;
        } else break;
    }
    string[strlen(string)-extraSpaces] = '\0';
}

int main() {
    int noOfFoodTypes = 0, noOfDrinks = 0;
    //char* voidPtr;
    ///FOODS
    char* userInput = (char*)malloc(5* CHAR_LENGTH* sizeof(char));
    gets(userInput);
    for (unsigned int i = 0; i < strlen(userInput); ++i) {
        if (!isdigit(userInput[i])) {
            userInput[i] = '\0';
            break;
        }
    }
    for (int i = strlen(userInput)-1; i >= 0 ; i--) {
        noOfFoodTypes = noOfFoodTypes*10 + (userInput[i]- '0');
    }
    char *username = (char*)malloc(CHAR_LENGTH* sizeof(char));
    char *password = (char*)malloc(CHAR_LENGTH* sizeof(char));;
    char **foodTypes = (char**)malloc(noOfFoodTypes* sizeof(char*));
    /*foodTypes[0] = (char*)malloc(CHAR_LENGTH* sizeof(char)); strcpy(foodTypes[0], "Pizza");
    foodTypes[1] = (char*)malloc(CHAR_LENGTH* sizeof(char)); strcpy(foodTypes[1], "Pasta");
    foodTypes[2] = (char*)malloc(CHAR_LENGTH* sizeof(char)); strcpy(foodTypes[2], "Salad");// {"Pizza", "Pasta", "Salad"};*/
    int foodTypeChoice = -1;
    int foodSubtypeChoice = -1;
    int drinkChoice = -2;
    int cutleryChoice = -1;
    int choice;
    int *noFoodSubtypes = (int*)malloc(noOfFoodTypes* sizeof(int));
    //noFoodSubtypes[0] = 3; noFoodSubtypes[1] = 2; noFoodSubtypes[2] = 4;//{3, 2, 4};
    int **foodSubtypePrices = (int**)malloc(noOfFoodTypes* sizeof(int*));
    /*foodSubtypePrices[0] = (int*)malloc(noFoodSubtypes[0]* sizeof(int)); foodSubtypePrices[0][0] = 21; foodSubtypePrices[0][1] = 23; foodSubtypePrices[0][2] = 19;
    foodSubtypePrices[1] = (int*)malloc(noFoodSubtypes[1]* sizeof(int)); foodSubtypePrices[1][0] = 23; foodSubtypePrices[1][1] = 21;
    foodSubtypePrices[2] = (int*)malloc(noFoodSubtypes[2]* sizeof(int)); foodSubtypePrices[2][0] = 23; foodSubtypePrices[2][1] = 22; foodSubtypePrices[2][2] = 19; foodSubtypePrices[2][3] = 21;
    *//*{
        {21, 23, 19},
        {23, 21},
        {23, 22, 19, 21} };*/
    char ***foodSubtypes = (char***)malloc(noOfFoodTypes* sizeof(char*));
    /*foodSubtypes[0] = (char**)malloc(noFoodSubtypes[0]* sizeof(char*));
        foodSubtypes[0][0] = (char*)malloc(CHAR_LENGTH* sizeof(char)); strcpy(foodSubtypes[0][0], "Pizza con Pollo");
        foodSubtypes[0][1] = (char*)malloc(CHAR_LENGTH* sizeof(char)); strcpy(foodSubtypes[0][1], "Pizza Diavola");
        foodSubtypes[0][2] = (char*)malloc(CHAR_LENGTH* sizeof(char)); strcpy(foodSubtypes[0][2], "Pizza Margherita");
    foodSubtypes[1] = (char**)malloc(noFoodSubtypes[1]* sizeof(char*));
        foodSubtypes[1][0] = (char*)malloc(CHAR_LENGTH* sizeof(char)); strcpy(foodSubtypes[1][0], "Chicken alfredo");
        foodSubtypes[1][1] = (char*)malloc(CHAR_LENGTH* sizeof(char)); strcpy(foodSubtypes[1][1], "Mac n cheese");
    foodSubtypes[2] = (char**)malloc(noFoodSubtypes[2]* sizeof(char*));
        foodSubtypes[2][0] = (char*)malloc(CHAR_LENGTH* sizeof(char)); strcpy(foodSubtypes[2][0], "Tuna salad");
        foodSubtypes[2][1] = (char*)malloc(CHAR_LENGTH* sizeof(char)); strcpy(foodSubtypes[2][1], "CHicken salad");
        foodSubtypes[2][2] = (char*)malloc(CHAR_LENGTH* sizeof(char)); strcpy(foodSubtypes[2][2], "Greek salad");
        foodSubtypes[2][3] = (char*)malloc(CHAR_LENGTH* sizeof(char)); strcpy(foodSubtypes[2][3], "Cobb salad");
    *///[NO_FOOD_TYPE][NO_FOOD_SUBTYPE][CHAR_LENGTH] = {
        //{"Pizza con Pollo", "Pizza Diavola", "Pizza Margherita"},
        //{"Chicken alfredo", "Mac&cheese"},
        //{"Tuna Salad", "Chicken Salad", "Greek Salad", "Cobb"} };
    for (int currentType = 0; currentType < noOfFoodTypes; ++currentType) {
        gets(userInput);
        noFoodSubtypes[currentType] = 0;
        ///COUNT FOOD SUBTYPES
        for (int j = 0; j < strlen(userInput); ++j) {
            if (userInput[j] == '(') noFoodSubtypes[currentType]++;
        }
        ///ASSIGN MEMORY
        foodTypes[currentType] = (char*)malloc(CHAR_LENGTH * sizeof(char));
        foodSubtypePrices[currentType] = (int*)malloc(noFoodSubtypes[currentType] * sizeof(int));
        foodSubtypes[currentType] = (char**) malloc(noFoodSubtypes[currentType] * sizeof(char*));
        for (int j = 0; j < noFoodSubtypes[currentType]; ++j) {
            foodSubtypes[currentType][j] = (char*) malloc(CHAR_LENGTH * sizeof(char));
        }
        ///PARSE INPUT
        for (int inputChar = 0; inputChar < strlen(userInput); ++inputChar) {
            int currentChar = 0;
            while (userInput[inputChar] != ':') {
                foodTypes[currentType][currentChar] = userInput[inputChar];
                inputChar++;
            } //found ':' -> end foodType string

        }
    }
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
    drinkOptions[0] = (char*)malloc(CHAR_LENGTH* sizeof(char)); strcpy(drinkOptions[0], "Coca-cola");
    drinkOptions[1] = (char*)malloc(CHAR_LENGTH* sizeof(char)); strcpy(drinkOptions[1], "fanta");
    drinkOptions[2] = (char*)malloc(CHAR_LENGTH* sizeof(char)); strcpy(drinkOptions[2], "lipton");
    drinkOptions[3] = (char*)malloc(CHAR_LENGTH* sizeof(char)); strcpy(drinkOptions[3], "Water");//[NO_DRINKS][CHAR_LENGTH] = {"Coca-Cola", "Fanta", "Lipton", "Water"};
    int* drinkOptionPrices = (int*)malloc(noOfDrinks* sizeof(int)); drinkOptionPrices[0] = 5; drinkOptionPrices[1] = 5; drinkOptionPrices[2] = 5; drinkOptionPrices[3] = 4; //[NO_DRINKS] = {5, 5, 5, 4};
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
