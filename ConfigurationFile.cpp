//
// Created by Marian Sobczyk on 04.11.2015.
//

#include <stdio.h>
#include "ConfigurationFile.h"
#include "FileContent.h"
#include "AESCBCEncryptor.h"
#include <iostream>

using namespace std;

#define KEY "Marian"

ConfigurationFile::ConfigurationFile() {
    unsigned char *key = new unsigned char[256];
    resizeKey(key, KEY);
    checkIfConfigurationFileExistsExists("/Users/marian/Desktop/ssl/config.cfg", key);
}

void ConfigurationFile::resizeKey(unsigned char *key, const char *keyToResize) {
    int i;
    for (i = 0; i < 256 && keyToResize[i] != '\0'; i++) {
        key[i] = (unsigned char) keyToResize[i];
    }
    for (; i < 256; i++) {
        key[i] = 0;
    }
}

void ConfigurationFile::checkIfConfigurationFileExistsExists(const char *path, unsigned char *key) {
    FILE *input = fopen(path, "rb");
    if (input == NULL) {
        createNewConfigurationFile((unsigned char *) path, key);
    } else {
        fclose(input);
    }
}

void ConfigurationFile::createNewConfigurationFile(unsigned char *path, unsigned char *key) {
    cout << "Podaj ścieżkę do keystore: ";
    string keystorePath;
    cin >> keystorePath;
    cout << "Podaj identyfikator klucza: ";
    string keyId;
    cin >> keyId;
    char *password = getpass("Podaj hasło do keystore: ");
    size_t passwordLength = strlen(password);

    unsigned int length = (unsigned int) (keystorePath.length() + 1 + keyId.length() + 1 + passwordLength);
    unsigned char *content = new unsigned char[length];
    int pos = 0;
    for (int i = 0; i < keystorePath.length(); i++) {
        content[pos] = (unsigned char) keystorePath.at((unsigned long) i);
        pos++;
    }
    content[pos] = ' ';
    pos++;
    for (int i = 0; i < keyId.length(); i++) {
        content[pos] = (unsigned char) keyId.at((unsigned long) i);
        pos++;
    }
    content[pos] = ' ';
    pos++;
    for (int i = 0; i < passwordLength; i++) {
        content[pos] = (unsigned char) password[i];
        pos++;
    }

    FileContent *fileContent = new FileContent(content, length, false);
    AESCBCEncryptor *encryptor = new AESCBCEncryptor(256, key);
    FileContent *encrypted = encryptor->encryptData(fileContent);
    encrypted->saveInPath((const char *) path);
    delete content;
    delete fileContent;
    delete encryptor;
    delete encrypted;
}
