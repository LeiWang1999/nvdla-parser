//
// Created by Deng Weijia on 7/26/18.
// This file reference some information about how blobs are organized from the nvdla/sw project
// https://github.com/nvdla/sw
//

#include "DLA_desc.h"

#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>


using std::istream;
using std::ostream;

using std::vector;
using std::string;
using std::istringstream;
using std::ostringstream;
using std::unordered_map;
using std::endl;





string Surf_desc::deal_with_dla_mem_type(int &index) {
    switch (deal_with_uint16(index)) {
        case 0: return "DLA_MEM_MC(External DRAM)";
        case 1: return "DLA_MEM_CV(CV-SRAM)";
        case 2: return "DLA_MEM_HW(DLA sub-module)";
        default: return num_to_string(blob[index - 1]);
    }
}


void
Surf_desc::deal_with_dla_data_cube(ostream &os, int &index, int sub_level, int layer_index, vector<int> &address_vector,
                                   bool address_valid) {
    os << "DLA_DATA_CUBE\n";
    out_put_tab(os, sub_level);
    os << "type : " << deal_with_dla_mem_type(index) << endl;
    out_put_tab(os, sub_level);

    int16_t address = deal_with_int16(index);

    os << "address(offset to the actual IOVA in task.address_list) : " << address << endl;
    out_put_tab(os, sub_level);
    uint32_t size = deal_with_uint32(index);
    os << "size : " << size << endl;
    if ((address != 0)&&(address!=-1)&&address_valid)
        address_vector.emplace_back(address);

    out_put_tab(os, sub_level);
    os << "/* cube dimensions */\n";

    out_put_tab(os, sub_level);
    os << "width : " << deal_with_uint16(index) << endl;
    out_put_tab(os, sub_level);
    os << "height : " << deal_with_uint16(index) << endl;
    out_put_tab(os, sub_level);
    os << "channel : " << deal_with_uint16(index) << endl;
    out_put_tab(os, sub_level);
    os << "reserved0 : " << deal_with_uint16(index) << endl;

    out_put_tab(os, sub_level);
    os << "/* stride information */\n";
    out_put_tab(os, sub_level);
    os << "line_stride : " << deal_with_uint32(index) << endl;
    out_put_tab(os, sub_level);
    os << "surf_stride : " << deal_with_uint32(index) << endl;
    out_put_tab(os, sub_level);
    os << "/* For Rubik only */\n";
    out_put_tab(os, sub_level);
    os << "plane_stride : " << deal_with_uint32(index) << endl;
}

void Surf_desc::deal_with_bdma_transfer_desc(ostream &os, int &index, int sub_level, int layer_index,
                                             vector<int> &src_address, vector<int> &dst_address, bool address_valid) {
    out_put_tab(os, sub_level);
    int16_t src_address_index = deal_with_int16(index);

    os << "source_address : " << src_address_index << endl;
    src_address.emplace_back(src_address_index);

    int16_t dst_address_index = deal_with_int16(index);
    os << "destination_address : " << dst_address_index << endl;
    dst_address.emplace_back(dst_address_index);


    out_put_tab(os, sub_level);
    os << "line_size : " << deal_with_uint32(index) << endl;
    out_put_tab(os, sub_level);
    os << "line_repeat : " << deal_with_uint32(index) << endl;
    out_put_tab(os, sub_level);
    os << "source_line : " << deal_with_uint32(index) << endl;
    out_put_tab(os, sub_level);
    os << "destination_line : " << deal_with_uint32(index) << endl;
    out_put_tab(os, sub_level);
    os << "surface_repeat : " << deal_with_uint32(index) << endl;
    out_put_tab(os, sub_level);
    os << "source_surface : " << deal_with_uint16(index) << endl;
    out_put_tab(os, sub_level);
    os << "destination_surface : " << deal_with_uint16(index) << endl;
}

