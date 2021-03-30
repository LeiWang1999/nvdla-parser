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
  const std::string filename = "/Users/wanglei/nvdla-depicter/data/lenet-mnist-caffe/fast-math.nvdla";

  if(!is_file_exists(filename)) {
    std::cout << "Read File Failed" << std::endl;
    return -1;
  }

  auto loadable = get_loadable(filename);
  auto memory_list = loadable->memory_list();
  for(auto it = memory_list->begin(); it != memory_list->end(); it++){
    auto MemoryListEntry = *it;
    auto domain = MemoryListEntry->domain();
    auto flags = MemoryListEntry->flags();

    std::cout << "Loadable MemoryListEntry : " << std::endl;
    std::cout << "id : " << MemoryListEntry->id() << std::endl;
    std::cout << "domain : " << MemoryListEntry->id() << std::endl;

    std::cout << "interface（enum Interface : uint { NONE = 0, DLA1 = 1, EMU1 = 2 }） : "
              << TaskListEntry->interface() << std::endl;
    std::cout << "instance : " << TaskListEntry->instance() << std::endl;

    std::cout << "address_list : ";
    for(auto a_it = address_list->begin(); a_it != address_list->end(); a_it++)
      std::cout << *a_it << " ";
    std::cout << std::endl;

    std::cout << "pre_actions : ";
    for(auto pre_it = pre_actions->begin(); pre_it != pre_actions->end(); pre_it++)
      std::cout << *pre_it << " ";
    std::cout << std::endl;

    std::cout << "post_actions List : ";
    for(auto pos_it = post_actions->begin(); pos_it != post_actions->end(); pos_it++)
      std::cout << *pos_it << " ";
    std::cout << std::endl << std::endl;
  }

  return 0;
}