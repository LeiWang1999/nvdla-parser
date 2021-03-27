//
// Created by Deng Weijia on 7/26/18.
// This file reference some information about how blobs are organized from the nvdla/sw project
// https://github.com/nvdla/sw
//

/// Process DLA blob data, which are raw memory data store in unsigned char format.
/// These data are supposed to be processed by the NVDLA hardware.

#ifndef OP_DESC_PARSER_OP_DESC_H
#define OP_DESC_PARSER_OP_DESC_H

#include "tools.h"
#include "external/loadable_generated.h"
#include "Global_desc.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


const int Kernel_split = 64;

//Define value got from the NVDLA/SW
const int DLA_OP_NUM = 6;
const int NUM_MAX_BDMA_OPS = 20;


// Class thats deal with the surface description blob, which describes the interface of dla operations.
class Surf_desc : public Surf_desc_base {
    std::string deal_with_dla_mem_type(int & index);

    void deal_with_dla_data_cube(std::ostream & os, int & index, int sub_level, int layer_index, std::vector<int> & address_vector, bool address_valid = true);

    void deal_with_bdma_transfer_desc(std::ostream & os, int & index, int sub_level, int layer_index,
                                      std::vector<int> & src_address,std::vector<int> & dst_address,
                                      bool address_valid = true);

    void generate_conv_surf(std::ostream & os, int index,int layer_index);
    void generate_sdp_surf(std::ostream & os, int index,int layer_index);

    void generate_bdma_surf(std::ostream & os, int index,int layer_index);

    void generate_cdp_surf(std::ostream & os, int index,int layer_index);

    void generate_pdp_surf(std::ostream & os, int index, int layer_index);

    void generate_rubik_surf(std::ostream & os, int index,int layer_index);

public:

    Surf_desc() { unit_size = 644; }

    void generate_file(std::ostream &os) override;
};

// Class that deals with the dependency description blob, which describes dependency relation between operations.

class Dep_graph_desc : public Desc_base {
public:struct Consumer;
private:



    std::string deal_with_op_type_num(int index);

    std::string deal_with_op_type(int & index);

    enum Event {
        DLA_EVENT_OP_COMPLETED,
        DLA_EVENT_OP_PROGRAMMED,
        DLA_EVENT_OP_ENABLED,
        DLA_EVENT_CDMA_WT_DONE,
        DLA_EVENT_CDMA_DT_DONE
    };

    enum Op_type {
        DLA_OP_BDMA,
        DLA_OP_CONV,
        DLA_OP_SDP,
        DLA_OP_PDP,
        DLA_OP_CDP,
        DLA_OP_RUBIK
    };




    std::string deal_with_event(int & index);

    void deal_with_dla_consumer(std::ostream & os, Consumer & target_consumer, int & index, int sub_level);


    void deal_with_common_op(std::ostream & os, int index);
    void generate_dot(std::ostream & os, int i, std::string const & title);
    void generate_edge(std::ostream & os, std::vector<std::pair<int,int> > & edge_list);

public:
    Dep_graph_desc() { unit_size = 36; }
    struct Consumer{
        int index;
        std::string event;
    };

    struct Net_unit {
        int index;
        int roi_index;
        std::string op_type;
        int dep_count;
        Consumer consumer[6];
        Consumer fused_parrent;

    };

    std::vector<Net_unit> converted_data;

    //Generate the python file that can draw the dependency flow.
    void generate_python(std::ostream & os);


    void generate_file(std::ostream &os) override;

    std::vector<std::string> get_configuration();

};


// Class that deals with the net description blob, which describes needed information to start a task.

class Net_desc:public Net_desc_base{

    int16_t operation_desc_index;
    int16_t surface_desc_index;

    int16_t dependency_graph_index;
    int16_t lut_data_index;

    int16_t roi_array_index;
    int16_t surface_index;

    int16_t stat_list_index;
    int16_t reserved1;

    int16_t op_head[DLA_OP_NUM];

    uint16_t num_rois;
    uint16_t num_operations;

    uint16_t num_luts;
    uint16_t num_addresses;

    int16_t input_layer;
    uint8_t dynamic_roi;
    uint8_t reserved0;

public:
    void generate_file(std::ostream &os) override;
    int16_t get_dep_index() override {
        return dependency_graph_index;
    }

    int16_t get_surf_index() override{
        return surface_desc_index;
    }

    int16_t get_num_op() override{
        return num_operations;
    }

    int16_t get_op_index() override{
        return operation_desc_index;
    };



};

// Class that deals with the operation description blob, which describes the behavior of each operation.


class Op_desc :public Desc_base {



    std::string deal_with_conv_mode(int & index);

    std::string deal_with_weight_format(int & index);

    std::string deal_with_precision(int & index);

    std::string deal_with_activation(int & index);

    std::string deal_with_pixel_override(int & index);


    std::string deal_with_mean_format(int & index);

    std::string deal_with_alu_type(int & index);

    std::string deal_with_sdp_op_type(int & index);

    std::string deal_with_sdp_op_mode(int & index);

    std::string deal_with_pool_mode(int & index);


    uint64_t deal_with_pool_size(int & index);

    std::string deal_with_dla_format_mode(int & index);

    void deal_with_cvt_param(std::ostream & os, int & index, int sub_level);

    void deal_with_dla_sdp_cvt(std::ostream & os, int & index, int sub_level);

    void deal_with_sdp_op(std::ostream & os, int & index, int sub_level);

    void generate_conv_desc(std::ostream & os, int index);

    void generate_sdp_desc(std::ostream & os, int index);

    void generate_cdp_desc(std::ostream & os, int index);

    std::string deal_with_rubik_mode(int & index);

    void generate_rubik_desc(std::ostream & os, int index);

    void generate_bdma_desc(std::ostream & os, int index);


    void generate_pdp_desc(std::ostream & os, int index);
public:
    Op_desc() { unit_size = 116; }

    void generate_file(std::ostream & os) override;


};

// Class that deals with the weight data description blob, which contains the weight data for each layer.
//TODO: complete this class
class Weight_data:public Desc_base{

    std::vector<half_float::half> original_data;
    int h;
    int w;
    int c;
    int k;
    int kernel_per_group;
    void read_raw_data(){
        int i = 0;
        while(i<blob.size()-1)
            original_data.emplace_back(deal_with_float16(i));
    }

    void out_put_weight_data(std::ostream & os);

    void out_put_bn_data(std::ostream & os);

    void out_put_scale_data_former(std::ostream & os);

    void out_put_data(std::ostream & os);

public:
    void generate_file(std::ostream &os) override;
};


#endif //OP_DESC_PARSER_OP_DESC_H
