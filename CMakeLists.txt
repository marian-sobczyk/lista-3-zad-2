cmake_minimum_required(VERSION 3.3)
project(lista_3_zad_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ConfigurationFile.cpp ConfigurationFile.h FileContent.cpp FileContent.h AESCBCEncryptor.cpp AESCBCEncryptor.h AESEncryptor.cpp AESEncryptor.h MusicFileFactory.cpp MusicFileFactory.h EncodedFileReader.cpp EncodedFileReader.h)

link_libraries("-lssl -lcrypto")

add_executable(lista_3_zad_2 ${SOURCE_FILES})

#link_libraries(${CMAKE_CURRENT_SOURCE_DIR}/)
#link_libraries(${CMAKE_CURRENT_SOURCE_DIR})

#link_directories(${CMAKE_CURRENT_SOURCE_DIR})

#add_library(IRRKLANG ALL ${CMAKE_CURRENT_SOURCE_DIR}/libirrklang.dylib)
#
#link_libraries(IRRKLANG)
#
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(lista_3_zad_2 ${CMAKE_CURRENT_SOURCE_DIR}/libirrklang.dylib)