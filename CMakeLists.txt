cmake_minimum_required(VERSION 3.3)
project(lista_3_zad_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

link_libraries("-lssl -lcrypto")

add_executable(lista_3_zad_2 ${SOURCE_FILES})