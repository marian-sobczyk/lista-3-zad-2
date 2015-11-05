//
// Created by Marian Sobczyk on 03.11.2015.
//

#ifndef LISTA_3_ZAD_1_KEYCHAIN_H
#define LISTA_3_ZAD_1_KEYCHAIN_H


class KeyChain {

public:
    KeyChain(unsigned char *path, unsigned char *pass, int index);

    void createNewKeychain(unsigned char *path, unsigned char *password);

    void checkIfKeychainExists(const unsigned char *path, const unsigned char *password);

    int getKeyLength(unsigned char type);

    unsigned char *key;

    void resizePassword(unsigned char *password, unsigned char *pass);
};


#endif //LISTA_3_ZAD_1_KEYCHAIN_H
