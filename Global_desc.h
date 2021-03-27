//
// Created by Deng Weijia on 8/27/18.
// This file reference some information about how blobs are organized from the nvdla/sw project
// https://github.com/nvdla/sw
//
/// Offers base class that deals with all kinds of blob data. Also offers class that contains information of
/// addr_list and mem_list in use of drawing the process graph.

#ifndef NVDLA_DEPICTER_GLOBAL_DESC_H
#define NVDLA_DEPICTER_GLOBAL_DESC_H

#include "external/loadable_generated.h"
#include <iostream>
#include <unordered_map>
#include "external/half.h"





//Class that contains information from addr_list that is useful when drawing process graph.
class Addr_list{
public:

    //Addr_list is a surjection of mem_list.
    //This hash table records the detailed projection.
    std::unordered_map<int,int> index_dict;
    explicit Addr_list(nvdla::loadable::Loadable const * loadable);
};

//Class that contains information from mem_list that is useful when drawing process graph.
class Mem_list{
public:
    //Mem_list is an injection of addr_list
    //Mem_block that the value has been set in the loadable file  has a name.
    std::unordered_map<int,std::string> alias_dict;
    explicit Mem_list(nvdla::loadable::Loadable const * loadable);

};


//Base class for all kinds of blob data.

class Desc_base {
protected:
    //The size of each unit in a blob. Different types of blobs have different unit_size.
    //The value is got from perusing the given loadable files.
    int unit_size;
    //Origin data
    std::vector<uint8_t > blob;
    //Type of each operation
    std::vector<std::string> configuration;

    //All deal_with functions with a return value do the following things:
    //  1. Return the value
    //  2. Proceed the index
    uint64_t deal_with_uint8(int & index) { return static_cast<uint64_t>(blob[index++]); }
    int64_t deal_with_int8(int & index) { return static_cast<int64_t>(blob[index++]); }
    float deal_with_float32(int & index);
    half_float::half deal_with_float16(int & index);
    uint16_t deal_with_uint16(int & index);
    int16_t deal_with_int16(int & index) { return static_cast<int16_t>(deal_with_uint16(index)); }
    uint32_t deal_with_uint32(int & index);
    int32_t deal_with_int32(int & index);
    int64_t deal_with_int64(int & index);


    void out_put_tab(std::ostream & os, int num);

    //All deal_with functions with no return value do the following things:
    //  1. Out the description read from blob
    //  2. Proceed the index
    void deal_with_array(std::ostream & os, int & index, int array_size);

    void deal_with_array_int16(std::ostream & os, int & index, int array_size);

    void deal_with_array_int32(std::ostream & os, int & index, int array_size);


public:
    void read_configuration(std::vector<std::string> const & layer_type);
    void read_data(nvdla::loadable::Blob const * blob);
    virtual void generate_file(std::ostream & os) = 0;
};

//Base class for all kinds of surf_desc data.

class Surf_desc_base : public Desc_base {

public:
    //Source address of each layer
    std::vector<std::vector<int> > source_list;
    //Destination address of each layer
    std::vector<std::vector<int> > dest_list;

};

//Base class for all kinds of net_desc data.

class Net_desc_base : public Desc_base{

protected:
    //The operation blob index of each task. Note that this index is taskwise rather than global.
    int16_t operation_desc_index;
    //The surf_desc blob of each task. Note that this index is taskwise rather than global.
    int16_t operation_buffer_desc_index;
    //Number of operations contains in current task.
    int16_t num_operations;

public:
    virtual int16_t get_dep_index()=0;

    virtual int16_t get_op_index()=0;

    virtual int16_t get_surf_index()=0;

    virtual int16_t get_num_op()=0;


};






#endif //NVDLA_DEPICTER_GLOBAL_DESC_H