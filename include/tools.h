
//
// Created by Deng Weijia on 8/27/18.
//
/**
*Provide basic tools for the facilitation of this project
*/


#ifndef NVDLA_DEPICTER_TOOLS_H
#define NVDLA_DEPICTER_TOOLS_H


#pragma once
#include<cmath>
#include<vector>
#include<string>
#include<sstream>
#include<iostream>
#include <random>
#include <cstring>


//Generate random string used for temp file name.
std::string get_random_name();

//Test whether a file exists.
int is_file_exists(const std::string & path);

//Test whether a folder exists.
int is_folder_exist(const std::string & path);





template<typename T>
std::string num_to_string(T num) {
    std::ostringstream oss;
    oss << num;
    return oss.str();
}

#endif //NVDLA_DEPICTER_TOOLS_H
