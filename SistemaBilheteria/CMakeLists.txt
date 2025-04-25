cmake_minimum_required(VERSION 3.29.6)
project(SistemaBilheteria C)

set(CMAKE_C_STANDARD 11)

add_executable(SistemaBilheteria main.c
        utils.h
        bilheteria.c
        bilheteria.h
        bilhete.c
        bilhete.h
        menu.c
        menu.h
        main.c
        main.c)
