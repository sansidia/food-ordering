//
// Created by diana on 05/11/2019.
//

#include "userdata.h"
#include <stdio.h>
#include "options.h"
#include "struct_type.h"
#include <string.h>

void printFormHeader(char*);
double paymentSum(double foodPrice, double drinkPrice, int drinkCode, int noDrink);
int doesPasswordExist(char*username, struct user *registeredUsers, int nrOfUsers);
int doesUsernameExist(char *username, struct user *registeredUsers, int nrOfUsers);

int signIn(struct user mUser, struct user *registeredUsers, int nrOfUsers) {
    int signInComplete = 0;
    getchar();
    while (signInComplete == 0) {
        printf(SIGNING_IN);
        printf("---Username:\n");
        gets(mUser.username);
        printf("---Password:\n");
        gets(mUser.password);
        if (doesUsernameExist(mUser.username, registeredUsers, nrOfUsers) == 0) {
            printf(USER_NOT_FOUND);
            return 0;
        } else if (doesPasswordExist(mUser.password, registeredUsers, nrOfUsers) == 0) {
            printf(INCORRECT_PASSWORD);
        } else {
            return 1;
        }
    }
}


int doesUsernameExist(char *username, struct user *registeredUsers, int nrOfUsers) {
    for (int i = 0; i < nrOfUsers; ++i) {
        if (strcmp(username, registeredUsers[i].username) == 0)
            return 1;
    }
    return 0;
}

int doesPasswordExist(char *username, struct user *registeredUsers, int nrOfUsers) {
    for (int i = 0; i < nrOfUsers; ++i) {
        if (strcmp(username, registeredUsers[i].username) == 0)
            return 1;
    }
    return 0;
}

int signUp(struct user mUser, struct user *registeredUsers, int nrOfUsers) {

}

void signInOrUp(struct user mUser, struct user *registeredUsers, int nrOfUsers) {
    printf("Welcome to Food Thingies!\n");
    int signComplete = 0;
    while (signComplete == 0) {
        printf(SIGN_IN_UP);
        printf("a) Sign in\n");
        printf("b) Sign up\n");
        char i;
        i = getchar();
        int choice = i - 'a';
        switch (choice) {
            case 0: {
                signComplete = signIn(mUser, registeredUsers, nrOfUsers);
                break;
            }
            case 1: {
                signComplete = signUp(mUser, registeredUsers, nrOfUsers);
                break;
            }
            default: {
                printf(INVALID_INPUT);
                break;
            }
        }
    }
}

void printForm(char* username, char* food, double foodPrice, char* drink, double drinkPrice, int drinkCode, int noDrink, int cutleryChoice, char *additionalInfo) {
    printFormHeader(username);
    printf("--%s: %.2f\n", food, foodPrice);
    if (drinkCode != noDrink) {
        printf("--%s: %.2f\n", drink, drinkPrice);
    }
    printf("Cutlery: %s\n", (cutleryChoice == 1? "no":"yes"));
    printf("Additional information: %s\n", additionalInfo);
    printf("Payment amount: %.2f\n", paymentSum(foodPrice, drinkPrice, drinkCode, noDrink));
    printf("-----------------\n");
}

void printFormHeader(char* name) {
    printf("-----------------\n"
           "This is your order:\n"
           "Name: %s\n"
           "Food items:\n", name);
}

double paymentSum(double foodPrice, double drinkPrice, int drinkCode, int noDrink) {
    double sum=0;
    if(drinkCode != noDrink)
        sum=foodPrice+drinkPrice;
    else sum=foodPrice;
    return sum;
}



