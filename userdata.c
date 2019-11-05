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

