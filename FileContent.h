//
// Created by Marian Sobczyk on 01.11.2015.
//

#ifndef LISTA_3_ZAD_1_FILECONTENT_H
#define LISTA_3_ZAD_1_FILECONTENT_H


class FileContent {

public:
    FileContent(long size, bool encrypted);

    FileContent(bool encrypted);

    FileContent(unsigned char *content, unsigned long length, bool encrypted);

    void readFromPath(const char *path);

    unsigned char *content;

    void saveInPath(const char *path);

    unsigned long filesize;

    unsigned char *initVector;
    bool encrypted;
};


#endif //LISTA_3_ZAD_1_FILECONTENT_H
