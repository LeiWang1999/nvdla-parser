//
// Created by Deng Weijia on 8/27/18.
// This file reference the flatbuffer examples.
//

#include <cstdio>
#include "Interface.h"
#include "tools.h"

//Get the pointer of the loadable file.
const nvdla::loadable::Loadable *get_loadable(const std::string &filename) {
    //Check whether the file exists.
    if(!is_file_exists(filename))
        return nullptr;
    FILE* file = fopen(filename.c_str(), "rb");
    fseek(file, 0L, SEEK_END);
    int length = ftell(file);
    fseek(file, 0L, SEEK_SET);
    char *data = new char[length];
    fread(data, sizeof(char), length, file);
    fclose(file);
    // Check whether the file is a loadable file.
    flatbuffers::Verifier verifier(reinterpret_cast<const uint8_t *>(data), length);
    if(!nvdla::loadable::VerifyLoadableBuffer(verifier))
        //File is not a loadable file
        return nullptr;
    return nvdla::loadable::GetLoadable(data);

}
