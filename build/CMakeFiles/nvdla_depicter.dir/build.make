# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/Xilinx/SDK/2019.1/tps/lnx64/cmake-3.3.2/bin/cmake

# The command to remove a file.
RM = /opt/Xilinx/SDK/2019.1/tps/lnx64/cmake-3.3.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lei/nvdla_depicter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lei/nvdla_depicter/build

# Include any dependencies generated for this target.
include CMakeFiles/nvdla_depicter.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/nvdla_depicter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/nvdla_depicter.dir/flags.make

CMakeFiles/nvdla_depicter.dir/main.cpp.o: CMakeFiles/nvdla_depicter.dir/flags.make
CMakeFiles/nvdla_depicter.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lei/nvdla_depicter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/nvdla_depicter.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nvdla_depicter.dir/main.cpp.o -c /home/lei/nvdla_depicter/main.cpp

CMakeFiles/nvdla_depicter.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nvdla_depicter.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lei/nvdla_depicter/main.cpp > CMakeFiles/nvdla_depicter.dir/main.cpp.i

CMakeFiles/nvdla_depicter.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nvdla_depicter.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lei/nvdla_depicter/main.cpp -o CMakeFiles/nvdla_depicter.dir/main.cpp.s

CMakeFiles/nvdla_depicter.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/nvdla_depicter.dir/main.cpp.o.requires

CMakeFiles/nvdla_depicter.dir/main.cpp.o.provides: CMakeFiles/nvdla_depicter.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/nvdla_depicter.dir/build.make CMakeFiles/nvdla_depicter.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/nvdla_depicter.dir/main.cpp.o.provides

CMakeFiles/nvdla_depicter.dir/main.cpp.o.provides.build: CMakeFiles/nvdla_depicter.dir/main.cpp.o


CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.o: CMakeFiles/nvdla_depicter.dir/flags.make
CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.o: ../DLA_desc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lei/nvdla_depicter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.o -c /home/lei/nvdla_depicter/DLA_desc.cpp

CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lei/nvdla_depicter/DLA_desc.cpp > CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.i

CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lei/nvdla_depicter/DLA_desc.cpp -o CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.s

CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.o.requires:

.PHONY : CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.o.requires

CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.o.provides: CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.o.requires
	$(MAKE) -f CMakeFiles/nvdla_depicter.dir/build.make CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.o.provides.build
.PHONY : CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.o.provides

CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.o.provides.build: CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.o


CMakeFiles/nvdla_depicter.dir/tools.cpp.o: CMakeFiles/nvdla_depicter.dir/flags.make
CMakeFiles/nvdla_depicter.dir/tools.cpp.o: ../tools.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lei/nvdla_depicter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/nvdla_depicter.dir/tools.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nvdla_depicter.dir/tools.cpp.o -c /home/lei/nvdla_depicter/tools.cpp

CMakeFiles/nvdla_depicter.dir/tools.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nvdla_depicter.dir/tools.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lei/nvdla_depicter/tools.cpp > CMakeFiles/nvdla_depicter.dir/tools.cpp.i

CMakeFiles/nvdla_depicter.dir/tools.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nvdla_depicter.dir/tools.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lei/nvdla_depicter/tools.cpp -o CMakeFiles/nvdla_depicter.dir/tools.cpp.s

CMakeFiles/nvdla_depicter.dir/tools.cpp.o.requires:

.PHONY : CMakeFiles/nvdla_depicter.dir/tools.cpp.o.requires

CMakeFiles/nvdla_depicter.dir/tools.cpp.o.provides: CMakeFiles/nvdla_depicter.dir/tools.cpp.o.requires
	$(MAKE) -f CMakeFiles/nvdla_depicter.dir/build.make CMakeFiles/nvdla_depicter.dir/tools.cpp.o.provides.build
.PHONY : CMakeFiles/nvdla_depicter.dir/tools.cpp.o.provides

CMakeFiles/nvdla_depicter.dir/tools.cpp.o.provides.build: CMakeFiles/nvdla_depicter.dir/tools.cpp.o


