#include <stdio.h>

int main() {

    char username[20], password[20];

    printf("Welcome to Food Thingies!\n");
    printf("Please sign in to continue!\n");
    printf("---Username:\n");
    gets(username);
    printf("---Password:\n");
    gets(password);

    printf("Username is %s and password is %s", username, password);

    return 0;
}