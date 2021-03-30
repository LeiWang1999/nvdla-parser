//
// Created by Deng Weijia on 8/27/18.
// This file reference some information about how blobs are organized from the nvdla/sw project
// https://github.com/nvdla/sw
//

#include "EMU_desc.h"

using std::ostream;
using std::string;
using std::endl;
using std::vector;

void EMU_Net_desc::deal_with_EMU_Net_desc(ostream &os, int i) {
    operation_desc_index = deal_with_int16(i);
    os<<"operation_desc_index : "<<operation_desc_index<<endl;
    operation_buffer_desc_index = deal_with_int16(i);
    os<<"operation_buffer_desc_index : "<<operation_buffer_desc_index<<endl;
    num_operations = deal_with_uint16(i);
    os<<"num_operations : "<<num_operations<<endl;

}

void EMU_Net_desc::generate_file(ostream &os) {
    for (int i = 0, j = 0; i < blob.size(); i += unit_size, j++) {
        deal_with_EMU_Net_desc(os,i);
    }
}

string EMU_Op_desc::deal_with_op_type(int &index) {
    switch (deal_with_uint8(index)) {
        case 0:
            configuration.emplace_back("EMU_Power");
            return "NVDLA_EMU_OP_POWER";
        case 1:
            configuration.emplace_back("EMU_Softmax");
            return "NVDLA_EMU_OP_SOFTMAX";
        default: return num_to_string(blob[index - 1]);
    }
}

void EMU_Op_desc::generate_softmax_desc(ostream &os, int i, int sub_level) {
    os << " Softmax Operation description\n";
    out_put_tab(os, sub_level);

    os<<"op_type : "<<deal_with_op_type(i)<<endl;
    out_put_tab(os, sub_level);

    os<<"axis : "<<deal_with_int16(i)<<endl;

}

void EMU_Op_desc::generate_power_desc(ostream &os, int i,int sub_level) {

    os << "Power Operation description\n";
    out_put_tab(os, sub_level);
    os<<"op_type : "<<deal_with_op_type(i)<<endl;
    out_put_tab(os, sub_level);
    os<<"power : "<<deal_with_float32(i)<<endl;
    out_put_tab(os, sub_level);
    os<<"axis : "<<deal_with_float32(i)<<endl;
    out_put_tab(os, sub_level);
    os<<"shift : "<<deal_with_float32(i)<<endl;

}

void EMU_Op_desc::generate_file(ostream &os) {
    for (int i = 0, j = 0; i<blob.size(); i += unit_size, j++)
    {
        os << "Index " << j;
        switch (figure_out_op_type(i)){
            case 0: generate_power_desc(os, i, 1);
                break;
            case 1: generate_softmax_desc(os, i, 1);
                break;
            default:
                break;
        }

    }

}

void EMU_Op_buf::deal_with_emu_buffer_desc(ostream &os, int index, int sub_level, int key) {
    os << "Emu_buffer_desc\n";
    out_put_tab(os, sub_level);
    int addr_index = deal_with_int16(index);
    if(key)
        dest_list.back().emplace_back(addr_index);
    else
        source_list.back().emplace_back(addr_index);

    os << "addressIndex : " <<  addr_index<< endl;
    out_put_tab(os, sub_level);
    os << "size : " << deal_with_uint32(index) << endl;
    out_put_tab(os, sub_level);
    os << "format : " << deal_with_uint16(index) << endl;

    out_put_tab(os, sub_level);
    os << "/* cube dimensions */\n";
    out_put_tab(os, sub_level);
    os << "width : " << deal_with_uint16(index) << endl;
    out_put_tab(os, sub_level);
    os << "height : " << deal_with_uint16(index) << endl;
    out_put_tab(os, sub_level);
    os << "channel : " << deal_with_uint16(index) << endl;
    out_put_tab(os, sub_level);
    os << "/* stride information */\n";
    out_put_tab(os, sub_level);
    os << "line_stride : " << deal_with_uint32(index) << endl;
    out_put_tab(os, sub_level);
    os << "surf_stride : " << deal_with_uint32(index) << endl;



}

void EMU_Op_buf::generate_file(ostream &os) {
    for (int i = 0, j = 0; i<blob.size(); i += unit_size, j++)
    {
        os << "Buffers description "<<j<<endl;
        if (!j%2) {
            source_list.emplace_back(vector<int>());
            dest_list.emplace_back(vector<int>());
            os << "  src_data ";
        }
        else
            os<< "  dst_data ";
        deal_with_emu_buffer_desc(os,i,1,j%2);
    }

}