void Surf_desc::generate_conv_surf(ostream &os, int index, int layer_index) {
    os << " Convolution Surface description\n";
    os << "    weight_data : ";
    deal_with_dla_data_cube(os, index, 2,layer_index,source_list[layer_index]);
    os << "    wmb_data : ";
    deal_with_dla_data_cube(os, index, 2,layer_index,source_list[layer_index]);
    os << "    wgs_data : ";
    deal_with_dla_data_cube(os, index, 2,layer_index,source_list[layer_index]);
    os << "    src_data : ";
    deal_with_dla_data_cube(os, index, 2,layer_index,source_list[layer_index]);
    os << "    dst_data : ";
    //For the convolution layer, the output address is meaningless, for convolution layers are not independent in nvdla.
    //They have to rely on SDP layers to output their data.
    deal_with_dla_data_cube(os, index, 2,layer_index,dest_list[layer_index], false);

    os << "/**\n"
       << "    * u_addr = input_data.source_addr + offset_u\n"
       << "    * this field should be set when YUV is not interleave format\n"
       << "    *\n"
       << "    */";
    os << "    offset_U : " << deal_with_int64(index) << endl;

    os << "    /* line stride for 2nd plane, must be 32bytes aligned */\n";

    os << "    in_line_uv_stride : " << deal_with_uint32(index) << endl;


}

void Surf_desc::generate_sdp_surf(ostream &os, int index, int layer_index) {
    os << " SDP Surface description\n";
    os << "    src_data : ";
    deal_with_dla_data_cube(os, index, 2,layer_index,source_list[layer_index]);
    os << "    x1_data : ";
    deal_with_dla_data_cube(os, index, 2,layer_index,source_list[layer_index]);
    os << "    x2_data : ";
    deal_with_dla_data_cube(os, index, 2,layer_index,source_list[layer_index]);
    os << "    y_data : ";
    deal_with_dla_data_cube(os, index, 2,layer_index,source_list[layer_index]);
    os << "    dst_data : ";
    deal_with_dla_data_cube(os, index, 2,layer_index,dest_list[layer_index]);
}

void Surf_desc::generate_bdma_surf(ostream &os, int index, int layer_index) {
    os << " BDMA Surface description\n";
    os << "    source_type : "<<deal_with_dla_mem_type(index)<<endl;
    os << "    destination_type : "<<deal_with_dla_mem_type(index)<<endl;
    os << "    num_transfers : "<<deal_with_uint16(index)<<endl;

    os << " transfers: ";
    for(int i=0;i<NUM_MAX_BDMA_OPS;i++){
        deal_with_bdma_transfer_desc(os, index, 2,layer_index,source_list[layer_index],dest_list[layer_index]);
    }
}

void Surf_desc::generate_cdp_surf(ostream &os, int index, int layer_index) {
    os << " CDP Surface description\n";
    os << "    src_data : ";
    deal_with_dla_data_cube(os, index, 2,layer_index,source_list[layer_index]);
    os << "    dst_data : ";
    deal_with_dla_data_cube(os, index, 2,layer_index,dest_list[layer_index]);
}

void Surf_desc::generate_pdp_surf(ostream &os, int index, int layer_index) {
    os << " PDP Surface description\n";
    os << "    src_data : ";
    deal_with_dla_data_cube(os, index, 2,layer_index,source_list[layer_index]);
    os << "    dst_data : ";
    deal_with_dla_data_cube(os, index, 2,layer_index,dest_list[layer_index]);
}

void Surf_desc::generate_rubik_surf(ostream &os, int index, int layer_index) {
    os << " Rubic Surface description\n";
    os << "    src_data : ";
    deal_with_dla_data_cube(os, index, 2,layer_index,source_list[layer_index]);
    os << "    dst_data : ";
    deal_with_dla_data_cube(os, index, 2,layer_index,dest_list[layer_index]);
}

void Surf_desc::generate_file(ostream &os) {
    unsigned long list_num = blob.size() / unit_size;
    source_list.resize(list_num);
    dest_list.resize(list_num);
    for (int i = 0, j = 0; i < blob.size(); i += unit_size, j++) {
        os << "Index " << j;
        if (configuration[j] == "Convolution")
            generate_conv_surf(os, i,j);
        else if (configuration[j] == "SDP")
            generate_sdp_surf(os, i,j);
        else if (configuration[j] == "PDP")
            generate_pdp_surf(os, i,j);
        else if (configuration[j] == "CDP")
            generate_cdp_surf(os, i,j);
        else if (configuration[j] == "BDMA")
            generate_bdma_surf(os, i,j);
        else if (configuration[j] == "Rubik")
            generate_rubik_surf(os, i,j);
        else
            std::cout << configuration[j];
    }

}

