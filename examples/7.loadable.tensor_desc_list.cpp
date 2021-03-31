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
    auto tensor_desc_list = loadable->tensor_desc_list();
    for(auto TensorDescListEntry : *tensor_desc_list){
        auto name = TensorDescListEntry->name();
        auto id = TensorDescListEntry->id();
        auto size = TensorDescListEntry->size();
        auto offset = TensorDescListEntry->offset();
        auto data_format = TensorDescListEntry->data_format();
        auto data_type = TensorDescListEntry->data_type();
        auto data_category = TensorDescListEntry->data_category();
        auto pixel_format = TensorDescListEntry->pixel_format();
        auto pixel_mapping = TensorDescListEntry->pixel_mapping();

        auto n = TensorDescListEntry->n();
        auto c = TensorDescListEntry->c();
        auto w = TensorDescListEntry->w();
        auto h = TensorDescListEntry->h();

        auto stride_0 = TensorDescListEntry->stride_0();
        auto stride_1 = TensorDescListEntry->stride_1();
        auto stride_2 = TensorDescListEntry->stride_2();
        auto stride_3 = TensorDescListEntry->stride_3();
        auto stride_4 = TensorDescListEntry->stride_4();
        auto stride_5 = TensorDescListEntry->stride_5();
        auto stride_6 = TensorDescListEntry->stride_6();
        auto stride_7 = TensorDescListEntry->stride_7();

        std::cout << "Loadable tensor_desc_list : " << std::endl;
        std::cout << "name : " << name->c_str() << std::endl;
        std::cout << "id : " << id << std::endl;
        std::cout << "size : " << size << std::endl;
        std::cout << "offset : " << offset << std::endl;
        std::cout << "data_format { UNKNOWN = 0, NCHW = 1, NHWC = 2 } : " << data_format << std::endl;
        std::cout << "data_type { UNKNOWN = 0, FLOAT = 1, HALF = 2, INT16 = 3, INT8 = 4 } : " << data_type << std::endl;
        std::cout << "data_category { IMAGE = 0, WEIGHT = 1, FEATURE = 2, PLANAR = 3, BIAS = 4 } : " << data_category << std::endl;
        std::cout << "pixel_format {\n"
                     "    R8 = 0,\n"
                     "    R10 = 1,\n"
                     "    R12 = 2,\n"
                     "    R16 = 3,\n"
                     "    R16_I = 4,\n"
                     "    R16_F = 5,\n"
                     "    A16B16G16R16 = 6,\n"
                     "    X16B16G16R16 = 7,\n"
                     "    A16B16G16R16_F = 8,\n"
                     "    A16Y16U16V16 = 9,\n"
                     "    V16U16Y16A16 = 10,\n"
                     "    A16Y16U16V16_F = 11,\n"
                     "    A8B8G8R8 = 12,\n"
                     "    A8R8G8B8 = 13,\n"
                     "    B8G8R8A8 = 14,\n"
                     "    R8G8B8A8 = 15,\n"
                     "    X8B8G8R8 = 16,\n"
                     "    X8R8G8B8 = 17,\n"
                     "    B8G8R8X8 = 18,\n"
                     "    R8G8B8X8 = 19,\n"
                     "    A2B10G10R10 = 20,\n"
                     "    A2R10G10B10 = 21,\n"
                     "    B10G10R10A2 = 22,\n"
                     "    R10G10B10A2 = 23,\n"
                     "    A2Y10U10V10 = 24,\n"
                     "    V10U10Y10A2 = 25,\n"
                     "    A8Y8U8V8    = 26,\n"
                     "    V8U8Y8A8    = 27,\n"
                     "    Y8_U8V8_N444 = 28,\n"
                     "    Y8_V8U8_N444 = 29,\n"
                     "    Y10_U10V10_N444 = 30,\n"
                     "    Y10_V10U10_N444 = 31,\n"
                     "    Y12_U12V12_N444 = 32,\n"
                     "    Y12_V12U12_N444 = 33,\n"
                     "    Y16_U16V16_N444 = 34,\n"
                     "    Y16_V16U16_N444 = 35,\n"
                     "    FEATURE = 36\n"
                     "} : " << pixel_format << std::endl;
        std::cout << "pixel_mapping { PITCH_LINEAR = 0, INVALID_PIXEL_MAP = 1 } : " << pixel_mapping << std::endl;
        std::cout << "n : " << n << std::endl;
        std::cout << "c : " << c << std::endl;
        std::cout << "w : " << w << std::endl;
        std::cout << "h : " << h << std::endl;
        std::cout << "stride_0 : " << stride_0 << std::endl;
        std::cout << "stride_1 : " << stride_1 << std::endl;
        std::cout << "stride_2 : " << stride_2 << std::endl;
        std::cout << "stride_3 : " << stride_3 << std::endl;
        std::cout << "stride_4 : " << stride_4 << std::endl;
        std::cout << "stride_5 : " << stride_5 << std::endl;
        std::cout << "stride_6 : " << stride_6 << std::endl;
        std::cout << "stride_7 : " << stride_7 << std::endl;

        std::cout << std::endl;
    }

    return 0;
}