//
// Created by diana on 05/11/2019.
//

#include "userdata.h"
#include <stdio.h>

void printFormHeader(char*);

double paymentSum(double foodPrice, double drinkPrice, int drinkCode, int noDrink);

void signIn(char *username, char *password) {
    printf("Welcome to Food Thingies!\n");
    printf("Please sign in to continue!\n");
    printf("---Username:\n");
    gets(username);
    printf("---Password:\n");
    gets(password);
}

void printForm(char* username, char* food, double foodPrice, char* drink, double drinkPrice, int drinkCode, int noDrink, int cutleryChoice, char *additionalInfo) {
    printFormHeader(username);
    printf("--%s: %f\n", food, foodPrice);
    if (drinkCode != noDrink) {
        printf("--%s: %f\n", drink, drinkPrice);
    }
    printf("Cutlery: %s\n", (cutleryChoice == 1? "no":"yes"));
    printf("Additional information: %s\n", additionalInfo);
    printf("Payment amount: %f\n", paymentSum(foodPrice, drinkPrice, drinkCode, noDrink));
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

