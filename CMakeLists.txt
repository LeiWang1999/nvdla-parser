cmake_minimum_required(VERSION 3.14)
project(nvdla_depicter)

# Enable C++ 11
set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR})

#add_executable(nvdla_depicter
#        external/flatbuffers/base.h
#        external/flatbuffers/flatbuffers.h
#        external/flatbuffers/stl_emulation.h
#        external/half.h
#        external/loadable_generated.h
#        DLA_desc.cpp
#        DLA_desc.h
#        driver.cpp
#        driver.h
#        EMU_desc.cpp
#        EMU_desc.h
#        Global_desc.cpp
#        Global_desc.h
#        Graph_generator.cpp
#        Graph_generator.h
#        Interface.cpp
#        Interface.h
#        main.cpp
#        main.h
#        README.md
#        tools.cpp
#        tools.h)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    option(BUILD_EXAMPLES   "whether or not examples should be built" ON)
    if(BUILD_EXAMPLES)
        add_subdirectory(examples)
    endif()
endif()