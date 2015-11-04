//
// Created by Marian Sobczyk on 04.11.2015.
//

#ifndef LISTA_3_ZAD_1_AESENCRYPTOR_H
#define LISTA_3_ZAD_1_AESENCRYPTOR_H

#include "FileContent.h"

class AESEncryptor {
public:
    virtual FileContent *encryptData(FileContent *fileContent) = 0;

    virtual FileContent *decryptData(FileContent *data) = 0;
};

#endif //LISTA_3_ZAD_1_AESENCRYPTOR_H