string Dep_graph_desc::deal_with_op_type_num(int index) {
    switch (index) {
        case 0:
            return "BDMA";
        case 1:
            return "Convolution";
        case 2:
            return "SDP";
        case 3:
            return "PDP";
        case 4:
            return "CDP";
        case 5:
            return "Rubik";
        default:
            return num_to_string(blob[index - 1]);
    }
}

string Dep_graph_desc::deal_with_op_type(int &index) {
    auto num = deal_with_uint8(index);
    return deal_with_op_type_num(num);

}

string Dep_graph_desc::deal_with_event(int &index) {
    switch (deal_with_uint8(index)) {
        case 1:
            return "DLA_EVENT_OP_COMPLETED";
        case 2:
            return "DLA_EVENT_OP_PROGRAMMED";
        case 3:
            return "DLA_EVENT_OP_ENABLED";
        case 4:
            return "DLA_EVENT_CDMA_WT_DONE";
        case 5:
            return "DLA_EVENT_CDMA_DT_DONE";
        default:
            return num_to_string(blob[index - 1]);
    }
}

void Dep_graph_desc::deal_with_dla_consumer(ostream &os, Dep_graph_desc::Consumer &target_consumer, int &index,
                                              int sub_level) {
    os << "DLA_CONSUMER\n";
    out_put_tab(os, sub_level);
    target_consumer.index = deal_with_int16(index);
    os << "index : " << target_consumer.index << endl;
    out_put_tab(os, sub_level);
    target_consumer.event = deal_with_event(index);
    os << "event : " << target_consumer.event << endl;
    out_put_tab(os, sub_level);
    os << "res : " << deal_with_uint8(index) << endl;

}

void Dep_graph_desc::deal_with_common_op(ostream &os, int index) {
    os << "    deal_with_common_op\n";
    converted_data.emplace_back(Net_unit());
    converted_data.back().index = deal_with_int16(index);

    os << "    index : " << converted_data.back().index << endl;
    converted_data.back().roi_index = static_cast<int>(deal_with_int8(index));


    os << "    roi_index : " << converted_data.back().roi_index << endl;
    converted_data.back().op_type = deal_with_op_type(index);


    os << "    op_type : " << converted_data.back().op_type << endl;

    converted_data.back().dep_count = static_cast<int>(deal_with_uint8(index));

    os << "    dependency_count : " << converted_data.back().dep_count << endl;
    os << "    reserved0 : ";
    deal_with_array(os, index, 3);
    os << "    consumers : [\n";

    for (int i = 0; i<6; i++)
    {
        out_put_tab(os, 1);
        os << deal_with_op_type_num(i);
        out_put_tab(os, 1);
        deal_with_dla_consumer(os,converted_data.back().consumer[i] , index, 2);
    }
    os << "    fused_parent : ";
    deal_with_dla_consumer(os, converted_data.back().fused_parrent, index, 2);
}

void Dep_graph_desc::generate_dot(ostream &os, int i, string const &title) {
    os << "dot.node('A" << i << "B','" << title << "')\n";
}

void Dep_graph_desc::generate_edge(ostream &os, vector<std::pair<int, int> > &edge_list) {

    for (auto & x : edge_list)
    {
        os << "dot.edge('A" << x.first << "B','A" << x.second << "B', '')" << endl;
    }


}

void Dep_graph_desc::generate_python(ostream &os) {
    os << "import graphviz as gz\n";
    os << "dot = gz.Digraph();\n";
    for (auto &i : converted_data) {
        generate_dot(os, i.index, i.op_type + num_to_string(i.index));
    }
    vector<std::pair<int, int> > edge_list;
    for (auto & x : converted_data)
    {
        int count = 0;
        for (auto &i : x.consumer) {
            if (i.index != -1)
                count++;

        }
        for (auto &i : x.consumer) {
            if(i.index!=-1)
                edge_list.emplace_back(std::pair<int, int>(x.index, i.index));

        }

    }
    generate_edge(os, edge_list);
    os << "dot.render('depth_graph', view=True)\n";

}

void Dep_graph_desc::generate_file(ostream &os) {
    for (int i = 0, j = 0; i < blob.size(); i += unit_size, j++) {
        os << "Index " << j;
        deal_with_common_op(os, i);
    }

}

