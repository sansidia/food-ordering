//
// Created by diana on 20/12/2019.
//

#include <stdbool.h>
#include "sign_in.h"

enum signInState {SIGN_IN_OR_UP_STATE, SIGNING_IN_STATE, INCORRECT_PASSWORD_STATE,
        NONEXISTENT_USERNAME_STATE, SIGNING_UP_STATE, SIGN_UP_ERROR_STATE, FINISHED_SIGNING_STATE};

int signIn(user *currentUser, userArray registeredUsers, int state);

int signUp(user *currentUser, userArray *registeredUsers, int state);

void signInOrUp(user *currentUser, userArray *registeredUsers) {
    int state = SIGN_IN_OR_UP_STATE;
    printf(WELCOME_MSG);
    while (state != FINISHED_SIGNING_STATE) {
        printf(SIGN_IN_UP);
        printf("a) %s", SIGN_IN_MSG);
        printf("b) %s", SIGN_UP_MSG);
        int choice = getchar();
        getchar();
        choice = choice - 'a';
        switch (choice) {
            case 0: {
                state = signIn(currentUser, *registeredUsers, SIGNING_IN_STATE);
                break;
            }
            case 1: {
                state = signUp(currentUser, registeredUsers, SIGNING_UP_STATE);
                break;
            }
            default: {
                break;
            }
        }
    }
}

int checkSignUpInfo(user *currentUser, userArray registeredUsers);

char *getSignUpError(user *currentUser, userArray registeredUsers);

int signUp(user *currentUser, userArray *registeredUsers, int state) {
    while (state != FINISHED_SIGNING_STATE && state != SIGN_IN_OR_UP_STATE) {
        switch (state) {
            case SIGNING_UP_STATE: {
                printf("%s", SIGNING_UP);
                printf("---Username:\n");
                gets(currentUser->username);
                printf("---Password:\n");
                gets(currentUser->password);

                state = checkSignUpInfo(currentUser, *registeredUsers);
                if (state == FINISHED_SIGNING_STATE) {
                    (registeredUsers->nrOfUsers)++;
                    registeredUsers->userList[registeredUsers->nrOfUsers] = *currentUser;
                }
                break;
            }
            case SIGN_UP_ERROR_STATE: {
                printf("%s", getSignUpError(currentUser, *registeredUsers));
                state = SIGNING_UP_STATE;
                break;
            }
        }
    }
    return state;
}

bool checkDuplicateUsers(user *pUser, userArray existingUsers);
bool checkPasswordLength(char *password);
bool checkPasswordSpecialChars(char *password);
bool checkPasswordContainsDigits(char *password);
bool checkUsernameNotInPassword(user *pUser);

char *getSignUpError(user *currentUser, userArray registeredUsers) {
    if (checkPasswordLength(currentUser->password)) return ERROR_PASSWORD_LONG;
    if (checkPasswordSpecialChars(currentUser->password)) return ERROR_PASSWORD_SPECIAL_CHAR;
    if (checkPasswordContainsDigits(currentUser->password)) return ERROR_PASSWORD_DIGITS;
    if (checkUsernameNotInPassword(currentUser)) return ERROR_PASSWORD_NOT_USERNAME;
    if (checkDuplicateUsers(currentUser, registeredUsers)) return DUPLICATE_USER;
    return NULL;
}

bool checkUsernameNotInPassword(user *pUser) {
    if (strstr(pUser->password, pUser->username)) return 1;
    return 0;
}
bool checkPasswordContainsDigits(char *password) {
    if (strpbrk(password, "0123456789")) return 0;
    return 1;
}
bool checkPasswordSpecialChars(char *password) {
    if (strpbrk(password, "!_.")) return 0;
    return 1;
}
bool checkPasswordLength(char *password) {
    if (strlen(password) < 7) return 1;
    return 0;
}
bool checkDuplicateUsers(user *pUser, userArray existingUsers) {
    for (int i = 0; i < MAX_NR_OF_USERS; ++i) {
        if (strcmp(pUser->username, existingUsers.userList[i].username) == 0)
            return 1;
    }
    return 0;
}

int checkSignUpInfo(user *currentUser, userArray registeredUsers) {
    if (getSignUpError(currentUser, registeredUsers) == NULL)
        return FINISHED_SIGNING_STATE;
    else return SIGN_UP_ERROR_STATE;
}

int infoIsValid(user *myUser, userArray existingUsers);
int checkSignInError(user *currentUser, userArray registeredUsers);

int signIn(user *currentUser, userArray registeredUsers, int state) {
    while (state != FINISHED_SIGNING_STATE && state != SIGN_IN_OR_UP_STATE) {
        switch (state) {
            case SIGNING_IN_STATE: {
                printf("%s", SIGNING_IN);
                printf("---Username:\n");
                gets(currentUser->username);
                printf("---Password:\n");
                gets(currentUser->password);

                if (infoIsValid(currentUser, registeredUsers)) {
                    state = FINISHED_SIGNING_STATE;
                }
                else
                    state = checkSignInError(currentUser, registeredUsers);
                break;
            }
            case INCORRECT_PASSWORD_STATE: {
                printf("%s", INCORRECT_PASSWORD);
                state = SIGNING_IN_STATE;
                break;
            }
            case NONEXISTENT_USERNAME_STATE: {
                printf("%s", USER_NOT_FOUND);
                state = SIGN_IN_OR_UP_STATE;
                break;
            }
        }
    }
    return state;
}

int checkSignInError(user *currentUser, userArray registeredUsers) {
    int usernameExists = 0, passwordMatches = 0;
    for (int i = 0; i < MAX_NR_OF_USERS; ++i) {
        if (strcmp(currentUser->username, registeredUsers.userList[i].username) == 0) {
            usernameExists = 1;
            if (strcmp(currentUser->password, registeredUsers.userList[i].password) == 0) {
                passwordMatches = 1;
                break;
            }
        }
    }
    if (usernameExists == 0) return NONEXISTENT_USERNAME_STATE;
    if (passwordMatches == 0) return INCORRECT_PASSWORD_STATE;
}
int infoIsValid(user *myUser, userArray existingUsers) {
    for (int i = 0; i < MAX_NR_OF_USERS; ++i) {
        if(strcmp(myUser->username, existingUsers.userList[i].username) == 0) {
            if (strcmp(myUser->password, existingUsers.userList[i].password) == 0)
                return 1;
        }
    }
    return 0;
}
