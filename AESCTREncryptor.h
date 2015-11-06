//
// Created by Marian Sobczyk on 02.11.2015.
//

#ifndef LISTA_3_ZAD_1_AESCTRENCRYPTOR_H
#define LISTA_3_ZAD_1_AESCTRENCRYPTOR_H


#include "FileContent.h"
#include "AESEncryptor.h"
#include <irrKlang.h>
#include <openssl/aes.h>

using namespace irrklang;

class AESCTREncryptor : public AESEncryptor {

public:

    AESCTREncryptor(unsigned char *key);

    AESCTREncryptor(unsigned char *key, FileContent *content);

    virtual FileContent *encryptData(FileContent *data);

    virtual FileContent *decryptData(FileContent *data);

    int getSize();

    ik_s32 fread(void *buffer, int elementSize, unsigned int size);

    int fseek(ik_s32 finalPosition, int type);

    ik_s32 ftell();

    void closeInput();

private:
    unsigned char *key;

    void initCtr();

    unsigned int num;
    unsigned char *ecount;
    unsigned char *ivec;

    unsigned char *initVector;
    FileContent *fileContent;
    AES_KEY dec_key;
};


#endif //LISTA_3_ZAD_1_AESCTRENCRYPTOR_H
