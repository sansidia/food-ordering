//
// Created by diana on 18/12/2019.
//

#include "load-data.h"
#include "string.h"
#include "parse-data.h"

void loadDataFromFile(FILE * inputFile, int *nrOfFoodsAddr, food **foodsAddr, int *nrOfDrinksAddr, drink **drinksAddr) {
    fscanf(inputFile, "%d", nrOfFoodsAddr);
    fgetc(inputFile);
    *foodsAddr = (food*) malloc((*nrOfFoodsAddr) * sizeof(food));
    for(int i = 1; i < *nrOfFoodsAddr; i++)
        foodsAddr[i] = foodsAddr[i - 1] + 1;
    char* inputLine;
    inputLine = (char*) malloc(INPUT_LINE_LENGTH* sizeof(char));
    for (int i = 0; i < *nrOfFoodsAddr; ++i) {
        inputLine = getInputFromFile(inputFile);
        parseFoodName(inputLine, foodsAddr[i]);
        inputLine = getInputFromFile(inputFile);
        parseSubtypes(inputLine, foodsAddr[i]);
    }
    fscanf(inputFile, "%d", nrOfDrinksAddr);
    fgetc(inputFile);
    *drinksAddr = (drink*) malloc((*nrOfDrinksAddr+1)* sizeof(drink));
    *drinksAddr[0] = createDrink();
    for(int i = 1; i < *nrOfDrinksAddr; i++) {
        drinksAddr[i] = drinksAddr[i - 1] + 1;
        *drinksAddr[i] = createDrink();
    }
    fgets(inputLine, INPUT_LINE_LENGTH, inputFile);
    parseDrinks(inputLine, *drinksAddr, *nrOfDrinksAddr);
    free(inputLine);
}

void loadDataFromConsole(int *nrOfFoodsAddr, food **foodsAddr, int *nrOfDrinksAddr, drink **drinksAddr) {
    printf("%s", INPUT_DATA_MSG);
    scanf("%d", nrOfFoodsAddr);
    getchar();
    *foodsAddr = (food*) malloc((*nrOfFoodsAddr+1)* sizeof(food));
    for(int i = 1; i < *nrOfFoodsAddr; i++)
        foodsAddr[i] = foodsAddr[i - 1] + 1;
    char *inputLine;
    inputLine = (char*) malloc(INPUT_LINE_LENGTH* sizeof(char));
    for (int i = 0; i < *nrOfFoodsAddr; ++i) {
        gets(inputLine);
        parseFoodName(inputLine, foodsAddr[i]);
        gets(inputLine);
        parseSubtypes(inputLine, foodsAddr[i]);
    }
    scanf("%d", nrOfDrinksAddr);
    getchar();
    *drinksAddr = (drink*) malloc((*nrOfDrinksAddr+1)* sizeof(drink));
    *drinksAddr[0] = createDrink();
    for(int i = 1; i < *nrOfDrinksAddr; i++) {
        drinksAddr[i] = drinksAddr[i - 1] + 1;
        *drinksAddr[i] = createDrink();
    }
    gets(inputLine);
    parseDrinks(inputLine, *drinksAddr, *nrOfDrinksAddr);
    free(inputLine);
}
