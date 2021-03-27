cmake_minimum_required(VERSION 3.3.2)
project(nvdla_depicter)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "-o3")


add_executable(nvdla_depicter main.cpp external/loadable_generated.h external/flatbuffers/flatbuffers.h external/flatbuffers/base.h DLA_desc.h DLA_desc.cpp tools.h Interface.h EMU_desc.h driver.h external/flatbuffers/stl_emulation.h Graph_generator.h main.h Global_desc.h tools.cpp Interface.cpp Graph_generator.cpp EMU_desc.cpp Global_desc.cpp external/half.h driver.cpp)
