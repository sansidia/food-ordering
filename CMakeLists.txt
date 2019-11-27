cmake_minimum_required(VERSION 3.15)
project(food_ordering C)

set(CMAKE_C_STANDARD 99)

add_executable(food_ordering main.c userdata.c userdata.h options.c options.h parse-string.c parse-string.h macros.h signin.c signin.h)