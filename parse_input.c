//
// Created by diana on 02/12/2019.
//

#include "parse_input.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

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

/*int getNrOfTypes(char* input) {
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
}*/

/*int parseNrOfTypes(char* input) {
    int number;
    char* nrChar = (char*) malloc(5* sizeof(char));
    char* pt;
    strcpy(nrChar, strtok(input, ":"));
    strcpy(input, strtok(NULL, ""));
    number = strtol(nrChar, &pt, 10);
    free(nrChar);
    return number;
}*/

void parseTypeName(char* input, char* destinationType) {
    strcpy(destinationType, strtok(input, " :"));
    strcpy(input, strtok(NULL, ""));
}

void getCurrentObject(char* input, char* object, int currentValue, int invalidateValue) {
    strcpy(object, strtok(input, ")"));
    cleanExtraChars(object, "( ,");
    if (currentValue != invalidateValue) strcpy(input, strtok(NULL, ""));
}

void parseObject(char* input, char* item, double* price, int currentValue, int invalidateValue) {
    char* object = (char*)malloc(40* sizeof(char));

    getCurrentObject(input, object, currentValue, invalidateValue);

    //get item name from object
    strcpy(item, strtok(object, "()-,"));
    cleanExtraChars(item, " ,()");

    //get remainder object string
    strcpy(object, strtok(NULL, ""));
    cleanExtraChars(object, "()- ,");

    //get item price from object
    char *ptr;
    *(price) = strtod(object, &ptr);

    free(object);
}