//
// Created by Marian Sobczyk on 04.11.2015.
//

#include "MusicFileFactory.h"
#include "EncodedFileReader.h"

IFileReader *MusicFileFactory::createFileReader(const ik_c8 *filename) {
    FILE* file = fopen(filename, "rb");
    if (!file)
        return 0;

    return new EncodedFileReader(file, filename);
}