vector<string> Dep_graph_desc::get_configuration() {
    configuration.resize(converted_data.size());
    for (int i=0;i<converted_data.size();i++)
    {
        configuration[i] = converted_data[i].op_type;
    }
    return configuration;
}

void Net_desc::generate_file(ostream &os) {
    os << "DLA Net Description\n";
    int index = 0;
    operation_desc_index = deal_with_int16(index);
    surface_desc_index = deal_with_int16(index);
    dependency_graph_index = deal_with_int16(index);
    lut_data_index = deal_with_int16(index);
    roi_array_index = deal_with_int16(index);
    surface_index = deal_with_int16(index);
    stat_list_index = deal_with_int16(index);
    reserved1 = deal_with_int16(index);
    os << "    operation_desc_index : "<<operation_desc_index<<endl;
    os << "    surface_desc_index : "<<operation_desc_index<<endl;
    os << "    dependency_graph_index : "<<dependency_graph_index<<endl;
    os << "    lut_data_index : "<<lut_data_index<<endl;
    os << "    roi_array_index : "<<roi_array_index<<endl;
    os << "    surface_index : "<<surface_index<<endl;
    os << "    stat_list_index : "<<stat_list_index<<endl;
    os << "    reserved1 : ";
    deal_with_array_int16(os,index,DLA_OP_NUM);
    num_rois = deal_with_uint16(index);
    num_operations = deal_with_uint16(index);
    num_luts = deal_with_uint16(index);
    num_addresses = deal_with_uint16(index);
    input_layer = deal_with_int16(index);
    dynamic_roi = deal_with_uint8(index);
    reserved0 = deal_with_uint8(index);

    os << "    num_rois : "<<num_rois<<endl;
    os << "    num_operations : "<<num_operations<<endl;
    os << "    num_luts : "<<num_luts<<endl;
    os << "    num_addresses : "<<num_addresses<<endl;
    os << "    input_layer : "<<input_layer<<endl;
    os << "    dynamic_roi : "<<int(dynamic_roi)<<endl;
    os << "    reserved0 : "<<int(reserved0)<<endl;

}

string Op_desc::deal_with_conv_mode(int &index) {
    switch (deal_with_uint8(index)) {
        case 0: return "CONV_MODE_DIRECT";
        case 1: return "CONV_MODE_WINOGRAD";
        default: return num_to_string(blob[index - 1]);
    }
}

string Op_desc::deal_with_weight_format(int &index) {
    switch (deal_with_uint8(index)) {
        case 0: return "WEIGHT_FORMAT_UNCOMPRESSED";
        case 1: return "WEIGHT_FORMAT_COMPRESSED";
        default: return num_to_string(blob[index - 1]);
    }
}

string Op_desc::deal_with_precision(int &index) {
    switch (deal_with_uint8(index)) {
        case 0: return "PRECISION_INT8";
        case 1: return "PRECISION_INT16";
        case 2: return "PRECISION_FP16";
        default: return num_to_string(blob[index - 1]);
    }
}

string Op_desc::deal_with_activation(int &index) {
    switch (deal_with_uint8(index)) {
        case 0: return "ACTIVATION_NONE";
        case 1: return "ACTIVATION_RELU";
        case 2: return "ACTIVATION_LUT";
        case 3: return "ACTIVATION_PRELU";
        default: return num_to_string(blob[index - 1]);
    }
}

string Op_desc::deal_with_pixel_override(int &index) {
    switch (deal_with_uint8(index)) {
        case 0: return "PIXEL_OVERRIDE_UINT";
        case 1: return "PIXEL_OVERRIDE_INT";
        default: return num_to_string(blob[index - 1]);
    }
}

string Op_desc::deal_with_mean_format(int &index) {
    switch (deal_with_uint8(index)) {
        case 0: return "MEAN_FORMAT_DISABLE";
        case 1: return "MEAN_FORMAT_ENABLE";
        default: return num_to_string(blob[index - 1]);
    }
}

string Op_desc::deal_with_alu_type(int &index) {
    switch (deal_with_uint8(index)) {
        case 0: return "SDP_ALU_OP_MAX";
        case 1: return "SDP_ALU_OP_MIN";
        case 2: return "SDP_ALU_OP_SUM";
        case 3: return "SDP_ALU_OP_EQL";
        default: return num_to_string(blob[index - 1]);
    }
}

