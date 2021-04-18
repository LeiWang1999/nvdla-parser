add_executable(parser_read_loadable)
set_target_properties(parser_read_loadable PROPERTIES OUTPUT_NAME "parser_read_loadable")
target_sources(parser_read_loadable PRIVATE 0.loadable.read.cpp)

add_executable(parser_read_version)
set_target_properties(parser_read_version PROPERTIES OUTPUT_NAME "parser_read_version")
target_link_libraries(parser_read_version ${PROJECT_NAME})
target_sources(parser_read_version PRIVATE 1.loadable.version.cpp)

add_executable(parser_read_task_list)
set_target_properties(parser_read_task_list PROPERTIES OUTPUT_NAME "parser_read_task_list")
target_link_libraries(parser_read_task_list ${PROJECT_NAME})
target_sources(parser_read_task_list PRIVATE 2.loadable.task_list.cpp)

add_executable(parser_read_memory_list)
set_target_properties(parser_read_memory_list PROPERTIES OUTPUT_NAME "parser_read_memory_list")
target_link_libraries(parser_read_memory_list ${PROJECT_NAME})
target_sources(parser_read_memory_list PRIVATE 3.loadable.memory_list.cpp)

add_executable(parser_read_address_list)
set_target_properties(parser_read_address_list PROPERTIES OUTPUT_NAME "parser_read_address_list")
target_link_libraries(parser_read_address_list ${PROJECT_NAME})
target_sources(parser_read_address_list PRIVATE 4.loadable.address_list.cpp)

add_executable(parser_read_event_list)
set_target_properties(parser_read_event_list PROPERTIES OUTPUT_NAME "parser_read_event_list")
target_link_libraries(parser_read_event_list ${PROJECT_NAME})
target_sources(parser_read_event_list PRIVATE 5.loadable.event_list.cpp)


add_executable(parser_read_blobs)
set_target_properties(parser_read_blobs PROPERTIES OUTPUT_NAME "parser_read_blobs")
target_link_libraries(parser_read_blobs ${PROJECT_NAME})
target_sources(parser_read_blobs PRIVATE 6.loadable.blobs.cpp)

add_executable(parser_read_tensor_desc_list)
set_target_properties(parser_read_tensor_desc_list PROPERTIES OUTPUT_NAME "parser_read_tensor_desc_list")
target_link_libraries(parser_read_tensor_desc_list ${PROJECT_NAME})
target_sources(parser_read_tensor_desc_list PRIVATE 7.loadable.tensor_desc_list.cpp)

add_executable(parser_read_reloc_list)
set_target_properties(parser_read_reloc_list PROPERTIES OUTPUT_NAME "parser_read_reloc_list")
target_link_libraries(parser_read_reloc_list ${PROJECT_NAME})
target_sources(parser_read_reloc_list PRIVATE 8.loadable.reloc_list.cpp)


add_executable(parser_read_submit_list)
set_target_properties(parser_read_submit_list PROPERTIES OUTPUT_NAME "parser_read_submit_list")
target_link_libraries(parser_read_submit_list ${PROJECT_NAME})
target_sources(parser_read_submit_list PRIVATE 9.loadable.submit_list.cpp)

add_executable(parser_read_network_desc)
set_target_properties(parser_read_network_desc PROPERTIES OUTPUT_NAME "parser_read_network_desc")
target_link_libraries(parser_read_network_desc ${PROJECT_NAME})
target_sources(parser_read_network_desc PRIVATE 10.read.network_desc.cpp)

add_executable(parser_read_surface_desc)
set_target_properties(parser_read_surface_desc PROPERTIES OUTPUT_NAME "parser_read_surface_desc")
target_link_libraries(parser_read_surface_desc ${PROJECT_NAME})
target_sources(parser_read_surface_desc PRIVATE 11.read.surface_desc.cpp)
