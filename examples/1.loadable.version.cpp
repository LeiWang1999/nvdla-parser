//
// Created by 王磊 on 2021/3/30.
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

  std::cout << "Loadable Version is "
            << (unsigned int )loadable->version()->major()
            << "."
            << (unsigned int )loadable->version()->minor()
            << "."
            << (unsigned int )loadable->version()->sub_minor() << std::endl;
  return 0;
}