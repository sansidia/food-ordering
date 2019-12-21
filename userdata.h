//
// Created by diana on 05/11/2019.
//

#ifndef FOOD_ORDERING_USERDATA_H
#define FOOD_ORDERING_USERDATA_H

#include "struct_type.h"

#define ERROR_PASSWORD_LONG "The password must be at least 7 chars long\n"
#define ERROR_PASSWORD_NOT_USERNAME "The password must not contain the username\n"
#define ERROR_PASSWORD_SPECIAL_CHAR "The password must contain one of the following characters: {'.', '_', '!'}\n"
#define ERROR_PASSWORD_DIGITS "The password must contain digits\n"
#define SIGN_IN_UP "Do you want to sign in or sign up?\n"
#define SIGN_IN "Sign in\n"
#define SIGN_UP "Sign up\n"
#define SIGNING_IN "Signing in!\n"
#define SIGNING_UP "Signing up!\n"
#define USER_NOT_FOUND "Username doesn't exist\n"
#define DUPLICATE_USER "Please choose another username!\n"
#define INCORRECT_PASSWORD "Incorrect password\n"

void signInOrUp(user mUser, user *registeredUsers, int *nrOfUsers);
void printForm(char* username, char* food, double foodPrice, char* drink, double drinkPrice, int drinkCode, int noDrink, int cutleryChoice, char* additionalInfo);

#endif //FOOD_ORDERING_USERDATA_H
