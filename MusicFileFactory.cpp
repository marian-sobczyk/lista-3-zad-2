//
// Created by Marian Sobczyk on 04.11.2015.
//

#include <string.h>
#include "MusicFileFactory.h"
#include "EncodedFileReader.h"

IFileReader *MusicFileFactory::createFileReader(const ik_c8 *filename) {
//    FILE* file = fopen(filename, "rb");
//    if (!file)
//        return 0;

    return new EncodedFileReader(NULL, filename, this->key);
}

MusicFileFactory::MusicFileFactory(unsigned char *key) {
    this->key = new unsigned char[128/8];
    memcpy(this->key, key, 128/8);
}
