cmake_minimum_required(VERSION 3.3)
project(lista_3_zad_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ConfigurationFile.cpp ConfigurationFile.h FileContent.cpp FileContent.h AESCBCEncryptor.cpp AESCBCEncryptor.h AESEncryptor.cpp AESEncryptor.h)

link_libraries("-lssl -lcrypto")

add_executable(lista_3_zad_2 ${SOURCE_FILES})