string Op_desc::deal_with_sdp_op_type(int &index) {
    switch (deal_with_uint8(index)) {
        case 0: return "SDP_OP_NONE";
        case 1: return "SDP_OP_MUL";
        case 2: return "SDP_OP_ADD";
        case 3: return "SDP_OP_BOTH";
        default: return num_to_string(blob[index - 1]);
    }
}

string Op_desc::deal_with_sdp_op_mode(int &index) {
    switch (deal_with_uint8(index)) {
        case 0: return "SDP_OP_PER_LAYER";
        case 1: return "SDP_OP_PER_CHANNEL";
        case 2: return "SDP_OP_PER_POINT";

        default: return num_to_string(blob[index - 1]);
    }
}

string Op_desc::deal_with_pool_mode(int &index) {
    switch (deal_with_uint8(index)) {
        case 0: return "POOL_MODE_AVG";
        case 1: return "POOL_MODE_MAX";
        case 2: return "POOL_MODE_MIN";
        default: return num_to_string(blob[index - 1]);
    }
}


uint64_t Op_desc::deal_with_pool_size(int &index) {
    return deal_with_uint8(index) + uint8_t(1);
}

string Op_desc::deal_with_dla_format_mode(int &index) {
    switch (deal_with_uint8(index)) {
        case 0: return "FORMAT_T_R8";
        case 1: return "FORMAT_T_R10";
        case 2: return "FORMAT_T_R12";
        case 3: return "FORMAT_T_R16";
        case 4: return "FORMAT_T_R16_I";
        case 5: return "FORMAT_T_R16_F";
        case 6: return "FORMAT_T_A16B16G16R16";
        case 7: return "FORMAT_T_X16B16G16R16";
        case 8: return "FORMAT_T_A16B16G16R16_F";
        case 9: return "FORMAT_T_A16Y16U16V16";
        case 10: return "FORMAT_T_V16U16Y16A16";
        case 11: return "FORMAT_T_A16Y16U16V16_F";
        case 12: return "FORMAT_T_A8B8G8R8";
        case 13: return "FORMAT_T_A8R8G8B8";
        case 14: return "FORMAT_T_B8G8R8A8";
        case 15: return "FORMAT_T_R8G8B8A8";
        case 16: return "FORMAT_T_X8B8G8R8";
        case 17: return "FORMAT_T_X8R8G8B8";
        case 18: return "FORMAT_T_B8G8R8X8";
        case 19: return "FORMAT_T_R8G8B8X8";
        case 20: return "FORMAT_T_A2B10G10R10";
        case 21: return "FORMAT_T_A2R10G10B10";
        case 22: return "FORMAT_T_B10G10R10A2";
        case 23: return "FORMAT_T_R10G10B10A2";
        case 24: return "FORMAT_T_A2Y10U10V10";
        case 25: return "FORMAT_T_V10U10Y10A2";
        case 26: return "FORMAT_T_A8Y8U8V8";
        case 27: return "FORMAT_T_V8U8Y8A8";
        case 28: return "FORMAT_T_Y8___U8V8_N444";
        case 29: return "FORMAT_T_Y8___V8U8_N444";
        case 30: return "FORMAT_T_Y10___U10V10_N444";
        case 31: return "FORMAT_T_Y10___V10U10_N444";
        case 32: return "FORMAT_T_Y12___U12V12_N444";
        case 33: return "FORMAT_T_Y12___V12U12_N444";
        case 34: return "FORMAT_T_Y16___U16V16_N444";
        case 35: return "FORMAT_T_Y16___V16U16_N444";
        case 36: return "FORMAT_FEATURE";
        default: return num_to_string(blob[index - 1]);
    }
}

void Op_desc::deal_with_cvt_param(ostream &os, int &index, int sub_level) {
    os << "Dla_Cvt_Param\n";
    out_put_tab(os, sub_level);
    os << "scale : " << deal_with_int16(index) << endl;
    out_put_tab(os, sub_level);
    os << "truncate : " << deal_with_uint8(index) << endl;
    out_put_tab(os, sub_level);
    os << "enable : " << deal_with_uint8(index) << endl;
    out_put_tab(os, sub_level);
    os << "offset : " << deal_with_int32(index) << endl;



}

