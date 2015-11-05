//
// Created by Marian Sobczyk on 04.11.2015.
//

#ifndef LISTA_3_ZAD_2_CMYREADFILE_H
#define LISTA_3_ZAD_2_CMYREADFILE_H

#include <irrKlang.h>
#include "AESCTREncryptor.h"

using namespace irrklang;

class EncodedFileReader : public IFileReader {

public:
    EncodedFileReader(FILE *openedFile, const ik_c8 *fileName, unsigned char *key);

    virtual ~EncodedFileReader();


    AESCTREncryptor *file;
    char fileName[1024];
    ik_s32 fileSize;

    virtual ik_s32 read(void *buffer, ik_u32 sizeToRead);

    virtual bool seek(ik_s32 finalPos, bool relativeMovement);

    virtual ik_s32 getSize();

    virtual ik_s32 getPos();

    virtual const ik_c8 *getFileName();
};


#endif //LISTA_3_ZAD_2_CMYREADFILE_H
