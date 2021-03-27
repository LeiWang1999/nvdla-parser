//
// Created by Deng Weijia on 8/23/18.
// The interactive interface reference some code from the nvdla/sw project
// https://github.com/nvdla/sw
//
///Provide a structure that stores all test information


#ifndef NVDLA_DEPICTER_MAIN_H
#define NVDLA_DEPICTER_MAIN_H

#include <string>



//Default test arguments.
struct Test_app_args
{
    std::string inputName;
    std::string outputPath;
    std::string outputName;
    std::string format;
    bool show_help;

    Test_app_args() :
            inputName(""),
            outputPath("output/"),
            outputName(""),
            format("pdf") ,
            show_help(false)

    {}
};


#endif //NVDLA_DEPICTER_MAIN_H
