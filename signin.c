//
// Created by diana on 27/11/2019.
//

#include "signin.h"
#include "macros.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int checkExistingUserInfo (FILE *inputFile, char* username, char* password) {
    int userExists = 0, passwordCorrect = 0;
    char* readline = (char*) malloc(2* MAX_ITEM_LENGTH* sizeof(char));
    fgets(readline, 2*MAX_ITEM_LENGTH , inputFile);
    while (readline!= NULL) {
        char* existingUsername = (char*) malloc(MAX_ITEM_LENGTH* sizeof(char));
        char* existingPassword = (char*) malloc(MAX_ITEM_LENGTH* sizeof(char));
        existingUsername = strtok(readline, " ");
        existingPassword = strtok(NULL, " ");
        fgets(readline, 2*MAX_ITEM_LENGTH, inputFile);
    }
}

void writeSignUpInfo (FILE *outputFile, char* username, char* password) {
    fputs(username, outputFile);
    fputc(' ', outputFile);
    fputs(password, outputFile);
    fputc('\n', outputFile);
}

int validatePassword (char* password, char* username) {
    //validate length
    int isPasswordValid = 1;
    if (strlen(password) < 7) {
        printf(ERROR_PASSWORD_LONG);
        isPasswordValid = 0;
        return isPasswordValid;
    } else if (strstr(strlwr(password), strlwr(username)) != NULL) { //validate if it contains username
        printf(ERROR_PASSWORD_NOT_USERNAME);
        isPasswordValid = 0;
        return isPasswordValid;
    } else if (strpbrk(password, "._!") == NULL) { //validate if it contains special chars
        printf(ERROR_PASSWORD_SPECIAL_CHAR);
        isPasswordValid = 0;
        return isPasswordValid;
    } else if (strpbrk(password, "0123456789") == NULL) { //validate if it contains a digit
        printf(ERROR_PASSWORD_DIGITS);
        isPasswordValid = 0;
        return isPasswordValid;
    } else return isPasswordValid;
}
