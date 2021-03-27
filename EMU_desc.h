//
// Created by Deng Weijia on 8/10/18.
// This file reference some information about how blobs are organized from the nvdla/sw project
// https://github.com/nvdla/sw
//

/// Process DLA blob data, which are raw memory data store in unsigned char format.
/// These data are supposed to be processed by the NVDLA software.

#ifndef OP_DESC_PARSER_EMU_DESC_H
#define OP_DESC_PARSER_EMU_DESC_H

#include "DLA_desc.h"
#include <iostream>
// Class that deals with the net description blob, which describes needed information for starting a task.

class EMU_Net_desc :public Net_desc_base{



    void deal_with_EMU_Net_desc(std::ostream & os, int i);
public:
    EMU_Net_desc(){
        unit_size = 256;
    }

    void generate_file(std::ostream & os) override;

    int16_t get_surf_index() override{
        return operation_buffer_desc_index;
    }

    int16_t get_op_index() override {
        return operation_desc_index;
    }

    int16_t get_num_op() override {
        return num_operations;
    }

    int16_t get_dep_index() override {
        return -1;
    }

};

// Class that deals with the operation description blob, which describes the behavior of each operation.

class EMU_Op_desc :public Desc_base{
    std::string deal_with_op_type(int & index);

    void generate_softmax_desc(std::ostream & os, int i,int sub_level);

    void generate_power_desc(std::ostream & os, int i,int sub_level);

    int figure_out_op_type(int index){
        return  blob[index];
    }

public:
    EMU_Op_desc(){
        unit_size = 16;
    }
    std::vector<std::string> configuration;

    void generate_file(std::ostream & os) override;
};


// Class thats deal with the surface description blob, which describes the interface of dla operations.

class EMU_Op_buf :public Surf_desc_base{




    void deal_with_emu_buffer_desc(std::ostream & os, int  index, int sub_level, int key);




public:
    EMU_Op_buf(){
        unit_size = 256;
    }
    void generate_file(std::ostream & os) override;
};


#endif //OP_DESC_PARSER_EMU_DESC_H
