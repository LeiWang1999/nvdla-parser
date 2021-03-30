//
// Created by Deng Weijia on 8/27/18.
// This file reference structure information from the nvdla/sw project
// https://github.com/nvdla/sw
//

#include "Global_desc.h"

#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>
#include <fstream>
#include "tools.h"

#include "tools.h"
#include "external/half.h"

using std::istream;
using std::ostream;
using std::vector;
using std::string;
using std::istringstream;
using std::ostringstream;
using std::unordered_map;
using std::endl;

Addr_list::Addr_list(const nvdla::loadable::Loadable *loadable) {
    auto address_list = loadable->address_list();
    for(int i = 0; i<address_list->size();i++){
        auto entry = address_list->Get(i);
        index_dict.emplace( std::pair<int,int>(entry->id(),entry->mem_id()) );
    }
}

Mem_list::Mem_list(const nvdla::loadable::Loadable  *loadable) {
    auto mem_list = loadable->memory_list();
    for(int i = 0; i<mem_list->size();i++){
        auto entry = mem_list->Get(i);
        if(entry->contents()->size())
            alias_dict.emplace(std::pair<int,string>(entry->id(),entry->contents()->Get(0)->c_str()));
    }

}


void Desc_base::read_configuration(vector<string> const & layer_type){

    configuration = layer_type;
}

void Desc_base::read_data(nvdla::loadable::Blob const * input_blob) {
    for(int i = 0; i < input_blob->size();i++)
    {
        blob.emplace_back(input_blob->data()->Get(i));
    }
}

float Desc_base::deal_with_float32(int &index) {
    uint32_t data = deal_with_uint32(index);
    auto * pointer = (float *) & data;
    return * pointer;
}

void Desc_base::out_put_tab(ostream &os, int num) {
    while (num >= 0) {
        os << "    ";
        num--;
    }
}

uint16_t Desc_base::deal_with_uint16(int &index) {
    index += 2;
    return (static_cast<uint16_t>(blob[index - 1]) << 8u) + blob[index - 2];
}

uint32_t Desc_base::deal_with_uint32(int &index) {
    index += 4;
    return (static_cast<uint32_t>(blob[index - 1]) << 24u) +
           (static_cast<uint32_t>(blob[index - 2]) << 16u) +
           (static_cast<uint32_t>(blob[index - 3]) << 8u) +
           blob[index - 4];
}

int32_t Desc_base::deal_with_int32(int &index) {
    return static_cast<int32_t>(deal_with_uint32(index));
}

int64_t Desc_base::deal_with_int64(int &index) {
    uint64_t low = deal_with_uint32(index);
    uint64_t high = deal_with_uint32(index);
    return static_cast<int64_t>(low + (high << 32u));
}

void Desc_base::deal_with_array(ostream &os, int &index, int array_size) {
    os << "[ ";
    for (int i = 0; i<array_size - 1; i++) {
        os << deal_with_uint8(index) << " , ";
    }
    os << deal_with_uint8(index) << " ]\n";
}

void Desc_base::deal_with_array_int16(ostream &os, int &index, int array_size) {
    os << "[ ";
    for (int i = 0; i<array_size - 1; i++) {
        os << deal_with_int16(index) << " , ";
    }
    os << deal_with_int16(index) << " ]\n";
}

void Desc_base::deal_with_array_int32(ostream &os, int &index, int array_size) {
    os << "[ ";
    for (int i = 0; i<array_size - 1; i++) {
        os << deal_with_int32(index) << " , ";
    }
    os << deal_with_int32(index) << " ]\n";
}

half_float::half Desc_base::deal_with_float16(int &index) {
    uint16_t data = deal_with_uint16(index);
    auto * pointer = (half_float::half *) & data;
    return *pointer;
}