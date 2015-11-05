//
// Created by Marian Sobczyk on 02.11.2015.
//

#include <string.h>
#include <openssl/rand.h>
#include "AESCTREncryptor.h"


void AESCTREncryptor::initCtr() {
    num = 0;
    ecount = new unsigned char[AES_BLOCK_SIZE];
    memset(ecount, 0, AES_BLOCK_SIZE);
    ivec = new unsigned char[AES_BLOCK_SIZE];
    memset(ivec + 8, 0, 8);
    memcpy(ivec, initVector, 8);
}

FileContent *AESCTREncryptor::encryptData(FileContent *data) {
    RAND_bytes(initVector, AES_BLOCK_SIZE);
    FileContent *outputData = new FileContent(data->filesize, true);
    memcpy(outputData->initVector, initVector, AES_BLOCK_SIZE);
    initCtr();
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);
    AES_ctr128_encrypt(data->content, outputData->content, data->filesize, &enc_key, ivec, ecount, &num);
    return outputData;
}

FileContent *AESCTREncryptor::decryptData(FileContent *data) {
    memcpy(initVector, data->initVector, AES_BLOCK_SIZE);
    initCtr();
    AES_KEY dec_key;
    AES_set_encrypt_key(key, 128, &dec_key);
    FileContent *outputData = new FileContent(data->filesize, false);
    AES_ctr128_encrypt(data->content, outputData->content, data->filesize, &dec_key, ivec, ecount, &num);
    return outputData;
}

AESCTREncryptor::AESCTREncryptor(unsigned char *key) {
    this->key = new unsigned char[128 / 8];
    memcpy(this->key, key, 128 / 8);
    this->initVector = new unsigned char[AES_BLOCK_SIZE];
}

AESCTREncryptor::AESCTREncryptor(unsigned char *key, FileContent *content) {
    this->key = new unsigned char[128 / 8];
    memcpy(this->key, key, 128 / 8);
    this->initVector = new unsigned char[AES_BLOCK_SIZE];
    memcpy(initVector, content->initVector, AES_BLOCK_SIZE);
    this->fileContent = content;
    initCtr();
    AES_set_encrypt_key(key, 128, &dec_key);
}

int AESCTREncryptor::getSize() {
    return (int) this->fileContent->filesize;
}

ik_s32 AESCTREncryptor::fread(void *buffer, int elementSize, unsigned int size) {
    unsigned char *toDecode = new unsigned char[elementSize];
    ik_s32 fetchedSize = this->fileContent->fcread(toDecode, size);
    unsigned char *decoded = new unsigned char[fetchedSize];
    AES_ctr128_encrypt(toDecode, decoded, (const unsigned long) fetchedSize, &dec_key, ivec, ecount, &num);

    buffer = decoded;
//    unsigned char *aaa = (unsigned char *) buffer;
////    buffer = &decoded;
////    buffer = new char[fetchedSize];
//    memcpy(aaa, decoded, (size_t) fetchedSize);
    return fetchedSize;
}

int AESCTREncryptor::fseek(ik_s32 finalPosition, int type) {
    this->fileContent->fcseek(finalPosition, type);
}

ik_s32 AESCTREncryptor::ftell() {
    return (ik_s32) fileContent->fctell();
}