CMakeFiles/nvdla_depicter.dir/Interface.cpp.o: CMakeFiles/nvdla_depicter.dir/flags.make
CMakeFiles/nvdla_depicter.dir/Interface.cpp.o: ../Interface.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lei/nvdla_depicter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/nvdla_depicter.dir/Interface.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nvdla_depicter.dir/Interface.cpp.o -c /home/lei/nvdla_depicter/Interface.cpp

CMakeFiles/nvdla_depicter.dir/Interface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nvdla_depicter.dir/Interface.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lei/nvdla_depicter/Interface.cpp > CMakeFiles/nvdla_depicter.dir/Interface.cpp.i

CMakeFiles/nvdla_depicter.dir/Interface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nvdla_depicter.dir/Interface.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lei/nvdla_depicter/Interface.cpp -o CMakeFiles/nvdla_depicter.dir/Interface.cpp.s

CMakeFiles/nvdla_depicter.dir/Interface.cpp.o.requires:

.PHONY : CMakeFiles/nvdla_depicter.dir/Interface.cpp.o.requires

CMakeFiles/nvdla_depicter.dir/Interface.cpp.o.provides: CMakeFiles/nvdla_depicter.dir/Interface.cpp.o.requires
	$(MAKE) -f CMakeFiles/nvdla_depicter.dir/build.make CMakeFiles/nvdla_depicter.dir/Interface.cpp.o.provides.build
.PHONY : CMakeFiles/nvdla_depicter.dir/Interface.cpp.o.provides

CMakeFiles/nvdla_depicter.dir/Interface.cpp.o.provides.build: CMakeFiles/nvdla_depicter.dir/Interface.cpp.o


CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.o: CMakeFiles/nvdla_depicter.dir/flags.make
CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.o: ../Graph_generator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lei/nvdla_depicter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.o -c /home/lei/nvdla_depicter/Graph_generator.cpp

CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lei/nvdla_depicter/Graph_generator.cpp > CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.i

CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lei/nvdla_depicter/Graph_generator.cpp -o CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.s

CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.o.requires:

.PHONY : CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.o.requires

CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.o.provides: CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.o.requires
	$(MAKE) -f CMakeFiles/nvdla_depicter.dir/build.make CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.o.provides.build
.PHONY : CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.o.provides

CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.o.provides.build: CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.o


CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.o: CMakeFiles/nvdla_depicter.dir/flags.make
CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.o: ../EMU_desc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lei/nvdla_depicter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.o -c /home/lei/nvdla_depicter/EMU_desc.cpp

CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lei/nvdla_depicter/EMU_desc.cpp > CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.i

CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lei/nvdla_depicter/EMU_desc.cpp -o CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.s

CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.o.requires:

.PHONY : CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.o.requires

CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.o.provides: CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.o.requires
	$(MAKE) -f CMakeFiles/nvdla_depicter.dir/build.make CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.o.provides.build
.PHONY : CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.o.provides

CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.o.provides.build: CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.o


CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.o: CMakeFiles/nvdla_depicter.dir/flags.make
CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.o: ../Global_desc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lei/nvdla_depicter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.o -c /home/lei/nvdla_depicter/Global_desc.cpp

CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lei/nvdla_depicter/Global_desc.cpp > CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.i

CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lei/nvdla_depicter/Global_desc.cpp -o CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.s

CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.o.requires:

.PHONY : CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.o.requires

CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.o.provides: CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.o.requires
	$(MAKE) -f CMakeFiles/nvdla_depicter.dir/build.make CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.o.provides.build
.PHONY : CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.o.provides

CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.o.provides.build: CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.o


CMakeFiles/nvdla_depicter.dir/driver.cpp.o: CMakeFiles/nvdla_depicter.dir/flags.make
CMakeFiles/nvdla_depicter.dir/driver.cpp.o: ../driver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lei/nvdla_depicter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/nvdla_depicter.dir/driver.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nvdla_depicter.dir/driver.cpp.o -c /home/lei/nvdla_depicter/driver.cpp

CMakeFiles/nvdla_depicter.dir/driver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nvdla_depicter.dir/driver.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lei/nvdla_depicter/driver.cpp > CMakeFiles/nvdla_depicter.dir/driver.cpp.i

