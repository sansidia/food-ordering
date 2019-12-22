//
// Created by diana on 18/12/2019.
//

#include "user.h"
#include "food-ordering-macros.h"
#include <stdlib.h>
#include <string.h>

user createUser() {
    user u;
    u.password = (char*) malloc(WORD_LENGTH* sizeof(char));
    u.username = (char*) malloc(WORD_LENGTH* sizeof(char));
    return u;
}

void defineDefaultUser(user *u) {
    strcpy(u->username, "admin");
    strcpy(u->password, "admin");
}
