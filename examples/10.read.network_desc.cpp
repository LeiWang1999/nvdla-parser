//
// Created by 王磊 on 2021/3/31.
//


#include <string>
#include <iostream>
#include "external/loadable_generated.h"
#include "tools.h"
#include "Interface.h"
#include "driver.h"

using namespace nvdla::loadable;

int main(){
  flatbuffers::FlatBufferBuilder builder;
  const std::string filename = "../../data/lenet-mnist-caffe/fast-math.nvdla";

  if(!is_file_exists(filename)) {
    std::cout << "Read File Failed" << std::endl;
    return -1;
  }

  auto loadable = get_loadable(filename);
  Driver driver(loadable);
  auto task_list = loadable->task_list();
  auto root_address_list = loadable->address_list();
  auto root_memory_list = loadable->memory_list();
  auto blobs = loadable->blobs();
  for(auto TaskListEntry : *task_list){
    std::cout << "Task Id :" << TaskListEntry->id() << std::endl;

    auto address_idx = TaskListEntry->address_list()->Get(0);
    std::cout << address_idx  << " : ";
    auto memory_idx = root_address_list->Get(address_idx)->mem_id();

    std::string contents_name;
    if(root_memory_list->Get(memory_idx)->contents()->size())
      contents_name = root_memory_list->Get(memory_idx)->contents()->Get(0)->c_str();
    std::cout << (contents_name.size()?contents_name:"noname") << std::endl;
    int blob_idx = 0;
    for (auto b : *blobs){
      if(!strcmp(b->name()->c_str(), contents_name.c_str())) break;
      blob_idx++;
    }
    std::cout << "Blob index : " << blob_idx << std::endl;

    auto blob = blobs->Get(blob_idx);

    struct dla_network_desc * net_desc = (struct dla_network_desc *) blob->data()->data();
    std::cout << net_desc->operation_desc_index << std::endl;

    std::cout << std::endl;
  }

  return 0;
}