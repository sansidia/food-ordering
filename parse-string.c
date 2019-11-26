//
// Created by diana on 25/11/2019.
//

#include "parse-string.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void parse(char* input, char item[3][25], char price[3][25]) {
    char separatorString[] = " (),-:;";
    char *splitter;
    int i = -1;
    while ((splitter = strtok(input, separatorString))) {
        i++;
        printf("splitter is %s and i is %d\n", splitter, i);

        if (isalpha(splitter[0])) {
            strcpy(item[i], splitter);
            strcat(item[i], " \0");
            printf("item[%d] is %s\n", i, item[i]);
        } else if (isdigit(splitter[0])) {
            strcpy(price[i], splitter);
        }
    }
}