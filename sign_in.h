//
// Created by diana on 20/12/2019.
//

#ifndef FOOD_ORDERING_V2_SIGN_IN_H
#define FOOD_ORDERING_V2_SIGN_IN_H

#include "user.h"
#include <stdio.h>
#include "food-ordering-macros.h"
#include "string.h"

#define WELCOME_MSG "Welcome to food thingies!\n"
#define ERROR_PASSWORD_LONG "The password must be at least 7 chars long\n"
#define ERROR_PASSWORD_NOT_USERNAME "The password must not contain the username\n"
#define ERROR_PASSWORD_SPECIAL_CHAR "The password must contain one of the following characters: {'.', '_', '!'}\n"
#define ERROR_PASSWORD_DIGITS "The password must contain digits\n"
#define SIGN_IN_UP "Do you want to sign in or sign up?\n"
#define SIGN_IN_MSG "Sign in\n"
#define SIGN_UP_MSG "Sign up\n"
#define SIGNING_IN "Signing in!\n"
#define SIGNING_UP "Signing up!\n"
#define USER_NOT_FOUND "Username doesn't exist\n"
#define DUPLICATE_USER "Please choose another username!\n"
#define INCORRECT_PASSWORD "Incorrect password\n"

void signInOrUp(user *currentUser, userArray *registeredUsers);

#endif //FOOD_ORDERING_V2_SIGN_IN_H
