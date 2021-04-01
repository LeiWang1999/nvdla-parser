//
// Created by 王磊 on 2021/4/1.
//

#ifndef NVDLA_DEPICTER_PROJECT_PARSER_H
#define NVDLA_DEPICTER_PROJECT_PARSER_H

#include "Interface.h"
#include <unordered_map>

//Class that contains information from addr_list that is useful when drawing process graph.
class Addr_list{
public:
  //Addr_list is a surjection of mem_list.
  //This hash table records the detailed projection.
  std::unordered_map<int,int> index_dict;
  explicit Addr_list(nvdla::loadable::Loadable const * loadable);
};

//Class that contains information from mem_list that is useful when drawing process graph.
class Mem_list{
public:
  //Mem_list is an injection of addr_list
  //Mem_block that the value has been set in the loadable file  has a name.
  std::unordered_map<int,std::string> alias_dict;
  explicit Mem_list(nvdla::loadable::Loadable const * loadable);

};

class Parser {

  struct dla_network_desc * network_desc;
  struct dla_common_op_desc * common_op_desc;
  union dla_surface_container * surface_desc;
  union dla_operation_container * operation_desc;

  nvdla::loadable::Loadable const * loadable;
  Addr_list address_list;
  Mem_list memory_list;

  std::string get_name (int address_idx);
  int get_blob_index(std::string const & str);
  int find_address_blobs_index(int address_idx);
  int find_blobs_index_from_task(int task_idx, int address_idx);
  const unsigned char * get_blob_data_pointer(int blob_idx);
  bool parse_network_desc(int blob_idx);
  bool parse_common_op_desc(int blob_idx);
  bool parse_surface_desc(int blob_idx);
  bool parse_operation_desc(int blob_idx);

public:
  explicit Parser(nvdla::loadable::Loadable const * loadable);
};

#endif // NVDLA_DEPICTER_PROJECT_PARSER_H
