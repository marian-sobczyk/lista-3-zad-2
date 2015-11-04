//
// Created by Marian Sobczyk on 01.11.2015.
//

#include <openssl/aes.h>
#include <string.h>
#include "AESCBCEncryptor.h"
#include <openssl/rand.h>

FileContent *AESCBCEncryptor::encryptData(FileContent *data) {
    unsigned char *initVector = new unsigned char[AES_BLOCK_SIZE];
    RAND_bytes(initVector, AES_BLOCK_SIZE);
    AES_KEY enc_key;
    AES_set_encrypt_key(key, keyLength * 8, &enc_key);
    long outputLength = ((data->filesize + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    FileContent *outputData = new FileContent(outputLength, true);
    memcpy(outputData->initVector, initVector, AES_BLOCK_SIZE);
    AES_cbc_encrypt(data->content, outputData->content, data->filesize,
                    &enc_key, initVector, AES_ENCRYPT);

    return outputData;
}

FileContent *AESCBCEncryptor::decryptData(FileContent *data) {
    unsigned char *initVector = new unsigned char[AES_BLOCK_SIZE];
    memcpy(initVector, data->initVector, AES_BLOCK_SIZE);
    AES_KEY dec_key;
    AES_set_decrypt_key(key, keyLength * 8, &dec_key);
    long outputLength = data->filesize;
    FileContent *outputData = new FileContent(outputLength, false);
    AES_cbc_encrypt(data->content, outputData->content, data->filesize, &dec_key, initVector,
                    AES_DECRYPT);
    return outputData;
}

AESCBCEncryptor::AESCBCEncryptor(int keyLength, unsigned char *key) {
    this->keyLength = keyLength / 8;
    this->key = new unsigned char[this->keyLength];
    memcpy(this->key, key, (size_t) this->keyLength);
}
