//
// Created by diana on 05/11/2019.
//

#include "userdata.h"
#include <stdio.h>

void printFormHeader(char*);
int paymentSum(int foodPrice, int drinkPrice, int drinkCode, int noDrink);

void signIn(char *username, char *password) {
    printf("Welcome to Food Thingies!\n");
    printf("Please sign in to continue!\n");
    printf("---Username:\n");
    gets(username);
    printf("---Password:\n");
    gets(password);
}

void printForm(char* username, char* food, int foodPrice, char* drink, int drinkPrice, int drinkCode, int noDrink, int cutleryChoice, char *additionalInfo) {
    printFormHeader(username);
    printf("--%s: %d\n", food, foodPrice);
    if (drinkCode != noDrink) {
        printf("--%s: %d\n", drink, drinkPrice);
    }
    printf("Cutlery: %s\n", (cutleryChoice == 1? "no":"yes"));
    printf("Additional information: %s\n", additionalInfo);
    printf("Payment amount: %d\n", paymentSum(foodPrice, drinkPrice, drinkCode, noDrink));
    printf("-----------------\n");
}

void printFormHeader(char* name) {
    printf("-----------------\n"
           "This is your order:\n"
           "Name: %s\n"
           "Food items:\n", name);
}

int paymentSum(int foodPrice, int drinkPrice, int drinkCode, int noDrink) {
    int sum=0;
    if(drinkCode != noDrink)
        sum=foodPrice+drinkPrice;
    else sum=foodPrice;
    return sum;
}

