//
// Created by 王磊 on 2021/3/29.
//
#include <string>
#include <unistd.h>
#include "external/loadable_generated.h"
#include <iostream>

using namespace nvdla::loadable;

int main(){
  flatbuffers::FlatBufferBuilder builder;
  const std::string filename = "/Users/wanglei/nvdla-depicter/data/lenet-mnist-caffe/fast-math.nvdla";

  if(access(filename.c_str(), F_OK)) {
    std::cout << "Read File Failed" << std::endl;
    return -1;
  }
  FILE* file = fopen(filename.c_str(), "rb");
  fseek(file, 0L, SEEK_END);
  int length = ftell(file);
  fseek(file, 0L, SEEK_SET);
  char *data = new char[length];
  fread(data, sizeof(char), length, file);
  fclose(file);
  // Check whether the file is a loadable file.
  flatbuffers::Verifier verifier(reinterpret_cast<const uint8_t *>(data), length);
  if(!nvdla::loadable::VerifyLoadableBuffer(verifier))
    //File is not a loadable file
    return -1;
  // Get access to the root:
  auto loadable = GetLoadable(data);

  std::cout << loadable->version()->major() << std::endl;
  std::cout << loadable->task_list()->size() << std::endl;
  std::cout << loadable->memory_list()->size() << std::endl;
  std::cout << loadable->address_list()->size()<< std::endl;
  std::cout << loadable->event_list()->size() << std::endl;
  std::cout << loadable->reloc_list()->size() << std::endl;
  std::cout << loadable->submit_list()->size() << std::endl;
  std::cout << loadable->blobs()->size() << std::endl;
  return 0;
}