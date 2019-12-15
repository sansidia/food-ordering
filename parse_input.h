//
// Created by diana on 02/12/2019.
//

#ifndef FOOD_ORDERING_PARSE_INPUT_H
#define FOOD_ORDERING_PARSE_INPUT_H

void cleanExtraChars(char *string, char *chars);
int getNrOfTypes(char* input);
int parseNrOfTypes(char* input);
void parseTypeName(char* input, char* destinationType);
void parseObject(char* input, char* item, double* price, int currentValue, int invalidateValue);

#endif //FOOD_ORDERING_PARSE_INPUT_H
