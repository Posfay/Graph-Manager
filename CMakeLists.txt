cmake_minimum_required(VERSION 3.20)
project(graf C)

set(CMAKE_C_STANDARD 99)

add_executable(graf main.c megjelenites.c megjelenites.h listak.c listak.h fajlkezeles.c fajlkezeles.h grafkezeles.c grafkezeles.h test.c test.h)
