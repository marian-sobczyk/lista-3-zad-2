//
// Created by Marian Sobczyk on 04.11.2015.
//

#include <stdio.h>
#include "ConfigurationFile.h"
#include "FileContent.h"
#include "AESCTREncryptor.h"
#include <iostream>

using namespace std;

#define KEY "Marian"

ConfigurationFile::ConfigurationFile() {
    unsigned char *key = new unsigned char[256];
    resizeKey(key, KEY);
    checkIfConfigurationFileExistsExists("/Users/marian/Desktop/ssl/config.cfg", key);

    FileContent *encodedConfigFile = new FileContent(true);
    encodedConfigFile->readFromPath("/Users/marian/Desktop/ssl/config.cfg");
    AESCTREncryptor *encryptor = new AESCTREncryptor(key);
    FileContent *configFile = encryptor->decryptData(encodedConfigFile);
    delete encodedConfigFile;
    delete encryptor;
    string path = "";
    int i = 0;
    while (configFile->content[i] != ' ') {
        path = path + (char) configFile->content[i];
        i++;
    }
    string keyId = "";
    i++;
    while (configFile->content[i] != ' ') {
        keyId = keyId + (char) configFile->content[i];
        i++;
    }
    string password = "";
    i++;
    while (configFile->content[i] != ' ') {
        password = password + (char) configFile->content[i];
        i++;
    }
    string pin = "";
    i++;
    while (configFile->content[i] != '\0') {
        pin = pin + (char) configFile->content[i];
        i++;
    }

    this->path = new char[path.length()];
    memcpy(this->path, path.c_str(), path.length());
    this->password = new char[password.length()];
    memcpy(this->password, password.c_str(), password.length());
    this->keyId = atoi(keyId.c_str());
    this->pin = new char[pin.length()];
    memcpy(this->pin, pin.c_str(), pin.length());
    delete configFile;
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
        fclose(input);
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
    cout << "Podaj PIN: ";
    string pin;
    cin >> pin;

    unsigned int length = (unsigned int) (keystorePath.length() + 1 + keyId.length() + 1 + passwordLength + 1 +
                                          pin.length());
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
    content[pos] = ' ';
    pos++;
    for (int i = 0; i < pin.length(); i++) {
        content[pos] = (unsigned char) pin.at(i);
        pos++;
    }

    FileContent *fileContent = new FileContent(content, length, false);
    AESCTREncryptor *encryptor = new AESCTREncryptor(key);
    FileContent *encrypted = encryptor->encryptData(fileContent);
    encrypted->saveInPath((const char *) path);
    delete content;
    delete fileContent;
    delete encryptor;
    delete encrypted;
}
