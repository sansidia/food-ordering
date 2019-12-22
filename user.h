//
// Created by diana on 18/12/2019.
//

#ifndef FOOD_ORDERING_V2_USER_H
#define FOOD_ORDERING_V2_USER_H

typedef struct _user {
    char* username;
    char* password;
} user;

user createUser();

void defineDefaultUser(user*);


#endif //FOOD_ORDERING_V2_USER_H