CMakeFiles/nvdla_depicter.dir/driver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nvdla_depicter.dir/driver.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lei/nvdla_depicter/driver.cpp -o CMakeFiles/nvdla_depicter.dir/driver.cpp.s

CMakeFiles/nvdla_depicter.dir/driver.cpp.o.requires:

.PHONY : CMakeFiles/nvdla_depicter.dir/driver.cpp.o.requires

CMakeFiles/nvdla_depicter.dir/driver.cpp.o.provides: CMakeFiles/nvdla_depicter.dir/driver.cpp.o.requires
	$(MAKE) -f CMakeFiles/nvdla_depicter.dir/build.make CMakeFiles/nvdla_depicter.dir/driver.cpp.o.provides.build
.PHONY : CMakeFiles/nvdla_depicter.dir/driver.cpp.o.provides

CMakeFiles/nvdla_depicter.dir/driver.cpp.o.provides.build: CMakeFiles/nvdla_depicter.dir/driver.cpp.o


# Object files for target nvdla_depicter
nvdla_depicter_OBJECTS = \
"CMakeFiles/nvdla_depicter.dir/main.cpp.o" \
"CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.o" \
"CMakeFiles/nvdla_depicter.dir/tools.cpp.o" \
"CMakeFiles/nvdla_depicter.dir/Interface.cpp.o" \
"CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.o" \
"CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.o" \
"CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.o" \
"CMakeFiles/nvdla_depicter.dir/driver.cpp.o"

# External object files for target nvdla_depicter
nvdla_depicter_EXTERNAL_OBJECTS =

nvdla_depicter: CMakeFiles/nvdla_depicter.dir/main.cpp.o
nvdla_depicter: CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.o
nvdla_depicter: CMakeFiles/nvdla_depicter.dir/tools.cpp.o
nvdla_depicter: CMakeFiles/nvdla_depicter.dir/Interface.cpp.o
nvdla_depicter: CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.o
nvdla_depicter: CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.o
nvdla_depicter: CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.o
nvdla_depicter: CMakeFiles/nvdla_depicter.dir/driver.cpp.o
nvdla_depicter: CMakeFiles/nvdla_depicter.dir/build.make
nvdla_depicter: CMakeFiles/nvdla_depicter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lei/nvdla_depicter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable nvdla_depicter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nvdla_depicter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/nvdla_depicter.dir/build: nvdla_depicter

.PHONY : CMakeFiles/nvdla_depicter.dir/build

CMakeFiles/nvdla_depicter.dir/requires: CMakeFiles/nvdla_depicter.dir/main.cpp.o.requires
CMakeFiles/nvdla_depicter.dir/requires: CMakeFiles/nvdla_depicter.dir/DLA_desc.cpp.o.requires
CMakeFiles/nvdla_depicter.dir/requires: CMakeFiles/nvdla_depicter.dir/tools.cpp.o.requires
CMakeFiles/nvdla_depicter.dir/requires: CMakeFiles/nvdla_depicter.dir/Interface.cpp.o.requires
CMakeFiles/nvdla_depicter.dir/requires: CMakeFiles/nvdla_depicter.dir/Graph_generator.cpp.o.requires
CMakeFiles/nvdla_depicter.dir/requires: CMakeFiles/nvdla_depicter.dir/EMU_desc.cpp.o.requires
CMakeFiles/nvdla_depicter.dir/requires: CMakeFiles/nvdla_depicter.dir/Global_desc.cpp.o.requires
CMakeFiles/nvdla_depicter.dir/requires: CMakeFiles/nvdla_depicter.dir/driver.cpp.o.requires

.PHONY : CMakeFiles/nvdla_depicter.dir/requires

CMakeFiles/nvdla_depicter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/nvdla_depicter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/nvdla_depicter.dir/clean

CMakeFiles/nvdla_depicter.dir/depend:
	cd /home/lei/nvdla_depicter/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lei/nvdla_depicter /home/lei/nvdla_depicter /home/lei/nvdla_depicter/build /home/lei/nvdla_depicter/build /home/lei/nvdla_depicter/build/CMakeFiles/nvdla_depicter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/nvdla_depicter.dir/depend

