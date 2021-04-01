//
// Created by lei on 21-3-31.
//

#include <string>
#include <iostream>
#include "external/loadable_generated.h"
#include "tools.h"
#include "Interface.h"

using namespace nvdla::loadable;

int main(){
    flatbuffers::FlatBufferBuilder builder;
    const std::string filename = "../../data/lenet-mnist-caffe/fast-math.nvdla";

    if(!is_file_exists(filename)) {
        std::cout << "Read File Failed" << std::endl;
        return -1;
    }

    auto loadable = get_loadable(filename);
    auto blobs = loadable->blobs();
    int idx = 0;
    for(auto Blob : *blobs){
        auto name = Blob->name();
        auto size = Blob->size();
        auto interface = Blob->interface();
        auto sub_interface = Blob->sub_interface();
        auto version = Blob->version();
        auto data = Blob->data();

        std::cout << "Loadable Blob : " << idx << std::endl;
        std::cout << "name : " << name->c_str() << std::endl;
        std::cout << "size : " << size << std::endl;
        std::cout << "interface { NONE = 0, DLA1 = 1, EMU1 = 2 } : " << interface << std::endl;
        std::cout << "sub_interface {0:NONE 1:ADDR0 2:DEPS 3:OPS 4:SURFS 5:LUTS} : " << sub_interface << std::endl;
        std::cout << "version : "
                  << (unsigned int )version->major()
                  << "."
                  << (unsigned int )version->minor()
                  << "."
                  << (unsigned int )version->sub_minor() << std::endl;
        std::cout << "data size is " << data->size() << " : "
                  <<std::endl;

        std::cout << std::endl;
        idx++;
    }

    return 0;
}