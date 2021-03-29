cmake_minimum_required(VERSION 3.14)
project(nvdla_depicter)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(external)
include_directories(external/flatbuffers)

add_executable(nvdla_depicter
        external/flatbuffers/base.h
        external/flatbuffers/flatbuffers.h
        external/flatbuffers/stl_emulation.h
        external/half.h
        external/loadable_generated.h
        DLA_desc.cpp
        DLA_desc.h
        driver.cpp
        driver.h
        EMU_desc.cpp
        EMU_desc.h
        Global_desc.cpp
        Global_desc.h
        Graph_generator.cpp
        Graph_generator.h
        Interface.cpp
        Interface.h
        main.cpp
        main.h
        README.md
        tools.cpp
        tools.h)
