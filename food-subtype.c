//
// Created by diana on 18/12/2019.
//

#include "food-subtype.h"
#include <stdlib.h>
#include "food-ordering-macros.h"

foodSubtype createSubtype() {
    foodSubtype f;
    f.name = (char*) malloc(WORD_LENGTH* sizeof(char));
    f.price = 0;
    return f;
}
