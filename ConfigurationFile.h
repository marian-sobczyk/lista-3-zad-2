//
// Created by Marian Sobczyk on 04.11.2015.
//

#ifndef LISTA_3_ZAD_2_CONFIGURATIONFILE_H
#define LISTA_3_ZAD_2_CONFIGURATIONFILE_H


class ConfigurationFile {

public:
    ConfigurationFile();

    void resizeKey(unsigned char *key, const char *keyToResize);

    void checkIfConfigurationFileExistsExists(const char *path, unsigned char *key);

    void createNewConfigurationFile(unsigned char *path, unsigned char *key);

    const char *path;
    const char *password;
    int keyId;
    const char *pin;
};


#endif //LISTA_3_ZAD_2_CONFIGURATIONFILE_H