void Op_desc::deal_with_dla_sdp_cvt(ostream &os, int &index, int sub_level) {
    os << "Dla_SDP_CVT\n";
    out_put_tab(os, sub_level);
    os << "alu_cvt : ";
    deal_with_cvt_param(os, index, sub_level + 1);
    out_put_tab(os, sub_level);
    os << "mul_cvt : ";
    deal_with_cvt_param(os, index, sub_level + 1);
}

void Op_desc::deal_with_sdp_op(ostream &os, int &index, int sub_level) {
    os << "DLA_SDP_OP\n";
    out_put_tab(os, sub_level);
    os << "enable : " << deal_with_uint8(index) << endl;
    out_put_tab(os, sub_level);
    os << "alu_type : " << deal_with_alu_type(index) << endl;
    out_put_tab(os, sub_level);
    os << "type : " << deal_with_sdp_op_type(index) << endl;
    out_put_tab(os, sub_level);
    os << "mode : " << deal_with_sdp_op_mode(index) << endl;
    out_put_tab(os, sub_level);
    os << "act : " << deal_with_activation(index) << endl;
    out_put_tab(os, sub_level);
    os << "left_shift_val : " << deal_with_uint8(index) << endl;
    out_put_tab(os, sub_level);
    os << "truncate : " << deal_with_uint8(index) << endl;
    out_put_tab(os, sub_level);
    os << "precision : " << deal_with_precision(index) << endl;
    out_put_tab(os, sub_level);
    os << "alu_operand : " << deal_with_int32(index) << endl;
    out_put_tab(os, sub_level);
    os << "mul_operand : " << deal_with_int32(index) << endl;
    out_put_tab(os, sub_level);
    os << "cvt : ";
    deal_with_dla_sdp_cvt(os, index, sub_level + 1);




}

void Op_desc::generate_conv_desc(ostream &os, int index) {
    os << " Convolution Operation description\n";
    os << "    " << "/* Performance parameters */ \n";
    os << "    conv_mode : " << deal_with_conv_mode(index) << endl;
    os << "    data_reuse : " << deal_with_uint8(index) << endl;
    os << "    weight_reuse : " << deal_with_uint8(index) << endl;
    os << "    skip_data_rls : " << deal_with_uint8(index) << endl;
    os << "    skip_weight_rls : " << deal_with_uint8(index) << endl;
    os << "    reserved0 : " << deal_with_uint8(index) << endl;
    os << "    entry_per_slice : " << deal_with_uint16(index) << endl;
    os << "    data_format : " << deal_with_dla_format_mode(index) << endl;
    os << "    pixel_mapping : " << deal_with_uint8(index) << endl;
    os << "    fetch_grain : " << deal_with_uint16(index) << endl;
    os << "    reserved_b : ";
    deal_with_array(os, index, 8);
    os << "    batch : " << deal_with_uint8(index) << endl;
    os << "    weight_format : " << deal_with_weight_format(index) << endl;
    os << "    data_bank : " << deal_with_uint8(index) << endl;
    os << "    weight_bank : " << deal_with_uint8(index) << endl;
    os << "    batch_stride : " << deal_with_uint32(index) << endl;
    os << "    post_extension : " << deal_with_uint8(index) << endl;
    os << "    pixel_override : " << deal_with_pixel_override(index) << endl;
    os << "    release : " << deal_with_uint16(index) << endl;
    os << "    input_width_csc : " << deal_with_uint16(index) << endl;
    os << "    input_height_csc : " << deal_with_uint16(index) << endl;
    os << "    input_channel_csc : " << deal_with_uint16(index) << endl;
    os << "    kernel_width_csc : " << deal_with_uint16(index) << endl;
    os << "    kernel_height_csc : " << deal_with_uint16(index) << endl;
    os << "    kernel_channel_csc : " << deal_with_uint16(index) << endl;
    os << "    input_width_cmac : " << deal_with_uint16(index) << endl;
    os << "    input_height_cmac : " << deal_with_uint16(index) << endl;
    os << "    bytes_per_kernel : " << deal_with_uint32(index) << endl;

    os << "    " << "/* Algorithm parameters */ \n";

    os << "    mean_ry : " << deal_with_int16(index) << endl;
    os << "    mean_gu : " << deal_with_int16(index) << endl;
    os << "    mean_bv : " << deal_with_int16(index) << endl;
    os << "    mean_ax : " << deal_with_int16(index) << endl;
    os << "    mean_format : " << deal_with_mean_format(index) << endl;
    os << "    conv_stride_x : " << deal_with_uint8(index) << endl;
    os << "    conv_stride_y : " << deal_with_uint8(index) << endl;
    os << "    pad_x_left : " << deal_with_uint8(index) << endl;
    os << "    pad_x_right : " << deal_with_uint8(index) << endl;
    os << "    pad_y_top : " << deal_with_uint8(index) << endl;
    os << "    pad_y_bottom : " << deal_with_uint8(index) << endl;
    os << "    dilation_x : " << deal_with_uint8(index) << endl;
    os << "    dilation_y : " << deal_with_uint8(index) << endl;
    os << "    reserved2 : ";
    deal_with_array(os, index, 2);

    os << "    pra_truncate : " << deal_with_uint8(index) << endl;
    os << "    in_precision : " << deal_with_precision(index) << endl;
    os << "    out_precision : " << deal_with_precision(index) << endl;
    os << "    pad_val : " << deal_with_int16(index) << endl;
    os << "    in_cvt : ";
    deal_with_cvt_param(os, index, 2);
    os << "    out_cvt : ";
    deal_with_cvt_param(os, index, 2);




}

