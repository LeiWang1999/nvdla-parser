add_executable(depicter_read_loadable)
set_target_properties(depicter_read_loadable PROPERTIES OUTPUT_NAME "depicter_read_loadable")
target_sources(depicter_read_loadable PRIVATE 0.loadable.read.cpp)

add_executable(depicter_read_version)
set_target_properties(depicter_read_version PROPERTIES OUTPUT_NAME "depicter_read_version")
target_link_libraries(depicter_read_version ${PROJECT_NAME})
target_sources(depicter_read_version PRIVATE 1.loadable.version.cpp)

add_executable(depicter_read_tasklist)
set_target_properties(depicter_read_tasklist PROPERTIES OUTPUT_NAME "depicter_read_tasklist")
target_link_libraries(depicter_read_tasklist ${PROJECT_NAME})
target_sources(depicter_read_tasklist PRIVATE 2.loadable.tasklist.cpp)
