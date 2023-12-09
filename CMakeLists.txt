cmake_minimum_required(VERSION 3.26)
project(DSA_exp5 C)

set(CMAKE_C_STANDARD 11)

add_executable(DSA_exp5 initTree.h
        initTree.c
        main.c
        decoder.h
        decoder.c
        encoder.h
        encoder.c)
