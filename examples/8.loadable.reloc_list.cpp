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
    auto reloc_list = loadable->reloc_list();
    for(auto RelocListEntry : *reloc_list){
        auto address_id = RelocListEntry->address_id();
        auto write_id = RelocListEntry->write_id();
        auto offset = RelocListEntry->offset();
        auto interface = RelocListEntry->interface();
        auto sub_interface = RelocListEntry->sub_interface();
        auto reloc_type = RelocListEntry->reloc_type();

        std::cout << "Loadable reloc_list : " << std::endl;
        std::cout << "address_id : " << address_id << std::endl;
        std::cout << "write_id : " << write_id << std::endl;
        std::cout << "offset : " << offset << std::endl;
        std::cout << "interface : " << interface << std::endl;
        std::cout << "sub_interface : " << sub_interface << std::endl;
        std::cout << "reloc_type : " <<(unsigned int) reloc_type << std::endl;

        std::cout << std::endl;
    }

    return 0;
}