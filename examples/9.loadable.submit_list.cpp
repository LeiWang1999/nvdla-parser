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
    auto submit_list = loadable->submit_list();
    for(auto SubmitListEntry : *submit_list){
        auto id = SubmitListEntry->id();
        auto task_id = SubmitListEntry->task_id();

        std::cout << "Loadable submit_list : " << std::endl;
        std::cout << "id : " << id << std::endl;
        std::cout << "task_id size is " << task_id->size() << " : " << std::endl;
        for(auto t : *task_id) std::cout << t << " ";

        std::cout << std::endl << std::endl;

    }

    return 0;
}