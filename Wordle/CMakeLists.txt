cmake_minimum_required(VERSION 3.21)
project(Wordle C)

set(CMAKE_C_STANDARD 99)

add_executable(Wordle main.c update_words.c)
