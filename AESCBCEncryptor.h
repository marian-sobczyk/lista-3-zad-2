//
// Created by Marian Sobczyk on 01.11.2015.
//

#ifndef LISTA_3_ZAD_1_AESCBCENCRYPTOR_H
#define LISTA_3_ZAD_1_AESCBCENCRYPTOR_H


#include "FileContent.h"
#include "AESEncryptor.h"
#include <openssl/aes.h>

class AESCBCEncryptor : public AESEncryptor {

public:
    AESCBCEncryptor(int keyLength, unsigned char *key);

    virtual FileContent *encryptData(FileContent *fileContent);

    virtual FileContent *decryptData(FileContent *data);

private:
    int keyLength;
    unsigned char *key;
};


#endif //LISTA_3_ZAD_1_AESCBCENCRYPTOR_H
