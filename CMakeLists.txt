cmake_minimum_required(VERSION 3.3)
project(lista_3_zad_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ConfigurationFile.cpp ConfigurationFile.h FileContent.cpp FileContent.h AESCBCEncryptor.cpp AESCBCEncryptor.h AESEncryptor.cpp AESEncryptor.h MusicFileFactory.cpp MusicFileFactory.h EncodedFileReader.cpp EncodedFileReader.h KeyChain.cpp KeyChain.h AESCTREncryptor.cpp AESCTREncryptor.h)

link_libraries("-lssl -lcrypto")

add_executable(lista_3_zad_2 ${SOURCE_FILES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(lista_3_zad_2 ${CMAKE_CURRENT_SOURCE_DIR}/libirrklang.dylib)