//
// Created by diana on 18/12/2019.
//

#include "food.h"
#include "food-ordering-macros.h"
#include <stdlib.h>

food createFood(int nr) {
    food f;
    f.name = (char*) malloc(WORD_LENGTH* sizeof(char));
    f.nrOfSubtypes = nr;
    f.subtypes = (foodSubtype*) malloc(f.nrOfSubtypes* sizeof(foodSubtype));
    for (int i = 0; i < f.nrOfSubtypes; ++i) {
        f.subtypes[i] = createSubtype();
    }
    return f;
}
