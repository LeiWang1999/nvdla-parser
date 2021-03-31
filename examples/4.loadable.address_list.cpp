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
    auto address_list = loadable->address_list();
    for(auto AddressListEntry : *address_list){
        auto id = AddressListEntry->id();
        auto mem_id = AddressListEntry->mem_id();
        auto offset = AddressListEntry->offset();
        auto size = AddressListEntry->size();

        std::cout << "Loadable AddressListEntry : " << std::endl;
        std::cout << "id : " << id << std::endl;
        std::cout << "mem_id : " << mem_id << std::endl;
        std::cout << "offset : " << offset << std::endl;
        std::cout << "size : " << size << std::endl;
        std::cout << std::endl;
    }

    return 0;
}