//
// Created by Marian Sobczyk on 01.11.2015.
//

#ifndef LISTA_3_ZAD_1_FILECONTENT_H
#define LISTA_3_ZAD_1_FILECONTENT_H

#include <stdio.h>

class FileContent {

public:
    FileContent(long size, bool encrypted);

    FileContent(bool encrypted);

    FileContent(unsigned char *content, unsigned long length, bool encrypted);

    FileContent(const char *path);

    void readFromPath(const char *path);

    unsigned char *content;

    void saveInPath(const char *path);

    unsigned long filesize;

    unsigned char *initVector;
    bool encrypted;

    int fcread(void *buffer, unsigned int size);

    void fcseek(int finalPosition, int type);

    long fctell();

private:
    FILE *input;

    void readInitVector();
};


#endif //LISTA_3_ZAD_1_FILECONTENT_H
