//
// Created by Marian Sobczyk on 03.11.2015.
//

#include <stdio.h>
#include <openssl/rand.h>
#include "KeyChain.h"
#include "FileContent.h"
#include "AESCTREncryptor.h"

#define KEYLENGTH 33

KeyChain::KeyChain(unsigned char *path, unsigned char *pass, int index) {
    unsigned char *password = new unsigned char[256];
    resizePassword(password, pass);
    checkIfKeychainExists(path, password);
    FileContent *keyChain = new FileContent(true);
    keyChain->readFromPath((const char *) path);
    AESCTREncryptor *encryptor = new AESCTREncryptor(password);
    FileContent *fileContent = encryptor->decryptData(keyChain);
    delete keyChain;
    delete encryptor;
    int start = index * KEYLENGTH;
    int keyLength = getKeyLength(fileContent->content[start]);
    this->key = new unsigned char[keyLength];
    for (int i = 0; i < keyLength; i++) {
        this->key[i] = fileContent->content[i + start + 1];
    }

    delete fileContent;
}

void KeyChain::checkIfKeychainExists(const unsigned char *path, const unsigned char *password) {
    FILE *input = fopen((const char *) path, "rb");
    if (input == NULL) {
        createNewKeychain((unsigned char *) path, (unsigned char *) password);
    } else {
        fclose(input);
    }
}

void KeyChain::createNewKeychain(unsigned char *path, unsigned char *password) {
    unsigned char *keyChain = new unsigned char[KEYLENGTH];
    RAND_bytes(keyChain, KEYLENGTH);
    FileContent *fileContent = new FileContent(keyChain, KEYLENGTH, false);
    AESCTREncryptor *encryptor = new AESCTREncryptor(password);
    FileContent *encrypted = encryptor->encryptData(fileContent);
    encrypted->saveInPath((const char *) path);
    delete keyChain;
    delete fileContent;
    delete encryptor;
    delete encrypted;
}

int KeyChain::getKeyLength(unsigned char type) {
    if (type == 0)
        return 256;
    if (type == 128)
        return 128;
    if (type == 196)
        return 196;
    return 256;
}

void KeyChain::resizePassword(unsigned char *password, unsigned char *pass) {
    int i;
    for (i = 0; i < 256 && pass[i] != '\0'; i++) {
        password[i] = pass[i];
    }
    for (; i < 256; i++) {
        password[i] = 0;
    }
}