void Op_desc::generate_sdp_desc(ostream &os, int index) {
    os << " SDP Operation description\n";
    os << "    /* Precision parameters */\n";
    os << "    src_precision : " << deal_with_precision(index) << endl;
    os << "    dst_precision : " << deal_with_precision(index) << endl;
    os << "    lut_index : " << deal_with_int16(index) << endl;
    os << "    out_cvt : ";
    deal_with_cvt_param(os, index, 2);
    os << "    /* Performance parameters */\n";
    os << "    conv_mode : " << deal_with_conv_mode(index) << endl;
    os << "    batch_num : " << deal_with_uint8(index) << endl;
    os << "    reserved0 : " << deal_with_uint16(index) << endl;
    os << "    batch_stride : " << deal_with_uint32(index) << endl;
    os << "    /* Algorithm parameters */\n";
    os << "    x1_op : ";
    deal_with_sdp_op(os, index, 2);
    os << "    x2_op : ";
    deal_with_sdp_op(os, index, 2);
    os << "    y_op : ";
    deal_with_sdp_op(os, index, 2);


}

void Op_desc::generate_cdp_desc(ostream &os, int index) {
    os << " CDP Operation description\n";
    os << "    /* Precision parameters */\n";
    os << "    in_precision : " << deal_with_precision(index) << endl;
    os << "    out_precision : " << deal_with_precision(index) << endl;
    os << "    lut_index : " << deal_with_int16(index) << endl;
    os << "    in_cvt : ";
    deal_with_cvt_param(os, index, 2);
    os << "    out_cvt : ";
    deal_with_cvt_param(os, index, 2);
    os << "    /* Algorithm parameters */\n";
    os << "    local_size : " << deal_with_uint8(index) << endl;
    os << "    bypass_sqsum : " << deal_with_uint8(index) << endl;
    os << "    bypass_out_mul : " << deal_with_uint8(index) << endl;
    os << "    reserved0 : " << deal_with_uint8(index) << endl;


}

string Op_desc::deal_with_rubik_mode(int &index) {
    switch (deal_with_uint8(index)) {
        case 0: return "RUBIK_MODE_CONTRACT";
        case 1: return "RUBIK_MODE_SPLIT";
        case 2: return "RUBIK_MODE_MERGE";

        default: return num_to_string(blob[index - 1]);
    }
}

void Op_desc::generate_file(ostream &os) {
    for (int i = 0, j = 0; i<blob.size(), j<configuration.size(); i += unit_size, j++)
    {
        os << "Index " << j;
        if (configuration[j] == "Convolution")
            generate_conv_desc(os, i);
        else if (configuration[j] == "SDP")
            generate_sdp_desc(os, i);
        else if (configuration[j] == "PDP")
            generate_pdp_desc(os, i);
        else if (configuration[j] == "CDP")
            generate_cdp_desc(os, i);
        else if (configuration[j] == "Rubik")
            generate_rubik_desc(os, i);
        else if (configuration[j] == "BDMA")
            generate_bdma_desc(os, i);
        else
            std::cout << configuration[j];
    }

}

