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
  auto memory_list = loadable->memory_list();
  for(auto it = memory_list->begin(); it != memory_list->end(); it++){
    auto MemoryListEntry = *it;
    auto id = MemoryListEntry->id();
    auto domain = MemoryListEntry->domain();
    auto flags = MemoryListEntry->flags();
    auto size = MemoryListEntry->size();
    auto alignment = MemoryListEntry->alignment();
    auto contents = MemoryListEntry->contents();
    auto offsets = MemoryListEntry->offsets();
    auto bind_id = MemoryListEntry->bind_id();
    auto tensor_desc_id = MemoryListEntry->tensor_desc_id();

    std::cout << "Loadable MemoryListEntry : " << std::endl;
    std::cout << "id : " << id << std::endl;
    std::cout << "domain { SYSTEM = 0, SRAM = 1 } : " << domain << std::endl;
    std::cout << "flags { NONE = 0, ALLOC = 1, SET = 2, INPUT = 4, OUTPUT = 8 } : "
              << flags << std::endl;
    std::cout << "size : " << size << std::endl;
    std::cout << "alignment : " << alignment << std::endl;

    std::cout << "contents size " << contents->size() << " : ";
    for(auto c_it = contents->begin(); c_it != contents->end(); c_it++)
      std::cout << (*c_it)->c_str() << " ";
    std::cout << std::endl;

    std::cout << "offsets size " << offsets->size() << " : ";
    for(auto o_it = offsets->begin(); o_it != offsets->end(); o_it++)
      std::cout << *o_it << " ";
    std::cout << std::endl;

    std::cout << "bind_id : " << bind_id << std::endl;
    std::cout << "tensor_desc_id : " << tensor_desc_id << std::endl;

    std::cout << std::endl;
  }

  return 0;
}