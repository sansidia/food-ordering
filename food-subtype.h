//
// Created by diana on 18/12/2019.
//

#ifndef FOOD_ORDERING_V2_FOOD_SUBTYPE_H
#define FOOD_ORDERING_V2_FOOD_SUBTYPE_H

typedef struct _foodSubtype {
    char* name;
    double price;
} foodSubtype;

foodSubtype createSubtype();

#endif //FOOD_ORDERING_V2_FOOD_SUBTYPE_H
