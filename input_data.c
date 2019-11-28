//
// Created by diana on 28/11/2019.
//


#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "input_data.h"
#include "macros.h"

int readNrOfTypes() {
    int nrOfTypes = 0;
    char* userInput =  (char*)malloc(ITEM_LENGTH* sizeof(char));
    gets(userInput);
    for (unsigned int i = 0; i < strlen(userInput); ++i) {
        if (!isdigit(userInput[i])) {
            userInput[i] = '\0';
            break;
        }
    }
    for (int i = strlen(userInput)-1; i >= 0 ; i--) {
        nrOfTypes = nrOfTypes*10 + (userInput[i]- '0');
    }
    return nrOfTypes;
}

int countSubtypes(char* string) {
    int number = 0;
    for (int j = 0; j < strlen(string); ++j) {
        if (string[j] == '(') number++;
    }
    return number;
}

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

void readData(int dataType, int nrOfGeneralTypes, char ***generalType, int **nrOfSubtypes, char ****subTypes,
         double ***subTypePrices) {
    for (int currentType = 0; currentType < nrOfGeneralTypes; ++currentType) {
        char* input = (char*) malloc(LONG_INPUT_LENGTH* sizeof(char));
        gets(input);
        *nrOfSubtypes[currentType] = countSubtypes(input);

        ///MEMORY ALLOCATION
        *generalType[currentType] = (char*)malloc(ITEM_LENGTH* sizeof(char));
        *subTypePrices[currentType] = (double*)malloc(*nrOfSubtypes[currentType]* sizeof(double));
        *subTypes[currentType] = (char**)malloc(*(nrOfSubtypes[currentType]+1)* sizeof(char*));
        printf()
        for (int j = 0; j < *nrOfSubtypes[currentType]; ++j) {
            *subTypes[currentType][j] = (char*) malloc(ITEM_LENGTH * sizeof(char));
        }

        ///PARSE INPUT
        char * auxString = (char*) malloc(strlen(input)* sizeof(char));
        if (dataType == DATA_TYPE_FOOD) {
            strcpy(*generalType[currentType], strtok(input, ": "));
            strcpy(auxString, (strtok(NULL, "")));
        } else {
            strcpy(auxString, input);
        }

        for (int currentSubtype = 0; currentSubtype < *nrOfSubtypes[currentType]; ++currentSubtype) {
            char* object = (char*) malloc(2 * ITEM_LENGTH * sizeof(char));
            strcpy(object, strtok(auxString, ")"));
            cleanExtraChars(object, " ");
            if(currentSubtype != *nrOfSubtypes[currentType] - 1) strcpy(auxString, strtok(NULL, ""));
            strcpy(*subTypes[currentType][currentSubtype], strtok(object, "()-"));
            cleanExtraChars(*subTypes[currentType][currentSubtype], " ");
            strcpy(object, strtok(NULL, ""));
            cleanExtraChars(object, "()- ");
            char* ptr;
            *subTypePrices[currentType][currentSubtype] = strtod(object, &ptr);

            free(object);
        }

        free(auxString);
    }
}
