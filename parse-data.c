//
// Created by diana on 18/12/2019.
//

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "parse-data.h"
#include "food-subtype.h"
#include "food.h"
#include "drink.h"
#include "food-ordering-macros.h"

void cleanExtraChars(char *string, char *chars);

char *getCurrentObject(char **string);

void parseFoodObject(char *object, foodSubtype* subtype);
void parseDrinkObject (char *object, drink *d);

void parseFoodName(char *string, food *f) {
    char* name = (char*) malloc(WORD_LENGTH* sizeof(char));
    int nr;
    strcpy(name, strtok(string, ":"));
    string = strtok(NULL, "");
    nr = atoi(string);
    *f = createFood(nr);
    strcpy(f->name, name);
    //printf("Created food %s with %d subtypes\n", f->name, f->nrOfSubtypes);
}


char *getInputFromFile(FILE *file) {
    char *line = (char*) malloc(INPUT_LINE_LENGTH* sizeof(char));
    fgets(line, INPUT_LINE_LENGTH, file);
    line[strlen(line)-1] = '\0';
    return line;
}



void parseSubtypes(char *string, food *foodItem) {
    char* object;
    object = (char*) malloc(OBJECT_LENGTH* sizeof(char));
    for (int i = 0; i < foodItem->nrOfSubtypes; ++i) {
        object = getCurrentObject(&string);
        parseFoodObject(object, &(foodItem->subtypes[i]));
        //printf("Created subtype %s, price %.2f\n", foodItem->subtypes[i].name, foodItem->subtypes[i].price);
    }

    free(object);
}

void parseDrinks(char *string, drink *d, int nrOfDrinks) {
    char* object;
    object = (char*) malloc(OBJECT_LENGTH* sizeof(char));
    for (int i = 0; i < nrOfDrinks; ++i) {
        object = getCurrentObject(&string);
        parseDrinkObject(object, &d[i]);
        //printf("Got drink %s price %.2f\n", d->name, d->price);
    }
    free(object);
}

void parseFoodObject(char *object, foodSubtype* subtype) {
    strcpy(subtype->name, strtok(object, "-"));
    object = strtok(NULL, "");
    if (object!= NULL) {
        char *p;
        subtype->price = strtod(object, &p);
    }
}

void parseDrinkObject(char* object, drink *d) {
    strcpy(d->name, strtok(object, "-"));
    object = strtok(NULL, "");
    if (object != NULL) {
        char *p;
        d->price = strtod(object, &p);
    }
}

char *getCurrentObject(char **string) {
    char * object = (char*) malloc(OBJECT_LENGTH* sizeof(char));
    strcpy(object, strtok(*string, ")"));
    *string=strtok(NULL, "");
    cleanExtraChars(object, "() ,");
    return object;
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

