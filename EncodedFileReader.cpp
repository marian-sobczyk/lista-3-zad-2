//
// Created by Marian Sobczyk on 04.11.2015.
//

#include <string.h>
#include "EncodedFileReader.h"
#include "FileContent.h"
#include "AESCTREncryptor.h"

EncodedFileReader::EncodedFileReader(FILE *openedFile, const ik_c8 *fileName, unsigned char *key) {
    file = new AESCTREncryptor(key, new FileContent(fileName));
    memcpy(this->fileName, fileName, 128 / 8);

    fileSize = file->getSize();
}


EncodedFileReader::~EncodedFileReader() {
    delete file;
}

ik_s32 EncodedFileReader::read(void *buffer, ik_u32 sizeToRead) {
    return (ik_s32)file->fread(buffer, 1, sizeToRead);
}

bool EncodedFileReader::seek(ik_s32 finalPos, bool relativeMovement) {
    return file->fseek(finalPos, relativeMovement ? SEEK_CUR : SEEK_SET) == 0;
}

ik_s32 EncodedFileReader::getSize() {
    return fileSize;
}


ik_s32 EncodedFileReader::getPos() {
    return (ik_s32) file->ftell();
}

const ik_c8 *EncodedFileReader::getFileName() {
    return fileName;
}