//
// Created by Marian Sobczyk on 04.11.2015.
//

#ifndef LISTA_3_ZAD_2_CMYFILEFACTORY_H
#define LISTA_3_ZAD_2_CMYFILEFACTORY_H

#include <irrKlang.h>

using namespace irrklang;

class MusicFileFactory : public IFileFactory {


public:
    MusicFileFactory(unsigned char *key);

    virtual IFileReader *createFileReader(const ik_c8 *filename) override;

private:
    unsigned char *key;
};


#endif //LISTA_3_ZAD_2_CMYFILEFACTORY_H
