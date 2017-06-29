cmake_minimum_required(VERSION 3.7)
project(Esercitazioni)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Alberi/Primo/alberi_1.c
        Alberi/Quarto/alberi_4.c
        Alberi/Secondo/alberi_2.c
        Alberi/Terzo/alberi_3.c
        Liste/Decimo/liste_10.c
        Liste/Dodicesimo/liste_12.c
        Liste/Nono/liste.h
        Liste/Nono/liste_9.c
        Liste/Nono/main.c
        Liste/Ottavo/liste_8.c
        Liste/Primo/liste_1.c
        Liste/Quarto/liste_4.c
        Liste/Quinto/liste_5.c
        Liste/Secondo/liste_2.c
        Liste/Sesto/liste_6.c
        Liste/Settimo/liste_7.c
        Liste/Terzo/liste_3.c
        Liste/Undicesimo/liste_11.c
        .gitignore)

add_executable(Esercitazioni ${SOURCE_FILES})