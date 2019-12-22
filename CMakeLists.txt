cmake_minimum_required(VERSION 3.15)
project(food_ordering C)

set(CMAKE_C_STANDARD 99)

add_executable(food_ordering main.c food-ordering-macros.h user.c user.h food.c food.h drink.c drink.h food-subtype.c food-subtype.h load-data.c load-data.h parse-data.c parse-data.h menu.c menu.h sign_in.c sign_in.h)