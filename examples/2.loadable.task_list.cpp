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
  auto task_list = loadable->task_list();
  for(auto TaskListEntry : *task_list){
    auto id = TaskListEntry->id();
    auto interface = TaskListEntry->interface();
    auto instance = TaskListEntry->instance();
    auto address_list = TaskListEntry->address_list();
    auto pre_actions = TaskListEntry->pre_actions();
    auto post_actions = TaskListEntry->post_actions();

    std::cout << "Loadable TaskListEntry : " << std::endl;
    std::cout << "id : " << id << std::endl;
    std::cout << "interface { NONE = 0, DLA1 = 1, EMU1 = 2 } : "
              << interface << std::endl;
    std::cout << "instance : " << instance << std::endl;

    std::cout << "address_list : ";
    for(auto ad :*address_list)
      std::cout << ad << " ";
    std::cout << std::endl;

    std::cout << "pre_actions : ";
    for(auto pr : *pre_actions)
      std::cout << pr << " ";
    std::cout << std::endl;

    std::cout << "post_actions List : ";
    for(auto po : *post_actions)
      std::cout << po << " ";
    std::cout << std::endl << std::endl;
  }

  return 0;
}