void Op_desc::generate_pdp_desc(ostream &os, int index) {
    os << " PDP Operation description\n";
    os << "    /* Performance parameters */\n";
    os << "    partial_in_width_first : " << deal_with_uint16(index) << endl;
    os << "    partial_in_width_mid : " << deal_with_uint16(index) << endl;
    os << "    partial_in_width_last : " << deal_with_uint16(index) << endl;
    os << "    partial_width_first : " << deal_with_uint16(index) << endl;
    os << "    partial_width_mid : " << deal_with_uint16(index) << endl;
    os << "    partial_width_last : " << deal_with_uint16(index) << endl;
    os << "    split_num : " << deal_with_uint8(index) << endl;
    os << "    /* Algorithm parameters */\n";
    os << "    pool_mode : " << deal_with_pool_mode(index) << endl;
    os << "    pool_width : " << deal_with_pool_size(index) << endl;
    os << "    pool_height : " << deal_with_pool_size(index) << endl;
    os << "    stride_x : " << deal_with_uint8(index) << endl;
    os << "    stride_y : " << deal_with_uint8(index) << endl;
    os << "    pad_left : " << deal_with_uint8(index) << endl;
    os << "    pad_right : " << deal_with_uint8(index) << endl;
    os << "    pad_top : " << deal_with_uint8(index) << endl;
    os << "    pad_bottom : " << deal_with_uint8(index) << endl;
    os << "    /* Precision parameters */\n";
    os << "    precision : " << deal_with_precision(index) << endl;
    os << "    reserved0 : " << deal_with_uint8(index) << endl;
    os << "    padding_value : ";
    deal_with_array_int32(os, index, 7);
}

void Op_desc::generate_bdma_desc(ostream &os, int index) {
    os << " BDMA Operation description\n";
    os << "    /* Precision parameters */\n";
    os << "    num_transfers : " << deal_with_uint16(index) << endl;
    os << "    reserved0 : " << deal_with_uint16(index) << endl;

}

void Op_desc::generate_rubik_desc(ostream &os, int index) {
    os << " Rubik Operation description\n";
    os << "    /* Precision parameters */\n";
    os << "    mode : " << deal_with_rubik_mode(index) << endl;
    os << "    precision : " << deal_with_precision(index) << endl;
    os << "    stride_x : " << deal_with_uint8(index) << endl;
    os << "    stride_y : " << deal_with_uint8(index) << endl;

}

void Weight_data::generate_file(ostream &os) {
    read_raw_data();
    h = 7;
    w = 7;
    c = 3;
    k = 64;
    kernel_per_group = 16;
    out_put_data(os);
}

void Weight_data::out_put_data(ostream &os) {

    for(int i=0;i<original_data.size();i++)
    {

        os<<original_data[i]<<" ";
    }



}

void Weight_data::out_put_weight_data(ostream &os) {
    vector<int> index_list(static_cast<unsigned long>(h) * w * c * k);

    //ceil
    int group_num = (k+(kernel_per_group-1))/kernel_per_group;
    int group_size = h*w*c*kernel_per_group;

    //Can visit this website to figure out how weight data are organized.
    //
    for(int i=0;i<index_list.size();i++)
    {
        if(i%w == 0)
            os<<endl;
        int group_index = i/group_size;
        int current_group_size =group_size;
        if(group_index == group_num -1)
            current_group_size = group_num%kernel_per_group;
        int group_reminder = i%current_group_size;
        int kernel_index = group_reminder/h/w;
        int kernel_remainder = group_reminder%(h*w);
        os<<original_data[group_index*current_group_size +  kernel_remainder* kernel_per_group*c + kernel_index]<<" ";
    }



}

void Weight_data::out_put_bn_data(ostream &os) {

    vector<half_float::half> variance;
    for(int i=0;i<original_data.size();i++)
    {
        if(!(i%2))

            os<<-original_data[i]<<" ";
    }
    os<<endl;
    for(int i=0;i<original_data.size();i++)
    {
        if(i%2)

            os<<(1/original_data[i])*(1/original_data[i])<<" ";
    }

}

void Weight_data::out_put_scale_data_former(ostream &os) {

    vector<half_float::half> variance;
    for(int i=0;i<original_data.size();i++)
    {
        if(!(i%2))
            os<<original_data[i]<<" ";
    }


}
