//
// Created by Deng Weijia on 8/22/18.
//

///Class that drives the whole process.

#ifndef NVDLA_DEPICTER_DRIVER_H
#define NVDLA_DEPICTER_DRIVER_H

#include "Global_desc.h"

using std::string;

//Class that drives the whole process.
class Driver{
    Addr_list addr_list;
    Mem_list mem_list;
    nvdla::loadable::Loadable const * loadable;

    //Get the blob name given addr_index.
    string get_name (int addr_index,int task_index){

        //Get the abstract addr_index from the relative addr_index
        auto addr_converted_index = loadable->task_list()->Get(task_index)->address_list()->Get(addr_index);

        //Since addr_index is a surjection of mem_list, and only mem_list has names, it should look up
        // the addr_index_dict to get the mem_index.
        return mem_list.alias_dict[addr_list.index_dict[addr_converted_index]];
    }

    //Given the name of a blob, retrieve the index of the blob.
    int get_blob_index (string const & str);



public:

    explicit Driver(nvdla::loadable::Loadable const * loadable_p):addr_list(loadable_p),mem_list(loadable_p),loadable(loadable_p){}

    //Start the engine.
    bool engine_start(const string &py_name, const string &format, const string &image_name, const string & file_dir);

};




#endif //NVDLA_DEPICTER_DRIVER_H