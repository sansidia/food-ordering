//
// Created by diana on 05/11/2019.
//

#include "userdata.h"
#include <stdio.h>

void signIn(char *username, char *password) {
    printf("Welcome to Food Thingies!\n");
    printf("Please sign in to continue!\n");
    printf("---Username:\n");
    gets(username);
    printf("---Password:\n");
    gets(password);
}

void printForm(char username[], char food[], int foodPrice, char drink[], int drinkPrice, int drinkCode, int noDrink, int cutleryChoice, char additionalInfo[]) {
    printf("-----------------\n"
           "This is your order:\n"
           "Name: %s\n"
           "Food items:\n"
           "--%s: %d\n", username, food, foodPrice);
    if (drinkCode != noDrink) {
        printf("--%s: %d\n", drink, drinkPrice);
    }
    printf("Cutlery: ");
    if (cutleryChoice == 1) printf("no\n");
    else printf("yes\n");
    printf("Additional information: %s\n", additionalInfo);
    if (drinkCode != noDrink)
        printf("Payment amount: %d\n", foodPrice + drinkPrice);
    else
        printf("Payment amount: %d\n", foodPrice);
    printf("-----------------\n");
}

