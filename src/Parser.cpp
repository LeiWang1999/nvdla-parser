//
// Created by 王磊 on 2021/4/1.
//

#include "Parser.h"

Parser::Parser(nvdla::loadable::Loadable const *loadable)
    :address_list(loadable)
    ,memory_list(loadable)
    ,loadable(loadable) {
  for(auto task_idx = 0; task_idx < loadable->task_list()->size() ; ++task_idx) {
    auto TaskListEntry = loadable->task_list()->Get(task_idx);
    if (TaskListEntry->interface() == nvdla::loadable::Interface_DLA1){
      for (const auto ad_idx : *TaskListEntry->address_list()){
        if(get_name(ad_idx).find("addr") != std::string::npos){
          // find network_desc blob_idx
          auto network_desc_blob_idx
              = find_blobs_index_from_task(task_idx, 0);
          if(!parse_network_desc(network_desc_blob_idx))
            return;
          auto common_op_desc_blob_idx = find_blobs_index_from_task(task_idx, network_desc->dependency_graph_index);
          if(!parse_common_op_desc(common_op_desc_blob_idx))
            return;
          auto surface_desc_blob_idx = find_blobs_index_from_task(task_idx, network_desc->surface_desc_index);
          if(!parse_surface_desc(surface_desc_blob_idx))
            return;
          auto operation_desc_blob_idx = find_blobs_index_from_task(task_idx, network_desc->operation_desc_index);
          if(!parse_operation_desc(operation_desc_blob_idx))
            return;

        }
      }

    }
  }
}

std::string Parser::get_name(int address_idx) {

  auto memory_key = address_list.index_dict.at(address_idx);

  return memory_list.alias_dict.at(memory_key);
}

int Parser::get_blob_index(const std::string & str) {
  auto blobs = loadable->blobs();
  for(int i = 0;i<blobs->size();i++)
  {
    auto entry = blobs->Get(i);
    if (!strcmp(str.c_str(),entry->name()->c_str()))
      return i;
  }
  return -1;
}

int Parser::find_address_blobs_index(int address_idx) {
    return get_blob_index(get_name(address_idx));
}


int Parser::find_blobs_index_from_task(int task_idx, int address_idx) {
  return find_address_blobs_index(
      loadable->task_list()->Get(task_idx)->address_list()->Get(address_idx)
      );
}

bool Parser::parse_network_desc(int blob_idx) {

  network_desc = (struct dla_network_desc *)get_blob_data_pointer(blob_idx);

  return true;
}
bool Parser::parse_common_op_desc(int blob_idx) {
  common_op_desc = (struct dla_common_op_desc *)get_blob_data_pointer(blob_idx);
  return true;
}

const unsigned char * Parser::get_blob_data_pointer(int blob_idx) {
  return loadable->blobs()->Get(static_cast<flatbuffers::uoffset_t>(blob_idx))->data()->data();
}

bool Parser::parse_surface_desc(int blob_idx) {
  surface_desc =  (union dla_surface_container *)get_blob_data_pointer(blob_idx);
  return true;
}
bool Parser::parse_operation_desc(int blob_idx) {
  operation_desc = (union dla_operation_container *)get_blob_data_pointer(blob_idx);
  return true;
}