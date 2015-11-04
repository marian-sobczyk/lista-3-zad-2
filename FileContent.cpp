//
// Created by Marian Sobczyk on 01.11.2015.
//

#include <stdio.h>
#include <openssl/aes.h>
#include <string.h>
#include "FileContent.h"

void FileContent::readFromPath(const char *path) {
    FILE *input = fopen(path, "rb");
    if (input == NULL) {
        return;
    }
    fseek(input, 0L, SEEK_END);
    filesize = (unsigned long) ftell(input);
    if (encrypted) {
        filesize -= AES_BLOCK_SIZE;
        initVector = new unsigned char[AES_BLOCK_SIZE];
    }
    fseek(input, 0L, SEEK_SET);
    content = new unsigned char[filesize];
    unsigned char character;
    if (encrypted) {
        for (int i = 0; i < AES_BLOCK_SIZE; i++) {
            fread(&character, 1, 1, input);
            initVector[i] = character;
        }
    }
    for (int i = 0; i < filesize; i++) {
        fread(&character, 1, 1, input);
        content[i] = character;
    }
    fclose(input);
}

void FileContent::saveInPath(const char *path) {
    FILE *output = fopen(path, "wb");
    if (output == NULL) {
        return;
    }
    if (encrypted) {
        for (int i = 0; i < AES_BLOCK_SIZE; i++) {
            fwrite(&initVector[i], 1, 1, output);
        }
    }
    for (int i = 0; i < filesize; i++) {
        fwrite(&content[i], 1, 1, output);
    }

    fclose(output);
}

FileContent::FileContent(long size, bool encrypted) {
    filesize = (unsigned long) size;
    content = new unsigned char[size];
    this->encrypted = encrypted;
    initVector = new unsigned char[AES_BLOCK_SIZE];
}

FileContent::FileContent(bool encrypted) {
    this->encrypted = encrypted;
    initVector = new unsigned char[AES_BLOCK_SIZE];
}

FileContent::FileContent(unsigned char *content, unsigned long length, bool encrypted) {
    this->content = new unsigned char[length];
    memcpy(this->content, content, (size_t) length);
    this->filesize = length;
    this->encrypted = encrypted;
}
