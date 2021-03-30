cmake_minimum_required(VERSION 3.14)
project(nvdla_depicter_demo)

# Enable C++ 11
set(CMAKE_CXX_STANDARD 11)

message("\n NVDLA Depicter\n")

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(
        ${PROJECT_SOURCE_DIR}/include
)

add_library(${PROJECT_NAME} SHARED
        src/DLA_desc.cpp
        src/driver.cpp
        src/EMU_desc.cpp
        src/Global_desc.cpp
        src/Graph_generator.cpp
        src/Interface.cpp
        src/tools.cpp
        )

add_executable(nvdla_depicter main.cpp)

target_link_libraries(nvdla_depicter ${PROJECT_NAME})

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    option(BUILD_EXAMPLES   "whether or not examples should be built" ON)
    if(BUILD_EXAMPLES)
        add_subdirectory(examples)
    endif()
endif()