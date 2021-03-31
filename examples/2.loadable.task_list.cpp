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
  for(auto it = task_list->begin(); it != task_list->end(); it++){
    auto TaskListEntry = *it;
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