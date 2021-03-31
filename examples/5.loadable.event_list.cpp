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
    auto event_list = loadable->event_list();
    for(auto EventListEntry : *event_list){
        auto id = EventListEntry->id();
        auto type = EventListEntry->type();
        auto target = EventListEntry->target();
        auto val = EventListEntry->val();
        auto op = EventListEntry->op();

        std::cout << "Loadable AddressListEntry : " << std::endl;
        std::cout << "id : " << id << std::endl;
        std::cout << "type { EVENTTYPE0 = 0, EVENTTYPE1 = 1, EVENTTYPE2 = 2 } : " << type << std::endl;
        std::cout << "target : " << target << std::endl;
        std::cout << "val : " << val << std::endl;
        std::cout << "op { WAIT = 0, SIGNAL = 1 } : " << op << std::endl;

        std::cout << std::endl;
    }

    return 0;
}