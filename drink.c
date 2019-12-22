//
// Created by diana on 18/12/2019.
//

#include "drink.h"
#include "food-ordering-macros.h"
#include <stdlib.h>

drink createDrink() {
    drink d;
    d.name = (char*) malloc(WORD_LENGTH* sizeof(char));
    return d;
}
