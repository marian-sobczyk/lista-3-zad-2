//
// Created by Marian Sobczyk on 04.11.2015.
//

#include <string.h>
#include "EncodedFileReader.h"

EncodedFileReader::EncodedFileReader(FILE *openedFile, const ik_c8 *fileName) {
    file = openedFile;
    strcpy(this->fileName, fileName);

    fseek(file, 0, SEEK_END);
    fileSize = (ik_s32) ftell(file);
    fseek(file, 0, SEEK_SET);
}

EncodedFileReader::~EncodedFileReader() {
    fclose(file);
}

ik_s32 EncodedFileReader::read(void *buffer, ik_u32 sizeToRead) {
    return (ik_s32)fread(buffer, 1, sizeToRead, file);
}

bool EncodedFileReader::seek(ik_s32 finalPos, bool relativeMovement) {
    return fseek(file, finalPos, relativeMovement ? SEEK_CUR : SEEK_SET) == 0;
}

ik_s32 EncodedFileReader::getSize() {
    return fileSize;
}


ik_s32 EncodedFileReader::getPos() {
    return (ik_s32) ftell(file);
}

const ik_c8 *EncodedFileReader::getFileName() {
    return fileName;
}
